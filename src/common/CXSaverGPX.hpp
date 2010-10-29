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

#ifndef __CXSAVERGPX_HPP__
#define __CXSAVERGPX_HPP__

#include "CXSaver.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSaverGPX : public CXSaver {
private:
    CXStringASCII       m_GPXHeader;            ///< oiu
    CXStringASCII       m_GPXFooter;            ///< oiu
    //-------------------------------------
    CXSaverGPX(const CXSaverGPX &);                     ///< Not used.
    const CXSaverGPX & operator = (const CXSaverGPX &); ///< Not used.
protected:
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    virtual void AfterOpen();
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    virtual void BeforeClose();
public:
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    CXSaverGPX();
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    virtual ~CXSaverGPX();
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    bool Write(double dLon, double dLat, double dHeight);
};

#endif //__CXSAVERGPX_HPP__
