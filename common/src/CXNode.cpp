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

#include "CXNode.hpp"


//----------------------------------------------------------------------------
//-------------------------------------
CXNode::CXNode(double dLon, double dLat) :
	m_Coor(dLon, dLat),
	m_DisplayX(0),
	m_DisplayY(0),
	m_oTerminator(false)
{
}

//-------------------------------------
CXNode::CXNode(const CXNode &rOther) :
	m_Coor(rOther.m_Coor),
	m_DisplayX(rOther.m_DisplayX),
	m_DisplayY(rOther.m_DisplayY),
	m_oTerminator(rOther.m_oTerminator)
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

//-------------------------------------
bool CXNode::IsTerminator() const {
	return m_oTerminator;
}

//-------------------------------------
void CXNode::SetTerminator() {
	m_oTerminator = true;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXPOINode::CXPOINode(double Lon, double Lat) :
	CXNode(Lon, Lat)
{
}

//-------------------------------------
CXPOINode::CXPOINode(const CXNode &rNode) :
	CXNode(rNode)
{
}

//-------------------------------------
CXPOINode::~CXPOINode() {
}

//-------------------------------------
size_t CXPOINode::GetPOITypeCount() const {
	return m_POITypes.GetSize();
}

//-------------------------------------
E_POI_TYPE CXPOINode::GetPOIType(size_t Index) const {
	size_t idx = Index;
	if(idx >= m_POITypes.GetSize())
		return e_POI_None;
	return m_POITypes[Index];
}

//-------------------------------------
void CXPOINode::SetPOIType(E_POI_TYPE ePOIType) {
	/// \todo check if ePOIType already in list
	m_POITypes.Append(ePOIType);
}

//-------------------------------------
void CXPOINode::SetName(const CXStringUTF8 &NewValue) {
	m_Name = NewValue;
}

//-------------------------------------
CXStringUTF8 CXPOINode::GetName() const {
	return m_Name;
}

//-------------------------------------
E_MAP_PLACE_TYPE CXPOINode::GetPlaceType() const {
	return m_ePlaceType;
}
//-------------------------------------
void CXPOINode::SetPlaceType(E_MAP_PLACE_TYPE ePlaceType) {
	m_ePlaceType = ePlaceType;
}


//----------------------------------------------------------------------------
//-------------------------------------
CXOrderedNodeList::CXOrderedNodeList() {
}

//-------------------------------------
CXOrderedNodeList::~CXOrderedNodeList() {
}

//-------------------------------------
void CXOrderedNodeList::AddNode(CXNode *pNode) {
	if(pNode != NULL) {
		m_Nodes.Append(pNode);
	}
}

//-------------------------------------
size_t CXOrderedNodeList::GetNodeCount() const {
	return m_Nodes.GetSize();
}

//-------------------------------------
CXNode *CXOrderedNodeList::GetNode(size_t Index) const {
	return m_Nodes[Index];
}

