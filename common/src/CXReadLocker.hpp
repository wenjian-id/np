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

#ifndef __CXREADLOCKER_HPP__
#define __CXREADLOCKER_HPP__

#include "CXRWLock.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXReadLocker {
private:
	CXRWLock	*m_pRWLock;		///< oiu
	//-------------------------------------
	CXReadLocker();											///< Not used.
	CXReadLocker(const CXReadLocker &);						///< Not used.
	const CXReadLocker & operator = (const CXReadLocker &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXReadLocker(CXRWLock *pRWLock);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXReadLocker();
};

#endif // __CXREADLOCKER_HPP__
