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

#ifndef __CXMAPCONTAINER_HPP__
#define __CXMAPCONTAINER_HPP__

#include "CXSmartPtr.hpp"
#include "CXRWLock.hpp"
#include "CXStringASCII.hpp"
#include "CXFile.hpp"


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXTOCMapContainer {
private:
	bool				m_oLoaded;	///< oiu
	mutable CXRWLock	m_RWLock;	///< Synchronization object.
	//-------------------------------------
	CXTOCMapContainer(const CXTOCMapContainer &);							///< Not used.
	const CXTOCMapContainer & operator = (const CXTOCMapContainer &);		///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCMapContainer_CurrentVersion(CXFile & rFile, unsigned char ZoomLevel);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCZoom_CurrentVersion(CXFile & rFile);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCZoom(CXFile & rFile);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXTOCMapContainer();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXTOCMapContainer();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool IsLoaded() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool Load(const CXStringASCII & FileName, unsigned char ZoomLevel);
};

typedef CXSmartPtr<CXTOCMapContainer> TTOCMapContainerPtr;


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapContainer {
private:
	// synchronisation
	mutable CXMutex		m_Mutex;				///< Synchronization object.
	//-------------------------------------
	CXMapContainer(const CXMapContainer &);							///< Not used.
	const CXMapContainer & operator = (const CXMapContainer &);		///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapContainer();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapContainer();
};

typedef CXSmartPtr<CXMapContainer> TMapContainerPtr;


#endif // __CXMAPCONTAINER_HPP__
