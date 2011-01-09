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
    m_ZoomLevel(e_ZoomLevel_0),
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
CXTOCMapSection::CXTOCMapSection(const CXTOCMapSection &rOther) :
    m_UID(0),
    m_ZoomLevel(e_ZoomLevel_0),
    m_dLonMin(0),
    m_dLonMax(0),
    m_dLatMin(0),
    m_dLatMax(0),
    m_Offset(0)
{
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
        delete pNode;
    }
    // delete POIs
    size_t Size_poi = m_POINodes.GetSize();
    for(size_t idx_poi = 0; idx_poi < Size_poi; idx_poi++) {
        CXNode *pNode = m_POINodes[idx_poi];
        delete pNode;
    }
    // delete nodes
    size_t Size_nodes = m_Nodes.GetSize();
    for(size_t idx_n = 0; idx_n < Size_nodes; idx_n++) {
        CXNode *pNode = m_Nodes[idx_n];
        delete pNode;
    }
    size_t Size_nodelists = m_NodeLists.GetSize();
    for(size_t idx_nl = 0; idx_nl < Size_nodelists; idx_nl++) {
        CXOrderedNodeList *pNodeList = m_NodeLists[idx_nl];
        delete pNodeList;
    }
    size_t Size_ways = m_Ways.GetSize();
    for(size_t idx_w = 0; idx_w < Size_ways; idx_w++) {
        CXWay *pWay = m_Ways[idx_w];
        delete pWay;
    }
    // delete waybuffers
    size_t Size_waybuffers = m_LayeredWayBuffer.GetSize();
    for(size_t idx_wb=0; idx_wb<Size_waybuffers; idx_wb++) {
        TWayBuffer *pWayBuffer = m_LayeredWayBuffer[idx_wb];
        delete pWayBuffer;
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
    Result = Result && (InFile.SetReadAheadSize(1000) == CXFile::E_OK);
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
        if(Version == 0x00010300) {
            // v 0.1.3
            Result = LoadMap_0_1_3(InFile);
        } else if(Version != ReqVersion) {
            // not supported version
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
    t_uint32 ulNode=0;
    for(ulNode=0; ulNode<NodeCount; ulNode++) {
        m_Nodes[ulNode] = NULL;
    }
    for(ulNode=0; ulNode<NodeCount; ulNode++) {
        // read node
        t_uint32 Lon = 0;
        t_uint32 Lat = 0;
        if(!ReadUI32(InFile, Lon)) {
            DoOutputErrorMessage("Error reading Lon");
            return false;
        }
        if(!ReadUI32(InFile, Lat)) {
            DoOutputErrorMessage("Error reading Lat");
            return false;
        }
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
    t_uint32 ulPlace=0;
    for(ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
        m_PlaceNodes[ulPlace] = NULL;
    }
    for(ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
        // read node index
        t_uint32 NodeIdx = 0;
        if(!ReadUI(InFile, eNodeCountType, NodeIdx)) {
            DoOutputErrorMessage("Error reading NodeIdx");
            return false;
        }

        // read Place type stuff
        unsigned char Place = 0;
        if(!ReadUI8(InFile, Place)) {
            DoOutputErrorMessage("Error reading Place");
            return false;
        }
        E_MAP_PLACE_TYPE PlaceType = static_cast<E_MAP_PLACE_TYPE>(Place);

        // read name
        CXStringUTF8 Name;
        if(!ReadStringUTF8(InFile, Name)) {
            DoOutputErrorMessage("Error reading Name");
            return false;
        }

        // create Place node
        CXPOINode *pPlaceNode = new CXPOINode(*m_Nodes[NodeIdx]);
        pPlaceNode->SetPlaceType(PlaceType);
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
    t_uint32 ulPOI=0;
    for(ulPOI=0; ulPOI<POICount; ulPOI++) {
        m_POINodes[ulPOI] = NULL;
    }
    for(ulPOI=0; ulPOI<POICount; ulPOI++) {
        // read node index
        t_uint32 NodeIdx = 0;
        if(!ReadUI(InFile, eNodeCountType, NodeIdx)) {
            DoOutputErrorMessage("Error reading NodeIdx");
            return false;
        }

        // create POI node
        CXPOINode *pPOINode = new CXPOINode(*m_Nodes[NodeIdx]);
        // read POI type stuff
        unsigned char POITypeCount = 0;
        if(!ReadUI8(InFile, POITypeCount)) {
            DoOutputErrorMessage("Error reading POITypeCount");
            delete pPOINode;
            return false;
        }
        for(t_uint32 cnt = 0; cnt < POITypeCount; cnt++) {
            t_uint16 POI = 0;
            if(!ReadUI16(InFile, POI)) {
                DoOutputErrorMessage("Error reading POI");
                delete pPOINode;
                return false;
            }
            E_POI_TYPE POIType = static_cast<E_POI_TYPE>(POI);
            pPOINode->SetPOIType(POIType);
        }

        // read name
        CXStringUTF8 Name;
        if(!ReadStringUTF8(InFile, Name)) {
            DoOutputErrorMessage("Error reading Name");
            delete pPOINode;
            return false;
        }
        pPOINode->SetName(Name);

        // add node to POI buffer
        m_POINodes[ulPOI] = pPOINode;
    }

    // node list count
    unsigned char NodeListCountType = 0;
    if(!ReadUI8(InFile, NodeListCountType)) {
        DoOutputErrorMessage("Error reading NodeListCountType");
        return false;
    }
    E_BIT_COUNT eNodeListCountType=static_cast<E_BIT_COUNT>(NodeListCountType);
    t_uint32 NodeListCount = 0;
    if(!ReadUI(InFile, eNodeListCountType, NodeListCount)) {
        DoOutputErrorMessage("Error reading NodeListCount");
        return false;
    }
    m_NodeLists.Resize(NodeListCount);
    t_uint32 ulNodeList=0;
    // read node lists
    for(ulNodeList=0; ulNodeList<NodeListCount; ulNodeList++) {
        m_NodeLists[ulNodeList] = NULL;
    }
    for(ulNodeList=0; ulNodeList<NodeListCount; ulNodeList++) {
        // create node list
        CXOrderedNodeList *pNodeList = new CXOrderedNodeList();
        if(!ReadUI(InFile, eNodeCountType, NodeCount)) {
            DoOutputErrorMessage("Error reading NodeCount");
            delete pNodeList;
            return false;
        }
        for(t_uint32 ul=0; ul<NodeCount; ul++) {
            t_uint32 Idx = 0;
            if(!ReadUI(InFile, eNodeCountType, Idx)) {
                DoOutputErrorMessage("Error reading Idx");
                delete pNodeList;
                return false;
            }
            CXNode *pNode = m_Nodes[Idx];
            pNodeList->AddNode(pNode);
        }
        m_NodeLists[ulNodeList] = pNodeList;
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
    m_Ways.Resize(WayCount);
    CXMapHashSimple<char, TWayBuffer *> Ways;
    // read ways
    t_uint32 ulWay=0;
    for(ulWay=0; ulWay<WayCount; ulWay++) {
        m_Ways[ulWay] = NULL;
    }
    for(ulWay=0; ulWay<WayCount; ulWay++) {
        // read Way: Idx, Name, node count, node ids
        unsigned char WayType = 0;
        CXStringUTF8 Name;
        CXStringUTF8 Ref;
        CXStringUTF8 IntRef;
        unsigned char MaxSpeedForward = 0;
        unsigned char MaxSpeedBackward = 0;
        if(!ReadUI8(InFile, WayType)) {
            DoOutputErrorMessage("Error reading WayType");
            return false;
        }
        unsigned char bLayer = 0;
        E_ONEWAY_TYPE eOneway = e_Oneway_None;
        // load locator information only in zoom level 0
        if(m_TOC.GetZoomLevel() == e_ZoomLevel_0) {
            t_uint16 DataType = 0;
            if(!ReadUI16(InFile, DataType)) {
                DoOutputErrorMessage("Error reading DataType");
                return false;
            }
            if((DataType & e_TagType_Name) != 0) {
                if(!ReadStringUTF8(InFile, Name)) {
                    DoOutputErrorMessage("Error reading Name");
                    return false;
                }
            }
            if((DataType & e_TagType_Ref) != 0) {
                if(!ReadStringUTF8(InFile, Ref)) {
                    DoOutputErrorMessage("Error reading Ref");
                    return false;
                }
            }
            if((DataType & e_TagType_IntRef) != 0) {
                if(!ReadStringUTF8(InFile, IntRef)) {
                    DoOutputErrorMessage("Error reading IntRef");
                    return false;
                }
            }
            if((DataType & e_TagType_MaxSpeedForward) != 0) {
                if(!ReadUI8(InFile, MaxSpeedForward)) {
                    DoOutputErrorMessage("Error reading MaxSpeedForward");
                    return false;
                }
            }
            if((DataType & e_TagType_MaxSpeedBackward) != 0) {
                if(!ReadUI8(InFile, MaxSpeedBackward)) {
                    DoOutputErrorMessage("Error reading MaxSpeedBackward");
                    return false;
                }
            }
            if((DataType & e_TagType_Layer) != 0) {
                if(!ReadUI8(InFile, bLayer)) {
                    DoOutputErrorMessage("Error reading bLayer");
                    return false;
                }
            }
            if((DataType & e_TagType_Oneway) != 0) {
                unsigned char Oneway = 0;
                if(!ReadUI8(InFile, Oneway)) {
                    DoOutputErrorMessage("Error reading Oneway");
                    return false;
                }
                eOneway = static_cast<E_ONEWAY_TYPE>(Oneway);
            }
        } else {
            if(!ReadUI8(InFile, bLayer)) {
                DoOutputErrorMessage("Error reading bLayer");
                return false;
            }
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
        m_Ways[ulWay] = pWay;
        pWay->SetMaxSpeedForward(MaxSpeedForward);
        pWay->SetMaxSpeedBackward(MaxSpeedBackward);
        pWay->SetLayer(Layer);
        pWay->SetOneway(eOneway);
        // add way
        TWayBuffer *pWayBuffer = NULL;
        if(!Ways.Lookup(Layer, pWayBuffer)) {
            Ways.SetAt(Layer, new TWayBuffer());
        }
        if(!Ways.Lookup(Layer, pWayBuffer)) {
            DoOutputErrorMessage("Something went completely wrong... 1");
            return false;
        }
        pWayBuffer->Append(pWay);
        // read node list of way
        t_uint32 Idx = 0;
        if(!ReadUI(InFile, eNodeListCountType, Idx)) {
            DoOutputErrorMessage("Error reading Idx");
            return false;
        }
        CXOrderedNodeList *pNodeList = m_NodeLists[Idx];
        pWay->SetNodeList(pNodeList);
    }
    char Layer = 0;
    // fill m_WayMapBuffer ordered by Layer ascending
    for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
        TWayBuffer *pWayBuffer = NULL;
        if(!Ways.Lookup(Layer, pWayBuffer)){
            TWayBuffer *pOld = m_LayeredWayBuffer[Layer - MINLAYER];
            delete pOld;
        }
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
        if(!ReadUI8(InFile, AreaType)) {
            DoOutputErrorMessage("Error reading AreaType");
            return false;
        }
        // layer
        unsigned char bLayer = 0;
        if(!ReadUI8(InFile, bLayer)) {
            DoOutputErrorMessage("Error reading bLayer");
            return false;
        }
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
        // read outer way
        t_uint32 Idx = 0;
        if(!ReadUI(InFile, eNodeListCountType, Idx)) {
            DoOutputErrorMessage("Error reading bLayer");
            delete pArea;
            return false;
        }
        CXOrderedNodeList *pOuterNodeList = m_NodeLists[Idx];
        pArea->SetOuterNodeList(pOuterNodeList);
        // read hole count
        t_uint32 HoleCount = 0;
        if(!ReadUI(InFile, eNodeListCountType, HoleCount)) {
            DoOutputErrorMessage("Error reading HoleCount");
            delete pArea;
            return false;
        }
        // read holes
        for(size_t h=0; h<HoleCount; h++) {
            t_uint32 IdxH = 0;
            if(!ReadUI(InFile, eNodeListCountType, IdxH)) {
                DoOutputErrorMessage("Error reading IdxH");
                delete pArea;
                return false;
            }
            CXOrderedNodeList *pHole = m_NodeLists[IdxH];
            pArea->AddHole(pHole);
        }
        // now insert area into Areas structure
        TAreaBuffer *pAreaBuffer = NULL;
        if(!Areas.Lookup(Layer, pAreaBuffer)) {
            Areas.SetAt(Layer, new TAreaBuffer());
        }
        if(!Areas.Lookup(Layer, pAreaBuffer)) {
            DoOutputErrorMessage("Something went completely wrong... 3");
            delete pArea;
            return false;
        }
        pAreaBuffer->Append(pArea);
    }
    // fill m_AreaMapBuffer ordered by Layer ascending
    for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
        TAreaBuffer *pAreaBuffer = NULL;
        if(!Areas.Lookup(Layer, pAreaBuffer)) {
            TAreaBuffer *pOld = m_LayeredAreaBuffer[Layer - MINLAYER];
            delete pOld;
        }
        m_LayeredAreaBuffer[Layer - MINLAYER] = pAreaBuffer;
    }

    // run OSMVali only on level 0
    if(m_TOC.GetZoomLevel() == e_ZoomLevel_0)
        RunOSMVali();
    return true;
}

//-------------------------------------
bool CXMapSection::LoadMap_0_1_3(CXFile & InFile) {
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
    t_uint32 ulNode=0;
    for(ulNode=0; ulNode<NodeCount; ulNode++) {
        m_Nodes[ulNode] = NULL;
    }
    for(ulNode=0; ulNode<NodeCount; ulNode++) {
        // read node
        t_uint32 Lon = 0;
        t_uint32 Lat = 0;
        if(!ReadUI32(InFile, Lon)) {
            DoOutputErrorMessage("Error reading Lon");
            return false;
        }
        if(!ReadUI32(InFile, Lat)) {
            DoOutputErrorMessage("Error reading Lat");
            return false;
        }
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
    t_uint32 ulPlace=0;
    for(ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
        m_PlaceNodes[ulPlace] = NULL;
    }
    for(ulPlace=0; ulPlace<PlaceCount; ulPlace++) {
        // read node index
        t_uint32 NodeIdx = 0;
        if(!ReadUI(InFile, eNodeCountType, NodeIdx)) {
            DoOutputErrorMessage("Error reading NodeIdx");
            return false;
        }

        // read Place type stuff
        unsigned char Place = 0;
        if(!ReadUI8(InFile, Place)) {
            DoOutputErrorMessage("Error reading Place");
            return false;
        }
        E_MAP_PLACE_TYPE PlaceType = static_cast<E_MAP_PLACE_TYPE>(Place);

        // read name
        CXStringUTF8 Name;
        if(!ReadStringUTF8(InFile, Name)) {
            DoOutputErrorMessage("Error reading Name");
            return false;
        }

        // create Place node
        CXPOINode *pPlaceNode = new CXPOINode(*m_Nodes[NodeIdx]);
        pPlaceNode->SetPlaceType(PlaceType);
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
    t_uint32 ulPOI=0;
    for(ulPOI=0; ulPOI<POICount; ulPOI++) {
        m_POINodes[ulPOI] = NULL;
    }
    for(ulPOI=0; ulPOI<POICount; ulPOI++) {
        // read node index
        t_uint32 NodeIdx = 0;
        if(!ReadUI(InFile, eNodeCountType, NodeIdx)) {
            DoOutputErrorMessage("Error reading NodeIdx");
            return false;
        }

        // create POI node
        CXPOINode *pPOINode = new CXPOINode(*m_Nodes[NodeIdx]);
        // read POI type stuff
        unsigned char POITypeCount = 0;
        if(!ReadUI8(InFile, POITypeCount)) {
            DoOutputErrorMessage("Error reading POITypeCount");
            delete pPOINode;
            return false;
        }
        for(t_uint32 cnt = 0; cnt < POITypeCount; cnt++) {
            t_uint16 POI = 0;
            if(!ReadUI16(InFile, POI)) {
                DoOutputErrorMessage("Error reading POI");
                delete pPOINode;
                return false;
            }
            E_POI_TYPE POIType = static_cast<E_POI_TYPE>(POI);
            pPOINode->SetPOIType(POIType);
        }

        // read name
        CXStringUTF8 Name;
        if(!ReadStringUTF8(InFile, Name)) {
            DoOutputErrorMessage("Error reading Name");
            delete pPOINode;
            return false;
        }
        pPOINode->SetName(Name);

        // add node to POI buffer
        m_POINodes[ulPOI] = pPOINode;
    }

    // node list count
    unsigned char NodeListCountType = 0;
    if(!ReadUI8(InFile, NodeListCountType)) {
        DoOutputErrorMessage("Error reading NodeListCountType");
        return false;
    }
    E_BIT_COUNT eNodeListCountType=static_cast<E_BIT_COUNT>(NodeListCountType);
    t_uint32 NodeListCount = 0;
    if(!ReadUI(InFile, eNodeListCountType, NodeListCount)) {
        DoOutputErrorMessage("Error reading NodeListCount");
        return false;
    }
    m_NodeLists.Resize(NodeListCount);
    t_uint32 ulNodeList=0;
    // read node lists
    for(ulNodeList=0; ulNodeList<NodeListCount; ulNodeList++) {
        m_NodeLists[ulNodeList] = NULL;
    }
    for(ulNodeList=0; ulNodeList<NodeListCount; ulNodeList++) {
        // create node list
        CXOrderedNodeList *pNodeList = new CXOrderedNodeList();
        m_NodeLists[ulNodeList] = pNodeList;
        if(!ReadUI(InFile, eNodeCountType, NodeCount)) {
            DoOutputErrorMessage("Error reading NodeCount");
            delete pNodeList;
            return false;
        }
        for(t_uint32 ul=0; ul<NodeCount; ul++) {
            t_uint32 Idx = 0;
            if(!ReadUI(InFile, eNodeCountType, Idx)) {
                DoOutputErrorMessage("Error reading Idx");
                delete pNodeList;
                return false;
            }
            CXNode *pNode = m_Nodes[Idx];
            pNodeList->AddNode(pNode);
        }
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
    m_Ways.Resize(WayCount);
    CXMapHashSimple<char, TWayBuffer *> Ways;
    // read ways
    t_uint32 ulWay=0;
    for(ulWay=0; ulWay<WayCount; ulWay++) {
        m_Ways[ulWay] = NULL;
    }
    for(ulWay=0; ulWay<WayCount; ulWay++) {
        // read Way: Idx, Name, node count, node ids
        unsigned char WayType = 0;
        CXStringUTF8 Name;
        CXStringUTF8 Ref;
        CXStringUTF8 IntRef;
        unsigned char MaxSpeedForward = 0;
        unsigned char MaxSpeedBackward = 0;
        if(!ReadUI8(InFile, WayType)) {
            DoOutputErrorMessage("Error reading WayType");
            return false;
        }
        unsigned char bLayer = 0;
        E_ONEWAY_TYPE eOneway = e_Oneway_None;
        // load locator information only in zoom level 0
        if(m_TOC.GetZoomLevel() == e_ZoomLevel_0) {
            t_uint16 DataType = 0;
            if(!ReadUI16(InFile, DataType)) {
                DoOutputErrorMessage("Error reading DataType");
                return false;
            }
            if((DataType & e_TagType_Name) != 0) {
                if(!ReadStringUTF8(InFile, Name)) {
                    DoOutputErrorMessage("Error reading Name");
                    return false;
                }
            }
            if((DataType & e_TagType_Ref) != 0) {
                if(!ReadStringUTF8(InFile, Ref)) {
                    DoOutputErrorMessage("Error reading Ref");
                    return false;
                }
            }
            if((DataType & e_TagType_IntRef) != 0) {
                if(!ReadStringUTF8(InFile, IntRef)) {
                    DoOutputErrorMessage("Error reading IntRef");
                    return false;
                }
            }
            if((DataType & e_TagType_MaxSpeedForward) != 0) {
                if(!ReadUI8(InFile, MaxSpeedForward)) {
                    DoOutputErrorMessage("Error reading MaxSpeedForward");
                    return false;
                }
            }
            if((DataType & e_TagType_MaxSpeedBackward) != 0) {
                if(!ReadUI8(InFile, MaxSpeedBackward)) {
                    DoOutputErrorMessage("Error reading MaxSpeedBackward");
                    return false;
                }
            }
            if((DataType & e_TagType_Layer) != 0) {
                if(!ReadUI8(InFile, bLayer)) {
                    DoOutputErrorMessage("Error reading bLayer");
                    return false;
                }
            }
            if((DataType & e_TagType_Oneway) != 0) {
                unsigned char Oneway = 0;
                if(!ReadUI8(InFile, Oneway)) {
                    DoOutputErrorMessage("Error reading Oneway");
                    return false;
                }
                eOneway = static_cast<E_ONEWAY_TYPE>(Oneway);
            }
        } else {
            if(!ReadUI8(InFile, bLayer)) {
                DoOutputErrorMessage("Error reading bLayer");
                return false;
            }
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
        m_Ways[ulWay] = pWay;
        pWay->SetMaxSpeedForward(MaxSpeedForward);
        pWay->SetMaxSpeedBackward(MaxSpeedBackward);
        pWay->SetLayer(Layer);
        pWay->SetOneway(eOneway);
        // add way
        TWayBuffer *pWayBuffer = NULL;
        if(!Ways.Lookup(Layer, pWayBuffer)) {
            Ways.SetAt(Layer, new TWayBuffer());
        }
        if(!Ways.Lookup(Layer, pWayBuffer)) {
            DoOutputErrorMessage("Something went completely wrong... 5");
            return false;
        }
        pWayBuffer->Append(pWay);
        // read node list of way
        t_uint32 Idx = 0;
        if(!ReadUI(InFile, eNodeListCountType, Idx)) {
            DoOutputErrorMessage("Error reading Idx");
            return false;
        }
        CXOrderedNodeList *pNodeList = m_NodeLists[Idx];
        pWay->SetNodeList(pNodeList);
    }
    char Layer = 0;
    // fill m_WayMapBuffer ordered by Layer ascending
    for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
        TWayBuffer *pWayBuffer = NULL;
        if(!Ways.Lookup(Layer, pWayBuffer)){
            TWayBuffer *pOld = m_LayeredWayBuffer[Layer - MINLAYER];
            delete pOld;
        }
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
        if(!ReadUI8(InFile, AreaType)) {
            DoOutputErrorMessage("Error reading AreaType");
            return false;
        }
        // layer
        unsigned char bLayer = 0;
        if(!ReadUI8(InFile, bLayer)) {
            DoOutputErrorMessage("Error reading bLayer");
            return false;
        }
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
        // read outer way
        t_uint32 Idx = 0;
        if(!ReadUI(InFile, eNodeListCountType, Idx)) {
            DoOutputErrorMessage("Error reading bLayer");
            delete pArea;
            return false;
        }
        CXOrderedNodeList *pOuterNodeList = m_NodeLists[Idx];
        pArea->SetOuterNodeList(pOuterNodeList);
        // read hole count
        t_uint32 HoleCount = 0;
        if(!ReadUI(InFile, eNodeListCountType, HoleCount)) {
            DoOutputErrorMessage("Error reading HoleCount");
            delete pArea;
            return false;
        }
        // read holes
        for(size_t h=0; h<HoleCount; h++) {
            t_uint32 IdxH = 0;
            if(!ReadUI(InFile, eNodeListCountType, IdxH)) {
                DoOutputErrorMessage("Error reading IdxH");
                delete pArea;
                return false;
            }
            CXOrderedNodeList *pHole = m_NodeLists[IdxH];
            pArea->AddHole(pHole);
        }
        // now insert area into Areas structure
        TAreaBuffer *pAreaBuffer = NULL;
        if(!Areas.Lookup(Layer, pAreaBuffer)) {
            Areas.SetAt(Layer, new TAreaBuffer());
        }
        if(!Areas.Lookup(Layer, pAreaBuffer)) {
            DoOutputErrorMessage("Something went completely wrong... 7");
            delete pArea;
            return false;
        }
        pAreaBuffer->Append(pArea);
    }
    // fill m_AreaMapBuffer ordered by Layer ascending
    for(Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
        TAreaBuffer *pAreaBuffer = NULL;
        if(!Areas.Lookup(Layer, pAreaBuffer)) {
            TAreaBuffer *pOld = m_LayeredAreaBuffer[Layer - MINLAYER];
            delete pOld;
        }
        m_LayeredAreaBuffer[Layer - MINLAYER] = pAreaBuffer;
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
            size_t Size = pWayBuffer->GetSize();
            for(size_t idx=0; idx<Size; idx++) {
                pWay = (*pWayBuffer)[idx];
                // check if way should be used for OSM validation
                E_WAY_TYPE eWayType = pWay->GetWayType();
                bool oUseForVali = false;
                switch(eWayType) {
                    case e_Way_Fading:          break;  // no
                    case e_Way_Unknown:         break;  // no
                    case e_Way_Motorway:        oUseForVali = true; break; // yes
                    case e_Way_MotorwayLink:    oUseForVali = true; break; // yes
                    case e_Way_Trunk:           oUseForVali = true; break; // yes
                    case e_Way_TrunkLink:       oUseForVali = true; break; // yes
                    case e_Way_Primary:         oUseForVali = true; break; // yes
                    case e_Way_PrimaryLink:     oUseForVali = true; break; // yes
                    case e_Way_Secondary:       oUseForVali = true; break; // yes
                    case e_Way_Tertiary:        oUseForVali = true; break; // yes
                    case e_Way_Unclassified:    oUseForVali = true; break; // yes
                    case e_Way_Track:           break;  // no
                    case e_Way_Residential:     oUseForVali = true; break; // yes
                    case e_Way_Service:         oUseForVali = true; break; // yes
                    case e_Way_Bridleway:       break;  // no
                    case e_Way_Cycleway:        break;  // no
                    case e_Way_Footway:         break;  // no
                    case e_Way_Pedestrian:      break;  // no
                    case e_Way_Steps:           break;  // no
                    case e_Way_LivingStreet:    oUseForVali = true; break; // yes
                    case e_Way_Railway_Thick:   oUseForVali = true; break; // yes
                    case e_Way_Railway_Thin:    oUseForVali = true; break; // yes
                    case e_Way_Water_Thick:     break;  // no
                    case e_Way_Water_Thin:      break;  // no
                    case e_Way_BorderThick:     break;  // no
                    case e_Way_BorderMedium:    break;  // no
                    case e_Way_BorderThin:      break;  // no
                    case e_Way_Path:            break;  // no
                    case e_Way_EnumCount:       break;  // no
                }
                bool Vali = true;
                if((pWay != NULL) && oUseForVali) {
                    if(CXOptions::Instance()->IsOSMValiFlagSet(CXOptions::e_OSMValiName)) {
                        // check name
                        if(pWay->GetName().IsEmpty()) {
                            Vali = false;
                        }
                    }
                    if(CXOptions::Instance()->IsOSMValiFlagSet(CXOptions::e_OSMValiRef)) {
                        // check ref
                        if(pWay->GetRef().IsEmpty()) {
                            Vali = false;
                        }
                    }
                    if(CXOptions::Instance()->IsOSMValiFlagSet(CXOptions::e_OSMValiMaxSpeed)) {
                        // check max speed
                        if((pWay->GetMaxSpeedForward() == 0) || (pWay->GetMaxSpeedBackward() == 0)) {
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
