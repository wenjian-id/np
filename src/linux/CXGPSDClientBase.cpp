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

#include "CXGPSDClientBase.hpp"
#include "CXMutexLocker.hpp"

#include <iostream>

//-------------------------------------
CXGPSDClientBase::CXGPSDClientBase() :
	m_oGPSPosInfoChanged(false),
	m_oGPSCourseInfoChanged(false),
	m_oGPSQualityInfoChanged(false)
{
}

//-------------------------------------
CXGPSDClientBase::~CXGPSDClientBase() {
}


//-------------------------------------
bool CXGPSDClientBase::GPSPosInfoChanged() const {
	CXMutexLocker ML(&m_Mutex);
	return m_oGPSPosInfoChanged;
}

//-------------------------------------
CXGPSPosInfo CXGPSDClientBase::GetGPSPosInfo() const {
	CXMutexLocker ML(&m_Mutex);
	return m_GPSPosInfo;
}

//-------------------------------------
void CXGPSDClientBase::ResetGPSPosInfoChanged() {
	CXMutexLocker ML(&m_Mutex);
	m_oGPSPosInfoChanged = false;
}

//-------------------------------------
bool CXGPSDClientBase::GPSCourseInfoChanged() const {
	CXMutexLocker ML(&m_Mutex);
	return m_oGPSCourseInfoChanged;
}

//-------------------------------------
CXGPSCourseInfo CXGPSDClientBase::GetGPSCourseInfo() const {
	CXMutexLocker ML(&m_Mutex);
	return m_GPSCourseInfo;
}

//-------------------------------------
void CXGPSDClientBase::ResetGPSCourseInfoChanged() {
	CXMutexLocker ML(&m_Mutex);
	m_oGPSCourseInfoChanged = false;
}

//-------------------------------------
bool CXGPSDClientBase::GPSQualityInfoChanged() const {
	CXMutexLocker ML(&m_Mutex);
	return m_oGPSQualityInfoChanged;
}

//-------------------------------------
CXGPSQualityInfo CXGPSDClientBase::GetGPSQualityInfo() const {
	CXMutexLocker ML(&m_Mutex);
	return m_GPSQualityInfo;
}

//-------------------------------------
void CXGPSDClientBase::ResetGPSQualityInfoChanged() {
	CXMutexLocker ML(&m_Mutex);
	m_oGPSQualityInfoChanged = false;
}

//-------------------------------------
void CXGPSDClientBase::DoProcessData(gps_data_t *pGPSData) {
	CXMutexLocker ML(&m_Mutex);
	std::cout << "x" << std::flush;
//	SetGPSCourseInfo(CXGPSCourseInfo(RMCPacket.GetUTC(), RMCPacket.HasFix(), RMCPacket.GetSpeed(), RMCPacket.GetCourse()));

	if(pGPSData == NULL)
		return;
	if(pGPSData->set & FIX_SET) {
		bool oFix = (pGPSData->fix.mode >= MODE_2D);
		m_GPSPosInfo.SetFix(oFix);
		m_oGPSPosInfoChanged = true;
	}
	if(pGPSData->set & ONLINE_SET) {
		std::cout << "o" << std::flush;
	}
	if(pGPSData->set & TIME_SET) {
		std::cout << "t" << std::flush;
	}
	if(pGPSData->set & LATLON_SET) {
		if(pGPSData->fix.mode >= MODE_2D) {
			m_GPSPosInfo.SetLon(pGPSData->fix.longitude);
			m_GPSPosInfo.SetLat(pGPSData->fix.latitude);
			m_oGPSPosInfoChanged = true;
		}
	}
	if(pGPSData->set & ALTITUDE_SET) {
		std::cout << "a" << std::flush;
		if(pGPSData->fix.mode == MODE_3D) {
			m_GPSPosInfo.SetHeight(pGPSData->fix.altitude);
			m_oGPSPosInfoChanged = true;
		}
	}
	if(pGPSData->set & SPEED_SET) {
		std::cout << "s" << std::flush;
	}
	if(pGPSData->set & STATUS_SET) {
		std::cout << "u" << std::flush;
		std::cout << " " << pGPSData->status << " " << std::flush;
	}
	if(pGPSData->set & HDOP_SET) {
		m_GPSQualityInfo.SetHDOP(pGPSData->hdop);
		m_oGPSQualityInfoChanged = true;
	}
	if(pGPSData->set & VDOP_SET) {
		m_GPSQualityInfo.SetVDOP(pGPSData->vdop);
		m_oGPSQualityInfoChanged = true;
	}
	if(pGPSData->set & SATELLITE_SET) {
		std::cout << "sat in view" << std::flush;
		std::cout << " " << pGPSData->satellites << " " << std::flush;
	}
	if(pGPSData->set & USED_SET) {
		std::cout << "sat used" << std::flush;
		std::cout << " " << pGPSData->satellites_used << " " << std::flush;
	}
	std::cout << "t6" << std::endl;
}

