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

#include "CXTarget.hpp"

//-------------------------------------
CXTarget::CXTarget() {
}

//-------------------------------------
CXTarget::CXTarget(const CXStringUTF8 & Name, const CXCoor & Coor):
    m_Name(Name),
    m_Coor(Coor)
{
}

//-------------------------------------
CXTarget::CXTarget(const CXTarget &rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
CXTarget::~CXTarget() {
}

//-------------------------------------
const CXTarget & CXTarget::operator = (const CXTarget &rOther) {
    if(this != &rOther) {
        CopyFrom(rOther);
    }
    return *this;
}

//-------------------------------------
void CXTarget::CopyFrom(const CXTarget & rOther) {
    m_Name = rOther.m_Name;
    m_Coor = rOther.m_Coor;
}

//-------------------------------------
CXStringUTF8 CXTarget::GetName() const {
    return m_Name;
}

//-------------------------------------
CXCoor CXTarget::GetCoor() const {
    return m_Coor;
}

//-------------------------------------
void CXTarget::SetName(const CXStringUTF8 & Name) {
    m_Name = Name;
}

//-------------------------------------
void CXTarget::SetCoor(const CXCoor &Coor) {
    m_Coor = Coor;
}
