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

#ifndef __CXGPSPROTOCOLGPSD_HPP__
#define __CXGPSPROTOCOLGPSD_HPP__

#include "CXGPSProtocol.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSProtocolGPSD : public CXGPSProtocol {
private:
	//-------------------------------------
	CXGPSProtocolGPSD(const CXGPSProtocolGPSD &);						///< Not used.
	const CXGPSProtocolGPSD & operator = (const CXGPSProtocolGPSD &);	///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool AfterOpen();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool BeforeClose();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool OnReadAndProcessData();
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSProtocolGPSD();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSProtocolGPSD();
};

#endif // __CXGPSPROTOCOLGPSD_HPP__
