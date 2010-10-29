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

#ifndef __ISEMAPHORE_HPP__
#define __ISEMAPHORE_HPP__

#include <TargetIncludes.hpp>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class ISemaphore {
private:
    size_t      m_MaxCount; ///< oiu
    //-------------------------------------
    ISemaphore();                                           ///< Not used.
    ISemaphore(const ISemaphore &);                         ///< Not used.
    const ISemaphore & operator = (const ISemaphore &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    ISemaphore(size_t MaxCount);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~ISemaphore();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t GetMaxCount() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Lock() = 0;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Unlock() = 0;
};

#endif // __ISEMAPHORE_HPP__
