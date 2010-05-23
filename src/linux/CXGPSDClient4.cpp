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


#include "CXGPSDClient4.hpp"

#if (GPSD_API_MAJOR_VERSION == 4)

//-------------------------------------
CXGPSDClient::CXGPSDClient() :
	m_pGPSData(NULL)
{
}

//-------------------------------------
CXGPSDClient::~CXGPSDClient() {
}

//-------------------------------------
bool CXGPSDClient::Open() {
	CXGPSDConfig Cfg = GetConfig();
	m_pGPSData = gps_open(Cfg.GetAddress().c_str(), Cfg.GetPort().c_str());
	if(m_pGPSData == NULL)
		return false;
	gps_stream(m_pGPSData, WATCH_ENABLE, NULL);
	return true;
}

//-------------------------------------
bool CXGPSDClient::Close() {
	if(m_pGPSData != NULL)
		gps_close(m_pGPSData);
	m_pGPSData = NULL;
	return true;
}

//-------------------------------------
bool CXGPSDClient::IsOpen() {
	return m_pGPSData != NULL;
}

//-------------------------------------
void CXGPSDClient::Read() {
	if(m_pGPSData == NULL)
		return;
	while(gps_waiting(m_pGPSData)) {
		gps_poll(m_pGPSData);
		DoProcessData(m_pGPSData);
	}
}

//-------------------------------------
void CXGPSDClient::ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP) {
	rHDOP = pGPSData->dop.hdop;
	rVDOP = pGPSData->dop.vdop;
}

//-------------------------------------
void CXGPSDClient::ReadSatelliteData(gps_data_t *pGPSData, CXBuffer<CXSatelliteInfo *> & rSatInfos, CXBuffer<int> & rActiveSats) {
	if(pGPSData->satellites > 0) {
		for(int i=0; i<pGPSData->satellites; i++) {
			CXSatelliteInfo *pInfo = new CXSatelliteInfo();
			pInfo->SetPRN(pGPSData->PRN[i]);
			pInfo->SetElevation(pGPSData->elevation[i]);
			pInfo->SetAzimuth(pGPSData->azimuth[i]);
			pInfo->SetSNR(pGPSData->ss[i]);
			rSatInfos.Append(pInfo);
		}
	}
	if(pGPSData->satellites_used > 0) {
		for(int i=0; i<pGPSData->satellites_used; i++) {
			rActiveSats.Append(pGPSData->used[i]);
		}
	}
}

#endif // (GPSD_API_MAJOR_VERSION == 4)
