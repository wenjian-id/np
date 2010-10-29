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

#ifndef __CXFILEINI_HPP__
#define __CXFILEINI_HPP__

#include "CXFile.hpp"
#include "CXStringASCII.hpp"
#include "CXMapSimple.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXFileIni {
private:
    CXMapSimple<CXStringASCII, CXStringASCII>   m_Content;      ///< oiu
    //-------------------------------------
    CXFileIni(const CXFileIni &);                       ///< Not used.
    const CXFileIni & operator = (const CXFileIni &);   ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Clear();
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXFileIni();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXFileIni();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool Read(const CXStringASCII & FileName);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII Get(const CXStringASCII & Key, const CXStringASCII & Default);
};

#endif // __CXFILEINI_HPP__
