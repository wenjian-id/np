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
#include "CXMutexLocker.hpp"


//-------------------------------------
CXNaviData::CXNaviData() :
	m_dLon(0.0),
	m_dLat(0.0),
	m_dHeight(0.0),
	m_nSat(0),
	m_MaxSpeed(0),
	m_WayID(0), m_oLocated(false),
	m_oTimeout(false),
	m_TargetDist(0.0),
	m_TargetCos(0.0),
	m_TargetSin(0.0),
	m_oChanged(false)
{
}

//-------------------------------------
CXNaviData::~CXNaviData() {
}

//-------------------------------------
CXNaviData::CXNaviData(const CXNaviData &rOther) {
	_CopyFrom(rOther);
}

//-------------------------------------
const CXNaviData & CXNaviData::operator = (const CXNaviData &rOther) {
	if(this != &rOther)
		_CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXNaviData::_CopyFrom(const CXNaviData &rOther) {
	CXMutexLocker L(&m_Mutex);
	CXMutexLocker Lo(&rOther.m_Mutex);
	m_dLon			= rOther.m_dLon;
	m_dLat			= rOther.m_dLat;
	m_dHeight		= rOther.m_dHeight;
	m_nSat			= rOther.m_nSat;
	m_UTMCoor		= rOther.m_UTMCoor;
	m_UTMSpeed		= rOther.m_UTMSpeed;
	m_StreetName	= rOther.m_StreetName;
	m_Ref			= rOther.m_Ref;
	m_MaxSpeed		= rOther.m_MaxSpeed;
	m_WayID			= rOther.m_WayID;
	m_oLocated		= rOther.m_oLocated;
	m_oTimeout		= rOther.m_oTimeout;
	m_TargetDist	= rOther.m_TargetDist;
	m_TargetCos		= rOther.m_TargetCos;
	m_TargetSin		= rOther.m_TargetSin;
	SetChangedFlag();
}

//-------------------------------------
double CXNaviData::GetLon() const {
	CXMutexLocker L(&m_Mutex);
	return m_dLon;
}

//-------------------------------------
void CXNaviData::SetLon(double dLon) {
	CXMutexLocker L(&m_Mutex);
	if(m_dLon != dLon)
		SetChangedFlag();
	m_dLon = dLon;
}

//-------------------------------------
double CXNaviData::GetLat() const {
	CXMutexLocker L(&m_Mutex);
	return m_dLat;
}

//-------------------------------------
void CXNaviData::SetLat(double dLat) {
	CXMutexLocker L(&m_Mutex);
	if(m_dLat != dLat)
		SetChangedFlag();
	m_dLat = dLat;
}

//-------------------------------------
double CXNaviData::GetHeight() const {
	CXMutexLocker L(&m_Mutex);
	return m_dHeight;
}

//-------------------------------------
void CXNaviData::SetHeight(double dHeight) {
	CXMutexLocker L(&m_Mutex);
	if(m_dHeight != dHeight)
		SetChangedFlag();
	m_dHeight = dHeight;
}

//-------------------------------------
int CXNaviData::GetnSat() const {
	CXMutexLocker L(&m_Mutex);
	return m_nSat;
}

//-------------------------------------
void CXNaviData::SetnSat(int nSat) {
	CXMutexLocker L(&m_Mutex);
	if(m_nSat != nSat)
		SetChangedFlag();
	m_nSat = nSat;
}

//-------------------------------------
CXUTMCoor CXNaviData::GetUTMCoor() const {
	CXMutexLocker L(&m_Mutex);
	return m_UTMCoor;
}

//-------------------------------------
void CXNaviData::SetUTMCoor(const CXUTMCoor &UTMCoor) {
	CXMutexLocker L(&m_Mutex);
	if(m_UTMCoor != UTMCoor)
		SetChangedFlag();
	m_UTMCoor = UTMCoor;
}

//-------------------------------------
CXUTMSpeed CXNaviData::GetUTMSpeed() const {
	CXMutexLocker L(&m_Mutex);
	return m_UTMSpeed;
}

//-------------------------------------
void CXNaviData::SetUTMSpeed(const CXUTMSpeed & UTMSpeed) {
	CXMutexLocker L(&m_Mutex);
	if(m_UTMSpeed != UTMSpeed)
		SetChangedFlag();
	m_UTMSpeed = UTMSpeed;
}


//-------------------------------------
CXStringUTF8 CXNaviData::GetStreetName() const {
	CXMutexLocker L(&m_Mutex);
	return m_StreetName;
}

//-------------------------------------
void CXNaviData::SetStreetName(const CXStringUTF8 & StreetName) {
	CXMutexLocker L(&m_Mutex);
	if(m_StreetName != StreetName)
		SetChangedFlag();
	m_StreetName = StreetName;
}

//-------------------------------------
CXStringUTF8 CXNaviData::GetRef() const {
	CXMutexLocker L(&m_Mutex);
	return m_Ref;
}

//-------------------------------------
void CXNaviData::SetRef(const CXStringUTF8 & Ref) {
	CXMutexLocker L(&m_Mutex);
	if(m_Ref != Ref)
		SetChangedFlag();
	m_Ref = Ref;
}

//-------------------------------------
unsigned char CXNaviData::GetMaxSpeed() const {
	CXMutexLocker L(&m_Mutex);
	return m_MaxSpeed;
}

//-------------------------------------
void CXNaviData::SetMaxSpeed(unsigned char MaxSpeed) {
	CXMutexLocker L(&m_Mutex);
	if(m_MaxSpeed != MaxSpeed)
		SetChangedFlag();
	m_MaxSpeed = MaxSpeed;
}

//-------------------------------------
t_uint64 CXNaviData::GetWayID() const {
	CXMutexLocker L(&m_Mutex);
	return m_WayID;
}

//-------------------------------------
void CXNaviData::SetWayID(t_uint64 ID) {
	CXMutexLocker L(&m_Mutex);
	if(m_WayID != ID)
		SetChangedFlag();
	m_WayID = ID;
}

//-------------------------------------
bool CXNaviData::GetLocated() const {
	CXMutexLocker L(&m_Mutex);
	return m_oLocated;
}

//-------------------------------------
void CXNaviData::SetLocated(bool Value) {
	CXMutexLocker L(&m_Mutex);
	if(m_oLocated != Value)
		SetChangedFlag();
	m_oLocated = Value;
}

//-------------------------------------
bool CXNaviData::IsTimeout() const {
	CXMutexLocker L(&m_Mutex);
	return m_oTimeout;
}

//-------------------------------------
void CXNaviData::SetTimeout(bool Value) {
	CXMutexLocker L(&m_Mutex);
	if(m_oTimeout != Value)
		SetChangedFlag();
	m_oTimeout = Value;
}

//-------------------------------------
void CXNaviData::SetTargetDist(double Value) {
	CXMutexLocker L(&m_Mutex);
	if(m_TargetDist != Value)
		SetChangedFlag();
	m_TargetDist = Value;
}

//-------------------------------------
double CXNaviData::GetTargetDist() const {
	CXMutexLocker L(&m_Mutex);
	return m_TargetDist;
}

//-------------------------------------
void CXNaviData::SetTargetCos(double Value) {
	CXMutexLocker L(&m_Mutex);
	if(m_TargetCos != Value)
		SetChangedFlag();
	m_TargetCos = Value;
}

//-------------------------------------
double CXNaviData::GetTargetCos() const {
	CXMutexLocker L(&m_Mutex);
	return m_TargetCos;
}

//-------------------------------------
void CXNaviData::SetTargetSin(double Value) {
	CXMutexLocker L(&m_Mutex);
	if(m_TargetSin != Value)
		SetChangedFlag();
	m_TargetSin = Value;
}

//-------------------------------------
double CXNaviData::GetTargetSin() const {
	CXMutexLocker L(&m_Mutex);
	return m_TargetSin;
}

//-------------------------------------
void CXNaviData::ClearChangedFlag() {
	CXMutexLocker L(&m_Mutex);
	m_oChanged = false;
}

//-------------------------------------
void CXNaviData::SetChangedFlag() {
	CXMutexLocker L(&m_Mutex);
	m_oChanged = true;
}

//-------------------------------------
bool CXNaviData::Changed() const {
	CXMutexLocker L(&m_Mutex);
	return m_oChanged;
}

