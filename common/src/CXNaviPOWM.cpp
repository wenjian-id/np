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

#include "CXNaviPOWM.hpp"
#include "CXGPSRecvThread.hpp"
#include "CXLocatorThread.hpp"
#include "CXMapPainterThread.hpp"
#include "CXWatchdogThread.hpp"
#include "CXInfoBarBottom.hpp"
#include "CXInfoBarTop.hpp"
#include "CXInfoBarSpeed.hpp"
#include "CXInfoBarCommon.hpp"
#include "CXSatelliteData.hpp"
#include "CXMutexLocker.hpp"
#include "IMainWindow.hpp"
#include "CXOptions.hpp"
#include "CXDeviceContext.hpp"
#include "Utils.hpp"

const char * VERSIONSTRING ="NaviPOWM 0.2.0-dev1";
const char * INFOSTRING1 ="(C) Doru Julian Bugariu";
const char * INFOSTRING2 ="http://sourceforge.net/projects/navipowm";


//-------------------------------------
CXZoomBtn::CXZoomBtn(E_COMMAND eCommand) :
	m_eCommand(eCommand)
{
}

//-------------------------------------
CXZoomBtn::~CXZoomBtn() {
}

//-------------------------------------
E_COMMAND CXZoomBtn::OnInternalMouseDown(int X, int Y) {
	if((X >= 0) && (X <= GetWidth()) && (Y >= 0) && (Y <= GetHeight()))
		return m_eCommand;
	return e_CmdNone;
}

//-------------------------------------
void CXZoomBtn::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	if(SizeChanged()) {
		m_Bmp.Create(pDC, GetWidth(), GetHeight());
		if(m_eCommand == e_CmdZoomIn)
			m_Bmp.LoadFromFile(CXOptions::Instance()->GetZoomInFileName());
		else
			m_Bmp.LoadFromFile(CXOptions::Instance()->GetZoomOutFileName());
	}
	if(!CXOptions::Instance()->MustShowLogo()) {
		pDC->DrawTransparent(&m_Bmp, OffsetX, OffsetY, COLOR_TRANSPARENT);
	}
}

//-------------------------------------
CXNaviPOWM::CXNaviPOWM() :
	m_eDisplayMode(e_ModeMap),
	m_pMainWindow(NULL),
	m_pGPSRecvThread(NULL),
	m_pLocatorThread(NULL),
	m_pMapPainterThread(NULL),
	m_pWatchdogThread(NULL),
	m_pInfoBarBottom(NULL),
	m_pInfoBarTop(NULL),
	m_pInfoBarSpeed(NULL),
	m_pInfoBarCommon(NULL),
	m_iWidth(0),
	m_iHeight(0),
	m_InfoBarTopPos(0,0,1,1),
	m_InfoBarBottomPos(0,0,1,1),
	m_InfoBarSpeedPos(0,0,1,1),
	m_InfoBarCommonPos(0,0,1,1),
	m_ZoomInPos(0,0,1,1),
	m_ZoomOutPos(0,0,1,1),
	m_ZoomInBtn(e_CmdZoomIn),
	m_ZoomOutBtn(e_CmdZoomOut)
{
}

//-------------------------------------
CXNaviPOWM::~CXNaviPOWM() {
	// clean up
	delete 	m_pGPSRecvThread;
	m_pGPSRecvThread = NULL;
	delete m_pLocatorThread;
	m_pLocatorThread = NULL;
	delete m_pMapPainterThread;
	m_pMapPainterThread = NULL;
	delete m_pWatchdogThread;
	m_pWatchdogThread = NULL;
	delete m_pInfoBarBottom;
	m_pInfoBarBottom =  NULL;
	delete m_pInfoBarTop;
	m_pInfoBarTop =  NULL;
	delete m_pInfoBarSpeed;
	m_pInfoBarSpeed = NULL;
	delete m_pInfoBarCommon;
	m_pInfoBarCommon = NULL;
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
void CXNaviPOWM::SetDisplayMode(E_DISPLAY_MODE eDisplayMode) {
	CXMutexLocker L(&m_Mutex);
	m_eDisplayMode = eDisplayMode;
}

//-------------------------------------
CXNaviPOWM::E_DISPLAY_MODE CXNaviPOWM::GetDisplayMode() const {
	CXMutexLocker L(&m_Mutex);
	return m_eDisplayMode;
}

//-------------------------------------
bool CXNaviPOWM::Init(IMainWindow *pMainWindow) {
	m_pMainWindow = pMainWindow;
	m_pInfoBarBottom = new CXInfoBarBottom();
	m_pInfoBarTop = new CXInfoBarTop();
	m_pInfoBarSpeed = new CXInfoBarSpeed();
	m_pInfoBarCommon = new CXInfoBarCommon();
	if(m_pGPSRecvThread != NULL)
		return false;
	if(m_pLocatorThread != NULL)
		return false;
	if(m_pMapPainterThread != NULL)
		return false;
	if(m_pWatchdogThread != NULL)
		return false;
	// create new threads
	m_pGPSRecvThread = new CXGPSRecvThread();
	m_pLocatorThread = new CXLocatorThread();
	m_pMapPainterThread = new CXMapPainterThread();
	m_pWatchdogThread = new CXWatchdogThread();
	// create connections between threads
	m_pGPSRecvThread->SetLocator(m_pLocatorThread);
	m_pLocatorThread->SetNaviPOWM(this);
	m_pMapPainterThread->SetNaviPOWM(this);
	return true;
}

//-------------------------------------
bool CXNaviPOWM::StartThreads() {
	if(m_pGPSRecvThread == NULL)
		return false;
	if(m_pLocatorThread == NULL)
		return false;
	if(m_pMapPainterThread == NULL)
		return false;
	if(m_pWatchdogThread == NULL)
		return false;
	// create and run thread s
	m_pGPSRecvThread->CreateThread();
	m_pLocatorThread->CreateThread();
	m_pMapPainterThread->CreateThread();
	m_pWatchdogThread->CreateThread();
	return true;
}

//-------------------------------------
void CXNaviPOWM::StopThreads() {
	if(m_pGPSRecvThread == NULL)
		return;
	if(m_pLocatorThread == NULL)
		return;
	if(m_pMapPainterThread == NULL)
		return;
	if(m_pWatchdogThread == NULL)
		return;
	// stop threads
	m_pGPSRecvThread->StopThread();
	m_pLocatorThread->StopThread();
	m_pMapPainterThread->StopThread();
	m_pWatchdogThread->StopThread();
	// wait for thread exit
	m_pGPSRecvThread->WaitForThreadExit(5000);
	m_pLocatorThread->WaitForThreadExit(5000);
	m_pMapPainterThread->WaitForThreadExit(5000);
	m_pWatchdogThread->WaitForThreadExit(5000);
}

//-------------------------------------
void CXNaviPOWM::DoRequestRepaint() {
	if(m_pMainWindow != NULL)
		m_pMainWindow->RequestRepaint();
}

//-------------------------------------
void CXNaviPOWM::RequestRepaint(E_DISPLAY_MODE eDisplayMode) {
	if(GetDisplayMode() == eDisplayMode)
		DoRequestRepaint();
}

//-------------------------------------
void CXNaviPOWM::Paint(CXDeviceContext *pDC) {
	if(pDC == NULL)
		return;
	if(m_pMapPainterThread == NULL)
		return;
	if(m_pInfoBarBottom == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	if(m_pInfoBarSpeed == NULL)
		return;
	if(m_pInfoBarCommon == NULL)
		return;

	// get display mode
	E_DISPLAY_MODE eDisplayMode = GetDisplayMode();
	if(eDisplayMode == e_ModeMap) {
		// paint map
		m_pMapPainterThread->Paint(pDC, 0, m_InfoBarTopPos.GetBottom());
	} else if (eDisplayMode == e_ModeSatInfo) {
		CXSatelliteData::Instance()->Paint(	pDC, 0, m_InfoBarTopPos.GetBottom(),
											GetWidth(), GetHeight() - m_InfoBarTopPos.GetHeight()  - m_InfoBarBottomPos.GetHeight());
	}
	m_pInfoBarBottom->Paint(pDC, m_InfoBarBottomPos.GetLeft(), m_InfoBarBottomPos.GetTop());
	m_pInfoBarTop->Paint(pDC, m_InfoBarTopPos.GetLeft(), m_InfoBarTopPos.GetTop());
	if(eDisplayMode == e_ModeMap) {
		if(CXOptions::Instance()->MustShowMaxSpeed()) {
			m_pInfoBarSpeed->Paint(pDC, m_InfoBarSpeedPos.GetLeft(), m_InfoBarSpeedPos.GetTop());
		}
		m_pInfoBarCommon->Paint(pDC, m_InfoBarCommonPos.GetLeft(), m_InfoBarCommonPos.GetTop());
		// paint zoom buttons
		if(CXOptions::Instance()->MustShowZoomButtons()) {
			m_ZoomInBtn.Paint(pDC, m_ZoomInPos.GetLeft(), m_ZoomInPos.GetTop());
			m_ZoomOutBtn.Paint(pDC, m_ZoomOutPos.GetLeft(), m_ZoomOutPos.GetTop());
		}
	}
	
	if(eDisplayMode == e_ModeInfo) {
		// show info
		CXBitmap Bmp;
		tIRect rect(0, 0, GetWidth(), GetHeight() - m_InfoBarTopPos.GetHeight()  - m_InfoBarBottomPos.GetHeight());
		Bmp.Create(pDC, rect.GetWidth(), rect.GetHeight());
		Bmp.DrawRect(rect, CXRGB(0,0,0), CXRGB(0,0,0));
		tIRect R1 = Bmp.CalcTextRectASCII(VERSIONSTRING, 2, 2);
		tIRect R2 = Bmp.CalcTextRectASCII(INFOSTRING1, 2, 2);
		tIRect R3 = Bmp.CalcTextRectASCII(INFOSTRING2, 2, 2);
		int Height = R1.GetHeight() + R2.GetHeight() + R3.GetHeight();
		int Width = Max(R1.GetWidth(), Max(R2.GetWidth(), R3.GetWidth()));
		int x0 = (rect.GetWidth() - Width)/2;
		int y0 = (rect.GetHeight() - Height)/2;
		int y1 = y0 + R1.GetHeight();
		R1.SetLeft(x0); R1.SetRight(x0+Width); R1.SetTop(y0); R1.SetBottom(y1);
		Bmp.DrawTextASCII(VERSIONSTRING, R1, CXRGB(0xff, 0xff, 0x00), CXRGB(0,0,0));
		y0 = y1; y1 = y0 + R2.GetHeight();
		R2.SetLeft(x0); R2.SetRight(x0+Width); R2.SetTop(y0); R2.SetBottom(y1);
		Bmp.DrawTextASCII(INFOSTRING1, R2, CXRGB(0xff, 0xff, 0x00), CXRGB(0,0,0));
		y0 = y1; y1 = y0 + R3.GetHeight();
		R3.SetLeft(x0); R3.SetRight(x0+Width); R3.SetTop(y0); R3.SetBottom(y1);
		Bmp.DrawTextASCII(INFOSTRING2, R3, CXRGB(0xff, 0xff, 0x00), CXRGB(0,0,0));
		pDC->Draw(&Bmp, 0, m_InfoBarTopPos.GetBottom());
	}
}

//-------------------------------------
void CXNaviPOWM::Resize(int Width, int Height) {
	if(m_pMapPainterThread == NULL)
		return;
	if(m_pInfoBarBottom == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	if(m_pInfoBarSpeed == NULL)
		return;
	if(m_pInfoBarCommon == NULL)
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

	const int ZoomSize = 40;
	m_ZoomInPos.SetBottom(m_InfoBarBottomPos.GetTop());
	m_ZoomInPos.SetTop(m_ZoomInPos.GetBottom() - ZoomSize);
	m_ZoomInPos.SetRight(Width);
	m_ZoomInPos.SetLeft(m_ZoomInPos.GetRight() - ZoomSize);

	m_ZoomOutPos.SetBottom(m_InfoBarBottomPos.GetTop());
	m_ZoomOutPos.SetTop(m_ZoomOutPos.GetBottom() - ZoomSize);
	m_ZoomOutPos.SetLeft(0);
	m_ZoomOutPos.SetRight(ZoomSize);

	m_pMapPainterThread->Resize(Width, Height - IBBH - IBTH);
	m_pInfoBarBottom->Resize(Width, IBBH);
	m_pInfoBarTop->Resize(Width, IBTH);
	m_ZoomInBtn.Resize(ZoomSize, ZoomSize);
	m_ZoomOutBtn.Resize(ZoomSize, ZoomSize);

	int InfoBarCommonWidth = 65;
	int MaxSpeedSize = CXOptions::Instance()->GetMaxSpeedSize();
	m_InfoBarSpeedPos.SetTop(IBTH);
	m_InfoBarSpeedPos.SetLeft(Width-InfoBarCommonWidth-MaxSpeedSize);
	m_InfoBarSpeedPos.SetRight(Width-InfoBarCommonWidth);
	m_InfoBarSpeedPos.SetBottom(IBTH+MaxSpeedSize);
	m_pInfoBarSpeed->Resize(m_InfoBarSpeedPos.GetWidth(), m_InfoBarSpeedPos.GetHeight());

	m_InfoBarCommonPos.SetTop(IBTH);
	m_InfoBarCommonPos.SetLeft(Width-InfoBarCommonWidth);
	m_InfoBarCommonPos.SetRight(Width);
	m_InfoBarCommonPos.SetBottom(IBTH+4*20);
	m_pInfoBarCommon->Resize(m_InfoBarCommonPos.GetWidth(), m_InfoBarCommonPos.GetHeight());
	DoRequestRepaint();
}

//-------------------------------------
void CXNaviPOWM::PositionChanged(const CXNaviData & NewData) {
	if(m_pMapPainterThread == NULL)
		return;
	if(m_pInfoBarBottom == NULL)
		return;
	if(m_pInfoBarTop == NULL)
		return;
	if(m_pInfoBarSpeed == NULL)
		return;
	if(m_pInfoBarCommon == NULL)
		return;
	m_pInfoBarTop->PositionChanged(NewData);
	m_pInfoBarBottom->PositionChanged(NewData);
	m_pMapPainterThread->PositionChanged(NewData);
	m_pInfoBarSpeed->PositionChanged(NewData);
	m_pInfoBarCommon->PositionChanged(NewData);
}

//-------------------------------------
void CXNaviPOWM::OnChar(int /*TheChar*/) {
}

//-------------------------------------
void CXNaviPOWM::OnKeyDown(int TheChar) {
	if(m_pMapPainterThread == NULL)
		return;
	if(TheChar == NP_LEFT)
		m_pMapPainterThread->ZoomOut();
	else if(TheChar == NP_RIGHT)
		m_pMapPainterThread->ZoomIn();
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
	// get display mode
	E_DISPLAY_MODE eDisplayMode = GetDisplayMode();
	if((eDisplayMode == e_ModeInfo) && !m_InfoBarTopPos.Contains(X, Y)) {
		// turn off showing info when clicking outside InfoBarTop
		SetDisplayMode(e_ModeMap);
		DoRequestRepaint();
		return;
	}
	if((eDisplayMode == e_ModeSatInfo) && !m_InfoBarTopPos.Contains(X, Y)) {
		// turn off showing info when clicking outside InfoBarTop
		SetDisplayMode(e_ModeMap);
		DoRequestRepaint();
		return;
	}
	// get command
	E_COMMAND Cmd = e_CmdNone;
	// check Info bar buttons
	Cmd = m_pInfoBarTop->OnMouseDown(X - m_InfoBarTopPos.GetLeft(), Y - m_InfoBarTopPos.GetTop());
	// check for zoom buttons
	if((eDisplayMode == e_ModeMap) && (CXOptions::Instance()->MustShowZoomButtons()) && (Cmd == e_CmdNone)) {
		Cmd = m_ZoomInBtn.OnMouseDown(X - m_ZoomInPos.GetLeft(), Y - m_ZoomInPos.GetTop());
		if(Cmd == e_CmdNone)
			Cmd = m_ZoomOutBtn.OnMouseDown(X - m_ZoomOutPos.GetLeft(), Y - m_ZoomOutPos.GetTop());
	}
	// turn off showing info when clicking outside info button
	if((eDisplayMode == e_ModeInfo) && (Cmd != e_CmdInfo))
		SetDisplayMode(e_ModeMap);
	// turn off showing info when clicking outside sat button
	if((eDisplayMode == e_ModeSatInfo) && (Cmd != e_CmdSat))
		SetDisplayMode(e_ModeMap);
	eDisplayMode = GetDisplayMode();
	switch(Cmd) {
		case e_CmdQuit:		m_pLocatorThread->SaveLastReceivedGPSCoordinate(); m_pMainWindow->RequestTermination(); break;
		case e_CmdMinimize:	m_pMainWindow->ShowMinimized(); break;
		case e_CmdInfo:		{
								if(eDisplayMode == e_ModeInfo)
									// switch back top map mode
									SetDisplayMode(e_ModeMap);
								else
									// switch to info mode
									SetDisplayMode(e_ModeInfo);
								DoRequestRepaint();
								break;
							}
		case e_CmdSat:		{
								if(eDisplayMode == e_ModeSatInfo)
									// switch back top map mode
									SetDisplayMode(e_ModeMap);
								else
									// switch to Sat mode
									SetDisplayMode(e_ModeSatInfo);
								DoRequestRepaint();
								break;
							}
		case e_CmdSave:		CXOptions::Instance()->ToggleSaving(); DoRequestRepaint(); break;
		case e_CmdZoomIn:	{
								if(m_pMapPainterThread != NULL)
									m_pMapPainterThread->ZoomIn();
								break;
							}
		case e_CmdZoomOut:	{
								if(m_pMapPainterThread != NULL)
									m_pMapPainterThread->ZoomOut();
								break;
							}
		default:			break;
	}
}
