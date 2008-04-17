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

#include "Utils.hpp"
#include "CXPOWMMap.hpp"
#include "CXExactTime.hpp"
#include "CXFile.hpp"
#include "CXMutexLocker.hpp"
#include "CXOptions.hpp"
#include "CXTransformationMatrix.hpp"
#include "CoordConversion.h"

const unsigned int MAPVERSION = 0x00010300; // 0.1.3

//----------------------------------------------------------------------------
//-------------------------------------
CXNode::CXNode(t_uint64 ID, double dLon, double dLat) :
	m_ID(ID),
	m_Coor(dLon, dLat)
{
}

//-------------------------------------
CXNode::~CXNode() {
}

//-------------------------------------
double CXNode::GetLon() const {
	return m_Coor.GetLon();
}

//-------------------------------------
double CXNode::GetLat() const {
	return m_Coor.GetLat();
}

//-------------------------------------
double CXNode::GetUTME() const {
	return m_Coor.GetUTMEasting();
}

//-------------------------------------
double CXNode::GetUTMN() const {
	return m_Coor.GetUTMNorthing();
}

//-------------------------------------
void CXNode::RelocateUTM(int NewUTMZone) {
	m_Coor.RelocateUTM(NewUTMZone);
}

//-------------------------------------
int CXNode::GetDisplayX() const {
	return m_DisplayX;
}

//-------------------------------------
void CXNode::SetDisplayX(int X) {
	m_DisplayX = X;
}

//-------------------------------------
int CXNode::GetDisplayY() const {
	return m_DisplayY;
}

//-------------------------------------
void CXNode::SetDisplayY(int Y) {
	m_DisplayY = Y;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXPOINode::CXPOINode(t_uint64 ID, double Lon, double Lat) :
	CXNode(ID, Lon, Lat)
{
	for(size_t i=0; i<MaxPOITypes; i++) {
		m_POI[i] = 0;
	}
}

//-------------------------------------
CXPOINode::~CXPOINode() {
}

//-------------------------------------
bool CXPOINode::IsPOI(size_t Index) const {
	if(Index >= MaxPOITypes)
		Index = 0;
	return m_POI[Index] != 0;
}

//-------------------------------------
t_uint32 CXPOINode::GetPOIType(size_t Index) const {
	if(Index >= MaxPOITypes)
		Index = 0;
	return m_POI[Index];
}

//-------------------------------------
void CXPOINode::SetPOIType(size_t Index, t_uint32 NewValue) {
	if(Index >= MaxPOITypes)
		Index = 0;
	m_POI[Index] = NewValue;
}

//-------------------------------------
void CXPOINode::ComputePOIPosInBMP(t_uint32 POI, int & rRow, int & rCol) {
	rRow = 0;
	rCol = 0;
	t_uint32 tmp = POI;
	if((tmp & 0xFFFF) == 0) {
		// no lower 16 bits set
		tmp = tmp >> 16;
		rRow += 2;
	}
	if((tmp & 0xFF) == 0) {
		// no lower 8 bits set
		tmp = tmp >> 8;
		rRow += 1;
	}
	// now compute column
	for(int i=0; i<8; i++) {
		if(tmp % 2 == 0) {
			// not found. shift right
			tmp = tmp >> 1;
			rCol++;
		} else {
			// found.
			break;
		}
	}
}

//-------------------------------------
void CXPOINode::SetName(const CXStringUTF8 &NewValue) {
	m_Name = NewValue;
}

//-------------------------------------
CXStringUTF8 CXPOINode::GetName() const {
	return m_Name;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXWay::CXWay(t_uint64 ID, E_KEYHIGHWAY eHighwayType, const CXStringUTF8 & Name, const CXStringUTF8 & Ref):
	m_ID(ID),
	m_eHighwayType(eHighwayType),
	m_Name(Name),
	m_Ref(Ref),
	m_MaxSpeed(0),
	m_oOSMValiFailed(false)
{
}

//-------------------------------------
CXWay::~CXWay() {
}

//-------------------------------------
t_uint64 CXWay::GetID() const {
	return m_ID;
}

//-------------------------------------
CXWay::E_KEYHIGHWAY CXWay::GetHighwayType() const {
	return m_eHighwayType;
}

//-------------------------------------
CXStringUTF8 CXWay::GetName() const {
	return m_Name;
}

//-------------------------------------
CXStringUTF8 CXWay::GetRef() const {
	return m_Ref;
}

//-------------------------------------
void CXWay::SetMaxSpeed(unsigned char MaxSpeed) {
	m_MaxSpeed = MaxSpeed;
}

//-------------------------------------
unsigned char CXWay::GetMaxSpeed() const {
	return m_MaxSpeed;
}

//-------------------------------------
void CXWay::AddNode(CXNode *pNode) {
	if(pNode != NULL) {
		m_Nodes.Append(pNode);
	}
}

//-------------------------------------
size_t CXWay::GetNodeCount() const {
	return m_Nodes.GetSize();
}

//-------------------------------------
CXNode *CXWay::GetNode(size_t Index) const {
	return m_Nodes[Index];
}

//-------------------------------------
bool CXWay::GetOSMValiState() const {
	return m_oOSMValiFailed;
}

//-------------------------------------
void CXWay::SetOSMVali(bool NewValue) {
	m_oOSMValiFailed = NewValue;
}


//----------------------------------------------------------------------------
CXPOWMMap *CXPOWMMap::m_pInstance = NULL;

//-------------------------------------
CXPOWMMap::CXPOWMMap() :
	m_iCurrentZone(UTMZoneNone)
{
	m_TrackLog.SetMaxSize(CXOptions::Instance()->GetTrackLogSize());
	m_TrackLog.SetMinDistance(CXOptions::Instance()->GetTrackLogMinDist());
}

//-------------------------------------
CXPOWMMap::~CXPOWMMap() {
	Clear();
}

//-------------------------------------
CXPOWMMap *CXPOWMMap::Instance() {
	if(m_pInstance == NULL)
		m_pInstance = new CXPOWMMap();
	return m_pInstance;
}

//-------------------------------------
void CXPOWMMap::Clear() {
	// delete nodes
	CXNode *pNode = NULL;
	POS PosN = m_NodeMap.GetStart();
	while (m_NodeMap.GetNext(PosN, pNode) != TNodeMap::NPOS) {
		if(pNode != NULL)
			delete pNode;
	}
	m_NodeMap.RemoveAll();
	m_POINodes.RemoveAll();
	// delete ways
	POS PosW = m_WayMap.GetStart();
	CXWay *pWay = NULL;
	while (m_WayMap.GetNext(PosW, pWay) != TWayMap::NPOS) {
		if(pWay != NULL)
			delete pWay;
	}
	m_WayMap.RemoveAll();
}

//-------------------------------------
int CXPOWMMap::GetCurrentZone() const {
	CXMutexLocker L(&m_Mutex);
	return m_iCurrentZone;
}

//-------------------------------------
void CXPOWMMap::PositionChanged(double dLon, double dLat) {
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
	// if neccessary ad new point to tracklog
	if(CXOptions::Instance()->MustShowTrackLog()) {
		m_TrackLog.AddCoordinate(dLon, dLat);
	}
}

//-------------------------------------
void CXPOWMMap::LockMap() {
	m_Mutex.Lock();
}

//-------------------------------------
void CXPOWMMap::UnlockMap() {
	m_Mutex.Unlock();
}

//-------------------------------------
TNodeMap &CXPOWMMap::GetNodeMap() {
	return m_NodeMap;
}

//-------------------------------------
TPOINodeMap &CXPOWMMap::GetPOINodeMap() {
	return m_POINodes;
}

//-------------------------------------
TWayMap &CXPOWMMap::GetWayMap() {
	return m_WayMap;
}

//-------------------------------------
CXWay *CXPOWMMap::GetWay(t_uint64 ID) {
	CXWay *Result = NULL;
	if(m_WayMap.Lookup(ID, Result))
		return Result;
	return NULL;
}

//-------------------------------------
CXStringASCII CXPOWMMap::GetFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_FileName;
}


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
		DoOutputErrorMessage(ErrorMsg.c_str());
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

//-------------------------------------
bool CXPOWMMap::LoadMap_CurrentVersion(CXFile & InFile, const CXStringASCII & FileName) {
	// node count
	t_uint32 NodeCount = 0;
	if(!ReadUI32(InFile, NodeCount)) {
		CXStringASCII ErrorMsg("Error reading NodeCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read nodes
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		unsigned char POIIdx = 0;
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI64(InFile, ID);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);
		ReadB(InFile, POIIdx);

		// compute lon
		double dLon = 1.0;
		if((Lon & 0x80000000) != 0) {
			// negative coordinate
			dLon = -1;
			Lon &= 0x7FFFFFFF;
		}
		// now scale back
		dLon = dLon*Lon/1000000.0;

		// compute lat
		double dLat = 1.0;
		if((Lat & 0x80000000) != 0) {
			// negative coordinate
			dLat = -1;
			Lat &= 0x7FFFFFFF;
		}
		// now scale back
		dLat = dLat*Lat/1000000.0;

		CXNode *pNode = NULL;
		if(POIIdx == 0) {
			// create node
			pNode = new CXNode(ID, dLon, dLat);
		} else {
			// create POI node
			CXPOINode *pPOINode = new CXPOINode(ID, dLon, dLat);

			t_uint32 POI = 0;
			for(size_t i=0; i<MaxPOITypes; i++) {
				if((POIIdx % 2) == 1) {
					ReadUI32(InFile, POI);
					pPOINode->SetPOIType(MaxPOITypes-i-1, POI);
				}
				POIIdx = POIIdx >> 1;
			}
			CXStringUTF8 Name;
			ReadStringUTF8(InFile, Name);
			pPOINode->SetName(Name);

			// add node to POI map
			m_POINodes.SetAt(ID, pPOINode);
			// set pNode
			pNode = pPOINode;
		}
		// add node to node map
		m_NodeMap.SetAt(ID, pNode);
	}

	// way count
	t_uint32 WayCount = 0;
	if(!ReadUI32(InFile, WayCount)) {
		CXStringASCII ErrorMsg("Error reading WayCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
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
		// create way
		CXWay *pWay = new CXWay(ID, static_cast<CXWay::E_KEYHIGHWAY>(HighwayType), Name, Ref);
		pWay->SetMaxSpeed(MaxSpeed);
		// add node
		m_WayMap.SetAt(ID, pWay);
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
	return true;
}

//-------------------------------------
bool CXPOWMMap::LoadMap0_1_2(CXFile & InFile, const CXStringASCII & FileName) {
	// node count
	t_uint32 NodeCount = 0;
	if(!ReadUI32(InFile, NodeCount)) {
		CXStringASCII ErrorMsg("Error reading NodeCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read nodes
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI64(InFile, ID);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);

		// compute lon
		double dLon = 1.0;
		if((Lon & 0x80000000) != 0) {
			// negative coordinate
			dLon = -1;
			Lon &= 0x7FFFFFFF;
		}
		// now scale back
		dLon = dLon*Lon/1000000.0;

		// compute lat
		double dLat = 1.0;
		if((Lat & 0x80000000) != 0) {
			// negative coordinate
			dLat = -1;
			Lat &= 0x7FFFFFFF;
		}
		// now scale back
		dLat = dLat*Lat/1000000.0;

		// create node
		CXNode *pNode = new CXNode(ID, dLon, dLat);
		// add node
		m_NodeMap.SetAt(ID, pNode);
	}

	// way count
	t_uint32 WayCount = 0;
	if(!ReadUI32(InFile, WayCount)) {
		CXStringASCII ErrorMsg("Error reading WayCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
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
		// create way
		CXWay *pWay = new CXWay(ID, static_cast<CXWay::E_KEYHIGHWAY>(HighwayType), Name, Ref);
		pWay->SetMaxSpeed(MaxSpeed);
		// add node
		m_WayMap.SetAt(ID, pWay);
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
	return true;
}

//-------------------------------------
bool CXPOWMMap::LoadMap0_1_1(CXFile & InFile, const CXStringASCII & FileName) {
	// node count
	t_uint32 NodeCount = 0;
	if(!ReadUI32(InFile, NodeCount)) {
		CXStringASCII ErrorMsg("Error reading NodeCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read nodes
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI64(InFile, ID);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);

		// compute lon
		double dLon = 1.0;
		if((Lon & 0x80000000) != 0) {
			// negative coordinate
			dLon = -1;
			Lon &= 0x7FFFFFFF;
		}
		// now scale back
		dLon = dLon*Lon/1000000.0;

		// compute lat
		double dLat = 1.0;
		if((Lat & 0x80000000) != 0) {
			// negative coordinate
			dLat = -1;
			Lat &= 0x7FFFFFFF;
		}
		// now scale back
		dLat = dLat*Lat/1000000.0;

		// create node
		CXNode *pNode = new CXNode(ID, dLon, dLat);
		// add node
		m_NodeMap.SetAt(ID, pNode);
	}

	// way count
	t_uint32 WayCount = 0;
	if(!ReadUI32(InFile, WayCount)) {
		CXStringASCII ErrorMsg("Error reading WayCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read ways
	for(t_uint32 ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		t_uint64 ID = 0;
		unsigned char HighwayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		ReadUI64(InFile, ID);
		ReadB(InFile, HighwayType);
		ReadStringUTF8(InFile, Name);
		ReadStringUTF8(InFile, Ref);
		// create way
		CXWay *pWay = new CXWay(ID, static_cast<CXWay::E_KEYHIGHWAY>(HighwayType), Name, Ref);
		// add node
		m_WayMap.SetAt(ID, pWay);
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
	return true;
}

//-------------------------------------
void CXPOWMMap::RunOSMVali() {
	POS PosW = m_WayMap.GetStart();
	CXWay *pWay = NULL;
	t_uint64 eValiFlags = CXOptions::Instance()->GetOSMValiFlags();
	while (m_WayMap.GetNext(PosW, pWay) != TWayMap::NPOS) {
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

//-------------------------------------
const CXTrackLog & CXPOWMMap::GetTrackLog() const {
	return m_TrackLog;
}

//-------------------------------------
void CXPOWMMap::ComputeDisplayCoordinates(const CXTransformationMatrix2D & TM) {
	// run coordinate transformation for every node
	CXNode *pNode = NULL;
	POS PosN = m_NodeMap.GetStart();
	while (m_NodeMap.GetNext(PosN, pNode) != TNodeMap::NPOS) {
		if(pNode != NULL) {
			CXCoorVector v = TM*CXCoorVector(pNode->GetUTME(), pNode->GetUTMN());
			pNode->SetDisplayX(v.GetIntX());
			pNode->SetDisplayY(v.GetIntY());
		}
	}
}
