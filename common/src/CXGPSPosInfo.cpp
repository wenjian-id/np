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

#include "CXGPSPosInfo.hpp"

//-------------------------------------
CXGPSPosInfo::CXGPSPosInfo() :
	m_oFix(false),
	m_dLon(0.0),
	m_dLat(0.0),
	m_dHeight(0.0),
	m_NSat(0)
{
}

//-------------------------------------
CXGPSPosInfo::CXGPSPosInfo(const CXStringASCII &UTC, bool oFix, double dLon, double dLat, double dHeight, int NSat) :
	m_UTC(UTC),
	m_oFix(oFix),
	m_dLon(dLon),
	m_dLat(dLat),
	m_dHeight(dHeight),
	m_NSat(NSat)
{
}

//-------------------------------------
CXGPSPosInfo::CXGPSPosInfo(const CXGPSPosInfo & rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXGPSPosInfo::~CXGPSPosInfo() {
}

//-------------------------------------
const CXGPSPosInfo & CXGPSPosInfo::operator = (const CXGPSPosInfo & rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXGPSPosInfo::CopyFrom(const CXGPSPosInfo &rOther) {
	m_UTC = rOther.m_UTC;
	m_oFix = rOther.m_oFix;
	m_dLon = rOther.m_dLon;
	m_dLat = rOther.m_dLat;
	m_dHeight = rOther.m_dHeight;
	m_NSat = rOther.m_NSat;
}

//-------------------------------------
CXStringASCII CXGPSPosInfo::GetUTC() const {
	return m_UTC;
}

//-------------------------------------
bool CXGPSPosInfo::GetFix() const {
	return m_oFix;
}

//-------------------------------------
double CXGPSPosInfo::GetLon() const {
	return m_dLon;
}

//-------------------------------------
double CXGPSPosInfo::GetLat() const {
	return m_dLat;
}

//-------------------------------------
double CXGPSPosInfo::GetHeight() const {
	return m_dHeight;
}

//-------------------------------------
int CXGPSPosInfo::GetNSat() const {
	return m_NSat;
}
