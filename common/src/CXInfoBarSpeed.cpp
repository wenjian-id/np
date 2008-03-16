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

#include "CXInfoBarSpeed.hpp"
#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"
#include "CXOptions.hpp"
#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"

#include "CXPen.hpp"

#include <math.h>

//-------------------------------------
CXInfoBarSpeed::CXInfoBarSpeed() {
}

//-------------------------------------
CXInfoBarSpeed::~CXInfoBarSpeed() {
}

//-------------------------------------
void CXInfoBarSpeed::PositionChanged(const CXNaviData & NewData) {
	m_NaviData = NewData;
}

//-------------------------------------
void CXInfoBarSpeed::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	int Width = GetWidth();
	int Height = GetHeight();

	if(!CXOptions::Instance()->MustShowLogo() && (m_NaviData.GetMaxSpeed() != 0)) {

		// create bitmap
		CXBitmap Bmp;
		Bmp.Create(pDC, Width, Height);

		// get client rect
		tIRect ClientRect(0,0,Width,Height);

		// draw backgound
		Bmp.DrawRect(ClientRect, COLOR_TRANSPARENT, COLOR_TRANSPARENT);

		double R = 1.0*Min(Width/2, Height/2);
		Bmp.DrawCircle(Width/2, Height/2, static_cast<int>(floor(R)), CXRGB(0xA0, 0xA0, 0xA0), CXRGB(0xFF, 0xFF, 0xFF));
		Bmp.DrawCircle(Width/2, Height/2, static_cast<int>(floor(0.90*R)), CXRGB(0xFF, 0x00, 0x00), CXRGB(0xFF, 0x00, 0x00));
		double WhiteRadius = 0.70*R;
		Bmp.DrawCircle(Width/2, Height/2, static_cast<int>(floor(WhiteRadius)), CXRGB(0xFF, 0xFF, 0xFF), CXRGB(0xFF, 0xFF, 0xFF));
		
		// draw text
		char buf[10];
		sprintf(buf, "%d", static_cast<int>(m_NaviData.GetMaxSpeed()));

		// fit text to white circle
		double Radius = 1.5*WhiteRadius;
		int FontSize = static_cast<int>(floor(Radius));
		for(;;) {
			Bmp.SetFont(static_cast<int>(floor(FontSize)), true);
			tIRect Rect = Bmp.CalcTextRectASCII(buf, 2, 2);
			if(Rect.GetWidth()*Rect.GetWidth() + Rect.GetHeight()*Rect.GetHeight() > 4*WhiteRadius*WhiteRadius) {
				// does not fit
				FontSize--;
			} else {
				break;
			}
			if(FontSize <= 5)
				break;
		}

		Bmp.DrawTextASCII(buf, ClientRect, CXRGB(0x00, 0x00, 0x00));
	
		// draw data
		pDC->DrawTransparent(&Bmp, OffsetX, OffsetY, COLOR_TRANSPARENT);
	}
}
