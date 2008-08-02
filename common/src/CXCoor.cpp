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

#include "CXCoor.hpp"

//-------------------------------------
CXCoor::CXCoor() :
	m_dLon(0),
	m_dLat(0)
{
}

//-------------------------------------
CXCoor::CXCoor(double dLon, double dLat) :
	m_dLon(dLon),
	m_dLat(dLat)
{
	RelocateUTM(UTMZoneNone);
}

//-------------------------------------
CXCoor::CXCoor(const CXCoor &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXCoor::~CXCoor() {
}

//-------------------------------------
void CXCoor::RelocateUTM(int NewUTMZone) {
	// relocate only if neccessary
	if((NewUTMZone == UTMZoneNone) || (m_UTMCoor.GetUTMZone() != NewUTMZone)) {
		int NewZone = UTMZoneNone;
		char UTMLetter = 0;
		double UTME = 0;
		double UTMN = 0;
		LLtoUTM(WGS84, m_dLon, m_dLat, NewUTMZone, NewZone, UTMLetter, UTME, UTMN);
		m_UTMCoor.SetUTMZone(NewZone);
		m_UTMCoor.SetUTMLetter(UTMLetter);
		m_UTMCoor.SetUTMEasting(UTME);
		m_UTMCoor.SetUTMNorthing(UTMN);
	}
}

//-------------------------------------
const CXCoor & CXCoor::operator = (const CXCoor &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXCoor::CopyFrom(const CXCoor &rOther) {
	m_dLon = rOther.m_dLon;
	m_dLat = rOther.m_dLat;
	m_UTMCoor = rOther.m_UTMCoor;
}

//-------------------------------------
bool CXCoor::operator == (const CXCoor &rOther) {
	return ((m_dLon == rOther.m_dLon) && (m_dLat == rOther.m_dLat));
}

//-------------------------------------
bool CXCoor::operator != (const CXCoor &rOther) {
	return !operator ==(rOther);
}

//-------------------------------------
double CXCoor::GetLon() const {
	return m_dLon;
}

//-------------------------------------
double CXCoor::GetLat() const {
	return m_dLat;
}

//-------------------------------------
int CXCoor::GetUTMZone() const {
	return m_UTMCoor.GetUTMZone();
}

//-------------------------------------
char CXCoor::GetUTMLetter() const {
	return m_UTMCoor.GetUTMLetter();
}

//-------------------------------------
double CXCoor::GetUTMEasting() const {
	return m_UTMCoor.GetUTMEasting();
}

//-------------------------------------
double CXCoor::GetUTMNorthing() const {
	return m_UTMCoor.GetUTMNorthing();
}

//-------------------------------------
void CXCoor::OffsetCoor(double dUTME, double dUTMN) {
	// offset UTMCoor
	m_UTMCoor.OffsetCoor(dUTME, dUTMN);
	// and compute lon / lat
	UTMtoLL(WGS84, m_UTMCoor.GetUTMEasting(), m_UTMCoor.GetUTMNorthing(), m_UTMCoor.GetUTMZone(), m_UTMCoor.GetUTMLetter(), m_dLon, m_dLat);
}
