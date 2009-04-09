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

#include "CXInfoBarTop.hpp"
#include "CXPen.hpp"
#include "CXDeviceContext.hpp"
#include "CXStringUTF8.hpp"
#include "CXExactTime.hpp"
#include "CXSatelliteData.hpp"
#include "CXOptions.hpp"

//-------------------------------------
CXInfoBarTop::CXInfoBarTop() :
	m_InfoRect(0,0,1,1),
	m_QuitRect(0,0,1,1),
	m_SatRect(0,0,1,1),
	m_ZoomRect(0,0,1,1),
	m_MoveRect(0,0,1,1),
	m_SaveRect(0,0,1,1),
	m_TimeRect(0,0,1,1),
	m_MinimizeRect(0,0,1,1)
{
}

//-------------------------------------
CXInfoBarTop::~CXInfoBarTop() {
}

//-------------------------------------
void CXInfoBarTop::PositionChanged(const CXNaviData & NewData) {
	m_NaviData = NewData;
}

//-------------------------------------
void CXInfoBarTop::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	CXBitmap Bmp;
	int Width = GetWidth();
	int Height = GetHeight();

	// create bitmap
	Bmp.Create(pDC, Width, Height);
	CXRGB BgColor(0x00, 0x00, 0x00);

	// set new font size
	Bmp.SetFont(Height-2, false);

	// get client rect
	tIRect ClientRect(0,0,Width,Height);

	// draw backgound
	Bmp.DrawRect(ClientRect, BgColor, BgColor);

	// check if size changed
	if(SizeChanged()) {
		m_InfoRect.SetRight(Height);
		m_InfoRect.SetBottom(Height);
		m_QuitRect.SetRight(Width);
		m_QuitRect.SetBottom(Height);
		m_QuitRect.SetLeft(Width - Height);
		m_MinimizeRect.SetRight(m_QuitRect.GetLeft() - 1);
		m_MinimizeRect.SetLeft(m_MinimizeRect.GetRight() - Height);
		m_MinimizeRect.SetBottom(Height);
		// calc width of SatRect
		m_SatRect = Bmp.CalcTextRectASCII("XX", 4, 0);
		m_SatRect.OffsetRect(Height, 0);
		m_SatRect.SetBottom(Height);
		// zoom rect
		m_ZoomRect.SetLeft(m_SatRect.GetRight() + 1);
		m_ZoomRect.SetBottom(Height);
		m_ZoomRect.SetRight(m_ZoomRect.GetLeft() + 2*Height);
		// move rect
		m_MoveRect.SetLeft(m_ZoomRect.GetRight() + 1);
		m_MoveRect.SetBottom(Height);
		m_MoveRect.SetRight(m_MoveRect.GetLeft() + Height);
		// time rect
		m_TimeRect = Bmp.CalcTextRectASCII("99:99", 4, 0);
		if(CXOptions::Instance()->MustShowMinimizeButton()) {
			// ends on minimize button
			m_TimeRect.OffsetRect(-m_TimeRect.GetRight() + m_MinimizeRect.GetLeft(), 0);
		} else {
			// ends on quit button
			m_TimeRect.OffsetRect(-m_TimeRect.GetRight() + m_QuitRect.GetLeft(), 0);
		}
		m_TimeRect.SetBottom(Height);
		// save rect
		m_SaveRect.SetRight(m_TimeRect.GetLeft()-1);
		m_SaveRect.SetLeft(m_SaveRect.GetRight() - Height);
		m_SaveRect.SetBottom(Height);

		// create new info bmp
		m_InfoBmp.Create(pDC, m_InfoRect.GetWidth(), m_InfoRect.GetHeight());
		m_InfoBmp.LoadFromFile(CXOptions::Instance()->GetInfoFileName());
		// create new quit bmp
		m_QuitBmp.Create(pDC, m_QuitRect.GetWidth(), m_QuitRect.GetHeight());
		m_QuitBmp.LoadFromFile(CXOptions::Instance()->GetQuitFileName());
		// create new minimize bmp
		m_MinimizeBmp.Create(pDC, m_MinimizeRect.GetWidth(), m_MinimizeRect.GetHeight());
		m_MinimizeBmp.LoadFromFile(CXOptions::Instance()->GetMinimizeFileName());
		// create new save bmps
		m_SaveOnBmp.Create(pDC, m_SaveRect.GetWidth(), m_SaveRect.GetHeight());
		m_SaveOnBmp.LoadFromFile(CXOptions::Instance()->GetSaveOnFileName());
		m_SaveOffBmp.Create(pDC, m_SaveRect.GetWidth(), m_SaveRect.GetHeight());
		m_SaveOffBmp.LoadFromFile(CXOptions::Instance()->GetSaveOffFileName());
		// create new move bmp
		m_MoveBmp.Create(pDC, m_MoveRect.GetWidth(), m_MoveRect.GetHeight());
		m_MoveBmp.LoadFromFile(CXOptions::Instance()->GetMoveFileName());
		// create new move bmp
		m_CurrentPosBmp.Create(pDC, m_MoveRect.GetWidth(), m_MoveRect.GetHeight());
		m_CurrentPosBmp.LoadFromFile(CXOptions::Instance()->GetCurrentPosFileName());
	}

	if(!CXOptions::Instance()->MustShowLogo()) {

		char buf[10];
		// draw satellite count
		int NSat = CXSatelliteData::Instance()->GetNrSat();
		snprintf(buf, 10, "%d", NSat);
		CXStringASCII StrNSat(buf);
		// compute color
		CXRGB NSatColor;
		if(NSat <= 5) {
			NSatColor = CXRGB(0xff, 0x80, 0x80);
		} else if(NSat <= 8) {
			NSatColor = CXRGB(0xff, 0xff, 0x00);
		} else {
			NSatColor = CXRGB(0x00, 0xff, 0x00);
		}
		Bmp.DrawTextASCII(StrNSat, m_SatRect, NSatColor, BgColor);

		// draw zoom level
		int RectWidth = m_ZoomRect.GetWidth();
		int dx = (RectWidth - (e_ZoomLevel_Count-1)) / e_ZoomLevel_Count;
		int BarWidth = Max(0, dx-1);
		int LeftOffset = (RectWidth - (e_ZoomLevel_Count*dx+(e_ZoomLevel_Count-1)))/2;
		// start with rightmost bar
		int StartOffset = LeftOffset + (e_ZoomLevel_Count-1)*dx;
		int BorderY = 2;
		int MaxBarHeight = Height - BorderY;
		tIRect r(m_ZoomRect.GetLeft() + StartOffset, 0, BarWidth, MaxBarHeight);
		int ZoomLevel = CXOptions::Instance()->GetZoomLevel();
		CXRGB BarOnColor(0x00, 0xFF, 0x00);
		CXRGB BarOffColor(0x00, 0x7F, 0x00);
		CXRGB AutomaticColor(0xFF, 0xFF, 0x00);
		for(int i=0; i<e_ZoomLevel_Count; i++) {
			int BarHeight = (e_ZoomLevel_Count-i)*(MaxBarHeight/e_ZoomLevel_Count);
			r.SetTop(r.GetBottom() - BarHeight);
			if(i >= ZoomLevel) {
				Bmp.DrawRect(r, BarOnColor, BarOnColor);
			} else {
				Bmp.DrawRect(r, BarOffColor, BarOffColor);
			}
			r.OffsetRect(-dx, 0);
		}
		if(CXOptions::Instance()->AutomaticZoom()) {
			// draw an "A"
			Bmp.SetPen(CXPen(CXPen::e_Solid, 1, AutomaticColor));
			Bmp.DrawLine(m_ZoomRect.GetLeft(), Height/2, m_ZoomRect.GetLeft(), BorderY);
			Bmp.DrawLine(m_ZoomRect.GetLeft(), BorderY, m_ZoomRect.GetLeft() + dx , BorderY);
			Bmp.DrawLine(m_ZoomRect.GetLeft() + dx, Height/2, m_ZoomRect.GetLeft() + dx, BorderY);
			Bmp.DrawLine(m_ZoomRect.GetLeft() + dx , BorderY, m_ZoomRect.GetLeft(), BorderY);
			Bmp.DrawLine(m_ZoomRect.GetLeft(), BorderY + (Height/2-BorderY)/2, m_ZoomRect.GetLeft() + dx, BorderY + (Height/2-BorderY)/2);
		}


		// get current time
		CXExactTime Now;
		snprintf(buf, 10, "%02d:%02d", Now.GetHour(), Now.GetMinute());
		CXStringASCII StrNow(buf);

		// draw time
		Bmp.DrawTextASCII(StrNow, m_TimeRect, CXRGB(0xff, 0xff, 0x00), BgColor);
	}

	// draw
	pDC->Draw(&Bmp, OffsetX, OffsetY);

	if(!CXOptions::Instance()->MustShowLogo()) {
		// draw info bmp
		pDC->Draw(&m_InfoBmp, m_InfoRect.GetLeft(), m_InfoRect.GetTop());
		// draw quit bmp
		pDC->Draw(&m_QuitBmp, m_QuitRect.GetLeft(), m_QuitRect.GetTop());
		// draw minimize bmp
		if(CXOptions::Instance()->MustShowMinimizeButton()) {
			pDC->Draw(&m_MinimizeBmp, m_MinimizeRect.GetLeft(), m_MinimizeRect.GetTop());
		}
		// draw save bmp
		if(CXOptions::Instance()->IsSaving())
			pDC->Draw(&m_SaveOnBmp, m_SaveRect.GetLeft(), m_SaveRect.GetTop());
		else
			pDC->Draw(&m_SaveOffBmp, m_SaveRect.GetLeft(), m_SaveRect.GetTop());
		if(CXOptions::Instance()->IsMapMovingManually()) {
			// draw move bitmap
			pDC->Draw(&m_MoveBmp, m_MoveRect.GetLeft(), m_MoveRect.GetTop());
		} else {
			// draw position bitmap
			pDC->Draw(&m_CurrentPosBmp, m_MoveRect.GetLeft(), m_MoveRect.GetTop());
		}
	}
}

//-------------------------------------
E_COMMAND CXInfoBarTop::OnInternalMouseDown(int X, int Y) {
	if(m_InfoRect.Contains(X, Y))
		return e_CmdInfo;
	if(m_SatRect.Contains(X, Y))
		return e_CmdSat;
	if(m_QuitRect.Contains(X, Y))
		return e_CmdQuit;
	if(m_ZoomRect.Contains(X, Y))
		return e_CmdAutoZoom;
	if(m_MoveRect.Contains(X, Y))
		return e_CmdMapMoveManually;
	if(CXOptions::Instance()->MustShowMinimizeButton()) {
		if(m_MinimizeRect.Contains(X, Y))
			return e_CmdMinimize;
	}
	if(m_SaveRect.Contains(X, Y))
		return e_CmdSave;
	return e_CmdNone;
}

