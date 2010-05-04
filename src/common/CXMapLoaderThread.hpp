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

#ifndef __CXMAPLOADERTHREAD_HPP__
#define __CXMAPLOADERTHREAD_HPP__

#include "CXWorkRequestThread.hpp"
#include "CXMapContainer.hpp"
#include "CXCache.hpp"
#include "CXMutex.hpp"

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
	E_ZOOM_LEVEL				m_ZoomLevel;	///< oiu
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
								E_ZOOM_LEVEL ZoomLevel);
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
	E_ZOOM_LEVEL GetZoomLevel() const;
};


//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapLoaderThread : public CXWorkRequestThread {
private:
	//----------------------------------------------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	class CXTOCDescr {
		private:
			//-------------------------------------
			CXTOCDescr();										///< Not used.
			CXTOCDescr(const CXTOCDescr &);						///< Not used.
			const CXTOCDescr & operator = (const CXTOCDescr &);	///< Not used.
		protected:
		public:
			CXStringASCII	m_FileName;		///< oiu
			E_ZOOM_LEVEL	m_ZoomLevel;	///< oiu
			t_uint32		m_Key;			///< oiu
			//-------------------------------------
			/**
			 * \brief oiu.
			 *
			 * oiu.
			 */
			CXTOCDescr(const CXStringASCII & FileName, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key) :
				m_FileName(FileName),
				m_ZoomLevel(ZoomLevel),
				m_Key(Key)
			{
			}
			//-------------------------------------
			/**
			 * \brief Destructor.
			 *
			 * Destructor.
			 */
			virtual ~CXTOCDescr() {
			}
	};
private:
	// load lists
	TTOCMapContainerPtrArray				m_TOCMapContainerLoadList;		///< oiu
	CXBuffer<CXTOCDescr *>					m_TOCDescrList;					///< oiu
	TMapSectionPtrArray						m_MapSectionDisplayLoadList;	///< oiu
	// chaches
	CXCache<t_uint32, CXTOCMapContainer>	m_TOCCache;						///< oiu
	CXCache<t_uint64, CXMapSection>			m_MapSectionDisplayCache;		///< oiu
	CXCache<t_uint64, CXMapSection>			m_MapSectionLocatorCache;		///< oiu
	mutable CXMutex							m_Mutex;						///< Synchronization object.
	mutable CXMutex							m_CacheMutex;					///< Synchronization object.
	//-------------------------------------
	CXMapLoaderThread(const CXMapLoaderThread &);							///< Not used.
	const CXMapLoaderThread & operator = (const CXMapLoaderThread &);		///< Not used.
	//-------------------------------------
	virtual void OnWorkFunc();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	t_uint32 GetCacheKeyFromCoor(double dLon, double dLat, unsigned char ZoomLevel);
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
	TMapSectionPtrArray GetMapSectionsXYZ(const CXVisibleMapSectionDescr &Descr, CXCache<t_uint64, CXMapSection> &Cache);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapLoaderThread();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapLoaderThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStarted();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStopped();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void LoadTOCMapContainer(TTOCMapContainerPtr &TOCMapContainer, const CXStringASCII & FileName, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void LoadMapSection(TMapSectionPtr &MapSectionPtr);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	TMapSectionPtrArray GetMapSectionsDisplay(const CXVisibleMapSectionDescr &Descr);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	TMapSectionPtrArray GetMapSectionsLocator(const CXVisibleMapSectionDescr &Descr);
};

#endif // __CXMAPLOADERTHREAD_HPP__
