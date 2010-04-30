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

#include "CXGPSRecvThread.hpp"
#include "Utils.hpp"
#include "CXMutexLocker.hpp"
#include "CXLocatorThread.hpp"
#include "CXOptions.hpp"
#include "CXNMEA.hpp"
#include "CXGPSProtocolNMEA.hpp"
#include "CXGPSProtocolGPSD.hpp"
#include "CXGPSInputChannelFile.hpp"
#include "CXGPSInputChannelSerial.hpp"
#include "CXGPSInputChannelGPSD.hpp"

#include <stdlib.h>

//-------------------------------------
CXGPSRecvThread::CXGPSRecvThread() :
	m_pGPSProtocol(NULL),
	m_pGPSInputChannel(NULL),
	m_LastGPSConnectTimeout(1000),
	m_pLocator(NULL)
{
	SetSleepTime(100);	// 100ms
}


//-------------------------------------
CXGPSRecvThread::~CXGPSRecvThread() {
	delete m_pGPSProtocol;
	delete m_pGPSInputChannel;
}

//-------------------------------------
void CXGPSRecvThread::CreateGPSProtocol() {
	CXMutexLocker L(&m_Mutex);
	delete m_pGPSProtocol;
	m_pGPSProtocol = NULL;
	delete m_pGPSInputChannel;
	m_pGPSInputChannel = NULL;
	// check which kind of protocol to use
	switch(CXOptions::Instance()->GetGPSProtocolType()) {
		case CXOptions::e_GPSProto_None:	m_pGPSProtocol = NULL; break;
		case CXOptions::e_GPSProto_NMEA:	m_pGPSProtocol = new CXGPSProtocolNMEA(); break;
		case CXOptions::e_GPSProto_GPSD:	m_pGPSProtocol = new CXGPSProtocolGPSD(); break;
	}
	// now set InputChannel
	switch(CXOptions::Instance()->GetGPSInputChannelType()) {
		case CXOptions::e_InputChannel_None:	m_pGPSInputChannel = NULL; break;
		case CXOptions::e_InputChannel_Serial:	m_pGPSInputChannel = new CXGPSInputChannelSerial(); break;
		case CXOptions::e_InputChannel_File:	m_pGPSInputChannel = new CXGPSInputChannelFile(); break;
		case CXOptions::e_InputChannel_GPSD:	m_pGPSInputChannel = new CXGPSInputChannelGPSD(); break;
	}
	if(m_pGPSInputChannel != NULL) {
		// read configuration of input channel
		m_pGPSInputChannel->ReadConfiguration();
		if(m_pGPSProtocol != NULL) {
			// set input channel in protocol
			m_pGPSProtocol->SetInputChannel(m_pGPSInputChannel);
		}
	}
}

//-------------------------------------
void CXGPSRecvThread::OpenGPSProtocol() {
	CXMutexLocker L(&m_Mutex);
	if(m_pGPSProtocol != NULL)
		m_pGPSProtocol->Open();
}

//-------------------------------------
void CXGPSRecvThread::ReopenGPSProtocol() {
	CloseGPSProtocol();
	OpenGPSProtocol();
}

//-------------------------------------
void CXGPSRecvThread::CloseGPSProtocol() {
	CXMutexLocker L(&m_Mutex);
	if(m_pGPSProtocol != NULL)
		m_pGPSProtocol->Close();
}

//-------------------------------------
void CXGPSRecvThread::OnThreadStarted() {
	CXMutexLocker L(&m_Mutex);
	m_LastGPSConnectTimeout = CXOptions::Instance()->GetGPSReconnectTimeout();
	// create gps Protocol
	CreateGPSProtocol();
	// open gps Protocol
	OpenGPSProtocol();
	// set connection status to locator thread
	if(m_pGPSProtocol != NULL)
		m_pLocator->SetGPSConnected(m_pGPSProtocol->IsOpen());
	else
		m_pLocator->SetGPSConnected(false);
}

//-------------------------------------
void CXGPSRecvThread::OnThreadLoop() {
	CXMutexLocker L(&m_Mutex);
	if(m_pGPSProtocol == NULL)
		return;
	if(!m_pGPSProtocol->IsOpen()) {
		// channel not open
		CXExactTime Now;
		size_t TO = Now - m_LastGPSConnect;
		if(TO > m_LastGPSConnectTimeout) {
			// try to reopen Protocol
			ReopenGPSProtocol();
			m_LastGPSConnect.SetNow();
			// set connection status to locator thread
			m_pLocator->SetGPSConnected(m_pGPSProtocol->IsOpen());
		}
	}
	if(!m_pGPSProtocol->IsOpen())
		return;
	// connected. now read data
	while(m_pGPSProtocol->ReadAndProcessData()) {
		// send data to locator thread
		if((m_pGPSProtocol->GetReceivedDataTypes() & CXGPSProtocol::e_RcvPosInfo) != 0) {
			// reset receive flag
			m_pGPSProtocol->ClearReceivedDataType(CXGPSProtocol::e_RcvPosInfo);
			// get data
			m_pLocator->SetGPSPosInfo(m_pGPSProtocol->GetGPSPosInfo());
		}
		if((m_pGPSProtocol->GetReceivedDataTypes() & CXGPSProtocol::e_RcvCourseInfo) != 0) {
			// reset receive flag
			m_pGPSProtocol->ClearReceivedDataType(CXGPSProtocol::e_RcvCourseInfo);
			// get data
			m_pLocator->SetGPSCourseInfo(m_pGPSProtocol->GetGPSCourseInfo());
		}
		if((m_pGPSProtocol->GetReceivedDataTypes() & CXGPSProtocol::e_RcvQualityInfo) != 0) {
			// reset receive flag
			m_pGPSProtocol->ClearReceivedDataType(CXGPSProtocol::e_RcvQualityInfo);
			// get data
			m_pLocator->SetGPSQualityInfo(m_pGPSProtocol->GetGPSQualityInfo());
		}
	}
}

//-------------------------------------
void CXGPSRecvThread::OnThreadStopped() {
	CXMutexLocker L(&m_Mutex);
	CloseGPSProtocol();
}

//-------------------------------------
void CXGPSRecvThread::SetLocator(CXLocatorThread *pLocator) {
	CXMutexLocker L(&m_Mutex);
	m_pLocator = pLocator;
}

//-------------------------------------
void CXGPSRecvThread::FlushInput() {
	CXMutexLocker L(&m_Mutex);
	if(m_pGPSProtocol != NULL)
		m_pGPSProtocol->FlushInput();
}
