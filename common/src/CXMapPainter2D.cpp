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

//-------------------------------------
CXPenHolder::CXPenHolder() {
	CreatePens();
}

//-------------------------------------
CXPenHolder::~CXPenHolder() {
	DestroyPens();
}

//-------------------------------------
void CXPenHolder::CreatePens() {

	for(size_t i=0; i<CXWay::eEnumCount; i++) {
		m_Pens.Append(new SPens());
	}
		
	SPens *pPens = NULL;

	// now create pens
	// Mapnik
	pPens = m_Pens[CXWay::eUnknown];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eMotorway];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 5, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eMotorwayLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 5, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eTrunk];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 5, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eTrunkLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 5, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::ePrimary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x60, 0x70));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 3, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::ePrimaryLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x6C, 0x70));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 3, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eSecondary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xA5, 0x7D, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFC, 0xBE, 0x6E));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eTertiary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xCB));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 3, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eUnclassified];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xDD));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 3, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eTrack];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 2, CXRGB(0xF9, 0x80, 0x72));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 2, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eResidential];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xFE));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 3, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eService];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE0, 0xE0, 0xE0));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 3, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eBridleway];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eCycleway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x80, 0x00));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eFootway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xF9, 0x80, 0x72));
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::ePedestrian];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));

	pPens = m_Pens[CXWay::eSteps];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;
	pPens->m_pSegmSel	= new CXPen(CXPen::e_Solid, 1, CXRGB(0xff, 0x00, 0x00));
}

//-------------------------------------
void CXPenHolder::DestroyPens() {
	for(size_t i=0; i<CXWay::eEnumCount; i++) {
		SPens *pPens = m_Pens[i];
		delete pPens->m_pBg;
		delete pPens->m_pSegm;
		delete pPens->m_pSegmSel;
		delete pPens;
	}
	m_Pens.Clear();
}

//-------------------------------------
CXPen *CXPenHolder::GetPenBg(CXWay::E_KEYHIGHWAY HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pBg;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetPenFg(CXWay::E_KEYHIGHWAY HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pSegm;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetPenFgSelected(CXWay::E_KEYHIGHWAY HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pSegmSel;
	return Result;
}

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
void CXMapPainter2D::DrawWay(IBitmap *pBMP, CXWay *pWay, const CXTransformationMatrix2D & TM, int Width, int Height) {
	if(pWay == NULL)
		return;
	size_t NodeCount = pWay->GetNodeCount();
	int x0 = 0;
	int y0 = 0;
	for(size_t i=0; i<NodeCount; i++) {
		CXNode *pNode = pWay->GetNode(i);
		CXCoorVector v = TM*CXCoorVector(pNode->GetX(), pNode->GetY());
		int x = v.GetIntX();
		int y = v.GetIntY();
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
void CXMapPainter2D::DrawWaysBg(IBitmap *pBMP, TWayBuffer *pWays, CXWay::E_KEYHIGHWAY eHighwayType, const CXTransformationMatrix2D & TM, int Width, int Height) {
	if(pWays == NULL)
		return;
	CXPen *pen = m_PenHolder.GetPenBg(eHighwayType);
	if(pen != NULL) {
		pBMP->SetPen(pen);
		size_t cnt = pWays->GetSize();
		for(size_t i=0; i<cnt; i++) {
			CXWay *pWay = (*pWays)[i];
			DrawWay(pBMP, pWay, TM, Width, Height);
		}
	}
}

//-------------------------------------
void CXMapPainter2D::DrawWaysFg(IBitmap *pBMP, TWayBuffer *pWays, CXWay::E_KEYHIGHWAY eHighwayType, const CXTransformationMatrix2D & TM, int Width, int Height) {
	if(pWays == NULL)
		return;
	CXPen *pen = m_PenHolder.GetPenFg(eHighwayType);
	if(pen != NULL) {
		pBMP->SetPen(pen);
		size_t cnt = pWays->GetSize();
		for(size_t i=0; i<cnt; i++) {
			CXWay *pWay = (*pWays)[i];
			DrawWay(pBMP, pWay, TM, Width, Height);
		}
	}
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

	// get zone
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

		CXTransformationMatrix2D TM;
		CXUTMSpeed UTMSpeed = NaviData.GetUTMSpeed();

		TM.Translate(-x0, -y0);			// x0, y0 is center of visible universe
		// rotate
		if(pOpt->Northing()) {
			xc = Width/2;
			yc = Height/2;
		} else {
			xc = Width/2;
			yc = 3*Height/4;
			TM.Rotate(UTMSpeed.GetCos(), -UTMSpeed.GetSin());
			// rotate 90 to left, since 0 is east amd we want it point to north
			TM.Rotate(UTMPI/2);
		}
		TM.Scale(m_Scale, -m_Scale);	// do scaling (negative for y!)
		TM.Translate(xc, yc);			// display it centered on screen

		// prepare drawing
		
		TWayMap &Ways = CXPOWMMap::Instance()->GetWayMap();
		POS pos = Ways.GetStart();
		CXWay *pWay = NULL;
		int cnt = 0;
		while (Ways.GetNext(pos, pWay) != TWayMap::NPOS) {
			CXWay::E_KEYHIGHWAY HighwayType = pWay->GetHighwayType();
			m_DrawWays[HighwayType]->Append(pWay);
			cnt++;
		}
		StopPrepare.SetNow();
		// ok, now draw bg
		for(i=0; i< CXWay::eEnumCount; i++) {
			DrawWaysBg(pBMP, m_DrawWays[Order[i]], Order[i], TM, Width, Height);
		}
		for(i=0; i< CXWay::eEnumCount; i++) {
			DrawWaysFg(pBMP, m_DrawWays[Order[i]], Order[i], TM, Width, Height);
		}

		// clear arrays
		for(i=0; i<CXWay::eEnumCount; i++) {
			TWayBuffer *pBuffer = m_DrawWays[i];
			pBuffer->Clear();
		}

		// show caches
		pBMP->DrawRect(tIRect(xc-5, yc-5, xc+5, yc+5), CXRGB(0x00, 0x00, 0x00), CXRGB(0xff, 0x00, 0x00));
	}
	CXPOWMMap::Instance()->UnlockMap();

	CXExactTime Stop;
	char buf[100];
	snprintf(buf, 100, "%ld - %ld ms", StopPrepare-StopLock, Stop-StopPrepare);
	CXStringASCII ttt = buf;
	tIRect TextRect = pBMP->CalcTextRectASCII(ttt, 2, 2);
	TextRect.OffsetRect(-TextRect.GetLeft(), -TextRect.GetTop());
	pBMP->DrawTextASCII(ttt, TextRect, FGCOLOR, BGCOLOR); 
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
