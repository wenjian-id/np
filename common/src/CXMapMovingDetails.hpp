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

#ifndef __CXMAPMOVINGDETAILS_HPP__
#define __CXMAPMOVINGDETAILS_HPP__

#include "CXRWLock.hpp"
#include "CXCoor.hpp"
#include "CXTransformationMatrix.hpp"


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapMovingDetails {
private:
	CXCoor							m_Position;			///< oiu
	CXTransformationMatrix2D		m_Matrix;			///< oiu
	static CXMapMovingDetails		*m_pInstance;		///< oiu
	mutable CXRWLock				m_RWLock;			///< Synchronization object.
	//-------------------------------------
	CXMapMovingDetails(const CXMapMovingDetails &);							///< Not used.
	const CXMapMovingDetails & operator = (const CXMapMovingDetails &);		///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Only allowed constructor.
	 *
	 * Only allowed constructor.
	 */
	CXMapMovingDetails();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapMovingDetails();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	static CXMapMovingDetails * Instance();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXCoor GetPosition() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void SetPosition(const CXCoor &NewValue);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void SetMatrix(const CXTransformationMatrix2D &Matrix);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void OffsetPosition(int OffsetPixelX, int OffsetPixelY);
};

#endif // __CXMAPMOVINGDETAILS_HPP__
