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

#include "CXArea.hpp"
//----------------------------------------------------------------------------
//-------------------------------------
CXArea::CXArea(E_AREA_TYPE eAreaType):
	m_eAreaType(eAreaType),
	m_Layer(0)
{
}

//-------------------------------------
CXArea::~CXArea() {
}

//-------------------------------------
E_AREA_TYPE CXArea::GetAreaType() const {
	return m_eAreaType;
}

//-------------------------------------
void CXArea::SetLayer(char NewValue) {
	m_Layer = NewValue;
}

//-------------------------------------
unsigned char CXArea::GetLayer() const {
	return m_Layer;
}
//-------------------------------------
void CXArea::AddNode(CXNode *pNode) {
	if(pNode != NULL) {
		m_Nodes.Append(pNode);
	}
}

//-------------------------------------
size_t CXArea::GetNodeCount() const {
	return m_Nodes.GetSize();
}

//-------------------------------------
CXNode *CXArea::GetNode(size_t Index) const {
	return m_Nodes[Index];
}
