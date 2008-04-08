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

#include "CXNaviData.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"


//-------------------------------------
CXNaviData::CXNaviData() :
	m_dHeight(0.0),
	m_MaxSpeed(0),
	m_WayID(0), m_oLocated(false),
	m_oTimeout(false)
{
}

//-------------------------------------
CXNaviData::~CXNaviData() {
}

//-------------------------------------
CXNaviData::CXNaviData(const CXNaviData &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
const CXNaviData & CXNaviData::operator = (const CXNaviData &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXNaviData::CopyFrom(const CXNaviData &rOther) {
	CXReadLocker RL(&rOther.m_RWLock);
	CXWriteLocker WL(&m_RWLock);
	m_dHeight		= rOther.m_dHeight;
	m_Coor			= rOther.m_Coor;
	m_UTMSpeed		= rOther.m_UTMSpeed;
	m_StreetName	= rOther.m_StreetName;
	m_Ref			= rOther.m_Ref;
	m_MaxSpeed		= rOther.m_MaxSpeed;
	m_WayID			= rOther.m_WayID;
	m_oLocated		= rOther.m_oLocated;
	m_oTimeout		= rOther.m_oTimeout;
}

//-------------------------------------
double CXNaviData::GetLon() const {
	CXReadLocker RL(&m_RWLock);
	return m_Coor.GetLon();
}

//-------------------------------------
double CXNaviData::GetLat() const {
	CXReadLocker RL(&m_RWLock);
	return m_Coor.GetLat();
}

//-------------------------------------
double CXNaviData::GetHeight() const {
	CXReadLocker RL(&m_RWLock);
	return m_dHeight;
}

//-------------------------------------
void CXNaviData::SetHeight(double dHeight) {
	CXWriteLocker WL(&m_RWLock);
	m_dHeight = dHeight;
}

//-------------------------------------
CXCoor CXNaviData::GetCoor() const {
	CXReadLocker RL(&m_RWLock);
	return m_Coor;
}

//-------------------------------------
void CXNaviData::SetCoor(const CXCoor &Coor) {
	CXWriteLocker WL(&m_RWLock);
	m_Coor = Coor;
}

//-------------------------------------
CXUTMSpeed CXNaviData::GetUTMSpeed() const {
	CXReadLocker RL(&m_RWLock);
	return m_UTMSpeed;
}

//-------------------------------------
void CXNaviData::SetUTMSpeed(const CXUTMSpeed & UTMSpeed) {
	CXWriteLocker WL(&m_RWLock);
	m_UTMSpeed = UTMSpeed;
}

//-------------------------------------
CXStringUTF8 CXNaviData::GetStreetName() const {
	CXReadLocker RL(&m_RWLock);
	return m_StreetName;
}

//-------------------------------------
void CXNaviData::SetStreetName(const CXStringUTF8 & StreetName) {
	CXWriteLocker WL(&m_RWLock);
	m_StreetName = StreetName;
}

//-------------------------------------
CXStringUTF8 CXNaviData::GetRef() const {
	CXReadLocker RL(&m_RWLock);
	return m_Ref;
}

//-------------------------------------
void CXNaviData::SetRef(const CXStringUTF8 & Ref) {
	CXWriteLocker WL(&m_RWLock);
	m_Ref = Ref;
}

//-------------------------------------
unsigned char CXNaviData::GetMaxSpeed() const {
	CXReadLocker RL(&m_RWLock);
	return m_MaxSpeed;
}

//-------------------------------------
void CXNaviData::SetMaxSpeed(unsigned char MaxSpeed) {
	CXWriteLocker WL(&m_RWLock);
	m_MaxSpeed = MaxSpeed;
}

//-------------------------------------
t_uint64 CXNaviData::GetWayID() const {
	CXReadLocker RL(&m_RWLock);
	return m_WayID;
}

//-------------------------------------
void CXNaviData::SetWayID(t_uint64 ID) {
	CXWriteLocker WL(&m_RWLock);
	m_WayID = ID;
}

//-------------------------------------
bool CXNaviData::GetLocated() const {
	CXReadLocker RL(&m_RWLock);
	return m_oLocated;
}

//-------------------------------------
void CXNaviData::SetLocated(bool Value) {
	CXWriteLocker WL(&m_RWLock);
	m_oLocated = Value;
}

//-------------------------------------
bool CXNaviData::IsTimeout() const {
	CXReadLocker RL(&m_RWLock);
	return m_oTimeout;
}

//-------------------------------------
void CXNaviData::SetTimeout(bool Value) {
	CXWriteLocker WL(&m_RWLock);
	m_oTimeout = Value;
}

