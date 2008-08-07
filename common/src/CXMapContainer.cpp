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
#include "Utils.hpp"

//----------------------------------------------------------------------------
//-------------------------------------
CXTOCMapContainer::CXTOCMapContainer() :
	m_oLoaded(false)
{
}

//-------------------------------------
CXTOCMapContainer::~CXTOCMapContainer() {
}

//-------------------------------------
bool CXTOCMapContainer::IsLoaded() const {
	CXReadLocker RL(&m_RWLock);
	return m_oLoaded;
}

//-------------------------------------
bool CXTOCMapContainer::Load(const CXStringASCII & FileName, unsigned char ZoomLevel, t_uint32 Key) {
	CXWriteLocker WL(&m_RWLock);
	// set loaded flag
	m_oLoaded = true;
	m_FileName = FileName;
	// try to load TOC

	DoOutputDebugString("Loading TOC for ");
	DoOutputDebugString(FileName.c_str());
	DoOutputDebugString(" in zoom level ");
	char bbb[10];
	snprintf(bbb, sizeof(bbb), "%d", ZoomLevel);
	DoOutputDebugString(bbb);
	DoOutputDebugString("\n");

	CXFile InFile;
	// reduce read ahead size to 100 bytes
	InFile.SetReadAheadSize(100);
	if(InFile.Open(FileName.c_str(), CXFile::E_READ) != CXFile::E_OK) {
		// no error message
		return false;
	}

	t_uint32 MagicCode = 0;
	t_uint32 ReqMagicCode = ('P' << 24) + ('O' << 16) + ('W' << 8) + 'M';
	if(!ReadUI32(InFile, MagicCode)) {
		CXStringASCII ErrorMsg("Error reading MagicCode from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	if(MagicCode != ReqMagicCode) {
		CXStringASCII ErrorMsg(FileName);
		ErrorMsg += " is not a NaviPOWM map";
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}

	// check version
	t_uint32 Version = 0;
	t_uint32 ReqVersion = MAPVERSION;
	if(!ReadUI32(InFile, Version)) {
		CXStringASCII ErrorMsg("Error reading Version from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	bool Result = false;

	// decide which load function to call
	// first of all check older versions
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
		return false;
	} else {
		// current version
		Result = LoadTOCMapContainer_CurrentVersion(InFile, ZoomLevel, Key);
	}
	return Result;

}

//-------------------------------------
bool CXTOCMapContainer::LoadTOCZoom(CXFile & rFile, t_uint32 Key) {
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
		Result = LoadTOCZoom_CurrentVersion(rFile, Key);
	}
	return Result;
}

//-------------------------------------
bool CXTOCMapContainer::LoadTOCMapContainer_CurrentVersion(CXFile & rFile, unsigned char ZoomLevel, t_uint32 Key) {
	t_uint32 TOCZOOMCount = 0;
	// read count and check it
	if(!ReadUI32(rFile, TOCZOOMCount))
		return false;
	if(ZoomLevel >= TOCZOOMCount)
		return false;
	// read offset for specific zoom level
	t_uint32 Offset = 0;
	for(t_uint32 i=0; i<=ZoomLevel; i++)
		if(!ReadUI32(rFile, Offset))
			return false;
	// now jump to offset
	if(rFile.Seek(Offset) != CXFile::E_OK)
		return false;
	// and load toc for specific zoom level
	return LoadTOCZoom(rFile, Key);
}

//-------------------------------------
bool CXTOCMapContainer::LoadTOCZoom_CurrentVersion(CXFile & rFile, t_uint32 Key) {
	t_uint32 TOCSectionCount = 0;
	// read count and check it
	if(!ReadUI32(rFile, TOCSectionCount))
		return false;
	// read TOCSection
	m_TOCSections.Resize(TOCSectionCount);
	t_uint32 Offset = 0, tmp = 0;
	for(t_uint32 i=0; i<TOCSectionCount; i++) {
		// read MinLon
		if(!ReadUI32(rFile, tmp))
			return false;
		double dLonMin = ConvertSavedUI32(tmp);

		// read MaxLon
		if(!ReadUI32(rFile, tmp))
			return false;
		double dLonMax = ConvertSavedUI32(tmp);

		// read MinLat
		if(!ReadUI32(rFile, tmp))
			return false;
		double dLatMin = ConvertSavedUI32(tmp);

		// read MaxLat
		if(!ReadUI32(rFile, tmp))
			return false;
		double dLatMax = ConvertSavedUI32(tmp);

		// read Offset
		if(!ReadUI32(rFile, Offset))
			return false;

		// create key
		t_uint64 Key64 = Key;
		Key64 = (Key64 << 32) + i;

		// append to array
		m_TOCSections[i] = TTOCMapSectionPtr(new CXTOCMapSection(Key64, dLonMin, dLonMax, dLatMin, dLatMax, m_FileName, Offset), false);
	}
	return true;
}

//-------------------------------------
void CXTOCMapContainer::GetMapSections(const tDRect &Rect, CXArray<TTOCMapSectionPtr> & rResult) {
	CXReadLocker RL(&m_RWLock);
	for(size_t i=0; i<m_TOCSections.GetSize(); i++) {
		TTOCMapSectionPtr Ptr = m_TOCSections[i];
		CXTOCMapSection *pSection = Ptr.GetPtr();
		if(pSection != NULL) {
			if(pSection->Intersects(Rect))
				rResult.Append(Ptr);
		}
	}
}

//----------------------------------------------------------------------------
//-------------------------------------
CXMapContainer::CXMapContainer() {
}

//-------------------------------------
CXMapContainer::~CXMapContainer() {
}

