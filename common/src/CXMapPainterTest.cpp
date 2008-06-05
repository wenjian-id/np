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
void CXMapPainterTest::OnInternalPaint(IBitmap *pBMP, int Width, int Height) {
	// get copy of navigation data
	CXNaviData Data = GetPosition();

	PaintPackground(pBMP, Width, Height);

/*	
	CXRGB C0(128, 42, 42);

	char buf[100];
	CXRGB C1(0x00, 0x00, 0x00);
	CXRGB C2(0xff, 0xff, 0xff);
	tIRect R1(0, 0, 200, 40);
	sprintf(buf, "%.6f %.6f %d", Data.GetLon(), Data.GetLat(), CXSatelliteData::Instance()->GetNrSat());
	pBMP->DrawTextASCII(buf, R1, C1, C2);

	tIRect R2(0, 50, 200, 90);
	sprintf(buf, "%.2f %.2f %d %c", Data.GetCoor().GetUTMEasting(), Data.GetCoor().GetUTMNorthing(), Data.GetCoor().GetUTMZone(), Data.GetCoor().GetUTMLetter());
	pBMP->DrawTextASCII(buf, R2, C1, C2);
	
	tIRect R3(0, 100, 200, 140);
	sprintf(buf, "%.2f %.2f %.2f", Data.GetUTMSpeed().GetSpeed(), Data.GetUTMSpeed().GetCos(), Data.GetUTMSpeed().GetSin());
	pBMP->DrawTextASCII(buf, R3, C1, C2);

	tIRect R4(0, 150, 200, 190);
	CXStringUTF8 Name = Data.GetStreetName();
	pBMP->DrawTextUTF8(Name, R4, C2, C0);
*/

}
