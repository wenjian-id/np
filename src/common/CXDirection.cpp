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

#include "CXDirection.hpp"

//-------------------------------------
CXDirection::CXDirection():
    m_dCos(1),
    m_dSin(0)
{
}

//-------------------------------------
CXDirection::CXDirection(double dCos, double dSin):
    m_dCos(dCos),
    m_dSin(dSin)
{
}

//-------------------------------------
CXDirection::CXDirection(const CXDirection &rOther) :
    m_dCos(0),
    m_dSin(0)
{
    CopyFrom(rOther);
}

//-------------------------------------
CXDirection::~CXDirection() {
}

//-------------------------------------
void CXDirection::CopyFrom(const CXDirection &rOther) {
    m_dCos = rOther.m_dCos;
    m_dSin = rOther.m_dSin;
}

//-------------------------------------
const CXDirection & CXDirection::operator = (const CXDirection &rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
bool CXDirection::operator == (const CXDirection & rOther) {
    return (m_dCos == rOther.m_dCos) && (m_dSin == rOther.m_dSin);
}

//-------------------------------------
CXDirection CXDirection::operator - () const {
    return CXDirection(m_dCos, -m_dSin);
}

//-------------------------------------
double CXDirection::GetCos() const {
    return m_dCos;
}

//-------------------------------------
double CXDirection::GetSin() const {
    return m_dSin;
}
