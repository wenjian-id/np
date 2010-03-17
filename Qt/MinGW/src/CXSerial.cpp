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

#include "CXSerial.hpp"
#include <stdio.h>

//-------------------------------------
CXSerial::CXSerial() :
	m_hComm(INVALID_HANDLE_VALUE)
{
}

//-------------------------------------
CXSerial::~CXSerial() {
    Close();
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Open(const CXSerialPortConfig & Config) {
    if(m_hComm != INVALID_HANDLE_VALUE)
    	return RC_CHANNEL_ALREADY_OPEN;

    m_hComm = CreateFile(Config.GetPort().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
    if(m_hComm == INVALID_HANDLE_VALUE)
    	return RC_CHANNEL_OPEN_ERROR;
    
    // configure
    DCB dcb;
    if(!GetCommState(m_hComm, &dcb))
    	return RC_CHANNEL_OPEN_ERROR;
    dcb.fBinary = TRUE;
    dcb.fParity = TRUE;
    
    // baud rate
    dcb.BaudRate = Config.GetBaudrate();
    // data bits
    dcb.ByteSize = Config.GetDataBits();
    // parity
    unsigned char ucParity = 0;
    switch(Config.GetParity()) {
    	case CXSerialPortConfig::SCP_NONE:	ucParity = NOPARITY; break;
    	case CXSerialPortConfig::SCP_EVEN:	ucParity = EVENPARITY; break;
    	case CXSerialPortConfig::SCP_ODD:	ucParity = ODDPARITY; break;
    	case CXSerialPortConfig::SCP_MARK:	ucParity = MARKPARITY; break;
		default :							Close(); return RC_WRONG_ARGUMENT;
    }
    dcb.Parity = ucParity;
    // stop bits
    unsigned char ucStopBits = 0;
    	switch(Config.GetStopBits()) {
    	case CXSerialPortConfig::SCS_ONE:		ucStopBits = ONESTOPBIT; break;
    	case CXSerialPortConfig::SCS_ONEFIVE:	ucStopBits = ONE5STOPBITS; break;
    	case CXSerialPortConfig::SCS_TWO:		ucStopBits = TWOSTOPBITS; break;
		default :								Close(); return RC_WRONG_ARGUMENT;
    }
    dcb.StopBits = ucStopBits;
    
    // disable hardware handshake
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fOutX = FALSE;
    dcb.fInX = FALSE;
    dcb.fNull = FALSE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError = FALSE;
    
    if(!SetCommState(m_hComm, &dcb)) {
		Close();
    	return RC_CHANNEL_OPEN_ERROR;
	}
    
    // disable timeouts
    COMMTIMEOUTS ct;
    GetCommTimeouts(m_hComm, &ct);
    ct.ReadIntervalTimeout = MAXDWORD;
    ct.ReadTotalTimeoutConstant = 0;
    ct.ReadTotalTimeoutMultiplier = 0;
    ct.WriteTotalTimeoutConstant = 0;
    ct.WriteTotalTimeoutMultiplier = 0;
    if(!SetCommTimeouts(m_hComm, &ct)) {
		Close();
    	return RC_CHANNEL_OPEN_ERROR;
	}
    
    return RC_OK;
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Close() {
    if(m_hComm == INVALID_HANDLE_VALUE)
    	return RC_NO_CHANNEL_OPEN;
    E_RESULTCODE eResult = RC_OK;
   	// close
   	if(!CloseHandle(m_hComm))
   		eResult = RC_CHANNEL_CLOSE_ERROR;
   	m_hComm = INVALID_HANDLE_VALUE;
    return eResult;
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Receive(unsigned long  ulDataSize, unsigned char *  pbData, unsigned long &  ulReceived) {
    ulReceived = 0;
    
    if(m_hComm == INVALID_HANDLE_VALUE)
    	return RC_NO_CHANNEL_OPEN;
    
    E_RESULTCODE eResult = RC_OK;
    
    DWORD dwReceived = 0;
    if(!ReadFile(m_hComm, pbData, ulDataSize, &dwReceived, NULL))
    	eResult = RC_RECEIVE_ERROR;
    else if(dwReceived == 0)
    	eResult = RC_RCV_NO_DATA;
    ulReceived = dwReceived;
    
    return eResult;
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Transmit(unsigned long  ulDataSize, const unsigned char *  pbData, unsigned long &  ulTransmitted) {
    ulTransmitted = 0;
    
    // if no data to send return RC_OK
    if(ulDataSize == 0)
    	return RC_OK;
    
    if(m_hComm == INVALID_HANDLE_VALUE)
    	return RC_NO_CHANNEL_OPEN;
    
    E_RESULTCODE eResult = RC_OK;
    
    DWORD dwWritten = 0;
    if(!WriteFile(m_hComm, pbData, ulDataSize, &dwWritten, NULL))
    	eResult = RC_TRANSMIT_ERROR;
    if(dwWritten != ulDataSize)
    	eResult = RC_TRANSMIT_ERROR;
    ulTransmitted = dwWritten;
    
    return eResult;
}

//-------------------------------------
bool CXSerial::IsOpen() const {
    return m_hComm != INVALID_HANDLE_VALUE;
}

