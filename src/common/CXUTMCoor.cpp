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

#include "CXUTMCoor.hpp"

//-------------------------------------
CXUTMCoor::CXUTMCoor() :
	m_UTMZone(UTMZoneNone),
	m_UTMLetter(UTMLetterNone),
	m_UTMEasting(0),
	m_UTMNorthing(0)
{
}

//-------------------------------------
CXUTMCoor::CXUTMCoor(int UTMZone, char UTMLetter, double UTMEasting, double UTMNorthing) :
	m_UTMZone(UTMZone),
	m_UTMLetter(UTMLetter),
	m_UTMEasting(UTMEasting),
	m_UTMNorthing(UTMNorthing)
{
}

//-------------------------------------
CXUTMCoor::CXUTMCoor(double dLon, double dLat) {
	m_UTMZone = UTMZoneNone;
	LLtoUTM(WGS84, dLon, dLat, UTMZoneNone, m_UTMZone, m_UTMLetter, m_UTMEasting, m_UTMNorthing);
}

//-------------------------------------
CXUTMCoor::CXUTMCoor(const CXUTMCoor &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXUTMCoor::~CXUTMCoor() {
}

//-------------------------------------
const CXUTMCoor & CXUTMCoor::operator = (const CXUTMCoor &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXUTMCoor::CopyFrom(const CXUTMCoor &rOther) {
	m_UTMZone = rOther.m_UTMZone;
	m_UTMLetter = rOther.m_UTMLetter;
	m_UTMEasting = rOther.m_UTMEasting;
	m_UTMNorthing = rOther.m_UTMNorthing;
}

//-------------------------------------
bool CXUTMCoor::operator == (const CXUTMCoor &rOther) {
	return (	
			(m_UTMZone == rOther.m_UTMZone) &&
			(m_UTMLetter == rOther.m_UTMLetter) &&
			(m_UTMEasting == rOther.m_UTMEasting) &&
			(m_UTMNorthing == rOther.m_UTMNorthing)
	);
}

//-------------------------------------
bool CXUTMCoor::operator != (const CXUTMCoor &rOther) {
	return !operator ==(rOther);
}

//-------------------------------------
int CXUTMCoor::GetUTMZone() const {
	return m_UTMZone;
}

//-------------------------------------
void CXUTMCoor::SetUTMZone(int NewValue) {
	m_UTMZone = NewValue;
}

//-------------------------------------
char CXUTMCoor::GetUTMLetter() const {
	return m_UTMLetter;
}

//-------------------------------------
void CXUTMCoor::SetUTMLetter(char NewValue) {
	m_UTMLetter = NewValue;
}

//-------------------------------------
double CXUTMCoor::GetUTMEasting() const {
	return m_UTMEasting;
}

//-------------------------------------
void CXUTMCoor::SetUTMEasting(double NewValue) {
	m_UTMEasting = NewValue;
}

//-------------------------------------
double CXUTMCoor::GetUTMNorthing() const {
	return m_UTMNorthing;
}

//-------------------------------------
void CXUTMCoor::SetUTMNorthing(double NewValue){
	m_UTMNorthing = NewValue;
}

//-------------------------------------
void CXUTMCoor::OffsetCoor(double dUTME, double dUTMN) {
	m_UTMEasting += dUTME;
	m_UTMNorthing += dUTMN;
}
