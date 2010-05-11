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

#include "CXInfoBarRouting.hpp"
#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"
#include "CXOptions.hpp"
#include "CXStringUTF8.hpp"
#include "CXTransformationMatrix.hpp"

#include <math.h>

static const CXRGB BGCOLOR(0x00, 0x00, 0x00);
static const CXRGB FGCOLOR(0xff, 0xff, 0x00);


//-------------------------------------
CXInfoBarRouting::CXInfoBarRouting() :
	m_TextHeightDist(5)
{
}

//-------------------------------------
CXInfoBarRouting::~CXInfoBarRouting() {
}

//-------------------------------------
void CXInfoBarRouting::PositionChanged(const CXNaviData & NewData) {
	// remember new position
	m_NaviData = NewData;
}

//-------------------------------------
void CXInfoBarRouting::OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	int Width = GetWidth();
	int Height = GetHeight();
	CXOptions *pOpt = CXOptions::Instance();
	CXCoor TargetCoor = pOpt->GetTargetCoor();
	CXCoor CurrentCoor;
	if(pOpt->MustSnapToWay()) {
		// get coordinates from locator
		CurrentCoor = m_NaviData.GetLocatedCoor();
	} else {
		// get corrected gps coordinates
		CurrentCoor = m_NaviData.GetCorrectedGPSCoor();
	}
	// calc distance and direction
	double dDist = CalcDistance(CurrentCoor, TargetCoor);
	CXDirection MoveDir = m_NaviData.GetUTMSpeed().GetDirection();
	CXDirection Dir;
	ComputeRelativeUTMAngle(CurrentCoor, TargetCoor, Dir);

	if(SizeChanged()) {
		// create bitmap
		tIRect ClientRect(0,0,Width,Height);
		CXBitmap Bmp;
		Bmp.Create(pDC, ClientRect.GetWidth(), ClientRect.GetHeight());
		CXStringUTF8 StrDist = "99999 km";
		m_TextHeightDist = CalcFontHeight(Bmp, StrDist, ClientRect);
	}

	if(!pOpt->MustShowLogo() && !pOpt->IsMapMovingManually()) {

		// create bitmap
		tIRect ClientRect(0,0,Width,Height);
		CXBitmap Bmp;
		Bmp.Create(pDC, ClientRect.GetWidth(), ClientRect.GetHeight());

		// draw backgound
		Bmp.DrawRect(ClientRect, BGCOLOR, BGCOLOR);

		if(pOpt->IsTargetSet()) {
			// draw distance
			char buf[100];
			if(dDist < 10) {
				snprintf(buf, sizeof(buf), "%0.2f m", dDist); // resolution 1cm
			} else if (dDist < 100) {
				snprintf(buf, sizeof(buf), "%0.1f m", dDist); // resolution 10cm
			} else if (dDist < 1000) {
				snprintf(buf, sizeof(buf), "%0.0f m", dDist); // resolution 1m
			} else if (dDist < 10000) {
				snprintf(buf, sizeof(buf), "%0.2f km", dDist/1000); // resolution 10m
			} else if (dDist < 100000) {
				snprintf(buf, sizeof(buf), "%0.1f km", dDist/1000); // resolution 100m
			} else {
				snprintf(buf, sizeof(buf), "%0.0f km", dDist/1000); // resolution 1km
			}
			Bmp.SetFont(m_TextHeightDist, false);
			CXStringUTF8 DistStr(buf);
			// position string bottom right adjusted
			tIRect DistRect = Bmp.CalcTextRectUTF8(DistStr, 4, 0);
			DistRect.OffsetRect(Width - DistRect.GetWidth(), Height - DistRect.GetHeight());
			Bmp.DrawTextUTF8(DistStr, DistRect, FGCOLOR, BGCOLOR);
	
			// now draw arrow
			CXTransformationMatrix2D TM;
			// rotate to target. compensate move direction
			TM.Rotate(Dir);
			TM.Rotate(-MoveDir);
			// y upwards down
			TM.Scale(1, -1);
			// position to center
			TM.Translate(Width/2, (Height-DistRect.GetHeight())/2);
			CXCoorVector v;
			int X[4];
			int Y[4];
			double R = 0.8*Min(Width, Height-DistRect.GetHeight())/2;
			v = TM*CXCoorVector(0, R);
			X[0] = v.GetIntX();
			Y[0] = v.GetIntY();
			v = TM*CXCoorVector(R/2, -0.7*R);
			X[1] = v.GetIntX();
			Y[1] = v.GetIntY();
			v = TM*CXCoorVector(0, -0.25*R);
			X[2] = v.GetIntX();
			Y[2] = v.GetIntY();
			v = TM*CXCoorVector(-R/2, -0.7*R);
			X[3] = v.GetIntX();
			Y[3] = v.GetIntY();
			Bmp.Polygon(X, Y, 4, CXRGB(0xff, 0xff, 0xff), CXRGB(0x00, 0x00, 0xB0));
		}
		// blend to device context
		pDC->Blend(&Bmp, OffsetX, OffsetY, 70);
	}
}
