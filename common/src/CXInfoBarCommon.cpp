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
#include "CXStringUTF8.hpp"

#include <math.h>

static const CXRGB BGCOLOR(0x00, 0x00, 0x00);
static const CXRGB FGCOLOR(0xff, 0xff, 0x00);

unsigned char DegUTF8[2] = {0xC2, 0xB0};

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
int CXInfoBarCommon::SetFontHeight(CXBitmap &Bmp, const CXStringUTF8 &Str, tIRect &rRect) {
	int Height = rRect.GetHeight();
	int Width = rRect.GetWidth();
	int FontHeight = Height;
	Bmp.SetFont(FontHeight, false);
	do {
		rRect = Bmp.CalcTextRectUTF8(Str, 2, 2);
		if(rRect.GetWidth() >= Width) {
			FontHeight--;
			Bmp.SetFont(FontHeight, false);
		}
	} while((rRect.GetWidth() >= Width) && (FontHeight > 2));
	return FontHeight;
}

//-------------------------------------
void CXInfoBarCommon::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	int Width = GetWidth();
	int CompleteHeight = GetHeight();
	int Height = CompleteHeight/4;

	if(!CXOptions::Instance()->MustShowLogo()) {

		// create bitmap
		CXBitmap Bmp;
		Bmp.Create(pDC, Width, CompleteHeight);

		// get client rect
		tIRect ClientRect1(0,0,Width,CompleteHeight);

		// draw backgound
		Bmp.DrawRect(ClientRect1, BGCOLOR, BGCOLOR);

		char buf[50];
		CXStringUTF8 Str;

		// draw lon
		tIRect LonRect(0, 0, Width, Height);
		Str = "-180.99999";
		Str.Append(DegUTF8, 2);
		SetFontHeight(Bmp, Str, LonRect);
		sprintf(buf, "%0.5f", m_NaviData.GetLon());
		Str = buf;
		Str.Append(DegUTF8, 2);
		LonRect = Bmp.CalcTextRectUTF8(Str, 4, 0);
		LonRect.OffsetRect(Width - LonRect.GetRight(), 0*Height-LonRect.GetTop());
		Bmp.DrawTextUTF8(Str, LonRect, FGCOLOR, BGCOLOR);

		// draw lat
		tIRect LatRect(0, 0, Width, Height);
		sprintf(buf, "%0.5f", m_NaviData.GetLat());
		Str = buf;
		Str.Append(DegUTF8, 2);
		LatRect = Bmp.CalcTextRectUTF8(Str, 4, 0);
		LatRect.OffsetRect(Width - LatRect.GetRight(), 1*Height-LatRect.GetTop());
		Bmp.DrawTextUTF8(Str, LatRect, FGCOLOR, BGCOLOR);

		// draw height
		tIRect HeightRect(0, 0, Width, Height);
		sprintf(buf, "%0.0f m", m_NaviData.GetHeight());
		HeightRect = Bmp.CalcTextRectUTF8(buf, 4, 0);
		HeightRect.OffsetRect(Width - HeightRect.GetRight(), 2*Height-HeightRect.GetTop());
		Bmp.DrawTextUTF8(buf, HeightRect, FGCOLOR, BGCOLOR);

		// draw speed
		tIRect SpeedRect(0, 0, Width, Height);
		SetFontHeight(Bmp, "999 kmh", SpeedRect);
		CXUTMSpeed UTMSpeed = m_NaviData.GetUTMSpeed();
		int Speed = static_cast<int>(floor(3.6*UTMSpeed.GetSpeed()));
		sprintf(buf, "%d kmh", Speed);
		SpeedRect = Bmp.CalcTextRectUTF8(buf, 4, 0);
		SpeedRect.OffsetRect(Width - SpeedRect.GetRight(), 3*Height-SpeedRect.GetTop());
		Bmp.DrawTextUTF8(buf, SpeedRect, FGCOLOR, BGCOLOR);


		// draw data
		pDC->Blend(&Bmp, OffsetX, OffsetY, 70);
	}
}
