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

#ifndef __CXSAVERRAW_HPP__
#define __CXSAVERRAW_HPP__

#include "CXSaver.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSaverRaw : public CXSaver {
private:
	//-------------------------------------
	CXSaverRaw(const CXSaverRaw &);						///< Not used.
	const CXSaverRaw & operator = (const CXSaverRaw &);	///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual void AfterOpen();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual void BeforeClose();
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	CXSaverRaw();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual ~CXSaverRaw();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool Write(const unsigned char *pbBuffer, size_t DataLength);
};

#endif //__CXSAVERRAW_HPP__
