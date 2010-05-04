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

#ifndef __CXUTMCOOR_HPP__
#define __CXUTMCOOR_HPP__

#include "CoordConversion.h"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXUTMCoor {
private:
	int			m_UTMZone;			///< UTM zone
	char		m_UTMLetter;		///< UTM Letter
	double		m_UTMEasting;		///< UTM Easting
	double		m_UTMNorthing;		///< UTM Northing
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXUTMCoor &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXUTMCoor();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTMCoor(int UTMZone, char UTMLetter, double UTMEasting, double UTMNorthing);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTMCoor(double dLon, double dLat);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXUTMCoor(const CXUTMCoor &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXUTMCoor();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXUTMCoor & operator = (const CXUTMCoor &rOther);
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if equal.
	 */
	bool operator == (const CXUTMCoor &rOther);
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if not equal.
	 */
	bool operator != (const CXUTMCoor &rOther);
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
	void SetUTMZone(int NewValue);
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
	void SetUTMLetter(char NewValue);
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
	void SetUTMEasting(double NewValue);
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
	void SetUTMNorthing(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void OffsetCoor(double dUTME, double dUTMN);
};

#endif // __CXUTMCOOR_HPP__
