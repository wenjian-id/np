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
