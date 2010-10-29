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

#ifndef __CXCOOR_HPP__
#define __CXCOOR_HPP__

#include "CXUTMCoor.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXCoor {
private:
    double      m_dLon;     ///< Longitude [deg]
    double      m_dLat;     ///< Latitude [deg]
    CXUTMCoor   m_UTMCoor;  ///< UTM coordinate
    //-------------------------------------
    /**
     * \brief Copy from other instance to self.
     *
     * Copy from other instance to self.
     * \param   rOther  Instance to copy from.
     */
    void CopyFrom(const CXCoor &rOther);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXCoor();
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    CXCoor(double dLon, double dLat);
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXCoor(const CXCoor &rOther);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXCoor();
    //-----------CXCoor-------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXCoor & operator = (const CXCoor &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if equal.
     */
    bool operator == (const CXCoor &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if not equal.
     */
    bool operator != (const CXCoor &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetLon() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetLat() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetUTMZone() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    char GetUTMLetter() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetUTMEasting() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetUTMNorthing() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void RelocateUTM(int NewUTMZone);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void OffsetCoor(double dUTME, double dUTMN);
};

#endif // __CXCOOR_HPP__
