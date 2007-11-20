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

#include "CXSerial.hpp"
#include <stdio.h>
#include "unistd.h"
#include "termios.h"
#include "fcntl.h"

//-------------------------------------
CXSerial::CXSerial() :
	m_iComm(-1)
{
}

//-------------------------------------
CXSerial::~CXSerial() {
    Close();
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Open(const CXSerialPortConfig & Config) {
	// check if channel already open
	if(m_iComm != -1)
		return RC_CHANNEL_ALREADY_OPEN;

	// try to open
    m_iComm = open(Config.GetPort().c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
    if(m_iComm < 0) {
    	return RC_CHANNEL_OPEN_ERROR;
    }
    
    struct termios t;
	// return immediately even if no char reveived
    t.c_cc[VMIN]  = 0;
    t.c_cc[VTIME] = 0;
    t.c_iflag = IGNBRK | IGNPAR;
    t.c_oflag = 0;
    t.c_lflag = 0;
    t.c_cflag = CLOCAL | CREAD | HUPCL;
    
    // set data bits
    unsigned char ucDataBits = Config.GetDataBits();
    if(ucDataBits == 7) {
    	t.c_cflag |= CS7;
    } else if(ucDataBits == 8) {
    	t.c_cflag |= CS8;
    } else {
    	Close();
		return RC_WRONG_ARGUMENT;
    }

	// set baud rate
	speed_t SerSpeed = B0;
	unsigned long ulBaudrate = Config.GetBaudrate();
	switch(ulBaudrate) {
		case 2400:		SerSpeed = B2400; break;
		case 4800:		SerSpeed = B4800; break;
		case 9600:		SerSpeed = B9600; break;
		case 19200:		SerSpeed = B19200; break;
		case 38400:		SerSpeed = B38400; break;
		case 57600:		SerSpeed = B57600; break;
		case 115200:	SerSpeed = B115200; break;
		default:		{
    						Close();
							return RC_WRONG_ARGUMENT;
						}
	}

    // parity
	switch(Config.GetParity()) {
		case CXSerialPortConfig::SCP_NONE:	{
												t.c_cflag &= ~PARENB;
												break;
											}
		case CXSerialPortConfig::SCP_EVEN:	{
												t.c_cflag |= PARENB;
												t.c_cflag &= ~PARODD;
												break;
											}
		case CXSerialPortConfig::SCP_ODD:	{
												t.c_cflag |= PARENB;
												t.c_cflag |= PARODD;
												break;
											}
		default:							{
												Close();
												return RC_WRONG_ARGUMENT;
											}
	}
    // stop bits
	switch(Config.GetStopBits()) {
    	case CXSerialPortConfig::SCS_ONE:		t.c_cflag &= ~CSTOPB; break;
    	case CXSerialPortConfig::SCS_TWO:		t.c_cflag |= CSTOPB; break;
		default:								Close(); return RC_WRONG_ARGUMENT;
	}
        
    if(cfsetispeed(&t, SerSpeed) == -1) {
    	Close();
    	return RC_CHANNEL_OPEN_ERROR;
    }
    if(cfsetospeed(&t, SerSpeed) == -1) {
    	Close();
    	return RC_CHANNEL_OPEN_ERROR;
    }
    
    // flush
    if(tcflush(m_iComm, TCIFLUSH) == -1 ) {
    	Close();
    	return RC_CHANNEL_OPEN_ERROR;
    }
    
    // Now set the terminal port attributes
    if(tcsetattr(m_iComm, TCSANOW, &t) == -1) {
    	Close();
    	return RC_CHANNEL_OPEN_ERROR;
    }
	// everyhing OK
    return RC_OK;
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Close() {
    if(m_iComm != -1) {
		// close
    	close(m_iComm);
    	m_iComm = -1;
    }
    return RC_OK;
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Receive(unsigned long  ulDataSize, unsigned char *  pbData, unsigned long &  ulReceived) {
    ulReceived = 0;
    
    if(m_iComm == -1)
    	return RC_NO_CHANNEL_OPEN;
    
    E_RESULTCODE eResult = RC_OK;
    
    int iReceived = read(m_iComm, pbData, ulDataSize);
    if(iReceived < 0)
    	eResult = RC_RECEIVE_ERROR;
    else if(iReceived == 0)
    	eResult = RC_RCV_NO_DATA;
	else
		ulReceived = iReceived;

    return eResult;
}

//-------------------------------------
CXSerial::E_RESULTCODE CXSerial::Transmit(unsigned long  ulDataSize, const unsigned char *  pbData, unsigned long &  ulTransmitted) {
    ulTransmitted = 0;
    
    // if no data to send return RC_OK
    if(ulDataSize == 0)
    	return RC_OK;
    
    if(m_iComm == -1)
    	return RC_NO_CHANNEL_OPEN;
    
    E_RESULTCODE eResult = RC_OK;
    
    int iWritten = write(m_iComm, pbData, ulDataSize);
    if(iWritten < 0 ) {
    	eResult = RC_TRANSMIT_ERROR;
    } else if(iWritten != static_cast<int>(ulDataSize)) {
	    ulTransmitted = iWritten;
    	eResult = RC_TRANSMIT_ERROR;
	} else {
	    ulTransmitted = iWritten;
	}
    
    return eResult;
}

//-------------------------------------
bool CXSerial::IsOpen() const {
    return m_iComm != -1;
}

