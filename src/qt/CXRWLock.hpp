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

#ifndef __CXRWLOCK_HPP__
#define __CXRWLOCK_HPP__

#include <IRWLock.hpp>

#include <qreadwritelock.h>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXRWLock : public IRWLock {
private:
    QReadWriteLock  m_RWLock;   ///< Synchronization object.
    //-------------------------------------
    CXRWLock(const CXRWLock &);                         ///< Not used.
    //-------------------------------------
    const CXRWLock & operator = (const CXRWLock &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXRWLock();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXRWLock();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void LockRead();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void LockWrite();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void UnlockRead();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void UnlockWrite();
};

#endif // __CXRWLOCK_HPP__
