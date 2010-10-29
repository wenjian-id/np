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

#ifndef __CXDEBUGINFO_HPP__
#define __CXDEBUGINFO_HPP__

#include "CXRWLock.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXDebugInfo {
private:
    static CXDebugInfo  *m_pInstance;                   ///< oiu
    int                 m_DrawTime;                     ///< oiu
    int                 m_LocatorTime;                  ///< oiu
    mutable CXRWLock    m_RWLock;                       ///< Synchronization object.
    //-------------------------------------
    CXDebugInfo(const CXDebugInfo &);                       ///< Not used.
    const CXDebugInfo & operator = (const CXDebugInfo &);   ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXDebugInfo();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXDebugInfo();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    static CXDebugInfo *Instance();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetDrawTime() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetDrawTime(int NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetLocatorTime() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetLocatorTime(int NewValue);
};

#endif // __CXDEBUGINFO_HPP__
