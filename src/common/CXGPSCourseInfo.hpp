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

#include "CXUTCTime.hpp"
#include "CXTimeStampData.hpp"

//----------------------------------------------------------------------------
/**
 * \brief Class containing GPS course information.
 *
 * Class containing GPS course information: UTC, speed and course.
 */
class CXGPSCourseInfo {
private:
	CXUTCTime		m_UTC;		///< UTC.
	bool			m_oFix;		///< Fix.
	double			m_dSpeed;	///< Speed [m/s].
	double			m_dCourse;	///< Course [deg].
	//-------------------------------------
	/**
	 * \brief Copy from other instance.
	 *
	 * Copy data from other instance.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXGPSCourseInfo &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSCourseInfo();
	//-------------------------------------
	/**
	 * \brief Constructor.
	 *
	 * A Constructor.
	 * \param	UTC			UTC time.
	 * \param	oFix		Fix.
	 * \param	dSpeed		Speed [m/s].
	 * \param	dCourse		Course [deg].
	 */
	CXGPSCourseInfo(const CXStringASCII &UTC, bool oFix, double dSpeed, double dcourse);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * The copy constructor.
	 * \param	rOther		Instance to copy from.
	 */
	CXGPSCourseInfo(const CXGPSCourseInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSCourseInfo();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * The assignment operator.
	 * \param	rOther		Instance to copy from..
	 * \return				Const pointer to self.
	 */
	const CXGPSCourseInfo & operator = (const CXGPSCourseInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Get UTC.
	 *
	 * Get UTC time.
	 * \return	UTC time as string.
	 */
	CXUTCTime GetUTC() const;
	//-------------------------------------
	/**
	 * \brief Set UTC.
	 *
	 * Set UTC time.
	 * \param	NewValue	UTC time as string.
	 */
	void SetUTC(const CXUTCTime &NewValue);
	//-------------------------------------
	/**
	 * \brief Check if GPS fix.
	 *
	 * Check if GPS fix or not.
	 * \return	true if fix.
	 */
	bool HasFix() const;
	//-------------------------------------
	/**
	 * \brief Set GPS fix.
	 *
	 * Set GPS fix or not.
	 * \param	NewValue	true if fix.
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/**
	 * \brief Get speed.
	 *
	 * Get the speed.
	 * \return	Speed [m/s].
	 */
	double GetSpeed() const;
	//-------------------------------------
	/**
	 * \brief Set speed.
	 *
	 * Set the speed.
	 * \param	NewValue	Speed [m/s].
	 */
	void SetSpeed(double NewValue);
	//-------------------------------------
	/**
	 * \brief Get course.
	 *
	 * Get course.
	 * \return	Course [deg].
	 */
	double GetCourse() const;
	//-------------------------------------
	/**
	 * \brief Set course.
	 *
	 * Set the course.
	 * \param	NewValue	Course [deg].
	 */
	void SetCourse(double NewValue);
};

typedef CXTimeStampData<CXGPSCourseInfo> tTimeStampedGPSCourseInfo;

#endif // __CXGPSCOURSEINFO_HPP__
