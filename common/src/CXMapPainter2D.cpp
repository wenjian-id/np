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

#include "CXMapPainter2D.hpp"
#include "OSSpecific.hpp"
#include "CXWriteLocker.hpp"
#include "CXExactTime.hpp"
#include "CXOptions.hpp"
#include "CoordConstants.h"
#include "CXStringASCII.hpp"
#include "CXPen.hpp"
#include "CXTransformationMatrix.hpp"
#include "TargetIncludes.hpp"
#include "CXTrackLog.hpp"
#include "CXReadLocker.hpp"
#include "CXDebugInfo.hpp"
#include "CXMapMovingDetails.hpp"

#include <math.h>

const double ZoomFactor = 1.2;
const double MAXMETERPERPIXEL = 500;	///< 500 m/pixel
const double MINMETERPERPIXEL = 0.1;	///< 0.1 m/pixel
static const int POIWIDTH		= 20;
static const int POIHEIGHT		= 20;
static const int POICOUNTHORZ	= 16;
static const int POICOUNTVERT	= 16;
static const double HYSTMAXOFFSETABS	= 1.4; ///< 1.4 m/s
static const double HYSTMAXOFFSETREL	= 0.1; ///< 10%


E_KEYHIGHWAY_TYPE Order[e_Highway_EnumCount] = {
	e_Highway_Unknown,
	e_Highway_Fading,
	e_Highway_LivingStreet,
	e_Highway_Steps,
	e_Highway_Pedestrian,
	e_Highway_Footway,
	e_Highway_Cycleway,
	e_Highway_Bridleway,
	e_Highway_Service,
	e_Highway_Residential,
	e_Highway_Track,
	e_Highway_PrimaryLink,
	e_Highway_TrunkLink,
	e_Highway_MotorwayLink,
	e_Highway_Unclassified,
	e_Highway_Tertiary,
	e_Highway_Secondary,
	e_Highway_Primary,
	e_Highway_Trunk,
	e_Highway_Motorway
};

//----------------------------------------------------------------------------
//-------------------------------------
CXMapPainter2D::CXMapPainter2D() :
	m_MeterPerPixel(3)
{
	for(size_t i=0; i<e_Highway_EnumCount; i++) {
		m_DrawWays.Append(new TWayBuffer());
	}
	UpdateZoomLevel();
	// create hysterezis
	CXStringASCII AutoZoomString = CXOptions::Instance()->GetAutomaticZoomString();
	bool oAutoZoom = ExtractFirstToken(AutoZoomString, ';') == "ON";
	while(!AutoZoomString.IsEmpty()) {
		double dSpeed = atof(ExtractFirstToken(AutoZoomString, ';').c_str());
		double dMeterPerPixel = atof(ExtractFirstToken(AutoZoomString, ';').c_str());
		// compute delta
		double delta = Min(HYSTMAXOFFSETABS, HYSTMAXOFFSETREL*dSpeed);
		m_AutoZoomLevels.AddInterval(dSpeed-delta, dSpeed+delta, dMeterPerPixel);
	}
	CXOptions::Instance()->SetAutomaticZoomFlag(oAutoZoom);
}

//-------------------------------------
CXMapPainter2D::~CXMapPainter2D() {
	// delete arrays
	size_t i=0;
	for(i=0; i<e_Highway_EnumCount; i++) {
		TWayBuffer *pBuffer = m_DrawWays[i];
		delete pBuffer;
	}
	m_DrawWays.Clear();

	// delete BMPs
	for(i=0; i<m_POIBMPs.GetSize(); i++) {
		delete m_POIBMPs[i];
	}
}

//-------------------------------------
void CXMapPainter2D::OnBuffersCreated(CXDeviceContext *pDC, int /*Width*/, int /*Height*/) {
	// reload POI bitmaps
	// iterate through BMPs
	if(m_POIBMPs.GetSize() == 0) {
		// create bitmaps
		for(size_t i=0; i<1; i++) {
			CXBitmap *pBMP = new CXBitmap();
			m_POIBMPs.Append(pBMP);
			pBMP->Create(pDC, POIWIDTH*POICOUNTHORZ, POIHEIGHT*POICOUNTVERT);
			CXStringASCII FileName = CXOptions::Instance()->GetDirectoryIcons();
			char buf[100];
			snprintf(buf,sizeof(buf),"poi%02X.bmp", i);
			FileName += buf;
			pBMP->LoadFromFile(FileName);
		}
	} else {
		// bitmaps already created. reload
		for(size_t i=0; i<m_POIBMPs.GetSize(); i++) {
			CXBitmap *pBMP = m_POIBMPs[i];
			CXStringASCII FileName = pBMP->GetFileName();
			pBMP->Create(pDC, POIWIDTH*POICOUNTHORZ, POIHEIGHT*POICOUNTVERT);
			pBMP->LoadFromFile(FileName);
		}
	}
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

int pX[1024];
int pY[1024];

//-------------------------------------
void CXMapPainter2D::DrawWay(IBitmap *pBMP, CXWay *pWay, int Width, int Height) {
	if(pWay == NULL)
		return;
	size_t NodeCount = pWay->GetNodeCount();
	int x0 = 0;
	int y0 = 0;
	bool oLastWasTerminator = false;
	bool oTerminator = false;
	size_t Count = 0;
	for(size_t i=0; i<NodeCount; i++) {
		CXNode *pNode = pWay->GetNode(i);
		oTerminator = (pNode->IsTerminator());
		int x = pNode->GetDisplayX();
		int y = pNode->GetDisplayY();
		if(!oTerminator && !oLastWasTerminator) {
			if(i != 0) {
				// check if it is worth drawing
				if(	((x0 < 0) && (x < 0)) ||
					((x0 > Width) && (x > Width)) ||
					((y0 < 0) && (y < 0)) ||
					((y0 > Height) && (y > Height)))
				{
					// no, nothing to draw.
					// check if we have something to draw
					if(Count != 0) {
						pBMP->DrawLine(Count, pX, pY);
						Count = 0;
					}
				} else {
					// yes, this segment is worth to be drawn
					if(Count == 0) {
						// add last point too, since it is first segment
						pX[Count] = x0;
						pY[Count] = y0;
						Count++;
					}
					// add current point
					pX[Count] = x;
					pY[Count] = y;
					Count++;
				}
			}
		} else {
			if(Count != 0) {
				pBMP->DrawLine(Count, pX, pY);
				Count = 0;
			}
		}
		x0 = x;
		y0 = y;
		oLastWasTerminator = oTerminator;
	}
	if(Count != 0) {
		pBMP->DrawLine(Count, pX, pY);
		Count = 0;
	}
}

//-------------------------------------
void CXMapPainter2D::DrawWaysBg(IBitmap *pBMP, TWayBuffer *pWays, E_KEYHIGHWAY_TYPE eHighwayType, int Width, int Height) {
	if(pWays == NULL)
		return;
	// get pen for this type of way
	CXPen *pPen = m_PenHolder.GetScaledPenBg(eHighwayType);
	bool OSMValiEnabled = CXOptions::Instance()->GetOSMValiFlags() != 0;
	size_t cnt = pWays->GetSize();
	if((cnt != 0) && (pPen != NULL)) {
		// create red pen
		CXPen RedPen = *pPen;
		RedPen.SetColor(CXRGB(0xff, 0x00, 0x00));
		// set normal pen
		pBMP->SetPen(*pPen);
		// now iterate through ways
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
void CXMapPainter2D::DrawWaysFg(IBitmap *pBMP, TWayBuffer *pWays, E_KEYHIGHWAY_TYPE eHighwayType, int Width, int Height) {
	if(pWays == NULL)
		return;
	// get pen for this type of way
	CXPen *pPen = m_PenHolder.GetScaledPenFg(eHighwayType);
	bool OSMValiEnabled = CXOptions::Instance()->GetOSMValiFlags() != 0;
	size_t cnt = pWays->GetSize();
	if((cnt != 0) && (pPen != NULL)) {
		// create red pen
		CXPen RedPen = *pPen;
		RedPen.SetColor(CXRGB(0xff, 0x00, 0x00));
		// set normal pen
		pBMP->SetPen(*pPen);
		// now iterate through ways
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
void CXMapPainter2D::DrawCompass(IBitmap *pBMP, const CXTransformationMatrix2D &TMCompass) {
	if(pBMP == NULL)
		return;

	if(CXOptions::Instance()->IsMapMovingManually())
		return;

	int CompassSize = CXOptions::Instance()->GetCompassSize();
	tIRect CompassRect(0,0,CompassSize,CompassSize);

	int CX = CompassRect.GetLeft() + CompassRect.GetWidth()/2;
	int CY = CompassRect.GetTop() + CompassRect.GetHeight()/2;
	double R = 0.8*CompassSize/2;

	CXPen pen(CXPen::e_Solid, 1, CXRGB(0xFF, 0x00, 0x00));
	pBMP->SetPen(pen);

	CXCoorVector v;
	int X[4];
	int Y[4];
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

//-------------------------------------
void CXMapPainter2D::DrawPOIs(IBitmap *pBMP, const TPOINodeBuffer &POINodes, int ScreenWidth, int ScreenHeight) {

	// iterate through POIs
	for(size_t n=0; n<POINodes.GetSize(); n++) {
		CXPOINode *pNode = POINodes[n];
		int x = pNode->GetDisplayX();
		int y = pNode->GetDisplayY();
		// check if visible
		if((x >= -POIWIDTH/2) && (x < ScreenWidth+POIWIDTH/2) && (y >= -POIHEIGHT/2) && (y < ScreenHeight+POIHEIGHT/2)) {
			for(size_t i=0; i<pNode->GetPOITypeCount(); i++) {
				size_t idx = 0;
				size_t row = 0;
				size_t col = 0;
				ComputePOIBMP(pNode->GetPOIType(i), idx, row, col);
				// draw POI bitmap
				if(idx < m_POIBMPs.GetSize()) {
					CXBitmap *pPOIBMP = m_POIBMPs[idx];
					// Bitmap loaded
					pBMP->DrawTransparent(	pPOIBMP,
											x-POIWIDTH/2, y-POIHEIGHT/2,
											col*POIWIDTH, row*POIHEIGHT,
											POIWIDTH, POIHEIGHT,
											COLOR_TRANSPARENT);
				}
				// draw name
				CXStringUTF8 Name = pNode->GetName();
				if(!Name.IsEmpty()) {
					tIRect NameRect = pBMP->CalcTextRectUTF8(Name, 0, 0);
					NameRect.OffsetRect(x - NameRect.GetWidth()/2, y - POIHEIGHT/2 - NameRect.GetHeight());
					pBMP->DrawTextUTF8(Name, NameRect, MAPPOITEXTCOLOR, MAPPOIBGCOLOR);
				}
			}
		}
	}
}

//-------------------------------------
void CXMapPainter2D::DrawPlaces(IBitmap *pBMP, const TPOINodeBuffer &PlaceNodes, int ScreenWidth, int ScreenHeight) {

	int FontSizeSmall = CXOptions::Instance()->GetCitySmallFontSize();
	int FontSizeMedium = CXOptions::Instance()->GetCityMediumFontSize();
	int FontSizeLarge = CXOptions::Instance()->GetCityLargeFontSize();

	// iterate through Places
	for(size_t n=0; n<PlaceNodes.GetSize(); n++) {
		CXPOINode *pNode = PlaceNodes[n];
		int x = pNode->GetDisplayX();
		int y = pNode->GetDisplayY();
		// check if visible
		if((x >= -POIWIDTH/2) && (x < ScreenWidth+POIWIDTH/2) && (y >= -POIHEIGHT/2) && (y < ScreenHeight+POIHEIGHT/2)) {
			size_t idx = 0;
			size_t row = 0;
			size_t col = 0;
			ComputePOIBMP(pNode->GetPOIType(0), idx, row, col);
			// draw POI bitmap
			if(idx < m_POIBMPs.GetSize()) {
				CXBitmap *pPOIBMP = m_POIBMPs[idx];
				// Bitmap loaded
				pBMP->DrawTransparent(	pPOIBMP,
										x-POIWIDTH/2, y-POIHEIGHT/2,
										col*POIWIDTH, row*POIHEIGHT,
										POIWIDTH, POIHEIGHT,
										COLOR_TRANSPARENT);
			}
			// draw name
			CXStringUTF8 Name = pNode->GetName();
			bool oBold = false;
			if(!Name.IsEmpty()) {
				// set font size for Places
				int FontSize = 16;
				switch(pNode->GetPOIType(0)) {
					case e_POI_PlaceSmall: 	FontSize = FontSizeSmall; oBold = false; break;
					case e_POI_PlaceMedium:	FontSize = FontSizeMedium; oBold = true; break;
					case e_POI_PlaceLarge:	FontSize = FontSizeLarge; oBold = true; break;
					default:				break;
				}
				pBMP->SetFont(FontSize, oBold);
				tIRect NameRect = pBMP->CalcTextRectUTF8(Name, 0, 0);
				NameRect.OffsetRect(x - NameRect.GetWidth()/2, y - POIHEIGHT/2 - NameRect.GetHeight());
				pBMP->DrawTextUTF8(Name, NameRect, MAPCITYTEXTCOLOR, MAPCITYBGCOLOR);
			}
		}
	}
}

//-------------------------------------
void CXMapPainter2D::DrawTrackLog(IBitmap *pBMP, const CXTransformationMatrix2D &TMMap) {
	if(pBMP == NULL)
		return;

	CXCoorVector v;

	/// \todo oiu redesign locking stuff...
	CXRWLock & RWLock = CXTrackLog::Instance()->GetRWLock();
	CXReadLocker RL(&RWLock);

	const TCoorBuffer & CoorBuffer = CXTrackLog::Instance()->GetCoordinates();
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

//-------------------------------------
void CXMapPainter2D::DrawScale(IBitmap *pBMP, int ScreenWidth, int ScreenHeight) {
	if(pBMP == NULL)
		return;
	if(CXOptions::Instance()->IsMapMovingManually())
		return;

	// set font
	pBMP->SetFont(CXOptions::Instance()->GetScaleFontSize(), false);

	// get scale dimensions
	int ScaleWidth = CXOptions::Instance()->GetScaleWidth();
	int ScaleHeight = CXOptions::Instance()->GetScaleHeight();
	if(m_MeterPerPixel > MAXMETERPERPIXEL)
		return;
	// get optimal scale display
	int exp = 1;
	int ScaleX = 1;
	int expFinal = exp;
	int ScaleXFinal = ScaleX;
	while(1.0*ScaleX*exp/m_MeterPerPixel < ScaleWidth) {
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
	int ScaleXPixel = static_cast<int>(1.0*ScaleX*exp/m_MeterPerPixel);
	// draw scale
	// first the black rectangle
	tIRect BlackRect((ScreenWidth - ScaleXPixel)/2, ScreenHeight - ScaleHeight - 5, ScaleXPixel, ScaleHeight);
	pBMP->DrawRect(BlackRect, CXRGB(0x00, 0x00, 0x00), CXRGB(0x00, 0x00, 0x00));
	// now the left yellow rectangle
	tIRect YellowRect((ScreenWidth - ScaleXPixel/2)/2, ScreenHeight - ScaleHeight - 5, ScaleXPixel/2 - ScaleXPixel/4, ScaleHeight);
	pBMP->DrawRect(YellowRect, CXRGB(0x00, 0x00, 0x00), CXRGB(0xff, 0xff, 0x00));
	// now the right yellow rectangle
	YellowRect.OffsetRect(ScaleXPixel/2, 0);
	pBMP->DrawRect(YellowRect, CXRGB(0x00, 0x00, 0x00), CXRGB(0xff, 0xff, 0x00));
	// draw scale description
	char buf[100];
	if(exp < 1000) {
		sprintf(buf, "%d m", ScaleX*exp);
	} else {
		sprintf(buf, "%d km", ScaleX*(exp/1000));
	}
	// calculate size of text
	tIRect TextRect = pBMP->CalcTextRectASCII(buf, 2, 2);
	// position it
	TextRect.OffsetRect(	ScreenWidth/2 - TextRect.GetWidth()/2,
							BlackRect.GetTop() - TextRect.GetHeight() - 1);
	// and draw it
	pBMP->DrawTextASCII(buf, TextRect, CXRGB(0x00, 0x00, 0x00), MAPBGCOLOR);
}


//-------------------------------------
void CXMapPainter2D::DrawCurrentPosition(IBitmap *pBMP, const CXNaviData &NaviData, const CXTransformationMatrix2D &TMCurrentPos) {
	if(pBMP == NULL)
		return;

	// draw current position
	CXCoorVector v;
	int X[4];
	int Y[4];
	double ArrowSize = 15.0;
	v = TMCurrentPos*CXCoorVector(0, ArrowSize);
	X[0] = v.GetIntX();
	Y[0] = v.GetIntY();
	v = TMCurrentPos*CXCoorVector(ArrowSize/2, -0.7*ArrowSize);
	X[1] = v.GetIntX();
	Y[1] = v.GetIntY();
	v = TMCurrentPos*CXCoorVector(0, -0.25*ArrowSize);
	X[2] = v.GetIntX();
	Y[2] = v.GetIntY();
	v = TMCurrentPos*CXCoorVector(-ArrowSize/2, -0.7*ArrowSize);
	X[3] = v.GetIntX();
	Y[3] = v.GetIntY();

	if(NaviData.HasFix())
		pBMP->Polygon(X, Y, 4, CXRGB(0x00, 0x00, 0x00), CXRGB(0x00, 0xFF, 0x00));
	else
		pBMP->Polygon(X, Y, 4, CXRGB(0x00, 0x00, 0x00), CXRGB(0xFF, 0x00, 0x00));
}

//-------------------------------------
void CXMapPainter2D::PaintPackground(IBitmap *pBMP, int Width, int Height) {
	if(pBMP == NULL)
		return;
	// clear wisible rect
	pBMP->DrawRect(tIRect(0,0, Width, Height), MAPBGCOLOR, MAPBGCOLOR);
}

//-------------------------------------
void CXMapPainter2D::OnInternalPaint(IBitmap *pBMP, int Width, int Height) {

	CXWriteLocker WL(&m_RWLock);

	CXExactTime StartTime;

	// get copy of navigation data
	CXNaviData NaviData = GetPosition();
	CXOptions *pOpt = CXOptions::Instance();

	// draw background
	PaintPackground(pBMP, Width, Height);

	// check if map
	if(CXPOWMMap::Instance() == NULL)
		return;

	CXExactTime StopDrawTime;

	CXExactTime StopDrawWays;
	CXExactTime StopTrackLog;
	CXExactTime StopScale;
	CXExactTime StopCompass;
	CXExactTime StopPos;


	// get zone
	int WayCount = 0;
	int xc = 0;
	int yc = 0;
	// compute coordinate
	CXCoor ImageCenter;
	CXCoor Position;
	if(pOpt->MustSnapToWay()) {
		// get coordinates from locator
		Position = NaviData.GetLocatedCoor();
	} else {
		// get corrected gps coordinates
		Position = NaviData.GetCorrectedGPSCoor();
	}
	if(pOpt->IsMapMovingManually()) {
		// get position from MapMovingDetails
		ImageCenter = CXMapMovingDetails::Instance()->GetPosition();
	} else {
		ImageCenter = Position;
		// set position also to MapMovingDetails
		CXMapMovingDetails::Instance()->SetPosition(Position);
	}
	double dLonImageCenter = ImageCenter.GetLon();
	double dLatImageCenter = ImageCenter.GetLat();

	// calc deviation for geographic north.
	CXCoor TmpCoor(dLonImageCenter + 0.001, dLatImageCenter);
	double dCos = 0;
	double dSin = 0;
	CalcAngle(ImageCenter, TmpCoor, dCos, dSin);

	// compute UTM coordinates of image center
	char UTMLetterCurrent = 0;
	double UTME = 0;
	double UTMN = 0;
	int UTMZoneCurrent = UTMZoneNone;
	LLtoUTM(WGS84, dLonImageCenter, dLatImageCenter, UTMZoneNone, UTMZoneCurrent, UTMLetterCurrent, UTME, UTMN);
	// OK, we have the coordinates of the image center
	// now compute coordinates of position

	// now compute all transformation matrices
	CXTransformationMatrix2D TMMap;				// for the map
	CXTransformationMatrix2D TMCompass;			// for the compass
	CXTransformationMatrix2D TMCurrentPos;		// for arrow indicating the current position

	CXUTMSpeed UTMSpeed = NaviData.GetUTMSpeed();

	double dSpeed = UTMSpeed.GetSpeed();
	if(pOpt->AutomaticZoom())
		ComputeZoomBySpeed(dSpeed);

	TMMap.Translate(-UTME, -UTMN);			// UTME, UTMN is center of visible universe
	// rotate
	if(pOpt->IsNorthing() || pOpt->IsMapMovingManually()) {
		xc = Width/2;
		yc = Height/2;
		TMCurrentPos.Rotate(UTMSpeed.GetCos(), UTMSpeed.GetSin());
		TMCurrentPos.Rotate(-UTMPI/2);
		// correct for geographic north
		TMMap.Rotate(dCos, -dSin);
		TMCurrentPos.Rotate(dCos, -dSin);
	} else {
		xc = Width/2;
		yc = 3*Height/4;
		TMMap.Rotate(UTMSpeed.GetCos(), -UTMSpeed.GetSin());
		TMCompass.Rotate(UTMSpeed.GetCos(), -UTMSpeed.GetSin());
		// rotate 90 to left, since 0 is east and we want it point to north
		TMMap.Rotate(UTMPI/2);
		TMCompass.Rotate(UTMPI/2);
		// correct for geographic north
		TMCompass.Rotate(dCos, -dSin);
	}

	TMMap.Scale(1.0/m_MeterPerPixel, -1.0/m_MeterPerPixel);		// do scaling (negative for y!)
	TMMap.Translate(xc, yc);									// display it centered on screen
	TMCompass.Scale(1, -1);										// do scaling (negative for y!)
	TMCurrentPos.Scale(1, -1);									// do scaling (negative for y!)

	// set transformation matrix also to MapMovingDetails
	CXMapMovingDetails::Instance()->SetMatrix(TMMap);

	// compute position of current position on map
	// we could always use the computations from the "if" branch,
	// but to avoid jitter of current position we use xc and yc for the "else" branch
	if(pOpt->IsMapMovingManually()) {
		int Zone = 0;
		LLtoUTM(WGS84, Position.GetLon(), Position.GetLat(), UTMZoneCurrent, Zone, UTMLetterCurrent, UTME, UTMN);
		CXCoorVector v = TMMap*CXCoorVector(UTME, UTMN);
		// adjust TMCurrentPos
		TMCurrentPos.Translate(v.GetIntX(), v.GetIntY());
	} else {
		// adjust TMCurrentPos
		TMCurrentPos.Translate(xc, yc);
	}

	// compute inverse to TMMap
	CXTransformationMatrix2D Inv = TMMap.Inverse();

	// compute coordinates of corners of the screen
	CXCoorVector TL = Inv*CXCoorVector(0,0);
	CXCoorVector TR = Inv*CXCoorVector(Width-1,0);
	CXCoorVector BL = Inv*CXCoorVector(0,Height-1);
	CXCoorVector BR = Inv*CXCoorVector(Width-1,Height-1);

	double dLonTL = 0; double dLatTL = 0;
	UTMtoLL(WGS84, TL.GetX(), TL.GetY(), UTMZoneCurrent, UTMLetterCurrent, dLonTL, dLatTL);
	double dLonTR = 0; double dLatTR = 0;
	UTMtoLL(WGS84, TR.GetX(), TR.GetY(), UTMZoneCurrent, UTMLetterCurrent, dLonTR, dLatTR);
	double dLonBL = 0; double dLatBL = 0;
	UTMtoLL(WGS84, BL.GetX(), BL.GetY(), UTMZoneCurrent, UTMLetterCurrent, dLonBL, dLatBL);
	double dLonBR = 0; double dLatBR = 0;
	UTMtoLL(WGS84, BR.GetX(), BR.GetY(), UTMZoneCurrent, UTMLetterCurrent, dLonBR, dLatBR);

	double dLonMin = Min(Min(dLonTL, dLonTR), Min(dLonBL, dLonBR));
	double dLonMax = Max(Max(dLonTL, dLonTR), Max(dLonBL, dLonBR));
	double dLatMin = Min(Min(dLatTL, dLatTR), Min(dLatBL, dLatBR));
	double dLatMax = Max(Max(dLatTL, dLatTR), Max(dLatBL, dLatBR));

	// now get map sections currently visible
	CXVisibleMapSectionDescr Descr(dLonMin, dLatMin, dLonMax, dLatMax, pOpt->GetZoomLevel());
	TMapSectionPtrArray MapSections = CXPOWMMap::Instance()->GetMapSectionsDisplay(Descr);

	size_t idx=0;
	// lock and prepare map sections
	CXBuffer<bool> LockedMapSections;
	LockedMapSections.Resize(MapSections.GetSize());
	size_t MapSectionSize = MapSections.GetSize();
	for(idx=0; idx<MapSectionSize; idx++) {
		CXMapSection *pMapSection = MapSections[idx].GetPtr();
		if(pMapSection->GetLoadStatus() == e_LSLoaded) {
			// lock
			pMapSection->Lock();
			// relocate
			pMapSection->RelocateUTM(UTMZoneCurrent);
			// compute display coordinates
			pMapSection->ComputeDisplayCoordinates(TMMap);
			LockedMapSections[idx] = true;
		} else {
			LockedMapSections[idx] = false;
		}
	}

	// relocate track log
	CXTrackLog::Instance()->RelocateUTM(UTMZoneCurrent);

	// draw layer for layer to avoid artefacts on map section borders
	MapSectionSize = MapSections.GetSize();
	for(char Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		for(idx=0; idx<MapSectionSize; idx++) {
			if(LockedMapSections[idx]) {
				CXMapSection *pMapSection = MapSections[idx].GetPtr();
				if(pMapSection != NULL) {
					// prepare drawing
					TWayBuffer *pWayBuffer = pMapSection->GetWayBuffer(Layer);
					if(pWayBuffer != NULL) {
						CXWay *pWay = NULL;
						//draw ways
						size_t ws = pWayBuffer->GetSize();
						for(size_t w=0; w<ws; w++) {
							pWay = (*pWayBuffer)[w];
							if (IsWayPossiblyVisible(pWay, Width, Height)) {
								E_KEYHIGHWAY_TYPE HighwayType = pWay->GetHighwayType();
								m_DrawWays[HighwayType]->Append(pWay);
								WayCount++;
							}
						}
					}
				}
			}
		}
		// since not all compilers can handle multiple for(size_t i=...)
		// we set size_t i=0; right here :-(((
		size_t i=0;
		// ok, now draw bg
		for(i=0; i< e_Highway_EnumCount; i++) {
			DrawWaysBg(pBMP, m_DrawWays[Order[i]], Order[i], Width, Height);
		}
		for(i=0; i< e_Highway_EnumCount; i++) {
			DrawWaysFg(pBMP, m_DrawWays[Order[i]], Order[i], Width, Height);
		}
		// clear arrays
		for(i=0; i<e_Highway_EnumCount; i++) {
			TWayBuffer *pBuffer = m_DrawWays[i];
			pBuffer->Clear();
		}
	}
	// now draw POIs
	// set font size for POIs
	pBMP->SetFont(pOpt->GetPOIFontSize(), false);
	if(pOpt->MustShowPOIs()) {
		// iterate through map sections
		for(idx=0; idx<MapSectionSize; idx++) {
			if(LockedMapSections[idx]) {
				CXMapSection *pMapSection = MapSections[idx].GetPtr();
				if(pMapSection != NULL) {
					// draw POIs
					const TPOINodeBuffer &POINodes = pMapSection->GetPOINodes();
					DrawPOIs(pBMP, POINodes, Width, Height);
				}
			}
		}
	}
	// now draw Places
	if(pOpt->MustShowCities()) {
		// iterate through map sections
		for(idx=0; idx<MapSectionSize; idx++) {
			if(LockedMapSections[idx]) {
				CXMapSection *pMapSection = MapSections[idx].GetPtr();
				if(pMapSection != NULL) {
					// draw Places
					const TPOINodeBuffer &PlaceNodes = pMapSection->GetPlaceNodes();
					DrawPlaces(pBMP, PlaceNodes, Width, Height);
				}
			}
		}
	}
	if(pOpt->IsDebugInfoFlagSet(CXOptions::e_DBGDrawMapSectionBorders)) {
		// draw border
		MapSectionSize = MapSections.GetSize();
		for(idx=0; idx<MapSectionSize; idx++) {
			CXMapSection *pMapSection = MapSections[idx].GetPtr();
			CXTOCMapSection TOC = pMapSection->GetTOC();
			double dLonMin = TOC.GetLonMin();
			double dLonMax = TOC.GetLonMax();
			double dLatMin = TOC.GetLatMin();
			double dLatMax = TOC.GetLatMax();

			int Zone = 0;
			char UTML = 0;
			double E0 = 0;
			double N0 = 0;

			LLtoUTM(WGS84, dLonMin, dLatMin, UTMZoneCurrent, Zone, UTML, E0, N0);
			CXCoorVector v0 = TMMap*CXCoorVector(E0, N0);

			LLtoUTM(WGS84, dLonMin, dLatMax, UTMZoneCurrent, Zone, UTML, E0, N0);
			CXCoorVector v1 = TMMap*CXCoorVector(E0, N0);

			LLtoUTM(WGS84, dLonMax, dLatMax, UTMZoneCurrent, Zone, UTML, E0, N0);
			CXCoorVector v2 = TMMap*CXCoorVector(E0, N0);

			LLtoUTM(WGS84, dLonMax, dLatMin, UTMZoneCurrent, Zone, UTML, E0, N0);
			CXCoorVector v3 = TMMap*CXCoorVector(E0, N0);

			pBMP->SetPen(CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00)));
			pBMP->DrawLine(v0.GetIntX(), v0.GetIntY(), v1.GetIntX(), v1.GetIntY());
			pBMP->DrawLine(v1.GetIntX(), v1.GetIntY(), v2.GetIntX(), v2.GetIntY());
			pBMP->DrawLine(v2.GetIntX(), v2.GetIntY(), v3.GetIntX(), v3.GetIntY());
			pBMP->DrawLine(v3.GetIntX(), v3.GetIntY(), v0.GetIntX(), v0.GetIntY());
		}
	}
	StopDrawWays.SetNow();

	// unlockmap sections
	for(idx=0; idx<MapSections.GetSize(); idx++) {
		if(LockedMapSections[idx]) {
			CXMapSection *pMapSection = MapSections[idx].GetPtr();
			// unlock
			pMapSection->Unlock();
		}
	}
	
	// draw TrackLog if neccessary
	if(pOpt->MustShowTrackLog()) {
		DrawTrackLog(pBMP, TMMap);
	}
	StopTrackLog.SetNow();

	// draw compass if necessary
	if(pOpt->MustShowCompass()) {
		DrawCompass(pBMP, TMCompass);
	}
	StopCompass.SetNow();

	// draw scale if necessary
	if(pOpt->MustShowScale()) {
		DrawScale(pBMP, Width, Height);
	}
	StopScale.SetNow();

	// draw current position
	DrawCurrentPosition(pBMP, NaviData, TMCurrentPos);

	// draw computed positions if neccessary
	if(pOpt->IsDebugInfoFlagSet(CXOptions::e_DBGDrawPositions)) {
		CXCoor Coor = NaviData.GetGPSCoor();
		Coor.RelocateUTM(UTMZoneCurrent);
		CXCoorVector GPSCoor = TMMap*CXCoorVector(Coor.GetUTMEasting(), Coor.GetUTMNorthing());
		pBMP->DrawCircle(GPSCoor.GetIntX(), GPSCoor.GetIntY(), 3, CXRGB(0x00, 0x00, 0x00), CXRGB(0xFF, 0x00, 0x00));

		Coor = NaviData.GetCorrectedGPSCoor();
		Coor.RelocateUTM(UTMZoneCurrent);
		CXCoorVector CorrectedGPSCoor = TMMap*CXCoorVector(Coor.GetUTMEasting(), Coor.GetUTMNorthing());
		pBMP->DrawCircle(CorrectedGPSCoor.GetIntX(), CorrectedGPSCoor.GetIntY(), 3, CXRGB(0x00, 0x00, 0x00), CXRGB(0x00, 0xFF, 0x00));

		Coor = NaviData.GetLocatedCoor();
		Coor.RelocateUTM(UTMZoneCurrent);
		CXCoorVector LocatedCoor = TMMap*CXCoorVector(Coor.GetUTMEasting(), Coor.GetUTMNorthing());
		pBMP->DrawCircle(LocatedCoor.GetIntX(), LocatedCoor.GetIntY(), 3, CXRGB(0x00, 0x00, 0x00), CXRGB(0x00, 0x00, 0xFF));
	}

	StopPos.SetNow();

	if(pOpt->IsDebugInfoFlagSet(CXOptions::e_DBGDrawTimes)) {
		// set font
		pBMP->SetFont(pOpt->GetDebugFontSize(), false);
		char buf[200];
		snprintf(	buf, sizeof(buf), "Wy:%ld (%d) TL:%ld",
					StopDrawWays-StartTime, WayCount, 
					StopTrackLog-StopDrawWays);
		CXStringASCII ttt = buf;
		tIRect TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
		TextRect.OffsetRect(0, pOpt->GetCompassSize() + 20);
		int bottom = TextRect.GetBottom();
		pBMP->DrawTextASCII(ttt, TextRect, MAPFGCOLOR, MAPBGCOLOR); 
		snprintf(buf, sizeof(buf), "LocatorTime: %d", CXDebugInfo::Instance()->GetLocatorTime());
		ttt = buf;
		TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
		TextRect.OffsetRect(0, bottom);
		pBMP->DrawTextASCII(ttt, TextRect, MAPFGCOLOR, MAPBGCOLOR); 
		bottom = TextRect.GetBottom();
		snprintf(buf, sizeof(buf), "Zoom: %d", pOpt->GetZoomLevel());
		ttt = buf;
		TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
		TextRect.OffsetRect(0, bottom);
		pBMP->DrawTextASCII(ttt, TextRect, MAPFGCOLOR, MAPBGCOLOR); 
		bottom = TextRect.GetBottom();
		snprintf(buf, sizeof(buf), "m/pixel: %0.2f", m_MeterPerPixel);
		ttt = buf;
		TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
		TextRect.OffsetRect(0, bottom);
		pBMP->DrawTextASCII(ttt, TextRect, MAPFGCOLOR, MAPBGCOLOR); 
		bottom = TextRect.GetBottom();
		snprintf(buf, sizeof(buf), "MB: %0.2f", 1.0*GetFreeMem()/1024/1024);
		ttt = buf;
		TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
		TextRect.OffsetRect(0, bottom);
		pBMP->DrawTextASCII(ttt, TextRect, MAPFGCOLOR, MAPBGCOLOR); 
	}

	StopDrawTime.SetNow();
	CXDebugInfo::Instance()->SetDrawTime(StopDrawTime - StartTime);
}

//-------------------------------------
void CXMapPainter2D::ComputeZoomBySpeed(double dSpeed) {
	double dNewMeterPerPixel = m_AutoZoomLevels.GetHysterezisValue(dSpeed);
	dNewMeterPerPixel  = Min(MAXMETERPERPIXEL, Max(dNewMeterPerPixel, MINMETERPERPIXEL));
	if(dNewMeterPerPixel != m_MeterPerPixel) {
		m_MeterPerPixel = dNewMeterPerPixel;
		UpdateZoomLevel();
	}
}

//-------------------------------------
bool CXMapPainter2D::ZoomIn() {
	CXWriteLocker WL(&m_RWLock);
	double dNewMeterPerPixel = m_MeterPerPixel / ZoomFactor;
	m_MeterPerPixel = Min(MAXMETERPERPIXEL, Max(dNewMeterPerPixel, MINMETERPERPIXEL));
	UpdateZoomLevel();
	return true;
}

//-------------------------------------
bool CXMapPainter2D::ZoomOut() {
	CXWriteLocker WL(&m_RWLock);
	double dNewMeterPerPixel = m_MeterPerPixel * ZoomFactor;
	m_MeterPerPixel = Min(MAXMETERPERPIXEL, Max(dNewMeterPerPixel, MINMETERPERPIXEL));
	UpdateZoomLevel();
	return true;
}

//-------------------------------------
void CXMapPainter2D::UpdateZoomLevel() {
	if(m_MeterPerPixel <= 4)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_0);
	else if(m_MeterPerPixel <= 8)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_1);
	else if(m_MeterPerPixel <= 14)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_2);
	else if(m_MeterPerPixel <= 25)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_3);
	else if(m_MeterPerPixel <= 50)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_4);
	else if(m_MeterPerPixel <= 100)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_5);
	else if(m_MeterPerPixel <= 220)
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_6);
	else
		CXOptions::Instance()->SetZoomLevel(e_ZoomLevel_7);
	// scale pens
	m_PenHolder.ScalePens(3.0/m_MeterPerPixel);
}
