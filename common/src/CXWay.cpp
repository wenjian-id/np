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

#include "CXWay.hpp"
//----------------------------------------------------------------------------
//-------------------------------------
CXWay::CXWay(E_WAY_TYPE eWayType, const CXStringUTF8 & Name, const CXStringUTF8 & Ref, const CXStringUTF8 & IntRef):
	m_eWayType(eWayType),
	m_Name(Name),
	m_Ref(Ref),
	m_IntRef(IntRef),
	m_MaxSpeed(0),
	m_Layer(0),
	m_eOneway(e_Oneway_None),
	m_oOSMValiOK(true),
	m_pNodeList(NULL)
{
}

//-------------------------------------
CXWay::~CXWay() {
}

//-------------------------------------
CXOrderedNodeList *CXWay::GetNodeList() const {
	return m_pNodeList;
}

//-------------------------------------
void CXWay::SetNodeList(CXOrderedNodeList *pNodeList) {
	m_pNodeList = pNodeList;
}

//-------------------------------------
E_WAY_TYPE CXWay::GetWayType() const {
	return m_eWayType;
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
CXStringUTF8 CXWay::GetIntRef() const {
	return m_IntRef;
}

//-------------------------------------
void CXWay::SetMaxSpeed(unsigned char NewValue) {
	m_MaxSpeed = NewValue;
}

//-------------------------------------
unsigned char CXWay::GetMaxSpeed() const {
	return m_MaxSpeed;
}

//-------------------------------------
void CXWay::SetLayer(char NewValue) {
	m_Layer = NewValue;
}

//-------------------------------------
unsigned char CXWay::GetLayer() const {
	return m_Layer;
}

//-------------------------------------
void CXWay::SetOneway(E_ONEWAY_TYPE NewValue) {
	m_eOneway = NewValue;
}

//-------------------------------------
E_ONEWAY_TYPE CXWay::GetOneway() const {
	return m_eOneway;
}

//-------------------------------------
bool CXWay::IsOSMValiOK() const {
	return m_oOSMValiOK;
}

//-------------------------------------
void CXWay::SetOSMValiOK(bool NewValue) {
	m_oOSMValiOK = NewValue;
}
