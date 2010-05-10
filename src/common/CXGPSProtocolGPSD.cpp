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

#include "CXGPSProtocolGPSD.hpp"
#include "CXSatelliteData.hpp"

//-------------------------------------
CXGPSProtocolGPSD::CXGPSProtocolGPSD():
	CXGPSProtocol()
{
}

//-------------------------------------
CXGPSProtocolGPSD::~CXGPSProtocolGPSD() {
}

//-------------------------------------
bool CXGPSProtocolGPSD::AfterOpen() {
	// nothing to do
	return true;
}

//-------------------------------------
bool CXGPSProtocolGPSD::BeforeClose() {
	// nothing to do
	return true;
}

//-------------------------------------
bool CXGPSProtocolGPSD::OnReadAndProcessData() {
	CXGPSPosInfo GPSPosInfo;
	bool oGPSPosInfoChanged = false;
	CXGPSCourseInfo GPSCourseInfo;
	bool oGPSCourseInfoChanged = false;
	CXGPSQualityInfo GPSQualityInfo;
	bool oGPSQualityInfoChanged = false;
	// check if new data received
	if(m_pInputChannel->Read(GPSPosInfo, oGPSPosInfoChanged, GPSCourseInfo, oGPSCourseInfoChanged, GPSQualityInfo, oGPSQualityInfoChanged)) {
		CXSatellites::Instance()->SetGPSDDataReceived();
		if(oGPSPosInfoChanged) {
			SetGPSPosInfo(GPSPosInfo);
			// save gpx data
			if(GPSPosInfo.HasFix()) {
				SaveGPXData(GPSPosInfo.GetLon(), GPSPosInfo.GetLat(), GPSPosInfo.GetHeight());
			}
		}
		if(oGPSCourseInfoChanged) {
			SetGPSCourseInfo(GPSCourseInfo);
		}
		if(oGPSQualityInfoChanged) {
			SetGPSQualityInfo(GPSQualityInfo);
		}
		return true;
	}
	return false;
}
