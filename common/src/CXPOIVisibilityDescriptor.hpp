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

#ifndef __CXPOIVISIBILITYDESCRIPTOR_HPP__
#define __CXPOIVISIBILITYDESCRIPTOR_HPP__

#include "Utils.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXPOIVisibilityDescriptor {
private:
	bool	m_oShowAll;								///< oiu
	bool	m_oVisibilityList[e_POI_EnumCount];		///< oiu
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void CopyFrom(const CXPOIVisibilityDescriptor &rOther);
	protected:
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPOIVisibilityDescriptor();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPOIVisibilityDescriptor(const CXPOIVisibilityDescriptor &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual ~CXPOIVisibilityDescriptor();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const CXPOIVisibilityDescriptor & operator = (const CXPOIVisibilityDescriptor &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowAll() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowAll(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowPOIType(E_POI_TYPE ePOIType) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowPOIType(E_POI_TYPE ePOIType, bool NewValue);
};

#endif // __CXPOIVISIBILITYDESCRIPTOR_HPP__
