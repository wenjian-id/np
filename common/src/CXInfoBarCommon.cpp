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


//-------------------------------------
CXInfoBarCommon::CXInfoBarCommon() {
}

//-------------------------------------
CXInfoBarCommon::~CXInfoBarCommon() {
}

//-------------------------------------
void CXInfoBarCommon::PositionChanged(const CXNaviData & NewData) {
	// remember new position
	m_NaviData = NewData;
}

//-------------------------------------
int CXInfoBarCommon::CalcFontHeight(CXBitmap &Bmp, const CXStringUTF8 &Str, tIRect &rRect) {
	int Height = rRect.GetHeight();
	int Width = rRect.GetWidth();
	int FontHeight = Height;
	Bmp.SetFont(FontHeight, false);
	// calculate font height, so text fits into rect
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

		// create temporary bitmap
		CXBitmap TmpBmp;
		TmpBmp.Create(pDC, Width, CompleteHeight);

		char buf[100];

		// calc lon rect
		tIRect LonRect(0, 0, Width, Height);
		CXStringUTF8 StrLon;
		StrLon = "-180.99999";
		StrLon.Append(DegUTF8, sizeof(DegUTF8));
		int FHLon = CalcFontHeight(TmpBmp, StrLon, LonRect);
		snprintf(buf, sizeof(buf), "%0.5f", m_NaviData.GetLon());
		StrLon = buf;
		StrLon.Append(DegUTF8, sizeof(DegUTF8));
		LonRect = TmpBmp.CalcTextRectUTF8(StrLon, 4, 0);
		LonRect.OffsetRect(Width - LonRect.GetRight(), 0);

		// calc lat rect
		tIRect LatRect(0, 0, Width, Height);
		CXStringUTF8 StrLat;
		snprintf(buf, sizeof(buf), "%0.5f", m_NaviData.GetLat());
		StrLat = buf;
		StrLat.Append(DegUTF8, sizeof(DegUTF8));
		LatRect = TmpBmp.CalcTextRectUTF8(StrLat, 4, 0);
		LatRect.OffsetRect(Width - LatRect.GetRight(), LonRect.GetBottom());

		// calc height rect
		tIRect HeightRect(0, 0, Width, Height);
		CXStringUTF8 StrHeight;
		snprintf(buf, sizeof(buf), "%0.0f m", m_NaviData.GetHeight());
		StrHeight = buf;
		HeightRect = TmpBmp.CalcTextRectUTF8(StrHeight, 4, 0);
		HeightRect.OffsetRect(Width - HeightRect.GetRight(), LatRect.GetBottom());

		// calc speed rect
		tIRect SpeedRect(0, 0, Width, Height);
		CXStringUTF8 StrSpeed;
		int FHSpeed = CalcFontHeight(TmpBmp, "999 kmh", SpeedRect);
		CXUTMSpeed UTMSpeed = m_NaviData.GetUTMSpeed();
		int Speed = static_cast<int>(floor(3.6*UTMSpeed.GetSpeed()));
		snprintf(buf, sizeof(buf), "%d kmh", Speed);
		StrSpeed = buf;
		SpeedRect = TmpBmp.CalcTextRectUTF8(StrSpeed, 4, 0);
		SpeedRect.OffsetRect(Width - SpeedRect.GetRight(), HeightRect.GetBottom());

		// calc speed rect1
		tIRect SpeedRect1(0, 0, Width, Height);
		CXStringUTF8 StrSpeed1;
		Speed = static_cast<int>(floor(3.6*m_NaviData.GetRMCSpeed()));
		snprintf(buf, sizeof(buf), "%d kmh", Speed);
		StrSpeed1 = buf;
		SpeedRect1 = TmpBmp.CalcTextRectUTF8(StrSpeed1, 4, 0);
		SpeedRect1.OffsetRect(Width - SpeedRect1.GetRight(), SpeedRect.GetBottom());

		// create bitmap
		CXBitmap Bmp;
		Bmp.Create(pDC, Width, SpeedRect1.GetBottom());

		// set rect
		tIRect ClientRect(0,0,Width,SpeedRect.GetBottom());
		// draw backgound
		Bmp.DrawRect(ClientRect, BGCOLOR, BGCOLOR);

		// now draw data
		Bmp.SetFont(FHLon, false);
		Bmp.DrawTextUTF8(StrLon, LonRect, FGCOLOR, BGCOLOR);
		Bmp.DrawTextUTF8(StrLat, LatRect, FGCOLOR, BGCOLOR);
		Bmp.DrawTextUTF8(StrHeight, HeightRect, FGCOLOR, BGCOLOR);
		Bmp.SetFont(FHSpeed, false);
		Bmp.DrawTextUTF8(StrSpeed, SpeedRect, FGCOLOR, BGCOLOR);
		Bmp.DrawTextUTF8(StrSpeed1, SpeedRect1, FGCOLOR, BGCOLOR);

		// blend to device context
		pDC->Blend(&Bmp, OffsetX, OffsetY, 70);
	}
}
