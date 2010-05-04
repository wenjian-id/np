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

#include "CXMapContainer.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"
#include "CXExactTime.hpp"
#include "Utils.hpp"

//----------------------------------------------------------------------------
//-------------------------------------
CXTOCMapContainer::CXTOCMapContainer() :
	m_eLoadStatus(e_LSNotLoaded),
	m_pTOCSections(NULL),
	m_dBaseLon(0),
	m_dBaseLat(0),
	m_Width(0),
	m_Height(0)
{
}

//-------------------------------------
CXTOCMapContainer::~CXTOCMapContainer() {
	Clear();
}

//-------------------------------------
void CXTOCMapContainer::Clear() {
	if(m_pTOCSections != NULL) {
		for(size_t x=0; x<m_Width; x++) {
			for(size_t y=0; y<m_Height; y++) {
				delete m_pTOCSections[x][y];
			}
			delete [] m_pTOCSections[x];
			m_pTOCSections[x] = NULL;
		}
		delete [] m_pTOCSections;
		m_pTOCSections = NULL;
	}
}

//-------------------------------------
void CXTOCMapContainer::Resize(size_t Width, size_t Height) {
	Clear();
	m_Width = Width;
	m_Height = Height;
	m_pTOCSections = new CXTOCMapSection **[m_Width];
	for(size_t x=0; x<m_Width; x++) {
		m_pTOCSections[x] = new CXTOCMapSection*[m_Height];
		for(size_t y=0; y<m_Height; y++) {
			m_pTOCSections[x][y] = NULL;
		}
	}
}

//-------------------------------------
E_LOADING_STATUS CXTOCMapContainer::GetLoadStatus() const {
	CXReadLocker RL(&m_StatusRWLock);
	return m_eLoadStatus;
}

//-------------------------------------
void CXTOCMapContainer::SetLoadStatus(E_LOADING_STATUS eStatus) {
	CXWriteLocker WL(&m_StatusRWLock);
	m_eLoadStatus = eStatus;
}

//-------------------------------------
bool CXTOCMapContainer::Load(const CXStringASCII & FileName, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key) {
	CXWriteLocker WL(&m_RWLock);
	// set loaded flag
	SetLoadStatus(e_LSLoading);
	m_FileName = FileName;
	// try to load TOC
	bool Result = true;
	CXFile InFile;
	// reduce read ahead size to 100 bytes
	InFile.SetReadAheadSize(100);
	Result = (InFile.Open(FileName.c_str(), CXFile::E_READ) == CXFile::E_OK);

	t_uint32 MagicCode = 0;
	t_uint32 ReqMagicCode = ('P' << 24) + ('O' << 16) + ('W' << 8) + 'M';
	Result = Result && ReadUI32(InFile, MagicCode);
	// check magic code
	Result = Result && (MagicCode == ReqMagicCode);

	// check version
	t_uint32 Version = 0;
	t_uint32 ReqVersion = MAPVERSION;
	Result = Result && ReadUI32(InFile, Version);

	// decide which load function to call
	// first of all check older versions
	if(Result) {
/*
	if(Version == 0x00000100) {
		// v 0.1.1
		Result = LoadMap0_1_1(InFile, FileName);
	} else if(Version == 0x00010200) {
		// v 0.1.2
		Result = LoadMap0_1_2(InFile, FileName);
	} else if(Version != ReqVersion) {
*/
		if(Version != ReqVersion) {
			// not supported version
			CXStringASCII ErrorMsg(FileName);
			ErrorMsg += " has wrong Version: ";
			char buf[100];
			if((Version & 0xff) == 0) {
				snprintf(	buf, sizeof(buf), "%d.%d.%d", 
							static_cast<unsigned char>((Version & 0xff000000) >> 24),
							static_cast<unsigned char>((Version & 0xff0000) >> 16),
							static_cast<unsigned char>((Version & 0xff00) >> 8));
			} else {
				snprintf(	buf, sizeof(buf), "%d.%d.%d-dev%d", 
							static_cast<unsigned char>((Version & 0xff000000) >> 24),
							static_cast<unsigned char>((Version & 0xff0000) >> 16),
							static_cast<unsigned char>((Version & 0xff00) >> 8),
							static_cast<unsigned char>((Version & 0xff)));
			}
			ErrorMsg += buf;
	//		DoOutputErrorMessage(ErrorMsg.c_str());
			Result = false;
		} else {
			// current version
			Result = LoadTOCMapContainer_CurrentVersion(InFile, ZoomLevel, Key);
		}
	}
	if(Result) {
		// set loaded flag
		SetLoadStatus(e_LSLoaded);
	} else {
		// set loaded flag
		SetLoadStatus(e_LSLoadError);
	}
	return Result;

}

//-------------------------------------
bool CXTOCMapContainer::LoadTOCZoom(CXFile & rFile, t_uint32 Key, E_ZOOM_LEVEL ZoomLevel) {
	t_uint32 MagicCode = 0;
	t_uint32 ReqMagicCode = ('Z' << 24) + ('O' << 16) + ('O' << 8) + 'M';
	if(!ReadUI32(rFile, MagicCode))
		return false;
	if(MagicCode != ReqMagicCode) {
		DoOutputErrorMessage("oiu");
		return false;
	}

	// check version
	t_uint32 Version = 0;
	t_uint32 ReqVersion = ZOOMVERSION;
	if(!ReadUI32(rFile, Version)) {
		DoOutputErrorMessage("oiu");
		return false;
	}
	bool Result = false;
	// decide which load function to call
	// first of all check older versions
/*
	if(Version == 0x00000100) {
		// v 0.1.1
		Result = LoadMap0_1_1(rFile, FileName);
	} else if(Version == 0x00010200) {
		// v 0.1.2
		Result = LoadMap0_1_2(rFile, FileName);
	} else if(Version != ReqVersion) {
*/
	if(Version != ReqVersion) {
		// not supported version
		CXStringASCII ErrorMsg;
		ErrorMsg += " has wrong Version: ";
		char buf[100];
		if((Version & 0xff) == 0) {
			snprintf(	buf, sizeof(buf), "%d.%d.%d", 
						static_cast<unsigned char>((Version & 0xff000000) >> 24),
						static_cast<unsigned char>((Version & 0xff0000) >> 16),
						static_cast<unsigned char>((Version & 0xff00) >> 8));
		} else {
			snprintf(	buf, sizeof(buf), "%d.%d.%d-dev%d", 
						static_cast<unsigned char>((Version & 0xff000000) >> 24),
						static_cast<unsigned char>((Version & 0xff0000) >> 16),
						static_cast<unsigned char>((Version & 0xff00) >> 8),
						static_cast<unsigned char>((Version & 0xff)));
		}
		ErrorMsg += buf;
//		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	} else {
		// current version
		Result = LoadTOCZoom_CurrentVersion(rFile, Key, ZoomLevel);
	}
	return Result;
}

//-------------------------------------
bool CXTOCMapContainer::LoadTOCMapContainer_CurrentVersion(CXFile & rFile, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key) {
	t_uint32 TOCZOOMCount = 0;
	// read count and check it
	if(!ReadUI32(rFile, TOCZOOMCount))
		return false;
	if((t_uint32)ZoomLevel >= TOCZOOMCount)
		return false;
	// read offset for specific zoom level
	t_uint32 Offset = 0;
	for(t_uint32 i=0; i<=(t_uint32)ZoomLevel; i++)
		if(!ReadUI32(rFile, Offset))
			return false;
	// now jump to offset
	if(rFile.Seek(Offset) != CXFile::E_OK)
		return false;
	// and load toc for specific zoom level
	return LoadTOCZoom(rFile, Key, ZoomLevel);
}

//-------------------------------------
bool CXTOCMapContainer::LoadTOCZoom_CurrentVersion(CXFile & rFile, t_uint32 Key, E_ZOOM_LEVEL ZoomLevel) {
	t_uint32 TOCSectionWidth = 0;
	t_uint32 TOCSectionHeight = 0;
	t_uint32 tmp = 0;
	// read BaseLon
	if(!ReadUI32(rFile, tmp))
		return false;
	m_dBaseLon = ConvertSavedUI32(tmp);

	// read BaseLat
	if(!ReadUI32(rFile, tmp))
		return false;
	m_dBaseLat = ConvertSavedUI32(tmp);

	// read count and check it
	if(!ReadUI32(rFile, TOCSectionWidth))
		return false;
	if(!ReadUI32(rFile, TOCSectionHeight))
		return false;
	// read TOCSection
	t_uint32 Offset = 0;
	Resize(TOCSectionWidth, TOCSectionHeight);
	for(t_uint32 i=0; i<TOCSectionWidth; i++) {
		for(t_uint32 j=0; j<TOCSectionHeight; j++) {
			// read Offset
			if(!ReadUI32(rFile, Offset))
				return false;

			// create key
			t_uint64 Key64 = Key;
			Key64 = (Key64 << 32) + (i<<16) + j;

			double dLonMin = m_dBaseLon + 1.0*i/TOCSectionWidth;
			double dLatMin = m_dBaseLat + 1.0*j/TOCSectionHeight;
			double dLonMax = dLonMin + 1.0/TOCSectionWidth;
			double dLatMax = dLatMin + 1.0/TOCSectionHeight;
			// append to array
			m_pTOCSections[i][j] = new CXTOCMapSection(Key64, ZoomLevel, dLonMin, dLonMax, dLatMin, dLatMax, m_FileName, Offset);
		}
	}
	return true;
}

//-------------------------------------
void CXTOCMapContainer::GetMapSections(const tDRect &Rect, CXBuffer<CXTOCMapSection *> & rResult) {
	CXReadLocker RL(&m_RWLock);
	CXExactTime Start;
	if((m_Width != 0) && (m_Height != 0) && (m_pTOCSections != NULL)) {
		double dLonMin = Rect.GetLeft();
		double dLonMax = Rect.GetRight();
		double dLatMin = Rect.GetTop();
		double dLatMax = Rect.GetBottom();
		if(dLonMin > m_dBaseLon + 1.0)
			return;
		if(dLonMax < m_dBaseLon)
			return;
		if(dLatMin > m_dBaseLat + 1.0)
			return;
		if(dLatMax < m_dBaseLat)
			return;

		dLonMin = Max(m_dBaseLon, dLonMin);
		dLatMin = Max(m_dBaseLat, dLatMin);
		dLonMax = Min(m_dBaseLon+1.0, dLonMax);
		dLatMax = Min(m_dBaseLat+1.0, dLatMax);

		size_t idxXMin = static_cast<size_t>(Max(0.0, m_Width*(dLonMin-m_dBaseLon)));
		size_t idxXMax = static_cast<size_t>(Max(0.0, m_Width*(dLonMax-m_dBaseLon)));
		size_t idxYMin = static_cast<size_t>(Max(0.0, m_Height*(dLatMin-m_dBaseLat)));
		size_t idxYMax = static_cast<size_t>(Max(0.0, m_Height*(dLatMax-m_dBaseLat)));

		idxXMin = Min(m_Width-1,idxXMin);
		idxXMax = Min(m_Width-1,idxXMax);
		idxYMin = Min(m_Height-1,idxYMin);
		idxYMax = Min(m_Height-1,idxYMax);
		for(size_t xx=idxXMin; xx<=idxXMax; xx++) {
			for(size_t yy=idxYMin; yy<=idxYMax; yy++) {
				rResult.Append(new CXTOCMapSection(*(m_pTOCSections[xx][yy])));
			}
		}
	}
	CXExactTime Stop;
	int diff = Stop - Start;
	char buf[100];
	snprintf(buf, sizeof(buf), "%d\n", diff);
//	DoOutputDebugString(buf);
}
