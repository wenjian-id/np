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

#ifndef __ISERIAL_HPP__
#define __ISERIAL_HPP__

class CXStringASCII;

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class ISerial {
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	enum E_RESULTCODE {
		RC_OK,						///< Everything OK
		RC_CHANNEL_CLOSE_ERROR,		///< Error when closing channel
		RC_CHANNEL_OPEN_ERROR,		///< Error opening serial channel
		RC_CHANNEL_ALREADY_OPEN,	///< Channel already open
		RC_NO_CHANNEL_OPEN,			///< Channel not open
		RC_RECEIVE_ERROR,			///< Receive error
		RC_RCV_NO_DATA,				///< No data received
		RC_TRANSMIT_ERROR,			///< Error sending data
		RC_WRONG_ARGUMENT,			///< Wrong argument
	};

	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	enum E_SERCOMMPARITY {
		SCP_NONE,		///< No parity
		SCP_EVEN,		///< Even parity
		SCP_ODD,		///< Odd parity
		SCP_MARK,		///< Mark parity
	};

	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	enum E_SERCOMMSTOPBITS {
		SCS_ONE,		///< 1 stop bits
		SCS_ONEFIVE,	///< 1.5 stop bits
		SCS_TWO,		///< 2 stop bits
	};
private:
	//-------------------------------------
	ISerial(const ISerial&);						///< Not used.
	const ISerial & operator = (const ISerial&);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	ISerial() {
	}
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~ISerial() {
	}
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Open(const CXStringASCII &SerialPort, unsigned long  ulBaudrate, unsigned char  ucDataBits, E_SERCOMMPARITY  eParity, E_SERCOMMSTOPBITS  eStopBits) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Close() = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Receive(unsigned long  ulDataSize, unsigned char *  pbData, unsigned long &  ulReceived) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Transmit(unsigned long  ulDataSize, const unsigned char *  pbData, unsigned long &  ulTransmitted) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual bool IsOpen() const = 0;
};


#endif // __ISERIAL_HPP__
