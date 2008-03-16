/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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

#include "CXGSVSatelliteInfo.hpp"


//----------------------------------------------------------------------------
//-------------------------------------
CXGSVSatelliteInfo::CXGSVSatelliteInfo() :
	m_PRN(0),
	m_Elevation(0),
	m_Azimuth(0),
	m_SNR(0)
{
}

//-------------------------------------
CXGSVSatelliteInfo::CXGSVSatelliteInfo(const CXGSVSatelliteInfo &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXGSVSatelliteInfo::~CXGSVSatelliteInfo() {
}

//-------------------------------------
const CXGSVSatelliteInfo & CXGSVSatelliteInfo::operator = (const CXGSVSatelliteInfo &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXGSVSatelliteInfo::CopyFrom(const CXGSVSatelliteInfo &rOther) {
	m_PRN		= rOther.m_PRN;
	m_Elevation	= rOther.m_Elevation;
	m_Azimuth	= rOther.m_Azimuth;
	m_SNR		= rOther.m_SNR;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetPRN() const {
	return m_PRN;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetPRN(int NewValue) {
	m_PRN = NewValue;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetElevation() const {
	return m_Elevation;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetElevation(int NewValue) {
	m_Elevation = NewValue;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetAzimuth() const {
	return m_Azimuth;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetAzimuth(int NewValue) {
	m_Azimuth = NewValue;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetSNR() const {
	return m_SNR;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetSNR(int NewValue) {
	m_SNR = NewValue;
}

