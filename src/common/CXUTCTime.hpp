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

#ifndef __CXUTCTIME_HPP__
#define __CXUTCTIME_HPP__

#include "CXStringASCII.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class CXUTCTime {
private:
	double 			m_UTCTimeDouble;	///<oiu
	CXStringASCII 	m_UTCTimeString;	///<oiu
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void CopyFrom(const CXUTCTime &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void FromString(const CXStringASCII &Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void FromDouble(double Value);
protected:
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTCTime();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTCTime(double UTCTime);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTCTime(const CXStringASCII & UTCTime);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTCTime(const CXUTCTime &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual ~CXUTCTime();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const CXUTCTime & operator = (const CXUTCTime &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetUTCTimeAsDouble() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetUTCTimeAsString() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetUTCTime(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetUTCTime(const CXStringASCII & NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTCTime operator - (const CXUTCTime & rOther) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool operator == (const CXUTCTime & rOther) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool operator != (const CXUTCTime & rOther) const;
};

#endif // __CXUTCTIME_HPP__
