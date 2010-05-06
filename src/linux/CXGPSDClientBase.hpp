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


#ifndef __CXGPSDCLIENTBASE_HPP__
#define __CXGPSDCLIENTBASE_HPP__

#include <gps.h>

#include "IGPSDClient.hpp"
#include "CXGPSPosInfo.hpp"
#include "CXGPSCourseInfo.hpp"
#include "CXGPSQualityInfo.hpp"
#include "CXMutex.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class CXGPSDClientBase : public IGPSDClient {
private:
	CXGPSPosInfo		m_GPSPosInfo;				///< oiu
	CXGPSCourseInfo		m_GPSCourseInfo;			///< oiu
	CXGPSQualityInfo	m_GPSQualityInfo;			///< oiu
	bool				m_oGPSPosInfoChanged;		///< oiu
	bool				m_oGPSCourseInfoChanged;	///< oiu
	bool				m_oGPSQualityInfoChanged;	///< oiu
	mutable CXMutex		m_Mutex;					///< Synchronisation object
	//-------------------------------------
	CXGPSDClientBase(const CXGPSDClientBase &);						///< Not used.
	const CXGPSDClientBase & operator = (const CXGPSDClientBase &);	///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void DoProcessData(gps_data_t *pGPSData);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP) = 0;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void ReadNumberOfVisibleSatellites(gps_data_t *pGPSData, int &rNVisibleSat) = 0;
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSDClientBase();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSDClientBase();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool GPSPosInfoChanged() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSPosInfo GetGPSPosInfo() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void ResetGPSPosInfoChanged();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool GPSCourseInfoChanged() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSCourseInfo GetGPSCourseInfo() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void ResetGPSCourseInfoChanged();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool GPSQualityInfoChanged() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSQualityInfo GetGPSQualityInfo() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void ResetGPSQualityInfoChanged();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void Read() = 0;
};


#endif // __CXGPSDCLIENTBASE_HPP__
