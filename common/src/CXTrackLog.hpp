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

#ifndef __CXTRACKLOG_HPP__
#define __CXTRACKLOG_HPP__

#include "CXBuffer.hpp"
#include "CXCoor.hpp"

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXTrackLog {
private:
	size_t				m_MaxSize;		///< oiu
	CXBuffer<CXCoor *>	m_Points;		///< oiu
	//-------------------------------------
	CXTrackLog(const CXTrackLog &);							///< Not used.
	const CXTrackLog & operator = (const CXTrackLog &);		///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void DeleteSuperfluous();
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXTrackLog();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXTrackLog();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetMaxSize(size_t MaxSize);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void RelocateUTM(int ForceUTMZone);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXBuffer<CXCoor *> & GetPoints() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void AddPoint(double dLon, double dLat);
};

typedef CXBuffer<CXCoor *>	TCoorBuffer;


#endif // __CXTRACKLOG_HPP__


