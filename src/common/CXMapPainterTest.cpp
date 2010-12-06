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

#include "CXMapPainterTest.hpp"
#include "CXSatelliteData.hpp"
#include "TargetIncludes.hpp"

#include <stdio.h>

//-------------------------------------
CXMapPainterTest::CXMapPainterTest() {
}

//-------------------------------------
CXMapPainterTest::~CXMapPainterTest() {
}

//-------------------------------------
bool CXMapPainterTest::ZoomIn() {
    DoOutputDebugString("ZoomIn\n");
    return true;
}

//-------------------------------------
bool CXMapPainterTest::ZoomOut() {
    DoOutputDebugString("ZoomOut\n");
    return true;
}

//-------------------------------------
void CXMapPainterTest::PaintPackground(IBitmap *pBMP, int Width, int Height) {
    tIRect R0(0, 0, Width, Height);
    CXRGB C0(128, 42, 42);
    pBMP->DrawRect(R0, C0, C0);
}


//-------------------------------------
void CXMapPainterTest::OnInternalPaint(IBitmap *pBMP, IBitmap */*pTmpBMP*/, int Width, int Height) {
    // get copy of navigation data
    CXNaviData Data = GetPosition();

    PaintPackground(pBMP, Width, Height);

}
