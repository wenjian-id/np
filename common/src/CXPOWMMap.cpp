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
#include "CXFile.hpp"
#include "CXMutexLocker.hpp"
#include "CXOptions.hpp"
#include "Utils.hpp"
#include "CoordConversion.h"

//----------------------------------------------------------------------------
//-------------------------------------
CXNode::CXNode(t_uint64 ID, double Lon, double Lat) :
	m_ID(ID),
	m_Lon(Lon),
	m_Lat(Lat),
	m_X(0),
	m_Y(0)
{
}

//-------------------------------------
CXNode::~CXNode() {
}

//-------------------------------------
double CXNode::GetLon() const {
	return m_Lon;
}

//-------------------------------------
double CXNode::GetLat() const {
	return m_Lat;
}

//-------------------------------------
double CXNode::GetX() const {
	return m_X;
}

//-------------------------------------
void CXNode::SetX(double X) {
	m_X = X;
}

//-------------------------------------
double CXNode::GetY() const {
	return m_Y;
}

//-------------------------------------
void CXNode::SetY(double Y) {
	m_Y = Y;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXWay::CXWay(t_uint64 ID, E_KEYHIGHWAY eHighwayType, const CXStringUTF8 & Name):
	m_ID(ID),
	m_eHighwayType(eHighwayType),
	m_Name(Name)
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


//----------------------------------------------------------------------------
CXPOWMMap *CXPOWMMap::m_pInstance = NULL;

//-------------------------------------
CXPOWMMap::CXPOWMMap() :
	m_iCurrentZone(UTMZoneNone)
{
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
	// go through all nodes and recompute xy
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
		while (m_NodeMap.GetNext(Pos, pNode) != TNodeMap::NPOS) {
			if(pNode != NULL) {
				LLtoUTM(WGS84, pNode->GetLon(), pNode->GetLat(), m_iCurrentZone, NewZone, UTMLetter, UTME, UTMN);
				pNode->SetX(UTME);
				pNode->SetY(UTMN);
			}
		}
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

	CXExactTime StartTime;

	m_FileName = FileName;
	m_iCurrentZone = UTMZoneNone;

	CXFile InFile;
	if(InFile.Open(FileName.c_str(), CXFile::E_READ) != CXFile::E_OK) {
		CXStringASCII ErrorMsg("Error opening file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}

	unsigned long MagicCode = 0;
	unsigned long ReqMagicCode = ('P' << 24) + ('O' << 16) + ('W' << 8) + 'M';
	if(!ReadUL(InFile, MagicCode)) {
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
	unsigned long ReqVersion = 0x00000100;
	if(!ReadUL(InFile, Version)) {
		CXStringASCII ErrorMsg("Error reading Version from file: ");
		ErrorMsg += FileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
		return false;
	}
	if(Version != ReqVersion) {
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
	}

	// node count
	unsigned long NodeCount = 0;
	if(!ReadUL(InFile, NodeCount)) {
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
		ReadUL(InFile, Lon);
		ReadUL(InFile, Lat);
		double dLon = 1.0*Lon/1000000.0;
		double dLat = 1.0*Lat/1000000.0;
		// create node
		CXNode *pNode = new CXNode(ID, dLon, dLat);
		// add node
		m_NodeMap.SetAt(ID, pNode);
	}

	// way count
	unsigned long WayCount = 0;
	if(!ReadUL(InFile, WayCount)) {
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
		ReadI64(InFile, ID);
		ReadB(InFile, HighwayType);
		ReadStringUTF8(InFile, Name);
		// create way
		CXWay *pWay = new CXWay(ID, static_cast<CXWay::E_KEYHIGHWAY>(HighwayType), Name);
		// add node
		m_WayMap.SetAt(ID, pWay);
		// 
		unsigned long NodeCount = 0;
		ReadUL(InFile, NodeCount);
		for(unsigned long ul=0; ul<NodeCount; ul++) {
			t_uint64 SegID = 0;
			ReadI64(InFile, SegID);
			CXNode *pNode = NULL;
			if(!m_NodeMap.Lookup(SegID, pNode))
				continue;
			pWay->AddNode(pNode);
		}
	}
	CXExactTime StopTime;
	unsigned long diff = StopTime - StartTime;
	diff = 42;
	return true;
}

