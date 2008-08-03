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
#include "Utils.hpp"
#include "CXExactTime.hpp"
#include "CXDebugInfo.hpp"
#include "CXOptions.hpp"
#include "CXTransformationMatrix.hpp"

static const char MINLAYER = -10;
static const char MAXLAYER = 10;

//----------------------------------------------------------------------------
//-------------------------------------
CXMapSection::CXMapSection() {
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
		TPOSWayMap PosW = pWayMap->GetStart();
		CXWay *pWay = NULL;
		while (pWayMap->GetNext(PosW, pWay) != TWayMap::NPOS) {
			if(pWay != NULL)
				delete pWay;
		}
		pWayMap->RemoveAll();
		delete pWayMap;
	}
	m_WayMapBuffer.Clear();
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
bool CXMapSection::LoadMap(CXFile & InFile) {
	/// \todo implement
	return true;
}

//-------------------------------------
bool CXMapSection::LoadMap_CurrentVersion(CXFile & InFile) {
	// node count

	CXExactTime Time1;
	Time1.SetNow();

	t_uint32 NodeCount = 0;
	if(!ReadUI32(InFile, NodeCount)) {
		DoOutputErrorMessage("Error reading NodeCount");
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
		if(Ways.Lookup(Layer, pWayMap)) {
			m_WayMapBuffer.Append(pWayMap);
		}
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
