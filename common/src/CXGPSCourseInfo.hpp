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

#ifndef __CXGPSCOURSEINFO_HPP__
#define __CXGPSCOURSEINFO_HPP__

#include "CXStringASCII.hpp"
#include "CXTimeStampData.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSCourseInfo {
private:
	CXStringASCII	m_UTC;		///< oiu
	double			m_dSpeed;	///< oiu
	double			m_dCourse;		///< oiu
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void CopyFrom(const CXGPSCourseInfo &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSCourseInfo();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSCourseInfo(const CXStringASCII &UTC, double dSpeed, double dcourse);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSCourseInfo(const CXGPSCourseInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSCourseInfo();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	const CXGPSCourseInfo & operator = (const CXGPSCourseInfo & rOther);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetSpeed() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetCourse() const;
};

typedef CXTimeStampData<CXGPSCourseInfo> tTimeStampedGPSCourseInfo;

#endif // __CXGPSCOURSEINFO_HPP__
