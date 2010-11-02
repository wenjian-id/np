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

#ifndef __CXTARGET_HPP__
#define __CXTARGET_HPP__

#include "CXStringUTF8.hpp"
#include "CXCoor.hpp"

//---------------------------------------------------------------------
/**
 * \brief Class encapsulating a target.
 */
class CXTarget {
private:
    CXStringUTF8    m_Name;     ///< Name of target.
    CXCoor          m_Coor;     ///< Coordinate of target.
    //-------------------------------------
    /**
     * \brief Copy from other instance.
     *
     * \param   rOther  Instance to copy from.
     */
    void CopyFrom(const CXTarget & rOther);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     */
    CXTarget();
    //-------------------------------------
    /**
     * \brief Default constructor.
     */
    CXTarget(const CXStringUTF8 & Name, const CXCoor & Coor);
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * \param   rOther  Instance to copy from.
     */
    CXTarget(const CXTarget &rOther);
    //-------------------------------------
    /**
     * \brief Destructor.
     */
    virtual ~CXTarget();
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXTarget & operator = (const CXTarget &rOther);
    //-------------------------------------
    /**
     * \brief Get name of target.
     *
     * \return  The name.
     */
    CXStringUTF8 GetName() const;
    //-------------------------------------
    /**
     * \brief Get coordinates of target.
     *
     * \return  The coordinates.
     */
    CXCoor GetCoor() const;
    //-------------------------------------
    /**
     * \brief Set name of target.
     *
     * \param   Name    The name.
     */
    void SetName(const CXStringUTF8 & Name);
    //-------------------------------------
    /**
     * \brief Set coordinates of target.
     *
     * \param   Coor    The coordinates.
     */
    void SetCoor(const CXCoor &Coor);
};

#endif // __CXTARGET_HPP__
