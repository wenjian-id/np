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
#include "CXDeviceContext.hpp"

#include <math.h>

const double ZoomFactor                 = 1.2;  ///< oiu
const double MAXMETERPERPIXEL           = 500;  ///< 500 m/pixel
const double MINMETERPERPIXEL           = 0.1;  ///< 0.1 m/pixel
static const int POICOUNTHORZ           = 16;   ///< Number of POIs in a row in bitmap file.
static const int POICOUNTVERT           = 16;   ///< Number of POIS in a column in bitmap file.
static const int PLACECOUNTHORZ         = 4;    ///< Number of places in a row in bitmap file.
static const int PLACECOUNTVERT         = 1;    ///< Number of places in a column in bitmap file.
static const CXRGB COLOR_RED(0xff, 0x00, 0x00); ///< oiu

E_WAY_TYPE WayOrder[e_Way_EnumCount] = {
    e_Way_Unknown,
    e_Way_Fading,
    e_Way_Water_Thin,
    e_Way_Water_Thick,
    e_Way_Railway_Thin,
    e_Way_Railway_Thick,
    e_Way_LivingStreet,
    e_Way_Steps,
    e_Way_Pedestrian,
    e_Way_Footway,
    e_Way_Cycleway,
    e_Way_Bridleway,
    e_Way_Service,
    e_Way_Residential,
    e_Way_Track,
    e_Way_PrimaryLink,
    e_Way_TrunkLink,
    e_Way_MotorwayLink,
    e_Way_Unclassified,
    e_Way_Tertiary,
    e_Way_Secondary,
    e_Way_Primary,
    e_Way_Trunk,
    e_Way_Motorway,
    e_Way_BorderThick,
    e_Way_BorderMedium,
    e_Way_BorderThin,
    e_Way_Path,
};

E_AREA_TYPE AreaOrder[e_Area_EnumCount] = {
    e_Area_None,
    e_Area_Water,
    e_Area_Wood,
};

//----------------------------------------------------------------------------
//-------------------------------------
CXMapPainter2D::CXMapPainter2D() :
    m_MeterPerPixel(3),
    m_RequestedMeterPerPixel(m_MeterPerPixel),
    m_pPlaceBMP(NULL),
    m_pTargetBMP(NULL)
{
    size_t i=0;
    for(i=0; i<e_Way_EnumCount; i++) {
        m_DrawWays.Append(new TWayBuffer());
    }
    for(i=0; i<e_Area_EnumCount; i++) {
        m_DrawAreas.Append(new TAreaBuffer());
    }
    UpdateZoomLevel();
    // create hysterezis
    CXStringASCII AutoZoomString = CXOptions::Instance()->GetAutomaticZoomString();
    double HystMaxOffsetAbs = CXOptions::Instance()->GetHystMaxOffsetAbs();
    double HystMaxOffsetRel = CXOptions::Instance()->GetHystMaxOffsetRel();
    bool oAutoZoom = ExtractFirstToken(AutoZoomString, ';') == "ON";
    while(!AutoZoomString.IsEmpty()) {
        double dSpeed = ExtractFirstToken(AutoZoomString, ';').ToDouble();
        double dMeterPerPixel = ExtractFirstToken(AutoZoomString, ';').ToDouble();
        // compute delta
        double delta = Min(HystMaxOffsetAbs, HystMaxOffsetRel*dSpeed);
        m_AutoZoomLevels.AddInterval(dSpeed-delta, dSpeed+delta, dMeterPerPixel);
    }
    CXOptions::Instance()->SetAutomaticZoomFlag(oAutoZoom);
}

//-------------------------------------
CXMapPainter2D::~CXMapPainter2D() {
    // delete arrays
    size_t i=0;
    for(i=0; i<e_Way_EnumCount; i++) {
        TWayBuffer *pBuffer = m_DrawWays[i];
        delete pBuffer;
    }
    m_DrawWays.Clear();
    for(i=0; i<e_Area_EnumCount; i++) {
        TAreaBuffer *pBuffer = m_DrawAreas[i];
        delete pBuffer;
    }
    m_DrawAreas.Clear();

    // delete BMPs
    for(i=0; i<m_POIBMPs.GetSize(); i++) {
        delete m_POIBMPs[i];
    }
    delete m_pPlaceBMP;
    m_pPlaceBMP = NULL;
    delete m_pTargetBMP;
    m_pTargetBMP = NULL;
}

//-------------------------------------
void CXMapPainter2D::OnBuffersCreated(CXDeviceContext *pDC, int /*Width*/, int /*Height*/) {
    // reload POI bitmaps
    int POIDisplaySize = CXOptions::Instance()->GetPOIDisplaySize();
    // iterate through BMPs
    if(m_POIBMPs.GetSize() == 0) {
        // create bitmaps
        for(size_t i=0; i<1; i++) {
            CXBitmap *pBMP = new CXBitmap();
            m_POIBMPs.Append(pBMP);
            pBMP->Create(pDC, POIDisplaySize*POICOUNTHORZ, POIDisplaySize*POICOUNTVERT);
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
            pBMP->Create(pDC, POIDisplaySize*POICOUNTHORZ, POIDisplaySize*POICOUNTVERT);
            pBMP->LoadFromFile(FileName);
        }
    }
    if(m_pPlaceBMP == NULL) {
        // create bitmap
        m_pPlaceBMP = new CXBitmap();
        m_pPlaceBMP->Create(pDC, POIDisplaySize*PLACECOUNTHORZ, POIDisplaySize*PLACECOUNTVERT);
        CXStringASCII FileName = CXOptions::Instance()->GetDirectoryIcons();
        FileName += "places.bmp";
        m_pPlaceBMP->LoadFromFile(FileName);
    } else {
        // bitmaps already created. reload
        CXStringASCII FileName = m_pPlaceBMP->GetFileName();
        m_pPlaceBMP->Create(pDC, POIDisplaySize*PLACECOUNTHORZ, POIDisplaySize*PLACECOUNTVERT);
        m_pPlaceBMP->LoadFromFile(FileName);
    }
    if(m_pTargetBMP == NULL) {
        // create bitmap
        m_pTargetBMP = new CXBitmap();
        m_pTargetBMP->Create(pDC, POIDisplaySize, POIDisplaySize*2);
        CXStringASCII FileName = CXOptions::Instance()->GetDirectoryIcons();
        FileName += "target.bmp";
        m_pTargetBMP->LoadFromFile(FileName);
    } else {
        // bitmaps already created. reload
        CXStringASCII FileName = m_pTargetBMP->GetFileName();
        m_pTargetBMP->Create(pDC, POIDisplaySize, POIDisplaySize*2);
        m_pTargetBMP->LoadFromFile(FileName);
    }
}

//-------------------------------------
bool CXMapPainter2D::IsWayPossiblyVisible(CXWay *pWay, int Width, int Height) {
    if(pWay == NULL)
        return false;

    int x0 = 0;
    int y0 = 0;
    size_t NodeCount = pWay->GetNodeList()->GetNodeCount();
    for(size_t i=0; i<NodeCount; i++) {
        CXNode *pNode = pWay->GetNodeList()->GetNode(i);
        int x = pNode->GetDisplayX();
        int y = pNode->GetDisplayY();
        // check if it is worth drawing
        if( ((x0 < 0) && (x < 0)) ||
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

/// \todo resize on demand?
int pX[1024000];
int pY[1024000];

//-------------------------------------
void CXMapPainter2D::DrawWay(IBitmap *pBMP, CXWay *pWay, int Width, int Height) {
    if(pWay == NULL)
        return;
    size_t NodeCount = pWay->GetNodeList()->GetNodeCount();
    int x0 = 0;
    int y0 = 0;
    bool oLastWasTerminator = false;
    bool oTerminator = false;
    size_t Count = 0;
    for(size_t i=0; i<NodeCount; i++) {
        CXNode *pNode = pWay->GetNodeList()->GetNode(i);
        oTerminator = (pNode->IsTerminator());
        int x = pNode->GetDisplayX();
        int y = pNode->GetDisplayY();
        if(!oTerminator && !oLastWasTerminator) {
            if(i != 0) {
                // check if it is worth drawing
                if( ((x0 < 0) && (x < 0)) ||
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
void CXMapPainter2D::DrawWaysBg(IBitmap *pBMP, TWayBuffer *pWays, E_WAY_TYPE eWayType, int Width, int Height) {
    if(pWays == NULL)
        return;
    // get pen for this type of way
    CXPen *pPen = m_PenHolder.GetScaledPenBg(eWayType);
    bool OSMValiEnabled = CXOptions::Instance()->GetOSMValiFlags() != 0;
    size_t cnt = pWays->GetSize();
    if((cnt != 0) && (pPen != NULL)) {
        // create red pen
        CXPen RedPen = *pPen;
        RedPen.SetColor(COLOR_RED);
        // set normal pen
        pBMP->SetPen(*pPen);
        // now iterate through ways
        for(size_t i=0; i<cnt; i++) {
            CXWay *pWay = (*pWays)[i];
            bool oUseRedPen = OSMValiEnabled && !pWay->IsOSMValiOK();
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
void CXMapPainter2D::DrawWaysFg(IBitmap *pBMP, TWayBuffer *pWays, E_WAY_TYPE eWayType, int Width, int Height) {
    if(pWays == NULL)
        return;
    // get pen for this type of way
    CXPen *pPen = m_PenHolder.GetScaledPenFg(eWayType);
    bool OSMValiEnabled = CXOptions::Instance()->GetOSMValiFlags() != 0;
    size_t cnt = pWays->GetSize();
    if((cnt != 0) && (pPen != NULL)) {
        // create red pen
        CXPen RedPen = *pPen;
        RedPen.SetColor(COLOR_RED);
        // set normal pen
        pBMP->SetPen(*pPen);
        // now iterate through ways
        for(size_t i=0; i<cnt; i++) {
            CXWay *pWay = (*pWays)[i];
            bool oUseRedPen = OSMValiEnabled && !pWay->IsOSMValiOK();
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
void CXMapPainter2D::DrawOneways(IBitmap *pBMP, TWayBuffer *pWays, E_WAY_TYPE eWayType, int Width, int Height) {
    // skip if nothing to draw
    /// \todo what does this mean?
    if( (pWays == NULL) ||
        (   (eWayType != e_Way_Motorway) && (eWayType != e_Way_MotorwayLink) &&
            (eWayType != e_Way_Trunk) && (eWayType != e_Way_TrunkLink) && (eWayType != e_Way_Primary) &&
            (eWayType != e_Way_PrimaryLink) && (eWayType != e_Way_Secondary) && (eWayType != e_Way_Tertiary) &&
            (eWayType != e_Way_Unclassified) && (eWayType != e_Way_Residential) && (eWayType != e_Way_Service) &&
            (eWayType != e_Way_Cycleway) && (eWayType != e_Way_LivingStreet)
        )
      )
    {
        return;
    }
    size_t cnt = pWays->GetSize();
    if(cnt == 0)
        return;
    // get pen for this type of way
    CXPen *pPenFg = m_PenHolder.GetScaledPenFg(eWayType);
    CXPen *pPenBg = m_PenHolder.GetScaledPenBg(eWayType);
    // take background pen for width
    // if this does not succeed take foreground pen width
    double ArrowSize = 0;
    if(pPenBg != NULL) {
        ArrowSize = pPenBg->GetWidth();
    } else if(pPenFg != NULL) {
        ArrowSize = pPenFg->GetWidth();
    } else {
        return;
    }
    // now iterate through ways
    for(size_t i=0; i<cnt; i++) {
        CXWay *pWay = (*pWays)[i];
        // check if oneway
        if(pWay->GetOneway() != e_Oneway_None) {
            size_t NodeCount = pWay->GetNodeList()->GetNodeCount();
            // get first node
            CXNode *pNode = pWay->GetNodeList()->GetNode(0);
            int x0 = pNode->GetDisplayX();
            int y0 = pNode->GetDisplayY();
            int prev_x = x0;
            int prev_y = y0;
            // now iterate through segments
            for(size_t j=1; j<NodeCount; j++) {
                pNode = pWay->GetNodeList()->GetNode(j);
                int x1 = pNode->GetDisplayX();
                int y1 = pNode->GetDisplayY();
                int x = (x0+x1)/2;
                int y = (y0+y1)/2;
                // skip if out of screen
                if((x >= 0) && (x <= Width) && (y >= 0) && (y <= Height)) {
                    // skip if too close
                    /// \todo why NodeCount - 1 ?
                    /// \todo 900 configurable

                    if( (((x-prev_x)*(x-prev_x) + (y-prev_y)*(y-prev_y)) > 30*30) &&
                        ((j < NodeCount - 1) || (((x-x1)*(x-x1) + (y-y1)*(y-y1)) > 30*30)))
                    {
                        // compute arrow position
                        CXTransformationMatrix2D TMOneway;
                        double seglen=sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1));
                        /// \todo minseglen
                        const int minseglen = 5;
                        if(seglen >= minseglen) {
                            if(pWay->GetOneway() == e_Oneway_Inverse)
                                TMOneway.Rotate((y0-y1)/seglen, (x1-x0)/seglen);
                            else
                                TMOneway.Rotate((y1-y0)/seglen, (x0-x1)/seglen);
                            TMOneway.Translate(x, y);
                            // draw directional arrow
                            CXCoorVector v;
                            int X[3];
                            int Y[3];
                            v = TMOneway*CXCoorVector(0, ArrowSize);
                            X[0] = v.GetIntX();
                            Y[0] = v.GetIntY();
                            v = TMOneway*CXCoorVector(0.4*ArrowSize, -0.4*ArrowSize);
                            X[1] = v.GetIntX();
                            Y[1] = v.GetIntY();
                            v = TMOneway*CXCoorVector(-0.4*ArrowSize, -0.4*ArrowSize);
                            X[2] = v.GetIntX();
                            Y[2] = v.GetIntY();
                            /// \todo colors
                            pBMP->Polygon(X, Y, 3, CXRGB(0x00, 0x00, 0xFF), CXRGB(0xFF, 0xFF, 0xFF));
                            prev_x = x;
                            prev_y = y;
                        }
                    }
                }
                x0 = x1;
                y0 = y1;
            }
        }
    }
}

//-------------------------------------
void CXMapPainter2D::DrawAreas(IBitmap *pBMP, IBitmap *pTmpBMP, TAreaBuffer *pAreas, E_AREA_TYPE eAreaType) {
    if(pAreas == NULL)
        return;

    CXRGB Color = m_AreaColorHolder.GetColor(eAreaType);
    size_t cnt = pAreas->GetSize();
    if(cnt == 0)
        return;

    // check if we must draw some holes
    bool oHolesPresent = false;
    for(size_t a=0; a<cnt; a++) {
        CXArea *pArea = (*pAreas)[a];
        if(pArea->GetHoleCount() != 0) {
            oHolesPresent = true;
            break;
        }
    }

    int xMin = 0;
    int xMax = 0;
    int yMin = 0;
    int yMax = 0;
	int Width = pBMP->GetWidth();
	int Height = pBMP->GetHeight();
    bool oFirst = true;
    IBitmap *pDrawBMP = pBMP;
    if(oHolesPresent) {
        pDrawBMP = pTmpBMP;
        tIRect ClientRect(0,0,Width,Height);
        // draw backgound
        pDrawBMP->DrawRect(ClientRect, COLOR_TRANSPARENT, COLOR_TRANSPARENT);
    }
    // now iterate through Areas
    for(size_t i=0; i<cnt; i++) {
        CXArea *pArea = (*pAreas)[i];
        CXOrderedNodeList *pOuterNodeList = pArea->GetOuterNodeList();
        size_t NodeCount = pOuterNodeList->GetNodeCount();
        for(size_t j=0; j<NodeCount; j++) {
            CXNode *pNode = pOuterNodeList->GetNode(j);
            int x = pNode->GetDisplayX();
            int y = pNode->GetDisplayY();
            pX[j] = x;
            pY[j] = y;
            if(oFirst) {
                xMin = x;
                xMax = x;
                yMin = y;
                yMax = y;
                oFirst = false;
            } else {
                xMin = Min(xMin, x);
                xMax = Max(xMax, x);
                yMin = Min(yMin, y);
                yMax = Max(yMax, y);
            }
        }
        pDrawBMP->Polygon(pX, pY, NodeCount, Color, Color);
        for(size_t h=0; h<pArea->GetHoleCount(); h++) {
            CXOrderedNodeList *pHole = pArea->GetHole(h);
            size_t HoleNodeCount = pHole->GetNodeCount();
            for(size_t j=0; j<HoleNodeCount; j++) {
                CXNode *pNode = pHole->GetNode(j);
                pX[j] = pNode->GetDisplayX();
                pY[j] = pNode->GetDisplayY();
            }
            pDrawBMP->Polygon(pX, pY, HoleNodeCount, COLOR_TRANSPARENT, COLOR_TRANSPARENT);
        }
    }
    if(oHolesPresent) {
        // DrawTransparent only for modified region
		// make sure we do not exceed width and height, or on windows XP and mobile
		// we won't see anything!
		xMin = Max(0, Min(xMin, Width-1));
		yMin = Max(0, Min(yMin, Height-1));
		xMax = Max(0, Min(xMax, Width-1));
		yMax = Max(0, Min(yMax, Height-1));
        pBMP->DrawTransparent(pDrawBMP, xMin, yMin, xMin, yMin, xMax-xMin+1, yMax-yMin+1, COLOR_TRANSPARENT);
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
    CXOptions *pOptions = CXOptions::Instance();
    CXPOIVisibilityDescriptor POIVisDescr = pOptions->GetPOIVisibilityDescriptorByRef();
    int POIDisplaySize = pOptions->GetPOIDisplaySize();
    // iterate through POIs
    for(size_t n=0; n<POINodes.GetSize(); n++) {
        CXPOINode *pNode = POINodes[n];
        int x = pNode->GetDisplayX();
        int y = pNode->GetDisplayY();
        // check if visible
        if((x >= -POIDisplaySize/2) && (x < ScreenWidth+POIDisplaySize/2) && (y >= -POIDisplaySize/2) && (y < ScreenHeight+POIDisplaySize/2)) {
            for(size_t i=0; i<pNode->GetPOITypeCount(); i++) {
                E_POI_TYPE ePOIType = pNode->GetPOIType(i);
                bool oVisible = POIVisDescr.MustShowAll() || POIVisDescr.MustShowPOIType(ePOIType);
                if(oVisible) {
                    size_t idx = 0;
                    size_t row = 0;
                    size_t col = 0;
                    ComputePOIBMP(ePOIType, idx, row, col);
                    // draw POI bitmap
                    if(idx < m_POIBMPs.GetSize()) {
                        CXBitmap *pPOIBMP = m_POIBMPs[idx];
                        // Bitmap loaded
                        pBMP->DrawTransparent(  pPOIBMP,
                                                x-POIDisplaySize/2, y-POIDisplaySize/2,
                                                col*POIDisplaySize, row*POIDisplaySize,
                                                POIDisplaySize, POIDisplaySize,
                                                COLOR_TRANSPARENT);
                    }
                    // draw name
                    CXStringUTF8 Name = pNode->GetName();
                    if(!Name.IsEmpty()) {
                        tIRect NameRect = pBMP->CalcTextRectUTF8(Name, 0, 0);
                        NameRect.OffsetRect(x - NameRect.GetWidth()/2, y - POIDisplaySize/2 - NameRect.GetHeight());
                        switch(pOptions->GetPOIBGType()) {
                            case e_BG_AREA:     pBMP->DrawTextUTF8(Name, NameRect, MAPPOITEXTCOLOR, MAPPOIBGCOLOR); break;
                            case e_BG_GLOW:     pBMP->DrawGlowTextUTF8(Name, NameRect, MAPPOITEXTCOLOR, MAPPOIBGCOLOR, 1); break;
                        }
                    }
                }
            }
        }
    }
}

//-------------------------------------
void CXMapPainter2D::DrawPlaces(IBitmap *pBMP, const TPOINodeBuffer &PlaceNodes, int ScreenWidth, int ScreenHeight) {

    CXOptions *pOptions = CXOptions::Instance();
    int FontSizeSmall = pOptions->GetCitySmallFontSize();
    int FontSizeMedium = pOptions->GetCityMediumFontSize();
    int FontSizeLarge = pOptions->GetCityLargeFontSize();
    int POIDisplaySize = pOptions->GetPOIDisplaySize();

    // iterate through Places
    for(size_t n=0; n<PlaceNodes.GetSize(); n++) {
        CXPOINode *pNode = PlaceNodes[n];
        int x = pNode->GetDisplayX();
        int y = pNode->GetDisplayY();
        // check if visible
        if((x >= -POIDisplaySize/2) && (x < ScreenWidth+POIDisplaySize/2) && (y >= -POIDisplaySize/2) && (y < ScreenHeight+POIDisplaySize/2)) {
            size_t col = pNode->GetPlaceType();
            size_t row = 0;
            // draw POI bitmap
            pBMP->DrawTransparent(  m_pPlaceBMP,
                                    x-POIDisplaySize/2, y-POIDisplaySize/2,
                                    col*POIDisplaySize, row*POIDisplaySize,
                                    POIDisplaySize, POIDisplaySize,
                                    COLOR_TRANSPARENT);
            // draw name
            CXStringUTF8 Name = pNode->GetName();
            bool oBold = false;
            if(!Name.IsEmpty()) {
                // set font size for Places
                int FontSize = 16;
                switch(pNode->GetPlaceType()) {
                    case e_MapPlace_Small:  FontSize = FontSizeSmall; oBold = false; break;
                    case e_MapPlace_Medium: FontSize = FontSizeMedium; oBold = true; break;
                    case e_MapPlace_Large:  FontSize = FontSizeLarge; oBold = true; break;
                    default:                break;
                }
                pBMP->SetFont(FontSize, oBold);
                tIRect NameRect = pBMP->CalcTextRectUTF8(Name, 0, 0);
                NameRect.OffsetRect(x - NameRect.GetWidth()/2, y - POIDisplaySize/2 - NameRect.GetHeight());
                switch(pOptions->GetCityBGType()) {
                    case e_BG_AREA:     pBMP->DrawTextUTF8(Name, NameRect, MAPCITYTEXTCOLOR, MAPCITYBGCOLOR); break;
                    case e_BG_GLOW:     pBMP->DrawGlowTextUTF8(Name, NameRect, MAPCITYTEXTCOLOR, MAPCITYBGCOLOR, 1); break;
                }
            }
        }
    }
}

//-------------------------------------
void CXMapPainter2D::DrawTrackLog(IBitmap *pBMP, const CXTransformationMatrix2D &TMMap) {
    if(pBMP == NULL)
        return;

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
        CXCoorVector v;
        for(size_t i=0; i<Size; i++) {
            CXCoor *pCoor = CoorBuffer[i];
            v = TMMap*CXCoorVector(pCoor->GetUTMEasting(), pCoor->GetUTMNorthing());
            pX[i] = v.GetIntX();
            pY[i] = v.GetIntY();
        }

        pBMP->DrawLine(Size, pX, pY);
        delete [] pX;
        delete [] pY;
    }
}

//-------------------------------------
void CXMapPainter2D::DrawScale(IBitmap *pBMP, int ScreenWidth, int ScreenHeight) {
    if(pBMP == NULL)
        return;
    CXOptions *pOptions = CXOptions::Instance();
    if(pOptions->IsMapMovingManually())
        return;

    // set font
    pBMP->SetFont(pOptions->GetScaleFontSize(), false);

    // get scale dimensions
    int ScaleWidth = pOptions->GetScaleWidth();
    int ScaleHeight = pOptions->GetScaleHeight();
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
    TextRect.OffsetRect(    ScreenWidth/2 - TextRect.GetWidth()/2,
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
void CXMapPainter2D::OnInternalPaint(IBitmap *pBMP, IBitmap *pTmpBMP, int Width, int Height) {

    CXExactTime StartTime;

    // get copy of navigation data
    CXNaviData NaviData = GetPosition();
    CXOptions *pOpt = CXOptions::Instance();
    double dReqMPP = GetRequestedMeterPerPixel();
    if(!pOpt->AutomaticZoom() && (dReqMPP != m_MeterPerPixel)) {
        m_MeterPerPixel = dReqMPP;
        UpdateZoomLevel();
    }

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
    int AreaCount = 0;
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
    CXDirection Dir;
    ComputeRelativeUTMAngle(ImageCenter, TmpCoor, Dir);

    // compute UTM coordinates of image center
    char UTMLetterCurrent = 0;
    double UTME = 0;
    double UTMN = 0;
    int UTMZoneCurrent = UTMZoneNone;
    LLtoUTM(WGS84, dLonImageCenter, dLatImageCenter, UTMZoneNone, UTMZoneCurrent, UTMLetterCurrent, UTME, UTMN);
    // OK, we have the coordinates of the image center
    // now compute coordinates of position

    // now compute all transformation matrices
    CXTransformationMatrix2D TMMap;             // for the map
    CXTransformationMatrix2D TMCompass;         // for the compass
    CXTransformationMatrix2D TMCurrentPos;      // for arrow indicating the current position

    CXUTMSpeed UTMSpeed = NaviData.GetUTMSpeed();

    double dSpeed = UTMSpeed.GetSpeed();
    if(pOpt->AutomaticZoom()) {
        SetRequestedMeterPerPixel(m_MeterPerPixel);
        ComputeZoomBySpeed(dSpeed);
    }

    TMMap.Translate(-UTME, -UTMN);          // UTME, UTMN is center of visible universe
    // rotate
    if(pOpt->IsNorthing() || pOpt->IsMapMovingManually()) {
        xc = Width/2;
        yc = Height/2;
        TMCurrentPos.Rotate(UTMSpeed.GetDirection());
        TMCurrentPos.Rotate(-UTMPI/2);
        // correct for geographic north
        TMMap.Rotate(-Dir);
        TMCurrentPos.Rotate(-Dir);
    } else {
        xc = Width/2;
        yc = 3*Height/4;
        TMMap.Rotate(-UTMSpeed.GetDirection());
        TMCompass.Rotate(-UTMSpeed.GetDirection());
        // rotate 90 to left, since 0 is east and we want it point to north
        TMMap.Rotate(UTMPI/2);
        TMCompass.Rotate(UTMPI/2);
        // correct for geographic north
        TMCompass.Rotate(-Dir);
    }

    TMMap.Scale(1.0/m_MeterPerPixel, -1.0/m_MeterPerPixel);     // do scaling (negative for y!)
    TMMap.Translate(xc, yc);                                    // display it centered on screen
    TMCompass.Scale(1, -1);                                     // do scaling (negative for y!)
    TMCurrentPos.Scale(1, -1);                                  // do scaling (negative for y!)

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
                    // draw areas
                    TAreaBuffer *pAreaBuffer = pMapSection->GetAreaBuffer(Layer);
                    if(pAreaBuffer != NULL) {
                        CXArea *pArea = NULL;
                        //draw Areas
                        size_t ws = pAreaBuffer->GetSize();
                        for(size_t w=0; w<ws; w++) {
                            pArea = (*pAreaBuffer)[w];
                            E_AREA_TYPE eAreaType = pArea->GetAreaType();
                            m_DrawAreas[eAreaType]->Append(pArea);
                            AreaCount++;
                        }
                    }
                    // draw ways
                    TWayBuffer *pWayBuffer = pMapSection->GetWayBuffer(Layer);
                    if(pWayBuffer != NULL) {
                        CXWay *pWay = NULL;
                        //draw ways
                        size_t ws = pWayBuffer->GetSize();
                        for(size_t w=0; w<ws; w++) {
                            pWay = (*pWayBuffer)[w];
                            if (IsWayPossiblyVisible(pWay, Width, Height)) {
                                E_WAY_TYPE eWayType = pWay->GetWayType();
                                m_DrawWays[eWayType]->Append(pWay);
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
        // draw areas
        for(i=0; i< e_Area_EnumCount; i++) {
            DrawAreas(pBMP, pTmpBMP, m_DrawAreas[AreaOrder[i]], AreaOrder[i]);
        }
        // now draw way bg
        for(i=0; i< e_Way_EnumCount; i++) {
            DrawWaysBg(pBMP, m_DrawWays[WayOrder[i]], WayOrder[i], Width, Height);
        }
        // and fg
        for(i=0; i< e_Way_EnumCount; i++) {
            DrawWaysFg(pBMP, m_DrawWays[WayOrder[i]], WayOrder[i], Width, Height);
        }
        // and oneway arrows
        if(pOpt->MustShowOneways()) {
            for(i=0; i< e_Way_EnumCount; i++) {
                DrawOneways(pBMP, m_DrawWays[WayOrder[i]], WayOrder[i], Width, Height);
            }
        }
        // clear arrays
        for(i=0; i<e_Way_EnumCount; i++) {
            TWayBuffer *pBuffer = m_DrawWays[i];
            pBuffer->Clear();
        }
        for(i=0; i<e_Area_EnumCount; i++) {
            TAreaBuffer *pBuffer = m_DrawAreas[i];
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

    if(pOpt->IsTargetSet()){
        CXCoor TargetCoor = pOpt->GetActiveTarget().GetCoor();
        TargetCoor.RelocateUTM(UTMZoneCurrent);
        CXCoorVector v = TMMap*CXCoorVector(TargetCoor.GetUTMEasting(), TargetCoor.GetUTMNorthing());
        // draw target if neccessary
        int POIDisplaySize = CXOptions::Instance()->GetPOIDisplaySize();
        pBMP->DrawTransparent(  m_pTargetBMP,
                                v.GetIntX()-POIDisplaySize/2, v.GetIntY()-3*POIDisplaySize/2,
                                0, 0, POIDisplaySize, 2*POIDisplaySize,
                                COLOR_TRANSPARENT);
    }

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
        snprintf(   buf, sizeof(buf), "W:%ld (%d), A: (%d)  TL:%ld",
                    StopDrawWays-StartTime, WayCount, AreaCount,
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
double CXMapPainter2D::GetRequestedMeterPerPixel() {
    CXReadLocker RL(&m_RWLock);
    return m_RequestedMeterPerPixel;
}

//-------------------------------------
void CXMapPainter2D::SetRequestedMeterPerPixel(double NewValue) {
    CXWriteLocker WL(&m_RWLock);
    m_RequestedMeterPerPixel = NewValue;
}

//-------------------------------------
bool CXMapPainter2D::ZoomIn() {
    CXWriteLocker WL(&m_RWLock);
    double dNewMeterPerPixel = m_RequestedMeterPerPixel / ZoomFactor;
    m_RequestedMeterPerPixel = Min(MAXMETERPERPIXEL, Max(dNewMeterPerPixel, MINMETERPERPIXEL));
    return true;
}

//-------------------------------------
bool CXMapPainter2D::ZoomOut() {
    CXWriteLocker WL(&m_RWLock);
    double dNewMeterPerPixel = m_RequestedMeterPerPixel * ZoomFactor;
    m_RequestedMeterPerPixel = Min(MAXMETERPERPIXEL, Max(dNewMeterPerPixel, MINMETERPERPIXEL));
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
    m_PenHolder.ScalePens(4.0/m_MeterPerPixel);
}
