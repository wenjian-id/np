/***************************************************************************
 *   Copyright (C) by Doru Julian Bugariu                                  *
 *   bugariu@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation                                              *
 *   51 Franklin Street, Fifth Floor                                       *
 *   Boston, MA 02110-1301, USA                                            *
 *   http://www.fsf.org/about/contact.html                                 *
 ***************************************************************************/

#include "CXMapPainterThread.hpp"
#include "CXWriteLocker.hpp"
#include "CXReadLocker.hpp"
#include "CXMapPainter2D.hpp"
#include "CXMapPainterTest.hpp"
#include "CXNaviPOWM.hpp"

//-------------------------------------
CXMapPainterThread::CXMapPainterThread() :
	m_pMapPainter(NULL),
	m_pNaviPOWM(NULL),
	m_oIgnoreRepaintRequests(false),
	m_oIgnoreRepaintRequestsChanged(false)
{
	m_pMapPainter = new CXMapPainter2D();
//	m_pMapPainter = new CXMapPainterTest();
}

//-------------------------------------
CXMapPainterThread::~CXMapPainterThread() {
	delete m_pMapPainter;
	m_pMapPainter = NULL;
}

//-------------------------------------
void CXMapPainterThread::SetNaviPOWM(CXNaviPOWM *pNaviPOWM) {
	CXWriteLocker WL(&m_RWLock);
	m_pNaviPOWM = pNaviPOWM;
}


//-------------------------------------
void CXMapPainterThread::PositionChanged(const CXNaviData &NewNaviData) {
	if(m_pMapPainter != NULL)
		m_pMapPainter->PositionChanged(NewNaviData);
	RequestWork();
}

//-------------------------------------
void CXMapPainterThread::ZoomIn() {
	if(m_pMapPainter == NULL)
		return;
	if(m_pMapPainter->ZoomIn())
		RequestWork();
}

//-------------------------------------
void CXMapPainterThread::ZoomOut() {
	if(m_pMapPainter == NULL)
		return;
	if(m_pMapPainter->ZoomOut())
		RequestWork();
}

//-------------------------------------
void CXMapPainterThread::RequestRepaint() {
	if(m_pMapPainter == NULL)
		return;
	m_pMapPainter->SetMustRepaint(true);
}

//-------------------------------------
void CXMapPainterThread::RedrawMap() {
	if(m_pMapPainter == NULL)
		return;
	RequestWork();
}

//-------------------------------------
void CXMapPainterThread::Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	if(m_pMapPainter != NULL)
		m_pMapPainter->Paint(pDC, OffsetX, OffsetY);
}

//-------------------------------------
void CXMapPainterThread::Resize(int Width, int Height) {
	if(m_pMapPainter != NULL)
		m_pMapPainter->Resize(Width, Height);
	RequestWork();
}

//-------------------------------------
bool CXMapPainterThread::MustIgnoreRepaints() const {
	CXReadLocker RL(&m_RWLock);
	return m_oIgnoreRepaintRequests;
}

//-------------------------------------
void CXMapPainterThread::SetMustIgnoreRepaints(bool Value) {
	CXWriteLocker WL(&m_RWLock);
	if(m_oIgnoreRepaintRequests != Value)
		m_oIgnoreRepaintRequestsChanged = true;
	m_oIgnoreRepaintRequests = Value;
}

//-------------------------------------
bool CXMapPainterThread::MustIgnoreRepaintsChanged() const {
	CXReadLocker RL(&m_RWLock);
	return m_oIgnoreRepaintRequestsChanged;
}

//-------------------------------------
void CXMapPainterThread::ResetMustIgnoreRepaintsChanged() {
	CXWriteLocker WL(&m_RWLock);
	m_oIgnoreRepaintRequestsChanged = false;
}

//-------------------------------------
void CXMapPainterThread::OnThreadStarted() {
	// nothing to do
}

//-------------------------------------
void CXMapPainterThread::OnThreadStopped() {
	// nothing to do
}

//-------------------------------------
void CXMapPainterThread::OnWorkFunc() {
	if(m_pMapPainter == NULL)
		return;
	if(m_pNaviPOWM == NULL)
		return;
	// check if we must do some work
	if(!MustIgnoreRepaints()) {
		// do work
		m_pMapPainter->DoWork();
		// check if paint allowed.
		if(m_pMapPainter->MustRepaint()) {
			// if MustIgnoreRepaintsChanged returns true here,
			// the time spent moving the map was shorter than drawing the map,
			// so we ignore it to avoid flickering around
			if(!MustIgnoreRepaintsChanged()) {
				m_pNaviPOWM->RequestRepaint(CXNaviPOWM::e_ModeMap);
			}
		}
		ResetMustIgnoreRepaintsChanged();
	}
}

