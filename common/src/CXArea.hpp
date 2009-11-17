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

#ifndef __CXAREA_HPP__
#define __CXAREA_HPP__

#include "CXNode.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXArea {
private:
	E_AREA_TYPE			m_eAreaType;		///< oiu
	CXOrderedNodeList	*m_pOuterNodeList;	///< oiu
	TNodeListBuffer		m_Holes;			///< oiu
	//-------------------------------------
	CXArea();									///< Not used.
	CXArea(const CXArea &);						///< Not used.
	const CXArea & operator = (const CXArea &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXArea(E_AREA_TYPE eAreaType);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXArea();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	E_AREA_TYPE GetAreaType() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetOuterNodeList(CXOrderedNodeList *pNodeList);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXOrderedNodeList *GetOuterNodeList() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void AddHole(CXOrderedNodeList *pNodeList);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t GetHoleCount();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXOrderedNodeList *GetHole(size_t Index);
};

typedef CXBuffer<CXArea *>		TAreaBuffer;		///< oiu

#endif // __CXAREA_HPP__
