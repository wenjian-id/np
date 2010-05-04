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

#ifndef __IRWLOCK_HPP__
#define __IRWLOCK_HPP__

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class IRWLock {
private:
	//-------------------------------------
	IRWLock(const IRWLock &);							///< Not used.
	const IRWLock & operator = (const IRWLock &);		///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	IRWLock() {
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~IRWLock() {
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void LockRead() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void LockWrite() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void UnlockRead() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void UnlockWrite() = 0;
};

#endif // __IRWLOCK_HPP__
