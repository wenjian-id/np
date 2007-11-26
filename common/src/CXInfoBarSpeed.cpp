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

#include <math.h>

static const CXRGB BGCOLOR(0xE2, 0xDE, 0xD8);

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

	if(!CXOptions::Instance()->ShowLogo()) {

		// create bitmap
		CXBitmap Bmp;
		Bmp.Create(pDC, Width, Height);

		// get client rect
		tIRect ClientRect(0,0,Width,Height);

		// draw backgound
		Bmp.DrawRect(ClientRect, BGCOLOR, BGCOLOR);

		// draw data
		pDC->Draw(&Bmp, OffsetX, OffsetY);
	}
}
