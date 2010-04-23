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

#ifndef __CXGPSINPUTCHANNELSERIAL_HPP__
#define __CXGPSINPUTCHANNELSERIAL_HPP__

#include "CXGPSInputChannel.hpp"
#include "CXSerial.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSInputChannelSerial : public CXGPSInputChannel {
private:
	CXSerial				m_Serial;		///< oiu
	CXSerialPortConfig		m_PortConfig;	///< oiu
	//-------------------------------------
	CXGPSInputChannelSerial(const CXGPSInputChannelSerial &);						///< Not used.
	const CXGPSInputChannelSerial & operator = (const CXGPSInputChannelSerial &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSInputChannelSerial();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSInputChannelSerial();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool Open();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool Close();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool IsOpen();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool ReadConfiguration();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool CanFlush();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize);
};

#endif // __CXGPSINPUTCHANNELSERIAL_HPP__
