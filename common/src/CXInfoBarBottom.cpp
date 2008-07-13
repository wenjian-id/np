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

#include "CXInfoBarBottom.hpp"
#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"
#include "CXOptions.hpp"
#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"


//-------------------------------------
CXInfoBarBottom::CXInfoBarBottom() {
}

//-------------------------------------
CXInfoBarBottom::~CXInfoBarBottom() {
}

//-------------------------------------
void CXInfoBarBottom::PositionChanged(const CXNaviData & NewData) {
	m_NaviData = NewData;
}

//-------------------------------------
void CXInfoBarBottom::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	CXBitmap Bmp;
	int Width = GetWidth();
	int Height = GetHeight();

	// create bitmap
	Bmp.Create(pDC, Width, Height);
	CXRGB BgColor(0x00, 0x00, 0x00);

	// set new font size
	Bmp.SetFont(Height -2, false);

	// get client rect
	tIRect ClientRect(0,0,Width,Height);

	// draw backgound
	Bmp.DrawRect(ClientRect, BgColor, BgColor);
	if(!CXOptions::Instance()->MustShowLogo()) {
		CXStringUTF8 Name = m_NaviData.GetStreetName();
		CXStringUTF8 Ref = m_NaviData.GetRef();
		// draw ref
		tIRect RefRect = Bmp.CalcTextRectUTF8(Ref, 4, 0);
		RefRect.OffsetRect(Width -RefRect.GetWidth(), 0);
		Bmp.DrawTextUTF8(Ref, RefRect, CXRGB(0xff, 0xff, 0x00), BgColor);
		// draw name
		tIRect NameRect = Bmp.CalcTextRectUTF8(Name, 0, 0);
		// check if name fits if displayed centered
		if(NameRect.GetWidth()/2 <= (Width/2 - RefRect.GetWidth())) {
			// display centered on screen
			NameRect = tIRect(RefRect.GetWidth(), 0, RefRect.GetLeft() - RefRect.GetWidth(), Height);
		} else {
			// does not fit centered. Display it centered in remaining slot
			NameRect = tIRect(0, 0, RefRect.GetLeft(), Height);
		}
		Bmp.DrawTextUTF8(Name, NameRect, CXRGB(0xff, 0xff, 0xff), BgColor);
	}

	// draw data
	pDC->Draw(&Bmp, OffsetX, OffsetY);
}
