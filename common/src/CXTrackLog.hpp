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

#ifndef __CXTRACKLOG_HPP__
#define __CXTRACKLOG_HPP__

#include "CXBuffer.hpp"
#include "CXCoor.hpp"

//---------------------------------------------------------------------
/*
 * \brief Class for keeping track log data.
 *
 * Class for keeping track log data. Works like a FIFO.
 */
class CXTrackLog {
private:
	size_t				m_MaxSize;		///< Max size of coordinates.
	unsigned int		m_MinDistance;	///< Min distance between last and new coordinate.
	CXBuffer<CXCoor *>	m_Coordinates;	///< The coordinates.
	//-------------------------------------
	CXTrackLog(const CXTrackLog &);							///< Not used.
	const CXTrackLog & operator = (const CXTrackLog &);		///< Not used.
	//-------------------------------------
	/*
	 * \brief Delete superfluous elements.
	 *
	 * Delete superfluous elements, so that only m_MaxSize elements remain in list.
	 */
	void DeleteSuperfluous();
protected:
public:
	//-------------------------------------
	/*
	 * \brief Default constructor.
	 * 
	 * Default constructor.
	 */
	CXTrackLog();
	//-------------------------------------
	/*
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXTrackLog();
	//-------------------------------------
	/*
	 * \brief Set max size of coordinates.
	 * 
	 * Set max size of coordinates.
	 * \param	MaxSize		Max size of coordinates.
	 */
	void SetMaxSize(size_t MaxSize);
	//-------------------------------------
	/*
	 * \brief Set MinDistance.
	 * 
	 * Set MinDistance. A new coordinate must be at least MinDistance away
	 * from last coordinate to be added.
	 * \param	MaxSize		Max size of coordinates.
	 */
	void SetMinDistance(unsigned int MinDistance);
	//-------------------------------------
	/*
	 * \brief Relocate coordinates to new UTM zone.
	 * 
	 * Relocate coordinates to new UTM zone.
	 * \param	NewUTMZone	New UTM Zone.
	 */
	void RelocateUTM(int NewUTMZone);
	//-------------------------------------
	/*
	 * \brief Get coordinates.
	 *
	 * Get coordinates.
	 * \return	const reference to coordinates.
	 */
	const CXBuffer<CXCoor *> & GetCoordinates() const;
	//-------------------------------------
	/*
	 * \brief Add coordinate.
	 *
	 * Add coordinate. If necessary remove older ones.
	 * \param	dLon	Longitude of new coordinate.
	 * \param	dLat	Latitude of new coordinate.
	 */
	void AddCoordinate(double dLon, double dLat);
};

typedef CXBuffer<CXCoor *>	TCoorBuffer;


#endif // __CXTRACKLOG_HPP__


