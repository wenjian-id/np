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

#ifndef __CXPENHOLDER_HPP__
#define __CXPENHOLDER_HPP__

#include "CXBuffer.hpp"
#include "CXPOWMMap.hpp"

class CXPen;

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXPenHolder {
private:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	struct SPens {
		CXPen	*m_pBg;			///< oiu
		CXPen	*m_pSegm;		///< oiu
	};
	CXBuffer<SPens *>		m_Pens;		///< oiu
	//-------------------------------------
	CXPenHolder(const CXPenHolder &);						///< Not used.
	const CXPenHolder & operator = (const CXPenHolder &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void CreatePens();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void DestroyPens();
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXPenHolder();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXPenHolder();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPen *GetPenBg(E_KEYHIGHWAY HighwayType);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPen *GetPenFg(E_KEYHIGHWAY HighwayType);
};

#endif // __CXPENHOLDER_HPP__
