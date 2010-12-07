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

#include "CXInfoBarCommon.hpp"
#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"
#include "CXOptions.hpp"
#include "CXStringUTF8.hpp"

#include <math.h>

static const CXRGB BGCOLOR(0x00, 0x00, 0x00);
static const CXRGB FGCOLOR(0xff, 0xff, 0x00);


//-------------------------------------
CXInfoBarCommon::CXInfoBarCommon() :
    m_TextHeightCoor(20),
    m_TextHeightSpeed(20)
{
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
void CXInfoBarCommon::CalcFontHeights(CXDeviceContext *pDC) {
    int Width = GetWidth();
    int Height = GetHeight();
    // create bitmap
    tIRect ClientRect(0,0,Width,Height);
    CXBitmap Bmp;
    Bmp.Create(pDC, ClientRect.GetWidth(), ClientRect.GetHeight());

    // calc coor font height
    tIRect LonRect(0, 0, Width, Height);
    CXStringUTF8 StrLon;
    StrLon = "-180.99999";
    StrLon.Append(DegUTF8, sizeof(DegUTF8));
    m_TextHeightCoor = CalcFontHeight(Bmp, StrLon, LonRect);

    // calc speed font height
    tIRect SpeedRect(0, 0, Width, Height);
    CXStringUTF8 StrSpeed;
    m_TextHeightSpeed = CalcFontHeight(Bmp, "999 kmh", SpeedRect);
}

//-------------------------------------
void CXInfoBarCommon::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
    int Width = GetWidth();
    int Height = GetHeight();

    if(SizeChanged()) {
        CalcFontHeights(pDC);
    }

    if(!CXOptions::Instance()->MustShowLogo() && !CXOptions::Instance()->IsMapMovingManually()) {

        // create bitmap
        tIRect ClientRect(0,0,Width,Height);
        CXBitmap Bmp;
        Bmp.Create(pDC, ClientRect.GetWidth(), ClientRect.GetHeight());

        // draw backgound
        Bmp.DrawRect(ClientRect, BGCOLOR, BGCOLOR);

        CXCoor Coor = m_NaviData.GetGPSCoor();
        CXStringUTF8 StrLon = FToA<CXStringUTF8>(Coor.GetLon(), 1, 5);
        StrLon.Append(DegUTF8, sizeof(DegUTF8));
        CXStringUTF8 StrLat = FToA<CXStringUTF8>(Coor.GetLat(), 1, 5);
        StrLat.Append(DegUTF8, sizeof(DegUTF8));
        CXStringUTF8 StrHeight = FToA<CXStringUTF8>(m_NaviData.GetHeight(), 1, 0) + " m";
        CXUTMSpeed UTMSpeed = m_NaviData.GetUTMSpeed();
        int Speed = static_cast<int>(floor(3.6*UTMSpeed.GetSpeed()));
        CXStringUTF8 StrSpeed = IToA<CXStringUTF8>(Speed) + " kmh";

        Bmp.SetFont(m_TextHeightCoor, false);

        // calc lon rect
        tIRect LonRect = Bmp.CalcTextRectUTF8(StrLon, 4, 0);
        LonRect.OffsetRect(Width - LonRect.GetWidth(), 0);

        // calc lat rect
        tIRect LatRect = Bmp.CalcTextRectUTF8(StrLat, 4, 0);
        LatRect.OffsetRect(Width - LatRect.GetWidth(), LonRect.GetBottom());

        // calc height rect
        tIRect HeightRect = Bmp.CalcTextRectUTF8(StrHeight, 4, 0);
        HeightRect.OffsetRect(Width - HeightRect.GetWidth(), LatRect.GetBottom());

        Bmp.SetFont(m_TextHeightSpeed, false);

        // calc speed rect
        tIRect SpeedRect = Bmp.CalcTextRectUTF8(StrSpeed, 4, 0);
        SpeedRect.OffsetRect(Width - SpeedRect.GetRight(), HeightRect.GetBottom());

        // now draw data
        Bmp.SetFont(m_TextHeightCoor, false);
        Bmp.DrawTextUTF8(StrLon, LonRect, FGCOLOR, BGCOLOR);
        Bmp.DrawTextUTF8(StrLat, LatRect, FGCOLOR, BGCOLOR);
        Bmp.DrawTextUTF8(StrHeight, HeightRect, FGCOLOR, BGCOLOR);
        Bmp.SetFont(m_TextHeightSpeed, false);
        Bmp.DrawTextUTF8(StrSpeed, SpeedRect, FGCOLOR, BGCOLOR);

        // blend to device context
        pDC->Blend(&Bmp, OffsetX, OffsetY, 70);
    }
}
