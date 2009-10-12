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
CXTOCMapSection::CXTOCMapSection(t_uint64 UID, E_ZOOM_LEVEL ZoomLevel, double dLonMin, double dLonMax, 
								 double dLatMin, double dLatMax, const CXStringASCII & FileName, t_uint32 Offset):
	m_UID(UID),
	m_ZoomLevel(ZoomLevel),
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
	m_ZoomLevel = rOther.m_ZoomLevel;
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
E_ZOOM_LEVEL CXTOCMapSection::GetZoomLevel() const {
	return m_ZoomLevel;
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
	m_UTMZone(UTMZoneNone),
	m_eLoadStatus(e_LSNotLoaded)
{
	char Layer = 0;
	for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		m_LayeredWayBuffer.Append(NULL);
	}
	for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		m_LayeredAreaBuffer.Append(NULL);
	}
}

//-------------------------------------
CXMapSection::~CXMapSection() {
	// delete places
	size_t Size_pl = m_PlaceNodes.GetSize();
	for(size_t idx_pl = 0; idx_pl < Size_pl; idx_pl++) {
		CXNode *pNode = m_PlaceNodes[idx_pl];
		if(pNode != NULL)
			delete pNode;
	}
	// delete POIs
	size_t Size_poi = m_POINodes.GetSize();
	for(size_t idx_poi = 0; idx_poi < Size_poi; idx_poi++) {
		CXNode *pNode = m_POINodes[idx_poi];
		if(pNode != NULL)
			delete pNode;
	}
	// delete nodes
	size_t Size_nodes = m_Nodes.GetSize();
	for(size_t idx_n = 0; idx_n < Size_nodes; idx_n++) {
		CXNode *pNode = m_Nodes[idx_n];
		if(pNode != NULL)
			delete pNode;
	}
	// delete ways
	size_t Size_ways = m_LayeredWayBuffer.GetSize();
	for(size_t idx_w=0; idx_w<Size_ways; idx_w++) {
		TWayBuffer *pWayBuffer = m_LayeredWayBuffer[idx_w];
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
	// delete areas
	size_t Size_Areas = m_LayeredAreaBuffer.GetSize();
	for(size_t idx_a=0; idx_a<Size_Areas; idx_a++) {
		TAreaBuffer *pAreaBuffer = m_LayeredAreaBuffer[idx_a];
		if(pAreaBuffer != NULL) {
			size_t Size = pAreaBuffer->GetSize();
			for(size_t i=0; i<Size; i++) {
				CXArea *pArea = (*pAreaBuffer)[i];
				if(pArea != NULL)
					delete pArea;
			}
			delete pAreaBuffer;
		}
	}
	m_LayeredAreaBuffer.Clear();
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
const TPOINodeBuffer & CXMapSection::GetPlaceNodes() const {
	return m_PlaceNodes;
}

//-------------------------------------
const TPOINodeBuffer & CXMapSection::GetPOINodes() const {
	return m_POINodes;
}

//-------------------------------------
const TNodeBuffer &CXMapSection::GetNodes() const {
	return m_Nodes;
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

		if(Version == 0x00010100) {
			// v 0.1.1
			Result = LoadMap_0_1_1(InFile);
		} else if(Version == 0x00010200) {
			// v 0.1.1
			Result = LoadMap_0_1_2(InFile);
		} else if(Version != ReqVersion) {
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
	// Node count type
	unsigned char NodeCountType = 0;
	if(!ReadUI8(InFile, NodeCountType)) {
		DoOutputErrorMessage("Error reading NodeCountType");
		return false;
	}
	E_BIT_COUNT eNodeCountType=static_cast<E_BIT_COUNT>(NodeCountType);
	// read place count
	t_uint32 NodeCount = 0;
	if(!ReadUI(InFile, eNodeCountType, NodeCount)) {
		DoOutputErrorMessage("Error reading NodeCount");
		return false;
	}
	if(NodeCount == 0) {
		// no further data to read
		return true;
	}
	m_Nodes.Resize(NodeCount);
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);
		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);
		// create node
		CXNode *pNode = new CXNode(dLon, dLat);

		// add node to Node buffer
		m_Nodes[ulNode] = pNode;
		// first node is terminator node
		if(ulNode == 0)
			pNode->SetTerminator();
	}

	// Place count type
	unsigned char PlaceCountType = 0;
	if(!ReadUI8(InFile, PlaceCountType)) {
		DoOutputErrorMessage("Error reading PlaceCountType");
		return false;
	}
	E_BIT_COUNT ePlaceCountType=static_cast<E_BIT_COUNT>(PlaceCountType);
	// read place count
	t_uint32 PlaceCount = 0;
	if(!ReadUI(InFile, ePlaceCountType, PlaceCount)) {
		DoOutputErrorMessage("Error reading PlaceCount");
		return false;
	}
	m_PlaceNodes.Resize(PlaceCount);
	for(t_uint32 ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
		// read node index
		t_uint32 NodeIdx = 0;
		ReadUI(InFile, eNodeCountType, NodeIdx);

		// create Place node
		CXPOINode *pPlaceNode = new CXPOINode(*m_Nodes[NodeIdx]);
		// read Place type stuff
		unsigned char Place = 0;
		ReadUI8(InFile, Place);
		E_MAP_PLACE_TYPE PlaceType = static_cast<E_MAP_PLACE_TYPE>(Place);
		pPlaceNode->SetPlaceType(PlaceType);

		// read name
		CXStringUTF8 Name;
		ReadStringUTF8(InFile, Name);
		pPlaceNode->SetName(Name);

		// add node to Place buffer
		m_PlaceNodes[ulPlace] = pPlaceNode;
	}


	// read POIs
	unsigned char POICountType = 0;
	if(!ReadUI8(InFile, POICountType)) {
		DoOutputErrorMessage("Error reading POICountType");
		return false;
	}
	E_BIT_COUNT ePOICountType=static_cast<E_BIT_COUNT>(POICountType);
	t_uint32 POICount = 0;
	if(!ReadUI(InFile, ePOICountType, POICount)) {
		DoOutputErrorMessage("Error reading POICount");
		return false;
	}
	m_POINodes.Resize(POICount);
	for(t_uint32 ulPOI=0; ulPOI<POICount; ulPOI++) {
		// read node index
		t_uint32 NodeIdx = 0;
		ReadUI(InFile, eNodeCountType, NodeIdx);

		// create POI node
		CXPOINode *pPOINode = new CXPOINode(*m_Nodes[NodeIdx]);
		// read POI type stuff
		unsigned char POITypeCount = 0;
		ReadUI8(InFile, POITypeCount);
		for(t_uint32 cnt = 0; cnt < POITypeCount; cnt++) {
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

	// way count
	unsigned char WayCountType = 0;
	if(!ReadUI8(InFile, WayCountType)) {
		DoOutputErrorMessage("Error reading WayCountType");
		return false;
	}
	E_BIT_COUNT eWayCountType=static_cast<E_BIT_COUNT>(WayCountType);
	t_uint32 WayCount = 0;
	if(!ReadUI(InFile, eWayCountType, WayCount)) {
		DoOutputErrorMessage("Error reading WayCount");
		return false;
	}
	CXMapHashSimple<char, TWayBuffer *> Ways;
	// read ways
	for(t_uint32 ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		unsigned char WayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		CXStringUTF8 IntRef;
		unsigned char MaxSpeed = 0;
		ReadUI8(InFile, WayType);
		unsigned char bLayer = 0;
		E_ONEWAY_TYPE eOneway = e_Oneway_None;
		// load locator information only in zoom level 0
		if(m_TOC.GetZoomLevel() == e_ZoomLevel_0) {
			t_uint16 DataType = 0;
			ReadUI16(InFile, DataType);
			if((DataType & e_Tag_Name) != 0)
				ReadStringUTF8(InFile, Name);
			if((DataType & e_Tag_Ref) != 0)
				ReadStringUTF8(InFile, Ref);
			if((DataType & e_Tag_IntRef) != 0)
				ReadStringUTF8(InFile, IntRef);
			if((DataType & e_Tag_MaxSpeed) != 0)
				ReadUI8(InFile, MaxSpeed);
			if((DataType & e_Tag_Layer) != 0)
				ReadUI8(InFile, bLayer);
			if((DataType & e_Tag_Oneway) != 0) {
				unsigned char Oneway = 0;
				ReadUI8(InFile, Oneway);
				eOneway = static_cast<E_ONEWAY_TYPE>(Oneway);
			}
		} else {
			ReadUI8(InFile, bLayer);
		}
		char Layer = 0;
		if((bLayer & 0x80) != 0)
			// negative value
			Layer = - (bLayer & 0x7F);
		else {
			// positive value
			Layer = bLayer;
		}
		// create way
		CXWay *pWay = new CXWay(static_cast<E_WAY_TYPE>(WayType), Name, Ref, IntRef);
		pWay->SetMaxSpeed(MaxSpeed);
		pWay->SetLayer(Layer);
		pWay->SetOneway(eOneway);
		// add way
		TWayBuffer *pWayBuffer = NULL;
		if(!Ways.Lookup(Layer, pWayBuffer)) {
			Ways.SetAt(Layer, new TWayBuffer());
		}
		Ways.Lookup(Layer, pWayBuffer);
		pWayBuffer->Append(pWay);
		// read nodes of way
		ReadUI(InFile, eNodeCountType, NodeCount);
		for(t_uint32 ul=0; ul<NodeCount; ul++) {
			t_uint32 Idx = 0;
			ReadUI(InFile, eNodeCountType, Idx);
			CXNode *pNode = m_Nodes[Idx];
			pWay->AddNode(pNode);
		}
	}
	char Layer = 0;
	// fill m_WayMapBuffer ordered by Layer ascending
	for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		TWayBuffer *pWayBuffer = NULL;
		Ways.Lookup(Layer, pWayBuffer);
		TWayBuffer *pOld = m_LayeredWayBuffer[Layer - MINLAYER];
		if(pOld != NULL)
			delete pOld;
		m_LayeredWayBuffer[Layer - MINLAYER] = pWayBuffer;
	}
	
	// area count
	unsigned char AreaCountType = 0;
	if(!ReadUI8(InFile, AreaCountType)) {
		DoOutputErrorMessage("Error reading AreaCountType");
		return false;
	}
	E_BIT_COUNT eAreaCountType=static_cast<E_BIT_COUNT>(AreaCountType);
	t_uint32 AreaCount = 0;
	if(!ReadUI(InFile, eAreaCountType, AreaCount)) {
		DoOutputErrorMessage("Error reading AreaCount");
		return false;
	}
	CXMapHashSimple<char, TAreaBuffer *> Areas;
	// read Areas
	for(t_uint32 ulArea=0; ulArea<AreaCount; ulArea++) {
		// read Area: Idx, node count, node ids
		unsigned char AreaType = 0;
		ReadUI8(InFile, AreaType);
		unsigned char bLayer = 0;
		// load locator information only in zoom level 0
		ReadUI8(InFile, bLayer);
		char Layer = 0;
		if((bLayer & 0x80) != 0)
			// negative value
			Layer = - (bLayer & 0x7F);
		else {
			// positive value
			Layer = bLayer;
		}
		// create Area
		CXArea *pArea = new CXArea(static_cast<E_AREA_TYPE>(AreaType));
		pArea->SetLayer(Layer);
		// add Area
		TAreaBuffer *pAreaBuffer = NULL;
		if(!Areas.Lookup(Layer, pAreaBuffer)) {
			Areas.SetAt(Layer, new TAreaBuffer());
		}
		Areas.Lookup(Layer, pAreaBuffer);
		pAreaBuffer->Append(pArea);

		// read nodes of Area
		ReadUI(InFile, eNodeCountType, NodeCount);
		for(t_uint32 ul=0; ul<NodeCount; ul++) {
			t_uint32 Idx = 0;
			ReadUI(InFile, eNodeCountType, Idx);
			CXNode *pNode = m_Nodes[Idx];
			pArea->AddNode(pNode);
		}
	}
	// fill m_AreaMapBuffer ordered by Layer ascending
	for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		TAreaBuffer *pAreaBuffer = NULL;
		Areas.Lookup(Layer, pAreaBuffer);
		TAreaBuffer *pOld = m_LayeredAreaBuffer[Layer - MINLAYER];
		if(pOld != NULL)
			delete pOld;
		m_LayeredAreaBuffer[Layer - MINLAYER] = pAreaBuffer;
	}

	// run OSMVali only on level 0
	if(m_TOC.GetZoomLevel() == e_ZoomLevel_0)
		RunOSMVali();
	return true;
}

//-------------------------------------
bool CXMapSection::LoadMap_0_1_2(CXFile & InFile) {
	// Node count type
	unsigned char NodeCountType = 0;
	if(!ReadUI8(InFile, NodeCountType)) {
		DoOutputErrorMessage("Error reading NodeCountType");
		return false;
	}
	E_BIT_COUNT eNodeCountType=static_cast<E_BIT_COUNT>(NodeCountType);
	// read place count
	t_uint32 NodeCount = 0;
	if(!ReadUI(InFile, eNodeCountType, NodeCount)) {
		DoOutputErrorMessage("Error reading NodeCount");
		return false;
	}
	if(NodeCount == 0) {
		// no further data to read
		return true;
	}
	m_Nodes.Resize(NodeCount);
	for(t_uint32 ulNode=0; ulNode<NodeCount; ulNode++) {
		// read node
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);
		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);
		// create node
		CXNode *pNode = new CXNode(dLon, dLat);

		// add node to Node buffer
		m_Nodes[ulNode] = pNode;
		// first node is terminator node
		if(ulNode == 0)
			pNode->SetTerminator();
	}

	// Place count type
	unsigned char PlaceCountType = 0;
	if(!ReadUI8(InFile, PlaceCountType)) {
		DoOutputErrorMessage("Error reading PlaceCountType");
		return false;
	}
	E_BIT_COUNT ePlaceCountType=static_cast<E_BIT_COUNT>(PlaceCountType);
	// read place count
	t_uint32 PlaceCount = 0;
	if(!ReadUI(InFile, ePlaceCountType, PlaceCount)) {
		DoOutputErrorMessage("Error reading PlaceCount");
		return false;
	}
	m_PlaceNodes.Resize(PlaceCount);
	for(t_uint32 ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
		// read node index
		t_uint32 NodeIdx = 0;
		ReadUI(InFile, eNodeCountType, NodeIdx);

		// create Place node
		CXPOINode *pPlaceNode = new CXPOINode(*m_Nodes[NodeIdx]);
		// read Place type stuff
		unsigned char Place = 0;
		ReadUI8(InFile, Place);
		E_MAP_PLACE_TYPE PlaceType = static_cast<E_MAP_PLACE_TYPE>(Place);
		pPlaceNode->SetPlaceType(PlaceType);

		// read name
		CXStringUTF8 Name;
		ReadStringUTF8(InFile, Name);
		pPlaceNode->SetName(Name);

		// add node to Place buffer
		m_PlaceNodes[ulPlace] = pPlaceNode;
	}


	// read POIs
	unsigned char POICountType = 0;
	if(!ReadUI8(InFile, POICountType)) {
		DoOutputErrorMessage("Error reading POICountType");
		return false;
	}
	E_BIT_COUNT ePOICountType=static_cast<E_BIT_COUNT>(POICountType);
	t_uint32 POICount = 0;
	if(!ReadUI(InFile, ePOICountType, POICount)) {
		DoOutputErrorMessage("Error reading POICount");
		return false;
	}
	m_POINodes.Resize(POICount);
	for(t_uint32 ulPOI=0; ulPOI<POICount; ulPOI++) {
		// read node index
		t_uint32 NodeIdx = 0;
		ReadUI(InFile, eNodeCountType, NodeIdx);

		// create POI node
		CXPOINode *pPOINode = new CXPOINode(*m_Nodes[NodeIdx]);
		// read POI type stuff
		unsigned char POITypeCount = 0;
		ReadUI8(InFile, POITypeCount);
		for(t_uint32 cnt = 0; cnt < POITypeCount; cnt++) {
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

	// way count
	unsigned char WayCountType = 0;
	if(!ReadUI8(InFile, WayCountType)) {
		DoOutputErrorMessage("Error reading WayCountType");
		return false;
	}
	E_BIT_COUNT eWayCountType=static_cast<E_BIT_COUNT>(WayCountType);
	t_uint32 WayCount = 0;
	if(!ReadUI(InFile, eWayCountType, WayCount)) {
		DoOutputErrorMessage("Error reading WayCount");
		return false;
	}
	CXMapHashSimple<char, TWayBuffer *> Ways;
	// read ways
	for(t_uint32 ulWay=0; ulWay<WayCount; ulWay++) {
		// read Way: Idx, Name, node count, node ids
		unsigned char WayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		CXStringUTF8 IntRef;
		unsigned char MaxSpeed = 0;
		ReadUI8(InFile, WayType);
		unsigned char bLayer = 0;
		E_ONEWAY_TYPE eOneway = e_Oneway_None;
		// load locator information only in zoom level 0
		if(m_TOC.GetZoomLevel() == e_ZoomLevel_0) {
			t_uint16 DataType = 0;
			ReadUI16(InFile, DataType);
			if((DataType & e_Tag_Name) != 0)
				ReadStringUTF8(InFile, Name);
			if((DataType & e_Tag_Ref) != 0)
				ReadStringUTF8(InFile, Ref);
			if((DataType & e_Tag_IntRef) != 0)
				ReadStringUTF8(InFile, IntRef);
			if((DataType & e_Tag_MaxSpeed) != 0)
				ReadUI8(InFile, MaxSpeed);
			if((DataType & e_Tag_Layer) != 0)
				ReadUI8(InFile, bLayer);
			if((DataType & e_Tag_Oneway) != 0) {
				unsigned char Oneway = 0;
				ReadUI8(InFile, Oneway);
				eOneway = static_cast<E_ONEWAY_TYPE>(Oneway);
			}
		} else {
			ReadUI8(InFile, bLayer);
		}
		char Layer = 0;
		if((bLayer & 0x80) != 0)
			// negative value
			Layer = - (bLayer & 0x7F);
		else {
			// positive value
			Layer = bLayer;
		}
		// create way
		CXWay *pWay = new CXWay(static_cast<E_WAY_TYPE>(WayType), Name, Ref, IntRef);
		pWay->SetMaxSpeed(MaxSpeed);
		pWay->SetLayer(Layer);
		pWay->SetOneway(eOneway);
		// add way
		TWayBuffer *pWayBuffer = NULL;
		if(!Ways.Lookup(Layer, pWayBuffer)) {
			Ways.SetAt(Layer, new TWayBuffer());
		}
		Ways.Lookup(Layer, pWayBuffer);
		pWayBuffer->Append(pWay);
		// read nodes of way
		ReadUI(InFile, eNodeCountType, NodeCount);
		for(t_uint32 ul=0; ul<NodeCount; ul++) {
			t_uint32 Idx = 0;
			ReadUI(InFile, eNodeCountType, Idx);
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
	
	// run OSMVali only on level 0
	if(m_TOC.GetZoomLevel() == e_ZoomLevel_0)
		RunOSMVali();
	return true;
}

//-------------------------------------
bool CXMapSection::LoadMap_0_1_1(CXFile & InFile) {
	// Place count
	t_uint32 PlaceCount = 0;
	if(!ReadUI32(InFile, PlaceCount)) {
		DoOutputErrorMessage("Error reading PlaceCount");
		return false;
	}
	m_PlaceNodes.Resize(PlaceCount);
	for(t_uint32 ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
		// read node
		t_uint32 Lon = 0; 
		t_uint32 Lat = 0;
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);
		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);
		// create Place node
		CXPOINode *pPlaceNode = new CXPOINode(dLon, dLat);
		// read Place type stuff
		t_uint16 POI = 0;
		ReadUI16(InFile, POI);
		E_POI_TYPE POIType = static_cast<E_POI_TYPE>(POI);
		E_MAP_PLACE_TYPE PlaceType = e_MapPlace_Small;
		// convert old POI values to new place values
		if(POIType == 0x23) {
			PlaceType = e_MapPlace_Small;
		} else if(POIType == 0x24) {
			PlaceType = e_MapPlace_Medium;
		} else if(POIType == 0x25) {
			PlaceType = e_MapPlace_Large;
		}
		pPlaceNode->SetPlaceType(PlaceType);

		// read name
		CXStringUTF8 Name;
		ReadStringUTF8(InFile, Name);
		pPlaceNode->SetName(Name);

		// add node to Place buffer
		m_PlaceNodes[ulPlace] = pPlaceNode;
	}

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
		ReadUI8(InFile, POICount);
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
		ReadUI8(InFile, IsTerminator);
		ReadUI32(InFile, Lon);
		ReadUI32(InFile, Lat);

		// compute lon
		double dLon = ConvertSavedUI32(Lon);
		double dLat = ConvertSavedUI32(Lat);

		CXNode *pNode = new CXNode(dLon, dLat);
		// create node
		if(IsTerminator != 0) {
			// terminator node
			pNode->SetTerminator();
		}

		// and add to m_Nodes
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
		unsigned char WayType = 0;
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		unsigned char MaxSpeed = 0;
		ReadUI8(InFile, WayType);
		// load locator information only in zoom level 0
		if(m_TOC.GetZoomLevel() == e_ZoomLevel_0) {
			ReadStringUTF8(InFile, Name);
			ReadStringUTF8(InFile, Ref);
			ReadUI8(InFile, MaxSpeed);
		}
		unsigned char bLayer = 0;
		ReadUI8(InFile, bLayer);
		char Layer = 0;
		if((bLayer & 0x80) != 0)
			// negative value
			Layer = - (bLayer & 0x7F);
		else {
			// positive value
			Layer = bLayer;
		}
		// create way
		CXWay *pWay = new CXWay(static_cast<E_WAY_TYPE>(WayType), Name, Ref, "");
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
	// run OSMVali only on level 0
	if(m_TOC.GetZoomLevel() == e_ZoomLevel_0)
		RunOSMVali();
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
				// check if way should be used for OSM validation
				E_WAY_TYPE eWayType = pWay->GetWayType();
				bool oUseForVali = false;
				switch(eWayType) {
					case e_Way_Fading:			break;	// no
					case e_Way_Unknown:			break;	// no
					case e_Way_Motorway:		oUseForVali = true; break; // yes
					case e_Way_MotorwayLink:	oUseForVali = true; break; // yes
					case e_Way_Trunk:			oUseForVali = true; break; // yes
					case e_Way_TrunkLink:		oUseForVali = true; break; // yes
					case e_Way_Primary:			oUseForVali = true; break; // yes
					case e_Way_PrimaryLink:		oUseForVali = true; break; // yes
					case e_Way_Secondary:		oUseForVali = true; break; // yes
					case e_Way_Tertiary:		oUseForVali = true; break; // yes
					case e_Way_Unclassified:	oUseForVali = true; break; // yes
					case e_Way_Track:			break;	// no
					case e_Way_Residential:		oUseForVali = true; break; // yes
					case e_Way_Service:			oUseForVali = true; break; // yes
					case e_Way_Bridleway:		break;	// no
					case e_Way_Cycleway:		break;	// no
					case e_Way_Footway:			break;	// no
					case e_Way_Pedestrian:		break;	// no
					case e_Way_Steps:			break;	// no
					case e_Way_LivingStreet:	oUseForVali = true; break; // yes
					case e_Way_NationalBorder:	break;	// no
					case e_Way_Railway_Thick:	oUseForVali = true; break; // yes
					case e_Way_Railway_Thin:	oUseForVali = true; break; // yes
					case e_Way_Water_Thick:		break;	// no
					case e_Way_Water_Thin:		break;	// no
					case e_Way_EnumCount:		break;	// no
				}
				bool Vali = true;
				if((pWay != NULL) && oUseForVali) {
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
					pWay->SetOSMValiOK(Vali);
				}
			}
		}
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
		for(size_t j=0; j<m_PlaceNodes.GetSize(); j++) {
			m_PlaceNodes[j]->RelocateUTM(m_UTMZone);
		}
	}
}


//-------------------------------------
void CXMapSection::ComputeDisplayCoordinates(const CXTransformationMatrix2D & TM) {
	// run coordinate transformation for every node
	const TNodeBuffer & Nodes = GetNodes();
	size_t Size = Nodes.GetSize();
	for(size_t idx = 0; idx < Size; idx++) {
		CXNode *pNode = Nodes[idx];
		if(pNode != NULL) {
			CXCoorVector v = TM*CXCoorVector(pNode->GetUTME(), pNode->GetUTMN());
			pNode->SetDisplayX(v.GetIntX());
			pNode->SetDisplayY(v.GetIntY());
		}
	}
	const TPOINodeBuffer & POINodes = GetPOINodes();
	for(size_t i=0; i<POINodes.GetSize(); i++) {
		CXPOINode *pPOINode = POINodes[i];
		CXCoorVector v = TM*CXCoorVector(pPOINode->GetUTME(), pPOINode->GetUTMN());
		pPOINode->SetDisplayX(v.GetIntX());
		pPOINode->SetDisplayY(v.GetIntY());
	}
	const TPOINodeBuffer & PlaceNodes = GetPlaceNodes();
	for(size_t j=0; j<PlaceNodes.GetSize(); j++) {
		CXPOINode *pPlaceNode = PlaceNodes[j];
		CXCoorVector v = TM*CXCoorVector(pPlaceNode->GetUTME(), pPlaceNode->GetUTMN());
		pPlaceNode->SetDisplayX(v.GetIntX());
		pPlaceNode->SetDisplayY(v.GetIntY());
	}
}
