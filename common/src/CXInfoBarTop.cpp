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

#include "CXInfoBarTop.hpp"
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
	m_SaveRect(0,0,1,1),
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
		m_SaveRect.SetLeft(m_SatRect.GetRight()+1);
		m_SaveRect.SetRight(m_SaveRect.GetLeft() + Height);
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
			NSatColor = CXRGB(0xff, 0x00, 0x00);
		} else if(NSat <= 8) {
			NSatColor = CXRGB(0xff, 0xff, 0x00);
		} else {
			NSatColor = CXRGB(0x00, 0xff, 0x00);
		}
		Bmp.DrawTextASCII(StrNSat, m_SatRect, NSatColor, BgColor);

		// get current time
		CXExactTime Now;
		snprintf(buf, 10, "%02d:%02d", Now.GetHour(), Now.GetMinute());
		CXStringASCII StrNow(buf);

		// draw time
		tIRect TimeRect = Bmp.CalcTextRectASCII(StrNow, 4, 0);
		if(CXOptions::Instance()->MustShowMinimizeButton()) {
			// ends on minimize button
			TimeRect.OffsetRect(-TimeRect.GetRight() + m_MinimizeRect.GetLeft(), 0);
		} else {
			// ends on quit button
			TimeRect.OffsetRect(-TimeRect.GetRight() + m_QuitRect.GetLeft(), 0);
		}
		TimeRect.SetBottom(Height);
		Bmp.DrawTextASCII(StrNow, TimeRect, CXRGB(0xff, 0xff, 0x00), BgColor);
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
	if(CXOptions::Instance()->MustShowMinimizeButton()) {
		if(m_MinimizeRect.Contains(X, Y))
			return e_CmdMinimize;
	}
	if(m_SaveRect.Contains(X, Y))
		return e_CmdSave;
	return e_CmdNone;
}

