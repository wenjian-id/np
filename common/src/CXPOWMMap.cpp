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

#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "CXMutexLocker.hpp"
#include "CXExactTime.hpp"
#include "CXDebugInfo.hpp"
#include "CXTransformationMatrix.hpp"
#include "CXMapLoaderThread.hpp"

#include <math.h>

static const size_t TOCCACHESIZE	= 100;		///< oiu
static const size_t MSCACHESIZE		= 200;		///< oiu


//----------------------------------------------------------------------------
//-------------------------------------
CXVisibleMapSectionDescr::CXVisibleMapSectionDescr(	double dLonMin,double dLatMin,
													double dLonMax,double dLatMax,
													unsigned char ZoomLevel,
													const CXTransformationMatrix2D &TMMap) :
	m_dLonMin(dLonMin),
	m_dLonMax(dLonMax),
	m_dLatMin(dLatMin),
	m_dLatMax(dLatMax),
	m_ZoomLevel(ZoomLevel),
	m_Matrix(TMMap)
{
}

//-------------------------------------
CXVisibleMapSectionDescr::~CXVisibleMapSectionDescr() {
}

//-------------------------------------
double CXVisibleMapSectionDescr::GetLonMin() const {
	return m_dLonMin;
}

//-------------------------------------
double CXVisibleMapSectionDescr::GetLatMin() const {
	return m_dLatMin;
}

//-------------------------------------
double CXVisibleMapSectionDescr::GetLonMax() const {
	return m_dLonMax;
}

//-------------------------------------
double CXVisibleMapSectionDescr::GetLatMax() const {
	return m_dLatMax;
}

//-------------------------------------
unsigned char CXVisibleMapSectionDescr::GetZoomLevel() const {
	return m_ZoomLevel;
}


//----------------------------------------------------------------------------
CXPOWMMap *CXPOWMMap::m_pInstance = NULL;

//-------------------------------------
CXPOWMMap::CXPOWMMap() :
	m_TOCCache(TOCCACHESIZE),
	m_MapSectionCache(MSCACHESIZE),
	m_pMapLoaderThread(NULL)
{
}

//-------------------------------------
CXPOWMMap::~CXPOWMMap() {
}

//-------------------------------------
CXPOWMMap *CXPOWMMap::Instance() {
	if(m_pInstance == NULL)
		m_pInstance = new CXPOWMMap();
	return m_pInstance;
}

//-------------------------------------
void CXPOWMMap::SetMapLoaderThread(CXMapLoaderThread *pMapLoaderThread) {
	m_pMapLoaderThread = pMapLoaderThread;
}

/*
//-------------------------------------
void CXPOWMMap::PositionChanged(double dLon, double dLat, bool oFix) {
	CXMutexLocker L(&m_Mutex);
	int NewZone = UTMZoneNone;
	char UTMLetter = 0;
	double UTME = 0;
	double UTMN = 0;
	LLtoUTM(WGS84, dLon, dLat, UTMZoneNone, NewZone, UTMLetter, UTME, UTMN);
	if((m_iCurrentZone == UTMZoneNone) || (NewZone != m_iCurrentZone)) {
		// set new zone
		m_iCurrentZone = NewZone;
		// refresh x and y of every node
		POS Pos = m_NodeMap.GetStart();
		CXNode *pNode = NULL;
		// go through all nodes and recompute xy
		while (m_NodeMap.GetNext(Pos, pNode) != TNodeMap::NPOS) {
			if(pNode != NULL) {
				pNode->RelocateUTM(m_iCurrentZone);
			}
		}

		// relocate tracklog
		m_TrackLog.RelocateUTM(m_iCurrentZone);
	}
}
*/

//-------------------------------------
CXStringASCII CXPOWMMap::GetFileNameFromCoor(double dLon, double dLat) {
	int NameLon = static_cast<int>(floor(fabs(dLon)));
	int NameLat = static_cast<int>(floor(fabs(dLat)));
	char EW = 'E';
	if(dLon < 0 )
		EW = 'W';
	char NS = 'N';
	if(dLat < 0 )
		NS = 'S';
	char buf[100];
	snprintf(buf, sizeof(buf), "%c%03d%c%02d.map", EW, NameLon, NS, NameLat);
	CXStringASCII Result=CXOptions::Instance()->GetDirectoryMaps();
	Result+=buf;
	return Result;
}

//-------------------------------------
t_uint32 CXPOWMMap::GetCacheKeyFromCoor(double dLon, double dLat, unsigned char ZoomLevel) {
	int NameLon = static_cast<int>(floor(dLon));
	int NameLat = static_cast<int>(floor(dLat));
	while(NameLon < -180)
		NameLon += 360;
	NameLon = NameLon % 360;	// [0 - 360]
	while(NameLat < -90)
		NameLat += 180;
	NameLat = NameLat % 180;	// [0 - 180]
	t_uint32 Result = NameLon << 16;
	Result += NameLat << 8;
	Result += ZoomLevel;
	return Result;
}


//-------------------------------------
TMapSectionPtrArray CXPOWMMap::GetMapSections(const CXVisibleMapSectionDescr &Descr) {
	/// \todo implement
	CXMutexLocker L(&m_Mutex);
	TMapSectionPtrArray Result;
	// compute file name from coordinates
	double dLonMin = 0;
	double dLonMax = 0;
	double dLatMin = 0;
	double dLatMax = 0;
	modf(Descr.GetLonMin(), &dLonMin);
	modf(Descr.GetLonMax(), &dLonMax);
	modf(Descr.GetLatMin(), &dLatMin);
	modf(Descr.GetLatMax(), &dLatMax);
	// increment cache counters
	m_TOCCache.IncrementCounters();
	// load all TOCMapContainer between 
	CXBuffer<CXTOCMapSection*> MapSectionTOCs;
	for(double dLon = dLonMin; dLon <= dLonMax; dLon++) {
		for(double dLat = dLatMin; dLat <= dLatMax; dLat++) {
			t_uint32 CacheKey = GetCacheKeyFromCoor(dLon, dLat, Descr.GetZoomLevel());
			// get TOCMapContainer from cache
			TTOCMapContainerPtr TOCMapContainerPtr = m_TOCCache.GetAt(CacheKey);
			CXTOCMapContainer *pTOC = TOCMapContainerPtr.GetPtr();
			if(pTOC->GetLoadStatus() == e_LSNotLoaded) {
				// load TOC for map container at a specific zoom level
				CXStringASCII FileName = GetFileNameFromCoor(dLon, dLat);
				m_pMapLoaderThread->LoadTOCMapContainer(TOCMapContainerPtr, FileName, Descr.GetZoomLevel(), CacheKey);
			}
			// get fiting map sections from this container for specific zoom level
			tDRect Rect(Descr.GetLonMin(), Descr.GetLatMin(), Descr.GetLonMax() - Descr.GetLonMin(), Descr.GetLatMax() - Descr.GetLatMin());
			pTOC->GetMapSections(Rect, MapSectionTOCs);
		}
	}
	// OK we now have the map section TOCs
	// increment cache counters for map sections
	m_MapSectionCache.IncrementCounters();
	// check to see which have to be loaded in MapSectionCache
	size_t cnt = MapSectionTOCs.GetSize();
	for(size_t i=0; i<cnt; i++) {
		CXTOCMapSection *pTOC = MapSectionTOCs[i];
		if(pTOC != NULL) {
			TMapSectionPtr MapSectionPtr = m_MapSectionCache.GetAt(pTOC->GetUID());
			CXMapSection *pS = MapSectionPtr.GetPtr();
			if(pS->GetLoadStatus() == e_LSNotLoaded) {
				pS->SetTOC(*pTOC);
				m_pMapLoaderThread->LoadMapSection(MapSectionPtr);
			}
			Result.Append(MapSectionPtr);
			delete pTOC;
			MapSectionTOCs[i] = NULL;
		}
	}
	return Result;
}
