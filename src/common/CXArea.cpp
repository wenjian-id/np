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
    m_Layer(0),
    m_pOuterNodeList(NULL)
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
unsigned char CXArea::GetLayer() const {
    return m_Layer;
}

//-------------------------------------
void CXArea::SetLayer(unsigned char Layer) {
    m_Layer = Layer;
}

//-------------------------------------
void CXArea::SetOuterNodeList(CXOrderedNodeList *pNodeList) {
    m_pOuterNodeList = pNodeList;
}

//-------------------------------------
CXOrderedNodeList *CXArea::GetOuterNodeList() const {
    return m_pOuterNodeList;
}

//-------------------------------------
void CXArea::AddHole(CXOrderedNodeList *pNodeList) {
    m_Holes.Append(pNodeList);
}

//-------------------------------------
size_t CXArea::GetHoleCount() {
    return m_Holes.GetSize();
}

//-------------------------------------
CXOrderedNodeList *CXArea::GetHole(size_t Index) {
    return m_Holes[Index];
}
