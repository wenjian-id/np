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


#include "CXGPSDClientNoVersion.hpp"
#include "CXMutexLocker.hpp"

#ifndef GPSD_API_MAJOR_VERSION

//-------------------------------------
CXGPSDThread::CXGPSDThread(CXGPSDClient *pClient):
	m_pClient(pClient),
	m_pGPSData(NULL)
{
	CXGPSDConfig Cfg = pClient->GetConfig();
	m_pGPSData = gps_open(Cfg.GetAddress().c_str(), Cfg.GetPort().c_str());
	if(m_pGPSData != NULL)
		gps_query(m_pGPSData, "w+x\n");
}

//-------------------------------------
CXGPSDThread::~CXGPSDThread() {
	if(m_pGPSData != NULL)
		gps_close(m_pGPSData);
	m_pClient = NULL;
	m_pGPSData = NULL;
}

//-------------------------------------
bool CXGPSDThread::IsOpen() {
	return m_pGPSData != NULL;
}

//-------------------------------------
void CXGPSDThread::OnThreadStarted() {
}

//-------------------------------------
void CXGPSDThread::OnThreadLoop() {
	if(m_pGPSData != NULL) {
		gps_poll(m_pGPSData);
		if(m_pClient != NULL) {
			if(!MustStopThread()) {
				m_pClient->ProcessData(m_pGPSData);
			}
		}
	}
}

//-------------------------------------
void CXGPSDThread::OnThreadStopped() {
}


//-------------------------------------
CXGPSDClient::CXGPSDClient() :
	m_pThread(NULL),
	m_oTerminating(false)
{
}

//-------------------------------------
CXGPSDClient::~CXGPSDClient() {
}

//-------------------------------------
bool CXGPSDClient::Open() {
	CXMutexLocker ML(&m_Mutex);
	m_pThread = new CXGPSDThread(this);
	m_pThread->CreateThread();
	return true;
}

//-------------------------------------
bool CXGPSDClient::Close() {
	SetTerminating();
	CXMutexLocker ML(&m_Mutex);
	m_pThread->StopThread();
	if(!m_pThread->WaitForThreadExit(1500)) {
		m_pThread->KillThread();
	}
	delete m_pThread;
	m_pThread = NULL;
	return true;
}

//-------------------------------------
bool CXGPSDClient::IsOpen() {
	CXMutexLocker ML(&m_Mutex);
	return m_pThread->IsOpen();
}

//-------------------------------------
bool CXGPSDClient::IsTerminating() const {
	CXMutexLocker ML(&m_Mutex);
	return m_oTerminating;
}

//-------------------------------------
void CXGPSDClient::SetTerminating() {
	CXMutexLocker ML(&m_Mutex);
	m_oTerminating = true;
}

//-------------------------------------
void CXGPSDClient::ProcessData(gps_data_t *pGPSData) {
	if(IsTerminating())
		return;
	DoProcessData(pGPSData);
}

//-------------------------------------
void CXGPSDClient::Read() {
	// do nothing
}

//-------------------------------------
void CXGPSDClient::ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP) {
	rHDOP = pGPSData->hdop;
	rVDOP = pGPSData->vdop;
}

//-------------------------------------
void CXGPSDClient::ReadSatelliteData(gps_data_t *pGPSData, CXBuffer<CXSatelliteInfo *> & rSatInfos, CXBuffer<int> & rActiveSats) {
	if(pGPSData->satellites > 0) {
		// number of satellites in view > 0
		for(int i=0; i<pGPSData->satellites; i++) {
			CXSatelliteInfo *pInfo = new CXSatelliteInfo();
			pInfo->SetPRN(pGPSData->PRN[i]);
			pInfo->SetElevation(pGPSData->elevation[i]);
			pInfo->SetAzimuth(pGPSData->azimuth[i]);
			pInfo->SetSNR(pGPSData->ss[i]);
			rSatInfos.Append(pInfo);
		}
		// number of satellites used > 0
		if(pGPSData->satellites_used > 0) {
			// get list of used satellites
			for(int i=0; i<pGPSData->satellites; i++) {
				if(pGPSData->used[i] != 0) {
					rActiveSats.Append(pGPSData->PRN[i]);
				}
			}
		}
	}
}

#endif // GPSD_API_MAJOR_VERSION
