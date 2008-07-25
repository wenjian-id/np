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

#ifndef __CXSERIAL_HPP__
#define __CXSERIAL_HPP__

#include <ISerial.hpp>
#include "CXStringASCII.hpp"
#include <OSSpecific.hpp>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSerial : public ISerial {
private:
    HANDLE	m_hComm;	///< oiu
	//-------------------------------------
	CXSerial(const CXSerial&);						///< Not used.
	const CXSerial & operator = (const CXSerial&);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXSerial();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXSerial();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
    E_RESULTCODE Open(const CXSerialPortConfig & Config);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Close();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Receive(unsigned long  ulDataSize, unsigned char *  pbData, unsigned long &  ulReceived);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
    virtual E_RESULTCODE Transmit(unsigned long  ulDataSize, const unsigned char *  pbData, unsigned long &  ulTransmitted);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool IsOpen() const;
};


#endif // __CXSERIAL_HPP__
