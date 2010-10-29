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

#include "CXGPSQualityInfo.hpp"

//-------------------------------------
CXGPSQualityInfo::CXGPSQualityInfo() :
    m_dHDOP(0.0),
    m_dVDOP(0.0)
{
}

//-------------------------------------
CXGPSQualityInfo::CXGPSQualityInfo(double dHDOP, double dVDOP) :
    m_dHDOP(dHDOP),
    m_dVDOP(dVDOP)
{
}

//-------------------------------------
CXGPSQualityInfo::CXGPSQualityInfo(const CXGPSQualityInfo & rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
CXGPSQualityInfo::~CXGPSQualityInfo() {
}

//-------------------------------------
const CXGPSQualityInfo & CXGPSQualityInfo::operator = (const CXGPSQualityInfo & rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXGPSQualityInfo::CopyFrom(const CXGPSQualityInfo &rOther) {
    m_dHDOP = rOther.m_dHDOP;
    m_dVDOP = rOther.m_dVDOP;
}

//-------------------------------------
double CXGPSQualityInfo::GetHDOP() const {
    return m_dHDOP;
}

//-------------------------------------
void CXGPSQualityInfo::SetHDOP(double NewValue) {
    m_dHDOP = NewValue;
}
//-------------------------------------
double CXGPSQualityInfo::GetVDOP() const {
    return m_dVDOP;
}

//-------------------------------------
void CXGPSQualityInfo::SetVDOP(double NewValue) {
    m_dVDOP = NewValue;
}
