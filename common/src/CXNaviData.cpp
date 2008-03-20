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
	m_dLon(0.0),
	m_dLat(0.0),
	m_dHeight(0.0),
	m_RMCSpeed(0),
	m_MaxSpeed(0),
	m_WayID(0), m_oLocated(false),
	m_oTimeout(false),
	m_TargetDist(0.0),
	m_TargetCos(0.0),
	m_TargetSin(0.0)
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
	m_dLon			= rOther.m_dLon;
	m_dLat			= rOther.m_dLat;
	m_dHeight		= rOther.m_dHeight;
	m_Coor			= rOther.m_Coor;
	m_UTMSpeed		= rOther.m_UTMSpeed;
	m_RMCSpeed		= rOther.m_RMCSpeed;
	m_StreetName	= rOther.m_StreetName;
	m_Ref			= rOther.m_Ref;
	m_MaxSpeed		= rOther.m_MaxSpeed;
	m_WayID			= rOther.m_WayID;
	m_oLocated		= rOther.m_oLocated;
	m_oTimeout		= rOther.m_oTimeout;
	m_TargetDist	= rOther.m_TargetDist;
	m_TargetCos		= rOther.m_TargetCos;
	m_TargetSin		= rOther.m_TargetSin;
}

//-------------------------------------
double CXNaviData::GetLon() const {
	CXReadLocker RL(&m_RWLock);
	return m_dLon;
}

//-------------------------------------
void CXNaviData::SetLon(double dLon) {
	CXWriteLocker WL(&m_RWLock);
	m_dLon = dLon;
}

//-------------------------------------
double CXNaviData::GetLat() const {
	CXReadLocker RL(&m_RWLock);
	return m_dLat;
}

//-------------------------------------
void CXNaviData::SetLat(double dLat) {
	CXWriteLocker WL(&m_RWLock);
	m_dLat = dLat;
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
void CXNaviData::SetUTMSpeedGGA(const CXUTMSpeed & UTMSpeed) {
	CXWriteLocker WL(&m_RWLock);
	m_UTMSpeed = UTMSpeed;
}

//-------------------------------------
double CXNaviData::GetRMCSpeed() const {
	CXReadLocker RL(&m_RWLock);
	return m_RMCSpeed;
}

//-------------------------------------
void CXNaviData::SetRMCSpeed(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_RMCSpeed = NewValue;
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

//-------------------------------------
void CXNaviData::SetTargetDist(double Value) {
	CXWriteLocker WL(&m_RWLock);
	m_TargetDist = Value;
}

//-------------------------------------
double CXNaviData::GetTargetDist() const {
	CXReadLocker RL(&m_RWLock);
	return m_TargetDist;
}

//-------------------------------------
void CXNaviData::SetTargetCos(double Value) {
	CXWriteLocker WL(&m_RWLock);
	m_TargetCos = Value;
}

//-------------------------------------
double CXNaviData::GetTargetCos() const {
	CXReadLocker RL(&m_RWLock);
	return m_TargetCos;
}

//-------------------------------------
void CXNaviData::SetTargetSin(double Value) {
	CXWriteLocker WL(&m_RWLock);
	m_TargetSin = Value;
}

//-------------------------------------
double CXNaviData::GetTargetSin() const {
	CXReadLocker RL(&m_RWLock);
	return m_TargetSin;
}

