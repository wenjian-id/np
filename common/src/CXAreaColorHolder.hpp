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

#ifndef __CXAREACOLORHOLDER_HPP__
#define __CXAREACOLORHOLDER_HPP__

#include "CXBuffer.hpp"
#include "CXRGB.hpp"
#include "Utils.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXAreaColorHolder {
private:
	CXBuffer<CXRGB *>	m_Colors;			///< oiu
	//-------------------------------------
	CXAreaColorHolder(const CXAreaColorHolder &);						///< Not used.
	const CXAreaColorHolder & operator = (const CXAreaColorHolder &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void CreateColors();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void DestroyColors();
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXAreaColorHolder();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXAreaColorHolder();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXRGB GetColor(E_AREA_TYPE AreaType);
};

#endif // __CXAREACOLORHOLDER_HPP__
