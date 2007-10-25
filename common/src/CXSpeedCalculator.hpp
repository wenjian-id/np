/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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

#ifndef __CXSPEEDCALCULATOR_HPP__
#define __CXSPEEDCALCULATOR_HPP__

#include "CXExactTime.hpp"
#include "CXUTMSpeed.hpp"
#include "CXUTMCoor.hpp"
#include "CXMutex.hpp"

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXSpeedCalculator {
private:

	//---------------------------------------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	class CXData {
	private:
		CXData();									///< Not used.
		CXData(const CXData &);						///< Not used.
		const CXData & operator = (const CXData &);	///< Not used.
		//-------------------------------------
	public:
		double			m_Lon;		///< oiu
		double			m_Lat;		///< oiu
		double			m_UTME;		///< oiu
		double			m_UTMN;		///< oiu
		CXExactTime		m_Time;		///< oiu
		//-------------------------------------
		/*
		 * \brief oiu
		 *
		 */
		CXData(double Lon, double Lat, double UTME, double UTMN, const CXExactTime & Time) {
			m_Lon = Lon;
			m_Lat = Lat;
			m_UTME = UTME;
			m_UTMN = UTMN;
			m_Time = Time;
		}
		//-------------------------------------
		/*
		 * \brief oiu
		 *
		 */
		virtual ~CXData() {
		}
	};


private:
	// buffer stuff
	size_t				m_iBufferSize;		///< oiu
	CXData				**m_pBuffer;		///< oiu
	// speed stuff
	bool				m_oValid;			///< oiu
	int					m_iUTMZone;			///< oiu
	CXUTMSpeed			m_Speed;			///< oiu
	CXUTMSpeed			m_LastValidSpeed;	///< oiu
	// sync stuff
	mutable CXMutex		m_Mutex;			///< oiu
	//-------------------------------------
	CXSpeedCalculator();												///< Not used.
	CXSpeedCalculator(const CXSpeedCalculator &);						///< Not used.
	const CXSpeedCalculator & operator = (const CXSpeedCalculator &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ClearBuffer();
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXSpeedCalculator(size_t BufferSize);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXSpeedCalculator();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetData(double Lon, double Lat, const CXUTMCoor & Coor, const CXExactTime & Time);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ResetData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Timeout();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool HasValidSpeed();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXUTMSpeed GetSpeed() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXUTMSpeed GetLastValidSpeed() const;
};

#endif // __CXSPEEDCALCULATOR_HPP__
