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

#include "CXMapPainter2D.hpp"
#include "CXMutexLocker.hpp"
#include "CXOptions.hpp"
#include "CXExactTime.hpp"
#include "CXOptions.hpp"
#include "CoordConstants.h"
#include "CXStringASCII.hpp"
#include "CXPen.hpp"
#include "CXTransformationMatrix.hpp"
#include "TargetIncludes.hpp"


// Mapnik colors
static const CXRGB BGCOLOR(0xE2, 0xDE, 0xD8);
static const CXRGB FGCOLOR(0x00, 0x00, 0x00);
const double ZoomFactor = 1.2;

CXWay::E_KEYHIGHWAY Order[CXWay::eEnumCount] = {
	CXWay::eUnknown,
	CXWay::eSteps,
	CXWay::ePedestrian,
	CXWay::eFootway,
	CXWay::eCycleway,
	CXWay::eBridleway,
	CXWay::eService,
	CXWay::eResidential,
	CXWay::eTrack,
	CXWay::eUnclassified,
	CXWay::eTertiary,
	CXWay::eSecondary,
	CXWay::ePrimaryLink,
	CXWay::eTrunkLink,
	CXWay::eMotorwayLink,
	CXWay::ePrimary,
	CXWay::eTrunk,
	CXWay::eMotorway
};

//----------------------------------------------------------------------------
//-------------------------------------
CXMapPainter2D::CXMapPainter2D() :
	m_Scale(1/2.5)
{
	for(size_t i=0; i<CXWay::eEnumCount; i++) {
		m_DrawWays.Append(new TWayBuffer());
	}
}

//-------------------------------------
CXMapPainter2D::~CXMapPainter2D() {
	// delete arrays
	for(size_t i=0; i<CXWay::eEnumCount; i++) {
		TWayBuffer *pBuffer = m_DrawWays[i];
		delete pBuffer;
	}
	m_DrawWays.Clear();
}

//-------------------------------------
bool CXMapPainter2D::IsWayPossiblyVisible(CXWay *pWay, int Width, int Height) {
	if(pWay == NULL)
		return false;

	int x0 = 0;
	int y0 = 0;
	size_t NodeCount = pWay->GetNodeCount();
	for(size_t i=0; i<NodeCount; i++) {
		CXNode *pNode = pWay->GetNode(i);
		int x = pNode->GetDisplayX();
		int y = pNode->GetDisplayY();
		// check if it is worth drawing
		if(	((x0 < 0) && (x < 0)) ||
			((x0 > Width) && (x > Width)) ||
			((y0 < 0) && (y < 0)) ||
			((y0 > Height) && (y > Height)))
		{
			// no
			// do nothing
		} else if (i != 0) {
			return true;
		}
		x0 = x;
		y0 = y;
	}
	return false;
}


//-------------------------------------
void CXMapPainter2D::DrawWay(IBitmap *pBMP, CXWay *pWay, int Width, int Height) {
	if(pWay == NULL)
		return;
	size_t NodeCount = pWay->GetNodeCount();
	int x0 = 0;
	int y0 = 0;
	for(size_t i=0; i<NodeCount; i++) {
		CXNode *pNode = pWay->GetNode(i);
		int x = pNode->GetDisplayX();
		int y = pNode->GetDisplayY();
		// check if it is worth drawing
		if(	((x0 < 0) && (x < 0)) ||
			((x0 > Width) && (x > Width)) ||
			((y0 < 0) && (y < 0)) ||
			((y0 > Height) && (y > Height)))
		{
			// no
			// do nothing
		} else {
			// yes
			if(i != 0)
				pBMP->DrawLine(x0, y0, x, y);
		}
		x0 = x;
		y0 = y;
	}
}

//-------------------------------------
void CXMapPainter2D::DrawWaysBg(IBitmap *pBMP, TWayBuffer *pWays, CXWay::E_KEYHIGHWAY eHighwayType, int Width, int Height) {
	if(pWays == NULL)
		return;
	// get pen for this type of way
	CXPen *pPen = m_PenHolder.GetPenBg(eHighwayType);
	bool OSMValiEnabled = CXOptions::Instance()->GetOSMValiFlags() != 0;
	if(pPen != NULL) {
		// create red pen
		CXPen RedPen = *pPen;
		RedPen.SetColor(CXRGB(0xff, 0x00, 0x00));
		// set normal pen
		pBMP->SetPen(*pPen);
		// now iterate through ways
		size_t cnt = pWays->GetSize();
		for(size_t i=0; i<cnt; i++) {
			CXWay *pWay = (*pWays)[i];
			bool oUseRedPen = OSMValiEnabled && !pWay->GetOSMValiState();
			// set red pen
			if(oUseRedPen)
				pBMP->SetPen(RedPen);
			DrawWay(pBMP, pWay, Width, Height);
			// set old pen
			if(oUseRedPen)
				pBMP->SetPen(*pPen);
		}
	}
}

//-------------------------------------
void CXMapPainter2D::DrawWaysFg(IBitmap *pBMP, TWayBuffer *pWays, CXWay::E_KEYHIGHWAY eHighwayType, int Width, int Height) {
	if(pWays == NULL)
		return;
	// get pen for this type of way
	CXPen *pPen = m_PenHolder.GetPenFg(eHighwayType);
	bool OSMValiEnabled = CXOptions::Instance()->GetOSMValiFlags() != 0;
	if(pPen != NULL) {
		// create red pen
		CXPen RedPen = *pPen;
		RedPen.SetColor(CXRGB(0xff, 0x00, 0x00));
		// set normal pen
		pBMP->SetPen(*pPen);
		// now iterate through ways
		size_t cnt = pWays->GetSize();
		for(size_t i=0; i<cnt; i++) {
			CXWay *pWay = (*pWays)[i];
			bool oUseRedPen = OSMValiEnabled && !pWay->GetOSMValiState();
			// set red pen
			if(oUseRedPen)
				pBMP->SetPen(RedPen);
			DrawWay(pBMP, pWay, Width, Height);
			// set old pen
			if(oUseRedPen)
				pBMP->SetPen(*pPen);
		}
	}
}

//-------------------------------------
void CXMapPainter2D::DrawScale(IBitmap *pBMP, int ScreenWidth, int ScreenHeight) {
	if(pBMP == NULL)
		return;

	// get scale dimensions
	int ScaleWidth = CXOptions::Instance()->GetScaleWidth();
	int ScaleHeight = CXOptions::Instance()->GetScaleHeight();
	const double EPSILON = 0.000001;
	if(m_Scale < EPSILON)
		return;
	// get optimal scale display
	int exp = 1;
	int ScaleX = 1;
	int expFinal = exp;
	int ScaleXFinal = ScaleX;
	while(1.0*ScaleX*exp*m_Scale < ScaleWidth) {
		expFinal = exp;
		ScaleXFinal = ScaleX;
		if(ScaleX == 1) {
			ScaleX = 2;
		} else if(ScaleX == 2) {
			ScaleX = 5;
		} else {
			ScaleX = 1;
			exp = 10*exp;
		}
	}
	exp = expFinal;
	ScaleX = ScaleXFinal;
	// compute scale width in pixel
	int ScaleXPixel = static_cast<int>(1.0*ScaleX*exp*m_Scale);
	// draw scale
	// first the black rectangle
	tIRect ScaleRect(	(ScreenWidth - ScaleXPixel)/2, ScreenHeight - ScaleHeight - 5,
						(ScreenWidth + ScaleXPixel)/2, ScreenHeight - 5);
	pBMP->DrawRect(ScaleRect, CXRGB(0x00, 0x00, 0x00), CXRGB(0x00, 0x00, 0x00));
	// now the left yellow rectangle
	tIRect ScaleRect1(	(ScreenWidth - ScaleXPixel/2)/2, ScreenHeight - ScaleHeight - 5,
						ScreenWidth/2, ScreenHeight - 5);
	pBMP->DrawRect(ScaleRect1, CXRGB(0x00, 0x00, 0x00), CXRGB(0xff, 0xff, 0x00));
	// now the right yellow rectangle
	ScaleRect1.OffsetRect(ScaleXPixel/2, 0);
	pBMP->DrawRect(ScaleRect1, CXRGB(0x00, 0x00, 0x00), CXRGB(0xff, 0xff, 0x00));
	// draw scale description
	char buf[100];
	if(exp < 1000) {
		sprintf(buf, "%d m", ScaleX*exp);
	} else {
		sprintf(buf, "%d km", ScaleX*(exp/1000));
	}
	// calculate size of text
	ScaleRect1 = pBMP->CalcTextRectASCII(buf, 2, 2);
	// position it
	ScaleRect1.OffsetRect(	-ScaleRect1.GetLeft() + ScreenWidth/2 - ScaleRect1.GetWidth()/2,
							-ScaleRect1.GetTop() + ScaleRect.GetTop() - ScaleRect1.GetHeight() - 1);
	// and draw it
	pBMP->DrawTextASCII(buf, ScaleRect1, CXRGB(0x00, 0x00, 0x00), BGCOLOR);
}


//-------------------------------------
void CXMapPainter2D::PaintPackground(IBitmap *pBMP, int Width, int Height) {
	// clear wisible rect
	pBMP->DrawRect(tIRect(0,0, Width, Height), BGCOLOR, BGCOLOR);
}

//-------------------------------------
void CXMapPainter2D::OnInternalPaint(IBitmap *pBMP, int Width, int Height) {

	// since not all compilers can handle multiple for(size_t i=...)
	// we set size_t i=0; right here :-(((
	size_t i=0;

	CXMutexLocker L(&m_Mutex);

	CXExactTime Start;

	// get copy of navigation data
	CXNaviData NaviData = GetPosition();
	CXOptions *pOpt = CXOptions::Instance();

	// draw background
	PaintPackground(pBMP, Width, Height);

	// check if map
	if(CXPOWMMap::Instance() == NULL)
		return;

	CXPOWMMap::Instance()->LockMap();
	CXExactTime StopLock;
	CXExactTime StopPrepare;
	CXExactTime StopDrawWays;
	CXExactTime StopTrackLog;
	CXExactTime StopScale;
	CXExactTime StopCompass;

	int CompassSize = CXOptions::Instance()->GetCompassSize();
	tIRect CompassRect(0,0,CompassSize,CompassSize);

	// get zone
	int WayCount = 0;
	int CurrentZone = CXPOWMMap::Instance()->GetCurrentZone();
	if(CurrentZone != UTMZoneNone) {
		int xc = 0;
		int yc = 0;
		// compute coordinate
		char UTMLetter = 0;
		double x0 = 0;
		double y0 = 0;
		int NewZone = UTMZoneNone;
		LLtoUTM(WGS84, NaviData.GetLon(), NaviData.GetLat(), CurrentZone, NewZone, UTMLetter, x0, y0);

		CXTransformationMatrix2D TMMap;
		CXTransformationMatrix2D TMCompass;
		CXTransformationMatrix2D TMCurrentPos;

		CXUTMSpeed UTMSpeed = NaviData.GetUTMSpeed();

		TMMap.Translate(-x0, -y0);			// x0, y0 is center of visible universe
		// rotate
		if(pOpt->IsNorthing()) {
			xc = Width/2;
			yc = Height/2;
			TMCurrentPos.Rotate(UTMSpeed.GetCos(), UTMSpeed.GetSin());
			TMCurrentPos.Rotate(-UTMPI/2);
		} else {
			xc = Width/2;
			yc = 3*Height/4;
			TMMap.Rotate(UTMSpeed.GetCos(), -UTMSpeed.GetSin());
			TMCompass.Rotate(UTMSpeed.GetCos(), -UTMSpeed.GetSin());
			// rotate 90 to left, since 0 is east amd we want it point to north
			TMMap.Rotate(UTMPI/2);
			TMCompass.Rotate(UTMPI/2);
		}

		TMMap.Scale(m_Scale, -m_Scale);		// do scaling (negative for y!)
		TMMap.Translate(xc, yc);			// display it centered on screen
		TMCompass.Scale(1, -1);				// do scaling (negative for y!)
		TMCurrentPos.Scale(1, -1);			// do scaling (negative for y!)

		// run coordinate transformations
		CXPOWMMap::Instance()->ComputeDisplayCoordinates(TMMap);

		// prepare drawing
		TWayMap &Ways = CXPOWMMap::Instance()->GetWayMap();
		POS pos = Ways.GetStart();
		CXWay *pWay = NULL;
		while (Ways.GetNext(pos, pWay) != TWayMap::NPOS) {
			if (IsWayPossiblyVisible(pWay, Width, Height)) {
				CXWay::E_KEYHIGHWAY HighwayType = pWay->GetHighwayType();
				m_DrawWays[HighwayType]->Append(pWay);
				WayCount++;
			}
		}
		StopPrepare.SetNow();
		// ok, now draw bg
		for(i=0; i< CXWay::eEnumCount; i++) {
			DrawWaysBg(pBMP, m_DrawWays[Order[i]], Order[i], Width, Height);
		}
		for(i=0; i< CXWay::eEnumCount; i++) {
			DrawWaysFg(pBMP, m_DrawWays[Order[i]], Order[i], Width, Height);
		}
		StopDrawWays.SetNow();

		// clear arrays
		for(i=0; i<CXWay::eEnumCount; i++) {
			TWayBuffer *pBuffer = m_DrawWays[i];
			pBuffer->Clear();
		}

		CXCoorVector v;
		// draw TrackLog if neccessary
		if(CXOptions::Instance()->MustShowTrackLog()) {
			const TCoorBuffer & CoorBuffer = CXPOWMMap::Instance()->GetTrackLog().GetCoordinates();
			size_t Size = CoorBuffer.GetSize();
			CXPen TLPen(CXPen::e_Solid, 2, CXRGB(0x00, 0x00, 0xFF));
			pBMP->SetPen(TLPen);
			if(Size > 1) {
				int *pX = new int[Size];
				int *pY = new int[Size];
				for(size_t i=0; i<Size; i++) {
					CXCoor *pCoor = CoorBuffer[i];
					v = TMMap*CXCoorVector(pCoor->GetUTMEasting(), pCoor->GetUTMNorthing());
					pX[i] = v.GetIntX();
					pY[i] = v.GetIntY();
				}

				pBMP->PolyLine(pX, pY, Size);
				delete [] pX;
				delete [] pY;
			}
		}
		StopTrackLog.SetNow();

		int X[4];
		int Y[4];
		// draw compass if necessary
		if(CXOptions::Instance()->MustShowCompass()) {
			int CX = CompassRect.GetLeft() + CompassRect.GetWidth()/2;
			int CY = CompassRect.GetTop() + CompassRect.GetHeight()/2;
			double R = 0.8*CompassSize/2;

			CXPen pen(CXPen::e_Solid, 1, CXRGB(0xFF, 0x00, 0x00));
			pBMP->SetPen(pen);

			v = TMCompass*CXCoorVector(0, R);
			X[0] = CX + v.GetIntX();
			Y[0] = CY + v.GetIntY();
			v = TMCompass*CXCoorVector(R/2, -0.7*R);
			X[1] = CX + v.GetIntX();
			Y[1] = CY + v.GetIntY();
			v = TMCompass*CXCoorVector(0, -0.25*R);
			X[2] = CX + v.GetIntX();
			Y[2] = CY + v.GetIntY();
			v = TMCompass*CXCoorVector(-R/2, -0.7*R);
			X[3] = CX + v.GetIntX();
			Y[3] = CY + v.GetIntY();
			pBMP->Polygon(X, Y, 4, CXRGB(0xB0, 0xB0, 0x00), CXRGB(0xB0, 0x00, 0x00));
		}
		StopCompass.SetNow();

		// draw scale if necessary
		if(CXOptions::Instance()->MustShowScale()) {
			DrawScale(pBMP, Width, Height);
		}
		StopScale.SetNow();

		// draw current position
		double ArrowSize = 15.0;
		v = TMCurrentPos*CXCoorVector(0, ArrowSize);
		X[0] = xc + v.GetIntX();
		Y[0] = yc + v.GetIntY();
		v = TMCurrentPos*CXCoorVector(ArrowSize/2, -0.7*ArrowSize);
		X[1] = xc + v.GetIntX();
		Y[1] = yc + v.GetIntY();
		v = TMCurrentPos*CXCoorVector(0, -0.25*ArrowSize);
		X[2] = xc + v.GetIntX();
		Y[2] = yc + v.GetIntY();
		v = TMCurrentPos*CXCoorVector(-ArrowSize/2, -0.7*ArrowSize);
		X[3] = xc + v.GetIntX();
		Y[3] = yc + v.GetIntY();

		pBMP->Polygon(X, Y, 4, CXRGB(0x00, 0x00, 0x00), CXRGB(0x00, 0xFF, 0x00));
//		pBMP->DrawRect(tIRect(xc-5, yc-5, xc+5, yc+5), CXRGB(0x00, 0x00, 0x00), CXRGB(0xff, 0x00, 0x00));
	}
	CXPOWMMap::Instance()->UnlockMap();


	CXExactTime Stop;

	if(CXOptions::Instance()->IsDebugInfoFlagSet(CXOptions::e_DBGDrawTimes)) {
		char buf[200];
		snprintf(	buf, sizeof(buf), "Pr:%ld Wy:%ld (%d) TL:%ld Co:%ld Sc:%ld Ps:%ld",
					StopPrepare-StopLock, StopDrawWays-StopPrepare, WayCount, 
					StopTrackLog-StopDrawWays, StopCompass-StopTrackLog, StopScale-StopCompass,
					Stop-StopScale);
		CXStringASCII ttt = buf;
		tIRect TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
		TextRect.OffsetRect(-TextRect.GetLeft(), CompassRect.GetBottom()-TextRect.GetTop());
		pBMP->DrawTextASCII(ttt, TextRect, FGCOLOR, BGCOLOR); 
	}
}

//-------------------------------------
bool CXMapPainter2D::ZoomIn() {
	CXMutexLocker L(&m_Mutex);
	m_Scale = m_Scale * ZoomFactor;
	return true;
}

//-------------------------------------
bool CXMapPainter2D::ZoomOut() {
	CXMutexLocker L(&m_Mutex);
	m_Scale = m_Scale / ZoomFactor;
	return true;
}
