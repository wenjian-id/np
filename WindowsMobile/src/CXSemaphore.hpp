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

#ifndef __CXSEMAPHORE_HPP__
#define __CXSEMAPHORE_HPP__

#include <ISemaphore.hpp>
#include <TargetIncludes.hpp>

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXSemaphore : public ISemaphore {
private:
	HANDLE	m_hSemaphore;	///< oiu
	//-------------------------------------
	CXSemaphore();												///< Not used.
	CXSemaphore(const CXSemaphore &);							///< Not used.
	const CXSemaphore & operator = (const CXSemaphore &);		///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXSemaphore(size_t MaxCount);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXSemaphore();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void Lock();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void Unlock();
};

#endif // __CXSEMAPHORE_HPP__
