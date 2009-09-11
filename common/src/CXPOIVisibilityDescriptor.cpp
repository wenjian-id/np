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

#include "CXPOIVisibilityDescriptor.hpp"

//-------------------------------------
CXPOIVisibilityDescriptor::CXPOIVisibilityDescriptor() :
	m_oShowAll(false)
{
	for(int i=0; i<e_POI_EnumCount; i++)
		m_oVisibilityList[i] = false;
}

//-------------------------------------
CXPOIVisibilityDescriptor::CXPOIVisibilityDescriptor(const CXPOIVisibilityDescriptor &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXPOIVisibilityDescriptor::~CXPOIVisibilityDescriptor() {
}

//-------------------------------------
const CXPOIVisibilityDescriptor & CXPOIVisibilityDescriptor::operator = (const CXPOIVisibilityDescriptor &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::CopyFrom(const CXPOIVisibilityDescriptor &rOther) {
	m_oShowAll = rOther.m_oShowAll;
	for(int i=0; i<e_POI_EnumCount; i++)
		m_oVisibilityList[i] = rOther.m_oVisibilityList[i];
}

//-------------------------------------
bool CXPOIVisibilityDescriptor::MustShowAll() const {
	return m_oShowAll;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowAll(bool NewValue) {
	m_oShowAll = NewValue;
}

//-------------------------------------
bool CXPOIVisibilityDescriptor::MustShowPOIType(E_POI_TYPE ePOIType) const {
	if((ePOIType == e_POI_None) || (ePOIType == e_POI_All))
		return false;
	return m_oVisibilityList[ePOIType];
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowPOIType(E_POI_TYPE ePOIType, bool NewValue) {
	if((ePOIType == e_POI_None) || (ePOIType == e_POI_All))
		return;
	m_oVisibilityList[ePOIType] = NewValue;
}
