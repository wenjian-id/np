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

#include "CXMapLoaderThread.hpp"
#include "CXMutexLocker.hpp"
#include "CXOptions.hpp"
#include "OSSpecific.hpp"

#include <math.h>


static const size_t TOCCACHEPURGEAGE		= 20;		///< oiu
static const size_t MSDISPLAYCACHEPURGEAGE	= 50;		///< oiu
static const size_t MSLOCATORCACHEPURGEAGE	= 16;		///< oiu


//----------------------------------------------------------------------------
//-------------------------------------
CXVisibleMapSectionDescr::CXVisibleMapSectionDescr(	double dLonMin,double dLatMin,
													double dLonMax,double dLatMax,
													E_ZOOM_LEVEL ZoomLevel) :
	m_dLonMin(dLonMin),
	m_dLonMax(dLonMax),
	m_dLatMin(dLatMin),
	m_dLatMax(dLatMax),
	m_ZoomLevel(ZoomLevel)
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
E_ZOOM_LEVEL CXVisibleMapSectionDescr::GetZoomLevel() const {
	return m_ZoomLevel;
}


//----------------------------------------------------------------------------
//-------------------------------------
CXMapLoaderThread::CXMapLoaderThread() :
	m_TOCCache(TOCCACHEPURGEAGE),
	m_MapSectionDisplayCache(MSDISPLAYCACHEPURGEAGE),
	m_MapSectionLocatorCache(MSLOCATORCACHEPURGEAGE)
{
}

//-------------------------------------
CXMapLoaderThread::~CXMapLoaderThread() {
	size_t cnt = m_TOCDescrList.GetSize();
	for(size_t i=0; i<cnt; i++)
		delete m_TOCDescrList[i];
}

//-------------------------------------
void CXMapLoaderThread::OnThreadStarted() {
	// nothing to do
}

//-------------------------------------
void CXMapLoaderThread::OnThreadStopped() {
	// nothing to do
}

//-------------------------------------
void CXMapLoaderThread::OnWorkFunc() {
	// check if enaugh memory left
	int Mem = GetFreeMem()/1024/1024;
	if((Mem > 0) && (Mem < 10)) {
		// purge caches
		m_TOCCache.Purge();
		m_MapSectionDisplayCache.Purge();
		m_MapSectionLocatorCache.Purge();
	}
	bool oFurtherWork = false;
	bool oLoadTOC = false;
	CXTOCDescr *pTOCDescr = NULL;
	// get first TOC to load
	TTOCMapContainerPtr TOC;
	{
		CXMutexLocker L(&m_Mutex);
		if(m_TOCMapContainerLoadList.GetSize() != 0) {
			oLoadTOC = true;
			TOC = m_TOCMapContainerLoadList[0];
			pTOCDescr = m_TOCDescrList[0];
			m_TOCMapContainerLoadList.RemoveAt(0);
			m_TOCDescrList.RemoveAt(0);
		}
	}
	if(oLoadTOC) {
		TOC.GetPtr()->Load(pTOCDescr->m_FileName, pTOCDescr->m_ZoomLevel, pTOCDescr->m_Key);
		delete pTOCDescr;
	}
	bool oLoadSection = false;
	TMapSectionPtr MS;
	{
		CXMutexLocker L(&m_Mutex);
		if(m_MapSectionDisplayLoadList.GetSize() != 0) {
			oLoadSection = true;
			MS = m_MapSectionDisplayLoadList[0];
			m_MapSectionDisplayLoadList.RemoveAt(0);
		}
	}
	if(oLoadSection) {
		MS.GetPtr()->LoadMap();
	}
	// check if more work to be done
	{
		CXMutexLocker L(&m_Mutex);
		if(m_TOCMapContainerLoadList.GetSize() != 0)
			oFurtherWork = true;
		if(m_MapSectionDisplayLoadList.GetSize() != 0)
			oFurtherWork = true;
	}
	if(oFurtherWork)
		RequestWork();
}

//-------------------------------------
void CXMapLoaderThread::LoadTOCMapContainer(TTOCMapContainerPtr &TOCMapContainer, const CXStringASCII & FileName, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key) {
	CXMutexLocker L(&m_Mutex);
	if(TOCMapContainer.GetPtr()->GetLoadStatus() == e_LSNotLoaded) {
		TOCMapContainer.GetPtr()->SetLoadStatus(e_LSInList);
		m_TOCMapContainerLoadList.Append(TOCMapContainer);
		m_TOCDescrList.Append(new CXTOCDescr(FileName, ZoomLevel, Key));
	}
	RequestWork();
}

//-------------------------------------
void CXMapLoaderThread::LoadMapSection(TMapSectionPtr &MapSectionDisplayPtr) {
	CXMutexLocker L(&m_Mutex);
	if(MapSectionDisplayPtr.GetPtr()->GetLoadStatus() == e_LSNotLoaded) {
		MapSectionDisplayPtr.GetPtr()->SetLoadStatus(e_LSInList);
		m_MapSectionDisplayLoadList.Append(MapSectionDisplayPtr);
	}
	RequestWork();
}

//-------------------------------------
t_uint32 CXMapLoaderThread::GetCacheKeyFromCoor(double dLon, double dLat, unsigned char ZoomLevel) {
	int NameLon = static_cast<int>(floor(dLon));
	int NameLat = static_cast<int>(floor(dLat));
	while(NameLon < -180)
		NameLon += 360;
	NameLon += 180;
	NameLon = NameLon % 360;	// [0 - 360]
	while(NameLat < -90)
		NameLat += 180;
	NameLat += 90;
	NameLat = NameLat % 180;	// [0 - 180]
	t_uint32 Result = NameLon << 16;
	Result += NameLat << 8;
	Result += ZoomLevel;
	return Result;
}

//-------------------------------------
CXStringASCII CXMapLoaderThread::GetFileNameFromCoor(double dLon, double dLat) {
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
TMapSectionPtrArray CXMapLoaderThread::GetMapSectionsXYZ(const CXVisibleMapSectionDescr &Descr, CXCache<t_uint64, CXMapSection> &Cache) {
	CXMutexLocker L(&m_CacheMutex);
	TMapSectionPtrArray Result;
	// compute file name from coordinates
	double dLonMin = Descr.GetLonMin();
	double dLonMax = Descr.GetLonMax();
	double dLatMin = Descr.GetLatMin();
	double dLatMax = Descr.GetLatMax();
	// increment cache counters
	m_TOCCache.IncrementCounters();
	// load all TOCMapContainer between 
	CXBuffer<CXTOCMapSection*> MapSectionTOCs;
	for(double dLon = dLonMin; dLon < dLonMax+1; dLon++) {
		for(double dLat = dLatMin; dLat < dLatMax+1; dLat++) {
			t_uint32 CacheKey = GetCacheKeyFromCoor(dLon, dLat, Descr.GetZoomLevel());
			// get TOCMapContainer from cache
			TTOCMapContainerPtr TOCMapContainerPtr = m_TOCCache.GetAt(CacheKey);
			CXTOCMapContainer *pTOC = TOCMapContainerPtr.GetPtr();
			if(pTOC->GetLoadStatus() == e_LSNotLoaded) {
				// load TOC for map container at a specific zoom level
				CXStringASCII FileName = GetFileNameFromCoor(dLon, dLat);
				LoadTOCMapContainer(TOCMapContainerPtr, FileName, Descr.GetZoomLevel(), CacheKey);
			}
			// get fiting map sections from this container for specific zoom level
			tDRect Rect(Descr.GetLonMin(), Descr.GetLatMin(), Descr.GetLonMax() - Descr.GetLonMin(), Descr.GetLatMax() - Descr.GetLatMin());
			pTOC->GetMapSections(Rect, MapSectionTOCs);
		}
	}
	// OK we now have the map section TOCs
	// increment cache counters for map sections
	Cache.IncrementCounters();
	// check to see which have to be loaded in MapSectionCache
	size_t cnt = MapSectionTOCs.GetSize();
	for(size_t i=0; i<cnt; i++) {
		CXTOCMapSection *pTOC = MapSectionTOCs[i];
		if(pTOC != NULL) {
			TMapSectionPtr MapSectionPtr = Cache.GetAt(pTOC->GetUID());
			CXMapSection *pS = MapSectionPtr.GetPtr();
			if(pS->GetLoadStatus() == e_LSNotLoaded) {
				pS->SetTOC(*pTOC);
				LoadMapSection(MapSectionPtr);
			}
			Result.Append(MapSectionPtr);
			delete pTOC;
			MapSectionTOCs[i] = NULL;
		}
	}
	return Result;
}

//-------------------------------------
TMapSectionPtrArray CXMapLoaderThread::GetMapSectionsDisplay(const CXVisibleMapSectionDescr &Descr) {
	return GetMapSectionsXYZ(Descr, m_MapSectionDisplayCache);
}

//-------------------------------------
TMapSectionPtrArray CXMapLoaderThread::GetMapSectionsLocator(const CXVisibleMapSectionDescr &Descr) {
	return GetMapSectionsXYZ(Descr, m_MapSectionLocatorCache);
}
