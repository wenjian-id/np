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
#include "CXSatelliteData.hpp"
#include "CXMutexLocker.hpp"

#include <math.h>
#include <iostream>

//-------------------------------------
CXGPSDClientBase::CXGPSDClientBase() {
}

//-------------------------------------
CXGPSDClientBase::~CXGPSDClientBase() {
}

//-------------------------------------
void CXGPSDClientBase::ClearBuffer(CXBuffer<CXSatelliteInfo *> & rBuffer) {
	for(size_t i=0; i<rBuffer.GetSize(); i++)
		delete rBuffer[i];
	rBuffer.Clear();
}

//-------------------------------------
void CXGPSDClientBase::DoProcessData(gps_data_t *pGPSData) {
	CXMutexLocker ML(&m_Mutex);
	std::cout << "x " << pGPSData->set << std::flush;
	if(pGPSData == NULL)
		return;
	if(pGPSData->set & MODE_SET) {
		bool oFix = (pGPSData->fix.mode >= MODE_2D);
		m_GPSPosInfo.SetFix(oFix);
		m_GPSCourseInfo.SetFix(oFix);
		m_oGPSPosInfoChanged = true;
		m_oGPSCourseInfoChanged = true;
	}
	if(pGPSData->set & ONLINE_SET) {
		std::cout << "o" << std::flush;
	}
	if(pGPSData->set & TIME_SET) {
		std::cout << "t" << std::flush;
		time_t t = pGPSData->fix.time;
		double dFract = pGPSData->fix.time - floor(pGPSData->fix.time);
		struct tm * ptm = gmtime(&t);
		double dUTC = ptm->tm_hour*10000 + ptm->tm_min*100 + ptm->tm_sec + dFract;
		std::cout << dUTC << " " << std::flush;
		CXUTCTime UTC(dUTC);
		std::cout << UTC.GetUTCTimeAsString().c_str() << " " << std::flush;
		m_GPSPosInfo.SetUTC(UTC);
		m_GPSCourseInfo.SetUTC(UTC);
		m_oGPSPosInfoChanged = true;
		m_oGPSCourseInfoChanged = true;
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
		m_GPSCourseInfo.SetSpeed(pGPSData->fix.speed);
		m_oGPSCourseInfoChanged = true;
	}
	if(pGPSData->set & TRACK_SET) {
		std::cout << "c" << std::flush;
		m_GPSCourseInfo.SetCourse(pGPSData->fix.track);
		m_oGPSCourseInfoChanged = true;
	}
	if(pGPSData->set & STATUS_SET) {
		std::cout << "u" << std::flush;
		std::cout << " " << pGPSData->status << " " << std::flush;
	}
	if(pGPSData->set & DOP_SET) {
		double HDOP = 0;
		double VDOP = 0;
		ReadDOP(pGPSData, HDOP, VDOP);
		m_GPSQualityInfo.SetHDOP(HDOP);
		m_GPSQualityInfo.SetVDOP(VDOP);
		m_oGPSQualityInfoChanged = true;
	}
	if(pGPSData->set & SATELLITE_SET) {
		std::cout << "sat in view" << std::flush;
		int NrSatVisible = 0;
		ReadNumberOfVisibleSatellites(pGPSData, NrSatVisible);
		std::cout << " " << NrSatVisible << " " << std::flush;
		CXBuffer<CXSatelliteInfo *> SatInfoBuffer;
		if(NrSatVisible > 0) {
			for(int i=0; i<NrSatVisible; i++) {
				CXSatelliteInfo *pInfo = new CXSatelliteInfo();
				pInfo->SetPRN(pGPSData->PRN[i]);
    			pInfo->SetElevation(pGPSData->elevation[i]);
    			pInfo->SetAzimuth(pGPSData->azimuth[i]);
    			pInfo->SetSNR(pGPSData->ss[i]);
				SatInfoBuffer.Append(pInfo);
			}
		}
		CXSatellites::Instance()->SetSatelliteInfos(SatInfoBuffer);
   		ClearBuffer(SatInfoBuffer);
	}
	if(pGPSData->set & USED_SET) {
		std::cout << "sat used" << std::flush;
		std::cout << " " << pGPSData->satellites_used << " " << std::flush;
		m_GPSPosInfo.SetNSat(pGPSData->satellites_used);
		m_oGPSPosInfoChanged = true;
		CXBuffer<int> ActiveSatBuffer;
		if(pGPSData->satellites_used > 0)
		for(int i=0; i<pGPSData->satellites_used; i++) {
			ActiveSatBuffer.Append(pGPSData->used[i]);
		}
		CXSatellites::Instance()->SetActiveSatellites(ActiveSatBuffer);
	}
	std::cout << std::endl;
}

