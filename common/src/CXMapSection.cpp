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
CXTOCMapSection::CXTOCMapSection() :
	m_UID(0),
	m_dLonMin(0),
	m_dLonMax(0),
	m_dLatMin(0),
	m_dLatMax(0),
	m_Offset(0)
{
}

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
CXTOCMapSection::CXTOCMapSection(const CXTOCMapSection &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXTOCMapSection::~CXTOCMapSection() {
}

//-------------------------------------
const CXTOCMapSection & CXTOCMapSection::operator = (const CXTOCMapSection &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXTOCMapSection::CopyFrom(const CXTOCMapSection & rOther) {
	m_UID = rOther.m_UID;
	m_dLonMin = rOther.m_dLonMin;
	m_dLonMax = rOther.m_dLonMax;
	m_dLatMin = rOther.m_dLatMin;
	m_dLatMax = rOther.m_dLatMax;
	m_FileName = rOther.m_FileName;
	m_Offset = rOther.m_Offset;
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

//----------------------------------------------------------------------------
//-------------------------------------
CXMapSection::CXMapSection() :
	m_eLoadStatus(e_LSNotLoaded),
	m_UTMZone(UTMZoneNone)
{
	for(char Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		m_LayeredWayBuffer.Append(NULL);
	}
}

//-------------------------------------
CXMapSection::~CXMapSection() {
	// delete nodes
	size_t Size = m_Nodes.GetSize();
	for(size_t idx = 0; idx < Size; idx++) {
		CXNode *pNode = m_Nodes[idx];
		if(pNode != NULL)
			delete pNode;
	}
	// delete ways
	size_t cnt = m_LayeredWayBuffer.GetSize();
	for(size_t i=0; i<cnt; i++) {
		TWayBuffer *pWayBuffer = m_LayeredWayBuffer[i];
		if(pWayBuffer != NULL) {
			size_t Size = pWayBuffer->GetSize();
			for(size_t i=0; i<Size; i++) {
				CXWay *pWay = (*pWayBuffer)[i];
				if(pWay != NULL)
					delete pWay;
			}
			delete pWayBuffer;
		}
	}
	m_LayeredWayBuffer.Clear();
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
CXTOCMapSection CXMapSection::GetTOC() const {
	return m_TOC;
}

//-------------------------------------
void CXMapSection::SetTOC(const CXTOCMapSection &TOC) {
	m_TOC = TOC;
}

//-------------------------------------
const TPOINodeBuffer & CXMapSection::GetPOINodeMap() const {
	return m_POINodes;
}

//-------------------------------------
bool CXMapSection::LoadMap() {
	CXMutexLocker L(&m_Mutex);

	SetLoadStatus(e_LSLoading);
	bool Result = true;

	CXStringASCII FileName = m_TOC.GetFileName();

	CXFile InFile;
	// reduce read ahead size to 1000 bytes
	InFile.SetReadAheadSize(1000);
	Result = Result && (InFile.Open(FileName.c_str(), CXFile::E_READ) == CXFile::E_OK);

	// seek to position
	Result = Result && InFile.Seek(m_TOC.GetOffset()) == CXFile::E_OK;

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

	// read POIs
	t_uint32 POICount = 0;
	if(!ReadUI32(InFile, POICount)) {
		DoOutputErrorMessage("Error reading POICount");
		return false;
	}
	m_POINodes.Resize(POICount);
	for(t_uint32 ulPOI=0; ulPOI<POICount; ulPOI++) {
		// read node
		unsigned char POICount = 0;
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);
		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);
		// create POI node
		CXPOINode *pPOINode = new CXPOINode(dLon, dLat);
		// read POI type stuff
		ReadB(InFile, POICount);
		for(t_uint32 cnt = 0; cnt < POICount; cnt++) {
			t_uint16 POI = 0;
			ReadUI16(InFile, POI);
			E_POI_TYPE POIType = static_cast<E_POI_TYPE>(POI);
			pPOINode->SetPOIType(POIType);
		}

		// read name
		CXStringUTF8 Name;
		ReadStringUTF8(InFile, Name);
		pPOINode->SetName(Name);

		// add node to POI buffer
		m_POINodes[ulPOI] = pPOINode;
	}
	// read nodes
	t_uint32 NodeCount = 0;
	if(!ReadUI32(InFile, NodeCount)) {
		DoOutputErrorMessage("Error reading NodeCount");
		return false;
	}
	m_Nodes.Resize(NodeCount);
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node: IDX, LON, LAT
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		unsigned char IsTerminator = 0;
		ReadB(InFile, IsTerminator);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);

		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);

		// create node
		CXNode *pNode = new CXNode((IsTerminator != 0), dLon, dLat);

		// and to m_Nodes
		m_Nodes[ulNode] = pNode;
	}

	// way count
	t_uint32 WayCount = 0;
	if(!ReadUI32(InFile, WayCount)) {
		DoOutputErrorMessage("Error reading WayCount");
		return false;
	}
	CXMapHashSimple<char, TWayBuffer *> Ways;
	// read ways
	for(t_uint32 ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		unsigned char HighwayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		unsigned char MaxSpeed = 0;
		ReadB(InFile, HighwayType);
//		ReadStringUTF8(InFile, Name);
//		ReadStringUTF8(InFile, Ref);
//		ReadB(InFile, MaxSpeed);
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
		CXWay *pWay = new CXWay(static_cast<E_KEYHIGHWAY_TYPE>(HighwayType), Name, Ref);
		pWay->SetMaxSpeed(MaxSpeed);
		pWay->SetLayer(Layer);
		// add way
		TWayBuffer *pWayBuffer = NULL;
		if(!Ways.Lookup(Layer, pWayBuffer)) {
			Ways.SetAt(Layer, new TWayBuffer());
		}
		Ways.Lookup(Layer, pWayBuffer);
		pWayBuffer->Append(pWay);
		// 
		t_uint32 NodeCount = 0;
		ReadUI32(InFile, NodeCount);
		for(t_uint32 ul=0; ul<NodeCount; ul++) {
			t_uint32 Idx = 0;
			ReadUI32(InFile, Idx);
			CXNode *pNode = m_Nodes[Idx];
			pWay->AddNode(pNode);
		}
	}
	// fill m_WayMapBuffer ordered by Layer ascending
	for(char Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		TWayBuffer *pWayBuffer = NULL;
		Ways.Lookup(Layer, pWayBuffer);
		TWayBuffer *pOld = m_LayeredWayBuffer[Layer - MINLAYER];
		if(pOld != NULL)
			delete pOld;
		m_LayeredWayBuffer[Layer - MINLAYER] = pWayBuffer;
	}

	return true;
}

//-------------------------------------
void CXMapSection::RunOSMVali() {
	size_t cnt = m_LayeredWayBuffer.GetSize();
	for(size_t i=0; i<cnt; i++) {
		TWayBuffer *pWayBuffer = m_LayeredWayBuffer[i];
		if(pWayBuffer != NULL) {
			CXWay *pWay = NULL;
			t_uint64 eValiFlags = CXOptions::Instance()->GetOSMValiFlags();
			size_t Size = pWayBuffer->GetSize();
			for(size_t idx=0; idx<Size; idx++) {
				pWay = (*pWayBuffer)[idx];
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
	size_t Size = m_Nodes.GetSize();
	for(size_t idx = 0; idx < Size; idx++) {
		CXNode *pNode = m_Nodes[idx];
		if(pNode != NULL) {
			CXCoorVector v = TM*CXCoorVector(pNode->GetUTME(), pNode->GetUTMN());
			pNode->SetDisplayX(v.GetIntX());
			pNode->SetDisplayY(v.GetIntY());
		}
	}
	for(size_t i=0; i<m_POINodes.GetSize(); i++) {
		CXPOINode *pPOINode = m_POINodes[i];
		CXCoorVector v = TM*CXCoorVector(pPOINode->GetUTME(), pPOINode->GetUTMN());
		pPOINode->SetDisplayX(v.GetIntX());
		pPOINode->SetDisplayY(v.GetIntY());
	}
}

//-------------------------------------
void CXMapSection::RelocateUTM(int NewZone) {
	if(NewZone != m_UTMZone) {
		m_UTMZone = NewZone;
		size_t Size = m_Nodes.GetSize();
		for(size_t idx = 0; idx < Size; idx++) {
			CXNode *pNode = m_Nodes[idx];
			if(pNode != NULL) {
				pNode->RelocateUTM(m_UTMZone);
			}
		}
		for(size_t i=0; i<m_POINodes.GetSize(); i++) {
			m_POINodes[i]->RelocateUTM(m_UTMZone);
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
