/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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

#include "CXMapThread.hpp"
#include "CXMutexLocker.hpp"
#include "CXMapPainter2D.hpp"
#include "CXMapPainterTest.hpp"
#include "CXNaviPOWM.hpp"

//-------------------------------------
CXMapThread::CXMapThread() :
	m_pMapPainter(NULL),
	m_pNaviPOWM(NULL)
{
	m_pMapPainter = new CXMapPainter2D();
//	m_pMapPainter = new CXMapPainterTest();
}

//-------------------------------------
CXMapThread::~CXMapThread() {
	delete m_pMapPainter;
	m_pMapPainter = NULL;
}

//-------------------------------------
void CXMapThread::SetNaviPOWM(CXNaviPOWM *pNaviPOWM) {
	CXMutexLocker L(&m_Mutex);
	m_pNaviPOWM = pNaviPOWM;
}


//-------------------------------------
void CXMapThread::PositionChanged(const CXNaviData &NewNaviData) {
	if(m_pMapPainter != NULL)
		m_pMapPainter->PositionChanged(NewNaviData);
	RequestWork();
}

//-------------------------------------
void CXMapThread::ZoomIn() {
	if(m_pMapPainter == NULL)
		return;
	if(m_pMapPainter->ZoomIn())
		RequestWork();
}

//-------------------------------------
void CXMapThread::ZoomOut() {
	if(m_pMapPainter == NULL)
		return;
	if(m_pMapPainter->ZoomOut())
		RequestWork();
}

//-------------------------------------
void CXMapThread::Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	if(m_pMapPainter != NULL)
		m_pMapPainter->Paint(pDC, OffsetX, OffsetY);
}

//-------------------------------------
void CXMapThread::Resize(int Width, int Height) {
	if(m_pMapPainter != NULL)
		m_pMapPainter->Resize(Width, Height);
	RequestWork();
}

//-------------------------------------
void CXMapThread::OnThreadStarted() {
	// nothing to do
}

//-------------------------------------
void CXMapThread::OnThreadStopped() {
	// nothing to do
}

//-------------------------------------
void CXMapThread::OnWorkFunc() {
	if(m_pMapPainter == NULL)
		return;
	// do work
	m_pMapPainter->DoWork();
	// check if paint needed
	if(m_pMapPainter->MustRepaint() && (m_pNaviPOWM != NULL)) {
		m_pNaviPOWM->RequestRepaint();
	}
}

