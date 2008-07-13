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

#ifndef __CXMUTEXLOCKER_HPP__
#define __CXMUTEXLOCKER_HPP__

#include "CXMutex.hpp"

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXMutexLocker {
private:
	CXMutex	*m_pMutex;		///< oiu
	//-------------------------------------
	CXMutexLocker();											///< Not used.
	CXMutexLocker(const CXMutexLocker &);						///< Not used.
	const CXMutexLocker & operator = (const CXMutexLocker &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXMutexLocker(CXMutex *pMutex);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXMutexLocker();
};

#endif // __CXMUTEXLOCKER_HPP__
