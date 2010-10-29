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

#ifndef __CXPOWMMAP_HPP__
#define __CXPOWMMAP_HPP__

#include "Utils.hpp"
#include "CXMapSection.hpp"
#include "CXMapContainer.hpp"
#include "CXFile.hpp"
#include "CXArray.hpp"
#include "CXTransformationMatrix.hpp"
#include "CXRect.hpp"
#include "CXMapLoaderThread.hpp"


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXPOWMMap {
private:
    static CXPOWMMap                        *m_pInstance;           ///< oiu
    CXMapLoaderThread                       *m_pMapLoaderThread;    ///< oiu
    //-------------------------------------
    CXPOWMMap(const CXPOWMMap &);                       ///< Not used.
    const CXPOWMMap & operator = (const CXPOWMMap &);   ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXPOWMMap();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXPOWMMap();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    static CXPOWMMap *Instance();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetMapLoaderThread(CXMapLoaderThread *pMapLoaderThread);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    TMapSectionPtrArray GetMapSectionsDisplay(const CXVisibleMapSectionDescr &Descr);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    TMapSectionPtrArray GetMapSectionsLocator(const CXVisibleMapSectionDescr &Descr);
};

#endif // __CXPOWMMAP_HPP__
