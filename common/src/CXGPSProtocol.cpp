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

#include "CXGPSProtocol.hpp"
#include "CXOptions.hpp"
#include "CXMutexLocker.hpp"

//-------------------------------------
CXGPSProtocol::CXGPSProtocol() :
	m_oInTimeout(false),
	m_ReceivedDataTypes(0),
	m_eBufferedDataType(e_BufNone),
	m_pInputChannel(NULL)
{
}

//-------------------------------------
CXGPSProtocol::~CXGPSProtocol() {
}

//-------------------------------------
void CXGPSProtocol::SetInputChannel(CXGPSInputChannel *pInputChannel) {
	CXMutexLocker ML(&m_Mutex);
	m_pInputChannel = pInputChannel;
}

//-------------------------------------
unsigned char CXGPSProtocol::GetReceivedDataTypes() const {
	CXMutexLocker ML(&m_Mutex);
	return m_ReceivedDataTypes;
}

//-------------------------------------
void CXGPSProtocol::ClearReceivedDataType(E_RECEIVED_DATA_TYPE eDataType) {
	CXMutexLocker ML(&m_Mutex);
	m_ReceivedDataTypes &= ~eDataType;
}

//-------------------------------------
tTimeStampedGPSPosInfo CXGPSProtocol::GetGPSPosInfo() const {
	CXMutexLocker ML(&m_Mutex);
	return m_GPSPosInfo;
}

//-------------------------------------
tTimeStampedGPSCourseInfo CXGPSProtocol::GetGPSCourseInfo() const {
	CXMutexLocker ML(&m_Mutex);
	return m_GPSCourseInfo;
}

//-------------------------------------
tTimeStampedGPSQualityInfo CXGPSProtocol::GetGPSQualityInfo() const {
	CXMutexLocker ML(&m_Mutex);
	return m_GPSQualityInfo;
}

//-------------------------------------
bool CXGPSProtocol::Open() {
	CXMutexLocker ML(&m_Mutex);
	// check if inputchannel exists
	if(m_pInputChannel == NULL)
		return false;
	// try to open input channel
	if(!m_pInputChannel->Open())
		return false;
	// run AfterOpen
	if(!AfterOpen()) {
		// AfterOpen failed. Close channel again
		m_pInputChannel->Close();
		return false;
	}
	// everything OK
	return true;
}

//-------------------------------------
bool CXGPSProtocol::Close() {
	CXMutexLocker ML(&m_Mutex);
	// check if inputchannel exists
	if(m_pInputChannel == NULL)
		return false;
	// run BeforeClose
	BeforeClose();
	// close channel
	return m_pInputChannel->Close();
}

//-------------------------------------
bool CXGPSProtocol::IsOpen() {
	CXMutexLocker ML(&m_Mutex);
	// check if inputchannel exists
	if(m_pInputChannel == NULL)
		return false;
	// check if open
	return m_pInputChannel->IsOpen();
}

//-------------------------------------
void CXGPSProtocol::FlushInput() {
	CXMutexLocker ML(&m_Mutex);
	// check if inputchannel exists
	if(m_pInputChannel == NULL)
		return;
	if(!m_pInputChannel->CanFlush())
		return;
	unsigned char buf[1024];
	size_t ReadSize = 0;
	while(m_pInputChannel->Read(buf, sizeof(buf), ReadSize))
		;
}

//-------------------------------------
void CXGPSProtocol::SetGPSPosInfo(const CXGPSPosInfo &GPSPosInfo) {
	// check if UTC changed and timeout specified
	if((m_pInputChannel->GetForcedTimeout() > 0) && (m_LastReceivedUTC != GPSPosInfo.GetUTC())) {
		// new UTC. switch to timeout mode
		// set timeout flag
		m_oInTimeout = true;
		m_eBufferedDataType = e_BufPosInfo;
		// remember received data
		m_BufferedGPSPosInfo = GPSPosInfo;
	} else {
		// process data directly
		ProcessGPSPosInfo(GPSPosInfo);
	}
}

//-------------------------------------
void CXGPSProtocol::ProcessGPSPosInfo(const CXGPSPosInfo &GPSPosInfo) {
	// set data
	m_GPSPosInfo.SetData(GPSPosInfo);
	// adjust time stamp
	m_GPSPosInfo.SetNow();
	// adjust UTC
	m_LastReceivedUTC = GPSPosInfo.GetUTC();
	// adjust flags
	m_ReceivedDataTypes |= e_RcvPosInfo;
}

//-------------------------------------
void CXGPSProtocol::SetGPSCourseInfo(const CXGPSCourseInfo &GPSCourseInfo) {
	// check if UTC changed and timeout specified
	if((m_pInputChannel->GetForcedTimeout() > 0) && (m_LastReceivedUTC != GPSCourseInfo.GetUTC())) {
		// new UTC. switch to timeout mode
		// set timeout flag
		m_oInTimeout = true;
		m_eBufferedDataType = e_BufCourseInfo;
		// remember received data
		m_BufferedGPSCourseInfo = GPSCourseInfo;
	} else {
		// process data directly
		ProcessGPSCourseInfo(GPSCourseInfo);
	}
}

//-------------------------------------
void CXGPSProtocol::ProcessGPSCourseInfo(const CXGPSCourseInfo &GPSCourseInfo) {
	// set data
	m_GPSCourseInfo.SetData(GPSCourseInfo);
	// adjust time stamp
	m_GPSCourseInfo.SetNow();
	// adjust UTC
	m_LastReceivedUTC = GPSCourseInfo.GetUTC();
	// adjust flags
	m_ReceivedDataTypes |= e_RcvCourseInfo;
}

//-------------------------------------
void CXGPSProtocol::SetGPSQualityInfo(const CXGPSQualityInfo &GPSQualityInfo) {
	// process data directly
	ProcessGPSQualityInfo(GPSQualityInfo);
}

//-------------------------------------
void CXGPSProtocol::ProcessGPSQualityInfo(const CXGPSQualityInfo &GPSQualityInfo) {
	// set data
	m_GPSQualityInfo.SetData(GPSQualityInfo);
	// adjust time stamp
	m_GPSQualityInfo.SetNow();
	// adjust flags
	m_ReceivedDataTypes |= e_RcvQualityInfo;
}

//-------------------------------------
bool CXGPSProtocol::ReadAndProcessData() {
	CXMutexLocker ML(&m_Mutex);
	// check if inputchannel exists
	if(m_pInputChannel == NULL)
		return false;
	bool oReturnValue = false;
	for(;;) {
		if(!m_oInTimeout) {
			if(!OnReadAndProcessData())
				// nothing received
				return oReturnValue;
			oReturnValue = true;
		}
		// check if we got into a timeout in OnReadAndProcessData
		if(m_oInTimeout) {
			// we must wait
			CXExactTime Now;
			size_t TO = Now - m_LastReceivedDataTimeStamp;
			// check if timeout elapsed
			if(TO < m_pInputChannel->GetForcedTimeout()) {
				// timeout not elapsed yet
				return oReturnValue;
			}
			// timeout elapsed.
			m_oInTimeout = false;
			// now set last received time
			m_LastReceivedDataTimeStamp.SetNow();
			// process buffered data
			switch(m_eBufferedDataType) {
				case e_BufNone:			return false;
				case e_BufPosInfo:		ProcessGPSPosInfo(m_BufferedGPSPosInfo); break;
				case e_BufCourseInfo:	ProcessGPSCourseInfo(m_BufferedGPSCourseInfo); break;
			}
			m_eBufferedDataType = e_BufNone;
		}
	}
	return oReturnValue;
}

//-------------------------------------
void CXGPSProtocol::SaveRawData(unsigned char *pbBuffer, size_t DataLength) {
	if(pbBuffer == NULL)
		return;
	if(DataLength == 0)
		return;
	if(CXOptions::Instance()->MustSaveRaw()) {
		// save buffer
		m_SaverRaw.Write(pbBuffer, DataLength);
	}
}

//-------------------------------------
void CXGPSProtocol::SaveGPXData(double dLon, double dLat, double dHeight) {
	if(CXOptions::Instance()->MustSaveGPX()) {
		// save buffer
		m_SaverGPX.Write(dLon, dLat, dHeight);
	}
}
