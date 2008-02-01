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

#include "CXTimeStampData.hpp"
#include "CXUTMSpeed.hpp"
#include "CXCoor.hpp"
#include "CXMutex.hpp"

//---------------------------------------------------------------------
/*
 * \brief Calculate speed from a bunch of UTM coordinates with timestamp.
 *
 * This class calculates a speed from a bunch of UTM coordinates with time stamp.
 * If there are N available coordinates a mean position and time stamp for the first
 * N-1 and the last N-1 values is computed. From this two values the current speed
 * is computed. The coordinates are kept in FIFO.
 */
class CXSpeedCalculator {
private:
	// buffer stuff
	size_t						m_iBufferSize;		///< Number of coordinates.
	CXTimeStampData<CXCoor>		**m_pBuffer;		///< Buffer with coordinates.
	// speed stuff
	int							m_iCurrentUTMZone;	///< Current UTM zone
	CXUTMSpeed					m_Speed;			///< Current speed
	bool						m_oValidSpeed;		///< Flag indicating if a valid speed exists.
	CXUTMSpeed					m_LastValidSpeed;	///< last valid computed speed.
	// sync stuff
	mutable CXMutex				m_Mutex;			///< Sync object
	//-------------------------------------
	CXSpeedCalculator();												///< Not used.
	CXSpeedCalculator(const CXSpeedCalculator &);						///< Not used.
	const CXSpeedCalculator & operator = (const CXSpeedCalculator &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief Clear buffer with coordinates.
	 *
	 * Clear buffer with coordinates.
	 */
	void ClearBuffer();
protected:
public:
	//-------------------------------------
	/*
	 * \brief Only allowed constructor.
	 *
	 * Only allowed constructor.
	 * \param	BufferSize	Max nunmber of coordinates.
	 */
	CXSpeedCalculator(size_t BufferSize);
	//-------------------------------------
	/*
	 * \brief Destructor.
	 * 
	 * Destructor.
	 */
	virtual ~CXSpeedCalculator();
	//-------------------------------------
	/*
	 * \brief Set new data.
	 *
	 * Set new data.
	 * \param	Coor		New coordinate.
	 * \param	TimeStamp	TiemStamp for the coordinate.
	 */
	void SetData(const CXTimeStampData<CXCoor> &Coor);
	//-------------------------------------
	/*
	 * \brief Reset data.
	 *
	 * All saved data is resetted.
	 */
	void ResetData();
	//-------------------------------------
	/*
	 * \brief Check if a valid speed is available.
	 *
	 * Check if a valid speed is available.
	 * \return	true	Returns true if a valid speed is available.
	 */
	bool HasValidSpeed();
	//-------------------------------------
	/*
	 * \brief Get speed.
	 *
	 * Get Speed.
	 * \return	The speed.
	 */
	CXUTMSpeed GetSpeed() const;
	//-------------------------------------
	/*
	 * \brief Get last valid speed.
	 *
	 * Get last Speed.
	 * \return	Last valid speed.
	 */
	CXUTMSpeed GetLastValidSpeed() const;
};

#endif // __CXSPEEDCALCULATOR_HPP__
