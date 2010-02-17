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

#include "CXInfoBarSpeed.hpp"
#include "CXDeviceContext.hpp"
#include "CXOptions.hpp"
#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"

#include "CXPen.hpp"

#include <math.h>

//-------------------------------------
CXInfoBarSpeed::CXInfoBarSpeed() :
	m_TextRect1(0,0,1,1),
	m_TextRect2(0,0,1,1),
	m_TextRect3(0,0,1,1),
	m_FontSize1(20),
	m_FontSize2(20),
	m_FontSize3(20)
{
}

//-------------------------------------
CXInfoBarSpeed::~CXInfoBarSpeed() {
}

//-------------------------------------
void CXInfoBarSpeed::PositionChanged(const CXNaviData & NewData) {
	m_NaviData = NewData;
}

//-------------------------------------
void CXInfoBarSpeed::CreateBitmaps(CXDeviceContext *pDC) {
	int Width = GetWidth();
	int Height = GetHeight();
	// create bitmap
	m_CircleBmp.Create(pDC, Width, Height);

	// get client rect
	tIRect ClientRect(0,0,Width,Height);

	// draw backgound
	m_CircleBmp.DrawRect(ClientRect, COLOR_TRANSPARENT, COLOR_TRANSPARENT);

	double R = 1.0*Min(Width/2, Height/2);
	m_CircleBmp.DrawCircle(Width/2, Height/2, static_cast<int>(floor(R)), CXRGB(0xA0, 0xA0, 0xA0), CXRGB(0xFF, 0xFF, 0xFF));
	m_CircleBmp.DrawCircle(Width/2, Height/2, static_cast<int>(floor(0.90*R)), CXRGB(0xFF, 0x00, 0x00), CXRGB(0xFF, 0x00, 0x00));
	double WhiteRadius = 0.70*R;
	m_CircleBmp.DrawCircle(Width/2, Height/2, static_cast<int>(floor(WhiteRadius)), CXRGB(0xFF, 0xFF, 0xFF), CXRGB(0xFF, 0xFF, 0xFF));

	// calc text size
	CalcFonts("9", WhiteRadius, m_TextRect1, m_FontSize1);
	// position speed
	m_TextRect1.OffsetRect((ClientRect.GetWidth() - m_TextRect1.GetWidth())/2, (ClientRect.GetHeight() - m_TextRect1.GetHeight())/2);
	// calc text size
	CalcFonts("99", WhiteRadius, m_TextRect2, m_FontSize2);
	// position speed
	m_TextRect2.OffsetRect((ClientRect.GetWidth() - m_TextRect2.GetWidth())/2, (ClientRect.GetHeight() - m_TextRect2.GetHeight())/2);
	// calc text size
	CalcFonts("999", WhiteRadius, m_TextRect3, m_FontSize3);
	// position speed
	m_TextRect3.OffsetRect((ClientRect.GetWidth() - m_TextRect3.GetWidth())/2, (ClientRect.GetHeight() - m_TextRect3.GetHeight())/2);

}

//-------------------------------------
void CXInfoBarSpeed::CalcFonts(const CXStringASCII &SpeedStr, double WhiteRadius, tIRect & rRect, int & rFontSize) {
	// fit text to white circle
	double Radius = 1.5*WhiteRadius;
	rFontSize = static_cast<int>(floor(Radius));
	for(;;) {
		m_CircleBmp.SetFont(static_cast<int>(floor(rFontSize)), true);
		rRect = m_CircleBmp.CalcTextRectASCII(SpeedStr, 2, 2);
		if(rRect.GetWidth()*rRect.GetWidth() + rRect.GetHeight()*rRect.GetHeight() > 4*WhiteRadius*WhiteRadius) {
			// does not fit
			rFontSize--;
		} else {
			break;
		}
		if(rFontSize <= 5)
			break;
	}
}


//-------------------------------------
void CXInfoBarSpeed::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	int Width = GetWidth();
	int Height = GetHeight();
	if(SizeChanged()) {
		CreateBitmaps(pDC);
	}
	if(!CXOptions::Instance()->MustShowLogo() && (m_NaviData.GetMaxSpeed() != 0) && !CXOptions::Instance()->IsMapMovingManually()) {
		// draw data
		CXBitmap Bmp;
		Bmp.Create(pDC, Width, Height);
		Bmp.Draw(&m_CircleBmp, 0, 0);
		int MaxSpeed = static_cast<int>(m_NaviData.GetMaxSpeed());
		char buf[10];
		sprintf(buf, "%d", MaxSpeed);
		if(MaxSpeed < 10) {
			Bmp.SetFont(m_FontSize1, true);
			Bmp.DrawTextASCII(buf, m_TextRect1, CXRGB(0x00, 0x00, 0x00));
		} else if(MaxSpeed < 100) {
			Bmp.SetFont(m_FontSize2, true);
			Bmp.DrawTextASCII(buf, m_TextRect2, CXRGB(0x00, 0x00, 0x00));
		} else {
			Bmp.SetFont(m_FontSize3, true);
			Bmp.DrawTextASCII(buf, m_TextRect3, CXRGB(0x00, 0x00, 0x00));
		}
		pDC->DrawTransparent(&Bmp, OffsetX, OffsetY, COLOR_TRANSPARENT);
	}
}
