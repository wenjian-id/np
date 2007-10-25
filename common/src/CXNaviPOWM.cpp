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

#include "CXNaviPOWM.hpp"
#include "CXGPSRecvThread.hpp"
#include "CXLocatorThread.hpp"
#include "CXMapThread.hpp"
#include "CXInfoBarBottom.hpp"
#include "CXInfoBarTop.hpp"
#include "CXMutexLocker.hpp"
#include "IMainWindow.hpp"
#include "CXOptions.hpp"

#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"

const char * VERSIONSTRING ="NaviPOWM 0.1.0";

//-------------------------------------
CXNaviPOWM::CXNaviPOWM() :
	m_pMainWindow(NULL),
	m_pGPSRecvThread(NULL),
	m_pLocatorThread(NULL),
	m_pMapThread(NULL),
	m_pInfoBarBottom(NULL),
	m_pInfoBarTop(NULL),
	m_iWidth(0),
	m_iHeight(0),
	m_InfoBarTopPos(0,0,1,1),
	m_InfoBarBottomPos(0,0,1,1),
	m_oShowInfo(false)
{
}

//-------------------------------------
CXNaviPOWM::~CXNaviPOWM() {
	// clean up
	delete 	m_pGPSRecvThread;
	m_pGPSRecvThread = NULL;
	delete m_pLocatorThread;
	m_pLocatorThread = NULL;
	delete m_pMapThread;
	m_pMapThread = NULL;
	delete m_pInfoBarBottom;
	m_pInfoBarBottom =  NULL;
	delete m_pInfoBarTop;
	m_pInfoBarTop =  NULL;
}

//-------------------------------------
int CXNaviPOWM::GetWidth() const {
	CXMutexLocker L(&m_Mutex);
	return m_iWidth;
}

//-------------------------------------
void CXNaviPOWM::SetWidth(int Width) {
	CXMutexLocker L(&m_Mutex);
	m_iWidth = Width;
}

//-------------------------------------
int CXNaviPOWM::GetHeight() const {
	CXMutexLocker L(&m_Mutex);
	return m_iHeight;
}

//-------------------------------------
void CXNaviPOWM::SetHeight(int Height) {
	CXMutexLocker L(&m_Mutex);
	m_iHeight = Height;
}

//-------------------------------------
bool CXNaviPOWM::Init(IMainWindow *pMainWindow) {
	m_pMainWindow = pMainWindow;
	m_pInfoBarBottom = new CXInfoBarBottom();
	m_pInfoBarTop = new CXInfoBarTop();
	if(m_pGPSRecvThread != NULL)
		return false;
	if(m_pLocatorThread != NULL)
		return false;
	if(m_pMapThread != NULL)
		return false;
	// create new threads
	m_pGPSRecvThread = new CXGPSRecvThread();
	m_pLocatorThread = new CXLocatorThread();
	m_pMapThread = new CXMapThread();
	// create connections between threads
	m_pGPSRecvThread->SetLocator(m_pLocatorThread);
	m_pLocatorThread->SetNaviPOWM(this);
	m_pMapThread->SetNaviPOWM(this);
	return true;
}

//-------------------------------------
bool CXNaviPOWM::StartThreads() {
	if(m_pGPSRecvThread == NULL)
		return false;
	if(m_pLocatorThread == NULL)
		return false;
	if(m_pMapThread == NULL)
		return false;
	// create and run thread s
	m_pGPSRecvThread->CreateThread();
	m_pLocatorThread->CreateThread();
	m_pMapThread->CreateThread();
	return true;
}

//-------------------------------------
void CXNaviPOWM::StopThreads() {
	if(m_pGPSRecvThread == NULL)
		return;
	if(m_pLocatorThread == NULL)
		return;
	if(m_pMapThread == NULL)
		return;
	// stop threads
	m_pGPSRecvThread->StopThread();
	m_pLocatorThread->StopThread();
	m_pMapThread->StopThread();
	// wait for thread exit
	m_pGPSRecvThread->WaitForThreadExit(5000);
	m_pLocatorThread->WaitForThreadExit(5000);
	m_pMapThread->WaitForThreadExit(5000);
}

//-------------------------------------
void CXNaviPOWM::RequestRepaint() {
	if(m_pMainWindow != NULL)
		m_pMainWindow->RequestRepaint();
}

//-------------------------------------
void CXNaviPOWM::Paint(CXDeviceContext *pDC) {
	if(pDC == NULL)
		return;
	if(m_pMapThread == NULL)
		return;
	if(m_pInfoBarBottom == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	
	m_pMapThread->Paint(pDC, 0, m_InfoBarTopPos.GetBottom());
	m_pInfoBarBottom->Paint(pDC, m_InfoBarBottomPos.GetLeft(), m_InfoBarBottomPos.GetTop());
	m_pInfoBarTop->Paint(pDC, m_InfoBarTopPos.GetLeft(), m_InfoBarTopPos.GetTop());
	if(m_oShowInfo) {
		// show info
		CXBitmap Bmp;
		tIRect rect(0, 0, GetWidth(), GetHeight() - m_InfoBarTopPos.GetHeight()  - m_InfoBarBottomPos.GetHeight());
		Bmp.Create(pDC, rect.GetWidth(), rect.GetHeight());
		Bmp.DrawRect(rect, CXRGB(0,0,0), CXRGB(0,0,0));
		Bmp.DrawTextASCII(VERSIONSTRING, rect, CXRGB(0xff, 0xff, 0x00), CXRGB(0,0,0));
		pDC->Draw(&Bmp, 0, m_InfoBarTopPos.GetBottom());
	}
}

//-------------------------------------
void CXNaviPOWM::Resize(int Width, int Height) {
	if(m_pMapThread == NULL)
		return;
	if(m_pInfoBarBottom == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	SetWidth(Width);
	SetHeight(Height);
	int IBBH = CXOptions::Instance()->GetInfoBarBottomHeight();
	int IBTH = CXOptions::Instance()->GetInfoBarTopHeight();
	m_InfoBarTopPos.SetLeft(0);
	m_InfoBarTopPos.SetTop(0);
	m_InfoBarTopPos.SetRight(Width);
	m_InfoBarTopPos.SetBottom(IBTH);
	
	m_InfoBarBottomPos.SetLeft(0);
	m_InfoBarBottomPos.SetTop(Height - IBBH);
	m_InfoBarBottomPos.SetRight(Width);
	m_InfoBarBottomPos.SetBottom(Height);

	m_pMapThread->Resize(Width, Height - IBBH - IBTH);
	m_pInfoBarBottom->Resize(Width, IBBH);
	m_pInfoBarTop->Resize(Width, IBTH);
	RequestRepaint();
}

//-------------------------------------
void CXNaviPOWM::PositionChanged(const CXNaviData & NewData) {
	if(m_pMapThread == NULL)
		return;
	if(m_pInfoBarBottom == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	m_pInfoBarTop->PositionChanged(NewData);
	m_pInfoBarBottom->PositionChanged(NewData);
	m_pMapThread->PositionChanged(NewData);
}

//-------------------------------------
void CXNaviPOWM::OnChar(int /*TheChar*/) {
}

//-------------------------------------
void CXNaviPOWM::OnKeyDown(int TheChar) {
	if(m_pMapThread == NULL)
		return;
	if(TheChar == NP_LEFT)
		m_pMapThread->ZoomOut();
	else if(TheChar == NP_RIGHT)
		m_pMapThread->ZoomIn();
}

//-------------------------------------
void CXNaviPOWM::OnKeyUp(int /*TheChar*/) {
}

//-------------------------------------
void CXNaviPOWM::OnMouseDown(int X, int Y) {
	if(m_pMainWindow == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	if(!m_InfoBarTopPos.Contains(X, Y)) {
		// turn off showing info when clicking outside InfoBarTop
		m_oShowInfo = false;
		RequestRepaint();
		return;
	}
	// turn off showing info
	// get command
	E_COMMAND Cmd = m_pInfoBarTop->OnMouseDown(X - m_InfoBarTopPos.GetLeft(), Y - m_InfoBarTopPos.GetTop());
	// turn off showing info when clicking outside info button
	if(m_oShowInfo && (Cmd != e_Info))
		m_oShowInfo = false;
	switch(Cmd) {
		case e_Quit:	m_pMainWindow->RequestTermination(); break;
		case e_Info:	m_oShowInfo = !m_oShowInfo; RequestRepaint(); break;
		case e_Save:	CXOptions::Instance()->ToggleSaving(); RequestRepaint(); break;
		default:		break;
	}
}
