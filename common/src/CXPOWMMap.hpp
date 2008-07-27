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

#ifndef __CXPOWMMAP_HPP__
#define __CXPOWMMAP_HPP__

#include "CXMutex.hpp"
#include "CXMapSection.hpp"
#include "CXFile.hpp"
#include "CXTrackLog.hpp"
#include "CXArray.hpp"
#include "Utils.hpp"

typedef CXArray<TMapSectionPtr> TMapSectionPtrArray;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXPOWMMap {
private:
	static CXPOWMMap	*m_pInstance;			///< oiu
	// stuff
	CXTrackLog			m_TrackLog;				///< oiu
	// synchronisation
	mutable CXMutex		m_Mutex;				///< Synchronization object.
	//-------------------------------------
	CXPOWMMap(const CXPOWMMap &);						///< Not used.
	const CXPOWMMap & operator = (const CXPOWMMap &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXPOWMMap();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXPOWMMap();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void PositionChanged(double dLon, double dLat, bool oFix);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const CXTrackLog & GetTrackLog() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	static CXPOWMMap *Instance();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	TMapSectionPtrArray GetMapSections(double dLon, double dLat, unsigned char ZoomLevel);
};

#endif // __CXPOWMMAP_HPP__
