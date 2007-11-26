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

#include "CXInfoBarCommon.hpp"
#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"
#include "CXOptions.hpp"
#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"

#include <math.h>

static const CXRGB BGCOLOR(0x00, 0x00, 0x00);

//-------------------------------------
CXInfoBarCommon::CXInfoBarCommon() {
}

//-------------------------------------
CXInfoBarCommon::~CXInfoBarCommon() {
}

//-------------------------------------
void CXInfoBarCommon::PositionChanged(const CXNaviData & NewData) {
	m_NaviData = NewData;
}

//-------------------------------------
void CXInfoBarCommon::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	int Width = GetWidth();
	int Height = GetHeight();

	if(!CXOptions::Instance()->ShowLogo()) {

		// create bitmap
		CXBitmap Bmp;
		Bmp.Create(pDC, Width, Height);

		// get client rect
		tIRect ClientRect1(0,0,Width,Height);

		// draw backgound
		Bmp.DrawRect(ClientRect1, BGCOLOR, BGCOLOR);

		// set new font size
		int FontHeight = Height - 2;
		Bmp.SetFontHeight(FontHeight);
		tIRect Rect(0,0,0,0);
		do {
			Rect = Bmp.CalcTextRectASCII("999 kmh", 4, 0);
			if(Rect.GetWidth() >= Width) {
				FontHeight--;
				Bmp.SetFontHeight(FontHeight);
			}

		} while((Rect.GetWidth() >= Width) && (FontHeight > 2));

		CXUTMSpeed UTMSpeed = m_NaviData.GetUTMSpeed();
		int Speed = static_cast<int>(floor(3.6*UTMSpeed.GetSpeed()));
		// draw ref
		char buf[50];
		sprintf(buf, "%d kmh", Speed);
		Bmp.DrawTextASCII(buf, tIRect(0,0,Width, Height), CXRGB(0xFF, 0xFF, 0x00), BGCOLOR);

		// draw data
		pDC->Blend(&Bmp, OffsetX, OffsetY, 70);
	}
}
