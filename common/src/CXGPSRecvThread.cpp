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

#include <stdlib.h>

static const unsigned char GGABEGIN[6]	= {'$', 'G', 'P', 'G', 'G', 'A'};
static const unsigned char RMCBEGIN[6]	= {'$', 'G', 'P', 'R', 'M', 'C'};
static const unsigned char GSABEGIN[6]	= {'$', 'G', 'P', 'G', 'S', 'A'};
static const unsigned char GSVBEGIN[6]	= {'$', 'G', 'P', 'G', 'S', 'V'};

//-------------------------------------
CXGPSRecvThread::CXGPSRecvThread() :
	m_oDemoMode(false),
	m_DemoTimeout(1000),
	m_pLocator(NULL),
	m_oSaving(false)
{
	SetSleepTime(100);	// 100ms
}


//-------------------------------------
CXGPSRecvThread::~CXGPSRecvThread() {
}


//-------------------------------------
void CXGPSRecvThread::OpenSerial() {
	CXMutexLocker L(&m_Mutex);
	CXSerialPortConfig Cfg = CXOptions::Instance()->GetSerialPortConfig();
	CXStringASCII Port = Cfg.GetPort();
	// look for "DEMO:"
	m_oDemoMode = Port.Find("DEMO;") == 0;
	if(m_oDemoMode) {
		ExtractFirstToken(Port, ';');
		// extract file name
		CXStringASCII FileName = CreateAbsoluteFileName(CXOptions::Instance()->GetStartPath(), ExtractFirstToken(Port, ';'));
		// extract timeout
		// check if "ms" is found.
		size_t PosMS = Port.Find("ms");
		if(PosMS == CXStringASCII::NPOS) {
			// timeout is given in seconds
			m_DemoTimeout = 1000*atoi(Port.c_str());
		} else {
			// timeout is given in milliseconds
			Port = Port.Left(PosMS);
			m_DemoTimeout = atoi(Port.c_str());
		}
		if(m_DemoTimeout == 0)
			m_DemoTimeout = 1000;
		if(m_DemoTimeout > 10000)
			m_DemoTimeout = 10000;
		// open file
		m_DemoFile.Open(FileName.c_str(), CXFile::E_READ);
	} else {
		// open serial port
		m_Serial.Open(Cfg);
	}
}


//-------------------------------------
void CXGPSRecvThread::ReopenSerial() {
	CloseSerial();
	OpenSerial();
}


//-------------------------------------
void CXGPSRecvThread::CloseSerial() {
	CXMutexLocker L(&m_Mutex);
	if(m_oDemoMode) {
		m_DemoFile.Close();
	} else {
		m_Serial.Close();
	}
}


//-------------------------------------
void CXGPSRecvThread::OnThreadStarted() {
	CXMutexLocker L(&m_Mutex);
	OpenSerial();
}


//-------------------------------------
bool CXGPSRecvThread::CheckGGA() {
    // length must be at least 11 : $ G P G G A * x x CR LF
    if(m_LastPacket.GetSize() < 11)
    	return false;
    
    // must start with "$GPGGA"
    if(!m_LastPacket.CompareBegin(GGABEGIN, sizeof(GGABEGIN))) {
    	return false;
    }

	// OK, it is a GGA packet
	return true;
}

//-------------------------------------
bool CXGPSRecvThread::CheckRMC() {
    // length must be at least 11 : $ G P R M C * x x CR LF
    if(m_LastPacket.GetSize() < 11)
    	return false;
    
    // must start with "$GPRMC"
    if(!m_LastPacket.CompareBegin(RMCBEGIN, sizeof(RMCBEGIN))) {
    	return false;
    }

	// OK, it is a RMC packet
	return true;
}

//-------------------------------------
bool CXGPSRecvThread::CheckGSA() {
    // length must be at least 11 : $ G P G S A * x x CR LF
    if(m_LastPacket.GetSize() < 11)
    	return false;
    
    // must start with "$GPGSA"
    if(!m_LastPacket.CompareBegin(GSABEGIN, sizeof(GSABEGIN))) {
    	return false;
    }

	// OK, it is a GSA packet
	return true;
}

//-------------------------------------
bool CXGPSRecvThread::CheckGSV() {
    // length must be at least 11 : $ G P G S V * x x CR LF
    if(m_LastPacket.GetSize() < 11)
    	return false;
    
    // must start with "$GPGSV"
    if(!m_LastPacket.CompareBegin(GSVBEGIN, sizeof(GSVBEGIN))) {
    	return false;
    }

	// OK, it is a GSV packet
	return true;
}

//-------------------------------------
void CXGPSRecvThread::OnThreadLoop() {
	CXMutexLocker L(&m_Mutex);
	// poll data on serial port
	if(ReceiveData()) {
		// process data
		while(ProcessData()) {
			// save data if necessary
			Save(m_LastPacket);
			// check GGA packet
			if(CheckRMC()) {
				// tell the locator that data is ready
				if(m_pLocator != NULL)
					m_pLocator->SetGPSDataRMC(m_LastPacket);
			}
			if(CheckGGA()) {
				// check if demo mode
				if(m_oDemoMode) {
					CXExactTime Now;
					size_t TO = Now - m_LastDemoGGA;
					// check if sleep necessary
					if(TO < m_DemoTimeout) {
						// yes, sleep some time
						DoSleep(m_DemoTimeout - TO);
					}
					// now set last received time
					m_LastDemoGGA.SetNow();
				}
				// tell the locator that data is ready
				if(m_pLocator != NULL)
					m_pLocator->SetGPSDataGGA(m_LastPacket);
			}
			if(CheckGSA()) {
				// tell the locator that data is ready
				if(m_pLocator != NULL)
					m_pLocator->SetGPSDataGSA(m_LastPacket);
			}
			if(CheckGSV()) {
				// tell the locator that data is ready
				if(m_pLocator != NULL)
					m_pLocator->SetGPSDataGSV(m_LastPacket);
			}
		}
	}
}

//-------------------------------------
void CXGPSRecvThread::OnThreadStopped() {
	CXMutexLocker L(&m_Mutex);
	CloseSerial();
}

//-------------------------------------
bool CXGPSRecvThread::ReceiveData() {
	bool Result = false;
	unsigned char buf[500];
	if(m_oDemoMode) {
		size_t ReadSize = 0;
		if((m_DemoFile.Read(buf, 500, ReadSize) == CXFile::E_OK) && (ReadSize != 0)) {
			// append data to m_Buffer
			m_Buffer.Append(buf, ReadSize);
			Result = true;
		} else {
			// restart demo
			ReopenSerial();
		}
	} else {
		// synchronisation has to be done in calling function
		unsigned long ulReceived = 0;
		m_Serial.Receive(500, buf, ulReceived);
		if(ulReceived > 0) {
			m_Buffer.Append(buf, ulReceived);
		}
		Result = ulReceived != 0;
	}
	return Result;
}

//-------------------------------------
bool CXGPSRecvThread::ProcessData() {
	// synchronisation has to be done in calling function

	// check if complete Packet arrived
	while(!m_Buffer.IsEmpty() && (m_Buffer[0] != '$')) {
		m_Buffer.DeleteFirst(1);
	}
	// check if empty
	if(m_Buffer.IsEmpty())
		return false;
	// OK, starts with $
	// check, if 0x0a inside
	unsigned long pos = m_Buffer.Find(0x0a);
	if(pos == tUCBuffer::NPOS)
		return false;
	// extract payload
	m_LastPacket = m_Buffer.Left(pos-1);
	// delete from input buffer
	m_Buffer.DeleteFirst(pos+1);
	return true;
}

//-------------------------------------
bool CXGPSRecvThread::IsOpen() const {
	CXMutexLocker L(&m_Mutex);
	return m_Serial.IsOpen();
}

//-------------------------------------
void CXGPSRecvThread::SetLocator(CXLocatorThread *pLocator) {
	CXMutexLocker L(&m_Mutex);
	m_pLocator = pLocator;
}

//-------------------------------------
void CXGPSRecvThread::FlushInput() {
	CXMutexLocker L(&m_Mutex);
	while(ReceiveData())
		;
}

//-------------------------------------
void CXGPSRecvThread::Save(const tUCBuffer & Buffer) {
	// check to see if state changed
	if(m_oSaving != CXOptions::Instance()->IsSaving()) {
		// yes
		m_oSaving = CXOptions::Instance()->IsSaving();
		if(!m_oSaving) {
			// saving just turned off
			m_SaveFile.Close();
		} else {
			// saving just turned on
			// reset flag in case of error
			m_oSaving = false;

			// get current time
			CXExactTime Now;
			char buf[100];
			for(int i=0; i<100; i++) {
				snprintf(buf, 100, "%04d%02d%02d%02d.txt", Now.GetYear(), Now.GetMonth(), Now.GetDay(), i);
				CXStringASCII FileName(CXOptions::Instance()->GetDirectorySave());
				FileName+=buf;

				// check if file already exists
				if(m_SaveFile.Open(FileName.c_str(), CXFile::E_READ) == CXFile::E_OK) {
					// yes. close it again.
					m_SaveFile.Close();
				} else {
					// no. open for writing
					m_SaveFile.Close();
					m_oSaving = m_SaveFile.Open(FileName.c_str(), CXFile::E_WRITE) == CXFile::E_OK;
					if(m_oSaving)
						break;
				}
			}

		}
	}
	if(m_oSaving != CXOptions::Instance()->IsSaving()) {
		// some error occured
		CXOptions::Instance()->ToggleSaving();
	}
	if(m_oSaving) {
		// save buffer
		size_t WriteSize = 0;
		m_SaveFile.Write(Buffer.GetBuffer(), Buffer.GetSize(), WriteSize);
		unsigned char DA[2] = {0x0d, 0x0a};
		m_SaveFile.Write(DA, 2, WriteSize);
	}
}
