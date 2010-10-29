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

#ifndef __CXUTMSPEED_HPP__
#define __CXUTMSPEED_HPP__

#include "CXDirection.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXUTMSpeed {
private:
    double          m_dSpeed;       ///< oiu
    CXDirection     m_Direction;    ///< oiu
    //-------------------------------------
    /**
     * \brief Copy from other instance to self.
     *
     * Copy from other instance to self.
     * \param   rOther  Instance to copy from.
     */
    void CopyFrom(const CXUTMSpeed &rOther);
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXUTMSpeed();
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXUTMSpeed(const CXUTMSpeed &rOther);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXUTMSpeed();
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXUTMSpeed & operator = (const CXUTMSpeed &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if equal.
     */
    bool operator == (const CXUTMSpeed &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if not equal.
     */
    bool operator != (const CXUTMSpeed &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Reset();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetSpeed() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetSpeed(double dSpeed);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXDirection GetDirection() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetDirection(const CXDirection &Direction);
};

#endif // __CXUTMSPEED_HPP__
