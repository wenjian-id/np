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

#include "Utils.hpp"
#include "CXMutex.hpp"
#include "CXMapSection.hpp"
#include "CXMapContainer.hpp"
#include "CXFile.hpp"
#include "CXArray.hpp"
#include "CXTransformationMatrix.hpp"
#include "CXRect.hpp"
#include "CXCache.hpp"


class CXMapLoaderThread;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXVisibleMapSectionDescr {
private:
	double						m_dLonMin;		///< oiu
	double						m_dLonMax;		///< oiu.
	double						m_dLatMin;		///< oiu
	double						m_dLatMax;		///< oiu
	unsigned char				m_ZoomLevel;	///< oiu
	CXTransformationMatrix2D	m_Matrix;		///< oiu
	//-------------------------------------
	CXVisibleMapSectionDescr();															///< Not used.
	CXVisibleMapSectionDescr(const CXVisibleMapSectionDescr &);							///< Not used.
	const CXVisibleMapSectionDescr & operator = (const CXVisibleMapSectionDescr &);		///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Only allowed constructor.
	 *
	 * Only allowed constructor.
	 */
	CXVisibleMapSectionDescr(	double dLonMin, double dLatMin,
								double dLonMax, double dLatMax,
								unsigned char ZoomLevel,
								const CXTransformationMatrix2D &TMMap);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXVisibleMapSectionDescr();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLonMin() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 */
	double GetLatMin() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLonMax() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 */
	double GetLatMax() const;
	//-------------------------------------
	/**
	 * \brief Get zoom level.
	 *
	 * Get zoom level.
	 * \return	Zoom level.
	 */
	unsigned char GetZoomLevel() const;
};


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXPOWMMap {
private:
	static CXPOWMMap						*m_pInstance;			///< oiu
	CXCache<t_uint32, CXTOCMapContainer>	m_TOCCache;				///< oiu
	CXCache<t_uint64, CXMapSection>			m_MapSectionCache;		///< oiu
	CXMapLoaderThread						*m_pMapLoaderThread;	///< oiu
	// synchronisation
	mutable CXMutex							m_Mutex;				///< Synchronization object.
	//-------------------------------------
	CXPOWMMap(const CXPOWMMap &);						///< Not used.
	const CXPOWMMap & operator = (const CXPOWMMap &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetFileNameFromCoor(double dLon, double dLat);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	t_uint32 GetCacheKeyFromCoor(double dLon, double dLat, unsigned char ZoomLevel);
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
	static CXPOWMMap *Instance();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMapLoaderThread(CXMapLoaderThread *pMapLoaderThread);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	TMapSectionPtrArray GetMapSections(const CXVisibleMapSectionDescr &Descr);
};

#endif // __CXPOWMMAP_HPP__
