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
	m_TextRect(0,0,1,1),
	m_FontSize(20)
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
	char buf[10];
	sprintf(buf, "%d", 999);

	// fit text to white circle
	double Radius = 1.5*WhiteRadius;
	m_FontSize = static_cast<int>(floor(Radius));
	for(;;) {
		m_CircleBmp.SetFont(static_cast<int>(floor(m_FontSize)), true);
		m_TextRect = m_CircleBmp.CalcTextRectASCII(buf, 2, 2);
		if(m_TextRect.GetWidth()*m_TextRect.GetWidth() + m_TextRect.GetHeight()*m_TextRect.GetHeight() > 4*WhiteRadius*WhiteRadius) {
			// does not fit
			m_FontSize--;
		} else {
			break;
		}
		if(m_FontSize <= 5)
			break;
	}
	// position speed
	m_TextRect.OffsetRect((ClientRect.GetWidth() - m_TextRect.GetWidth())/2, (ClientRect.GetHeight() - m_TextRect.GetHeight())/2);

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
		Bmp.SetFont(m_FontSize, true);
		char buf[10];
		sprintf(buf, "%d", static_cast<int>(m_NaviData.GetMaxSpeed()));
		Bmp.DrawTextASCII(buf, m_TextRect, CXRGB(0x00, 0x00, 0x00));
		pDC->DrawTransparent(&Bmp, OffsetX, OffsetY, COLOR_TRANSPARENT);
	}
}
