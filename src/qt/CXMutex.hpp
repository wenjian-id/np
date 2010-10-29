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

#ifndef __CXMUTEX_HPP__
#define __CXMUTEX_HPP__

#include <IMutex.hpp>

#include <qmutex.h>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMutex : public IMutex {
private:
    QMutex  m_Mutex;    ///< Synchronization object.
    //-------------------------------------
    CXMutex(const CXMutex &);                           ///< Not used.
    //-------------------------------------
    const CXMutex & operator = (const CXMutex &);       ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXMutex();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXMutex();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Lock();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Unlock();
};

#endif // __CXMUTEX_HPP__
