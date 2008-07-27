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

#include "Utils.hpp"
#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "CXMutexLocker.hpp"
#include "CXExactTime.hpp"
#include "CXDebugInfo.hpp"
#include "CXTransformationMatrix.hpp"

const unsigned int MAPVERSION = 0x00020001; // 0.2.0-dev1

//----------------------------------------------------------------------------
CXPOWMMap *CXPOWMMap::m_pInstance = NULL;

//-------------------------------------
CXPOWMMap::CXPOWMMap() {
	m_TrackLog.SetMaxSize(CXOptions::Instance()->GetTrackLogSize());
	m_TrackLog.SetMinDistance(CXOptions::Instance()->GetTrackLogMinDist());
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
void CXPOWMMap::PositionChanged(double dLon, double dLat, bool oFix) {
	CXMutexLocker L(&m_Mutex);
/*
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
*/
	// if neccessary ad new point to tracklog
	if(oFix && CXOptions::Instance()->MustShowTrackLog()) {
		m_TrackLog.AddCoordinate(dLon, dLat);
	}
}

/*
//-------------------------------------
bool CXPOWMMap::LoadMap(const CXStringASCII & FileName) {
	CXMutexLocker L(&m_Mutex);

	Clear();

	m_FileName = FileName;
	m_iCurrentZone = UTMZoneNone;

	CXFile InFile;
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
	if(Version == 0x00000100) {
		// v 0.1.1
		Result = LoadMap0_1_1(InFile, FileName);
	} else if(Version == 0x00010200) {
		// v 0.1.2
		Result = LoadMap0_1_2(InFile, FileName);
	} else if(Version != ReqVersion) {
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
		Result = LoadMap_CurrentVersion(InFile, FileName);
	}

	// check return code and do other sutff
	if(Result) {
		// check OSMVali
		if(CXOptions::Instance()->GetOSMValiFlags() != 0) {
			// run vali;
			RunOSMVali();
		}
	}
	return Result;
}
*/

/*
	// check if new map has to be loaded
	char buf[100];
	CXCoor Coor = m_NaviData.GetCorrectedGPSCoor();
	/// \todo which coor
	double dLon = Coor.GetLon();
	double dLat = Coor.GetLat();
	int NameLon = static_cast<int>(floor(fabs(dLon*10)));
	int NameLat = static_cast<int>(floor(fabs(dLat*10)));
	char EW = 'E';
	if(dLon < 0 )
		EW = 'W';
	char NS = 'N';
	if(dLat < 0 )
		NS = 'S';
	snprintf(buf, 100, "%c%04d%c%03d.map", EW, NameLon, NS, NameLat);
	CXStringASCII FileName=CXOptions::Instance()->GetDirectoryMaps();
	FileName+=buf;
	if(pPOWMMap->GetFileName() != FileName) {
		if(oLoadMap) {
			pPOWMMap->LoadMap(FileName);
		} else {
			// do not load any map (no fix yet and not starting with last saved coordinate
		}
	}
*/

//-------------------------------------
const CXTrackLog & CXPOWMMap::GetTrackLog() const {
	return m_TrackLog;
}

//-------------------------------------
TMapSectionPtrArray CXPOWMMap::GetMapSections(double dLon, double dLat, unsigned char ZoomLevel) {
	TMapSectionPtrArray tmp;
	TMapSectionPtr oiu(new CXMapSection(), false);
	tmp.Append(oiu);
	return tmp;
}
