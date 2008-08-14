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

#include "CXMapSection.hpp"
#include "CXExactTime.hpp"
#include "CXDebugInfo.hpp"
#include "CXOptions.hpp"
#include "CXTransformationMatrix.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"

//----------------------------------------------------------------------------
//-------------------------------------
CXTOCMapSection::CXTOCMapSection(t_uint64 UID, double dLonMin, double dLonMax, 
								 double dLatMin, double dLatMax, const CXStringASCII & FileName, t_uint32 Offset):
	m_UID(UID),
	m_dLonMin(dLonMin),
	m_dLonMax(dLonMax),
	m_dLatMin(dLatMin),
	m_dLatMax(dLatMax),
	m_FileName(FileName),
	m_Offset(Offset)
{
}

//-------------------------------------
CXTOCMapSection::~CXTOCMapSection() {
}

//-------------------------------------
t_uint64 CXTOCMapSection::GetUID() const {
	return m_UID;
}

//-------------------------------------
double CXTOCMapSection::GetLonMin() const {
	return m_dLonMin;
}

//-------------------------------------
double CXTOCMapSection::GetLonMax() const {
	return m_dLonMax;
}

//-------------------------------------
double CXTOCMapSection::GetLatMin() const {
	return m_dLatMin;
}

//-------------------------------------
double CXTOCMapSection::GetLatMax() const {
	return m_dLatMax;
}

//-------------------------------------
CXStringASCII CXTOCMapSection::GetFileName() const {
	return m_FileName;
}

//-------------------------------------
t_uint32 CXTOCMapSection::GetOffset() const{
	return m_Offset;
}

//-------------------------------------
bool CXTOCMapSection::Intersects(const tDRect & Rect) const {
	if(m_dLonMin > Rect.GetRight())
		return false;
	if(m_dLonMax < Rect.GetLeft())
		return false;
	if(m_dLatMin > Rect.GetBottom())	// Bottom > Top!!!
		return false;
	if(m_dLatMax < Rect.GetTop())		// Bottom > Top!!!
		return false;
	return true;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXMapSection::CXMapSection() :
	m_eLoadStatus(e_LSNotLoaded),
	m_UTMZone(UTMZoneNone)
{
	for(char Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		m_WayMapBuffer.Append(NULL);
	}
}

//-------------------------------------
CXMapSection::~CXMapSection() {
	// delete nodes
	CXNode *pNode = NULL;
	TPOSNodeMap PosN = m_NodeMap.GetStart();
	while (m_NodeMap.GetNext(PosN, pNode) != TNodeMap::NPOS) {
		if(pNode != NULL)
			delete pNode;
	}
	m_NodeMap.RemoveAll();
	m_POINodes.RemoveAll();
	// delete ways
	for(size_t i=0; i<m_WayMapBuffer.GetSize(); i++) {
		TWayMap *pWayMap = m_WayMapBuffer[i];
		if(pWayMap != NULL) {
			TPOSWayMap PosW = pWayMap->GetStart();
			CXWay *pWay = NULL;
			while (pWayMap->GetNext(PosW, pWay) != TWayMap::NPOS) {
				if(pWay != NULL)
					delete pWay;
			}
			pWayMap->RemoveAll();
			delete pWayMap;
		}
	}
	m_WayMapBuffer.Clear();
}

//-------------------------------------
E_LOADING_STATUS CXMapSection::GetLoadStatus() const {
	CXReadLocker RL(&m_StatusRWLock);
	return m_eLoadStatus;
}

//-------------------------------------
void CXMapSection::SetLoadStatus(E_LOADING_STATUS eStatus) {
	CXWriteLocker WL(&m_StatusRWLock);
	m_eLoadStatus = eStatus;
}

//-------------------------------------
TTOCMapSectionPtr CXMapSection::GetTOC() const {
	return m_TOC;
}

//-------------------------------------
void CXMapSection::SetTOC(const TTOCMapSectionPtr & TOCPtr) {
	m_TOC = TOCPtr;
}

//-------------------------------------
const TPOINodeMap &CXMapSection::GetPOINodeMap() const {
	return m_POINodes;
}

//-------------------------------------
CXWay *CXMapSection::GetWay(t_uint64 ID) {
	CXWay *Result = NULL;
	for(size_t i=0; i<m_WayMapBuffer.GetSize(); i++) {
		TWayMap *pWayMap = m_WayMapBuffer[i];
		if(pWayMap != NULL) {
			if(pWayMap->Lookup(ID, Result))
				return Result;
		}
	}
	return NULL;
}

//-------------------------------------
bool CXMapSection::LoadMap() {
	CXMutexLocker L(&m_Mutex);

	SetLoadStatus(e_LSLoading);
	bool Result = true;

	CXStringASCII FileName = m_TOC.GetPtr()->GetFileName();
	char buf[1024];
	snprintf(buf, sizeof(buf), "Loading MapSection for %s: %0.2f x %0.2f - %0.2f x %0.2f\n", FileName.c_str(), 
								m_TOC.GetPtr()->GetLonMin(), m_TOC.GetPtr()->GetLatMin(),
								m_TOC.GetPtr()->GetLonMax(), m_TOC.GetPtr()->GetLatMax());
	DoOutputDebugString(buf);

	CXFile InFile;
	// reduce read ahead size to 1000 bytes
	InFile.SetReadAheadSize(1000);
	Result = Result && (InFile.Open(FileName.c_str(), CXFile::E_READ) == CXFile::E_OK);

	// seek to position
	Result = Result && InFile.Seek(m_TOC.GetPtr()->GetOffset()) == CXFile::E_OK;

	t_uint32 MagicCode = 0;
	t_uint32 ReqMagicCode = ('S' << 24) + ('E' << 16) + ('C' << 8) + 'T';
	Result = Result && ReadUI32(InFile, MagicCode);
	Result = Result && (MagicCode == ReqMagicCode);

	// check version
	t_uint32 Version = 0;
	t_uint32 ReqVersion = SECTVERSION;
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
/*
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
			DoOutputErrorMessage(ErrorMsg.c_str());
*/
			Result = false;
		} else {
			// current version
			Result = LoadMap_CurrentVersion(InFile);
		}
	}
	if(Result)
		SetLoadStatus(e_LSLoaded);
	else
		SetLoadStatus(e_LSLoadError);

	return Result;
}

//-------------------------------------
bool CXMapSection::LoadMap_CurrentVersion(CXFile & InFile) {
	// node count

	CXExactTime Time1;
	Time1.SetNow();

	// read POIs
	t_uint32 POICount = 0;
	if(!ReadUI32(InFile, POICount)) {
		DoOutputErrorMessage("Error reading POICount");
		return false;
	}
	for(t_uint32 ulPOI=0; ulPOI<POICount; ulPOI++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		unsigned char POIIdx = 0;
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		t_uint32 POI = 0;
		ReadUI64(InFile, ID);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);
		ReadB(InFile, POIIdx);
		ReadUI32(InFile, POI);

		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);

		// create POI node
		CXPOINode *pPOINode = new CXPOINode(ID, dLon, dLat);

		for(size_t i=0; i<MaxPOITypes; i++) {
			if((POIIdx % 2) == 1) {
				pPOINode->SetPOIType(MaxPOITypes-i-1, POI);
			}
			POIIdx = POIIdx >> 1;
		}
		CXStringUTF8 Name;
		ReadStringUTF8(InFile, Name);
		pPOINode->SetName(Name);

		// add node to POI map
		m_POINodes.SetAt(ID, pPOINode);
	}
	// read nodes
	t_uint32 NodeCount = 0;
	if(!ReadUI32(InFile, NodeCount)) {
		DoOutputErrorMessage("Error reading NodeCount");
		return false;
	}
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI64(InFile, ID);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);

		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);

		// create node
		CXNode *pNode = new CXNode(ID, dLon, dLat);

		// add node to node map
		m_NodeMap.SetAt(ID, pNode);
	}

	CXExactTime Time2;
	Time2.SetNow();
	// way count
	t_uint32 WayCount = 0;
	if(!ReadUI32(InFile, WayCount)) {
		DoOutputErrorMessage("Error reading WayCount");
		return false;
	}
	CXMapHashSimple<char, TWayMap *> Ways;
	// read ways
	for(t_uint32 ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		t_uint64 ID = 0;
		unsigned char HighwayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		unsigned char MaxSpeed = 0;
		ReadUI64(InFile, ID);
		ReadB(InFile, HighwayType);
		ReadStringUTF8(InFile, Name);
		ReadStringUTF8(InFile, Ref);
		ReadB(InFile, MaxSpeed);
		unsigned char bLayer = 0;
		ReadB(InFile, bLayer);
		char Layer = 0;
		if((bLayer & 0x80) != 0)
			// negative value
			Layer = - (bLayer & 0x7F);
		else {
			// positive value
			Layer = bLayer;
		}
		// create way
		CXWay *pWay = new CXWay(ID, static_cast<CXWay::E_KEYHIGHWAY>(HighwayType), Name, Ref);
		pWay->SetMaxSpeed(MaxSpeed);
		pWay->SetLayer(Layer);
		// add way
		TWayMap *pWayMap = NULL;
		if(!Ways.Lookup(Layer, pWayMap)) {
			Ways.SetAt(Layer, new TWayMap());
		}
		Ways.Lookup(Layer, pWayMap);
		pWayMap->SetAt(ID, pWay);
		// 
		t_uint32 NodeCount = 0;
		ReadUI32(InFile, NodeCount);
		for(t_uint32 ul=0; ul<NodeCount; ul++) {
			t_uint64 SegID = 0;
			ReadUI64(InFile, SegID);
			CXNode *pNode = NULL;
			if(!m_NodeMap.Lookup(SegID, pNode))
				continue;
			pWay->AddNode(pNode);
		}
	}
	// fill m_WayMapBuffer ordered by Layer ascending
	for(char Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		TWayMap *pWayMap = NULL;
		Ways.Lookup(Layer, pWayMap);
		TWayMap *pOld = m_WayMapBuffer[Layer - MINLAYER];
		if(pOld != NULL)
			delete pOld;
		m_WayMapBuffer[Layer - MINLAYER] = pWayMap;
	}

	CXExactTime Time3;
	Time3.SetNow();

	CXDebugInfo::Instance()->SetLoadTimeNodes(Time2 - Time1);
	CXDebugInfo::Instance()->SetLoadTimeWays(Time3 - Time2);
	return true;
}

//-------------------------------------
void CXMapSection::RunOSMVali() {
	for(size_t i=0; i<m_WayMapBuffer.GetSize(); i++) {
		TWayMap *pWayMap = m_WayMapBuffer[i];
		if(pWayMap != NULL) {
			TPOSWayMap PosW = pWayMap->GetStart();
			CXWay *pWay = NULL;
			t_uint64 eValiFlags = CXOptions::Instance()->GetOSMValiFlags();
			while (pWayMap->GetNext(PosW, pWay) != TWayMap::NPOS) {
				bool Vali = true;
				if(pWay != NULL) {
					if((eValiFlags & CXOptions::e_OSMValiName) != 0) {
						// check name
						if(pWay->GetName().IsEmpty()) {
							Vali = false;
						}
					}
					if((eValiFlags & CXOptions::e_OSMValiRef) != 0) {
						// check ref
						if(pWay->GetRef().IsEmpty()) {
							Vali = false;
						}
					}
					if((eValiFlags & CXOptions::e_OSMValiMaxSpeed) != 0) {
						// check max speed
						if(pWay->GetMaxSpeed() == 0) {
							Vali = false;
						}
					}
					// set result
					pWay->SetOSMVali(Vali);
				}
			}
		}
	}
}

//-------------------------------------
void CXMapSection::ComputeDisplayCoordinates(const CXTransformationMatrix2D & TM) {
	// run coordinate transformation for every node
	CXNode *pNode = NULL;
	TPOSNodeMap PosN = m_NodeMap.GetStart();
	while (m_NodeMap.GetNext(PosN, pNode) != TNodeMap::NPOS) {
		if(pNode != NULL) {
			CXCoorVector v = TM*CXCoorVector(pNode->GetUTME(), pNode->GetUTMN());
			pNode->SetDisplayX(v.GetIntX());
			pNode->SetDisplayY(v.GetIntY());
		}
	}
	CXPOINode *pPOINode = NULL;
	TPOSPOINodeMap PosPN = m_POINodes.GetStart();
	while (m_POINodes.GetNext(PosPN, pPOINode) != TPOINodeMap::NPOS) {
		if(pPOINode != NULL) {
			CXCoorVector v = TM*CXCoorVector(pPOINode->GetUTME(), pPOINode->GetUTMN());
			pPOINode->SetDisplayX(v.GetIntX());
			pPOINode->SetDisplayY(v.GetIntY());
		}
	}
}

//-------------------------------------
void CXMapSection::RelocateUTMZone(int NewZone) {
	if(NewZone != m_UTMZone) {
		m_UTMZone = NewZone;
		CXNode *pNode = NULL;
		TPOSNodeMap PosN = m_NodeMap.GetStart();
		while (m_NodeMap.GetNext(PosN, pNode) != TNodeMap::NPOS) {
			if(pNode != NULL) {
				pNode->RelocateUTM(m_UTMZone);
			}
		}
		CXPOINode *pPOINode = NULL;
		TPOSPOINodeMap PosPN = m_POINodes.GetStart();
		while (m_POINodes.GetNext(PosPN, pPOINode) != TPOINodeMap::NPOS) {
			if(pPOINode != NULL) {
				pPOINode->RelocateUTM(m_UTMZone);
			}
		}
	}
}


/*
	// check return code and do other sutff
	if(Result) {
		// check OSMVali
		if(CXOptions::Instance()->GetOSMValiFlags() != 0) {
			// run vali;
			RunOSMVali();
		}
	}
*/
