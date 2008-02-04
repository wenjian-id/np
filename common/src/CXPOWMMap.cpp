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

#include "CXPOWMMap.hpp"
#include "CXExactTime.hpp"
#include "CXFile.hpp"
#include "CXMutexLocker.hpp"
#include "CXOptions.hpp"
#include "CXTransformationMatrix.hpp"
#include "Utils.hpp"
#include "CoordConversion.h"

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

	unsigned long MagicCode = 0;
	unsigned long ReqMagicCode = ('P' << 24) + ('O' << 16) + ('W' << 8) + 'M';
	if(!ReadUL32(InFile, MagicCode)) {
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
	unsigned long Version = 0;
	unsigned long ReqVersion = 0x01010201; // 0.1.2 dev1
	if(!ReadUL32(InFile, Version)) {
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
	} else if(Version != ReqVersion) {
		// not supported version
		CXStringASCII ErrorMsg(FileName);
		ErrorMsg += " has wrong Version: ";
		char buf[10];
		snprintf(	buf, 10, "%d.%d.%d", 
					static_cast<unsigned char>((Version & 0xff0000) >> 16),
					static_cast<unsigned char>((Version & 0xff00) >> 8),
					static_cast<unsigned char>(Version & 0xff));
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
	unsigned long NodeCount = 0;
	if(!ReadUL32(InFile, NodeCount)) {
		CXStringASCII ErrorMsg("Error reading NodeCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read nodes
	for(unsigned long ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		unsigned long Lon = 0; 
		unsigned long Lat = 0;
		ReadI64(InFile, ID);
		ReadUL32(InFile, Lon);
		ReadUL32(InFile, Lat);

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
	unsigned long WayCount = 0;
	if(!ReadUL32(InFile, WayCount)) {
		CXStringASCII ErrorMsg("Error reading WayCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read ways
	for(unsigned long ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		t_uint64 ID = 0;
		unsigned char HighwayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		unsigned char MaxSpeed = 0;
		ReadI64(InFile, ID);
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
		unsigned long NodeCount = 0;
		ReadUL32(InFile, NodeCount);
		for(unsigned long ul=0; ul<NodeCount; ul++) {
			t_uint64 SegID = 0;
			ReadI64(InFile, SegID);
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
	unsigned long NodeCount = 0;
	if(!ReadUL32(InFile, NodeCount)) {
		CXStringASCII ErrorMsg("Error reading NodeCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read nodes
	for(unsigned long ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint64 ID = 0;
		unsigned long Lon = 0; 
		unsigned long Lat = 0;
		ReadI64(InFile, ID);
		ReadUL32(InFile, Lon);
		ReadUL32(InFile, Lat);

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
	unsigned long WayCount = 0;
	if(!ReadUL32(InFile, WayCount)) {
		CXStringASCII ErrorMsg("Error reading WayCount from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	// read ways
	for(unsigned long ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		t_uint64 ID = 0;
		unsigned char HighwayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		ReadI64(InFile, ID);
		ReadB(InFile, HighwayType);
		ReadStringUTF8(InFile, Name);
		ReadStringUTF8(InFile, Ref);
		// create way
		CXWay *pWay = new CXWay(ID, static_cast<CXWay::E_KEYHIGHWAY>(HighwayType), Name, Ref);
		// add node
		m_WayMap.SetAt(ID, pWay);
		// 
		unsigned long NodeCount = 0;
		ReadUL32(InFile, NodeCount);
		for(unsigned long ul=0; ul<NodeCount; ul++) {
			t_uint64 SegID = 0;
			ReadI64(InFile, SegID);
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
