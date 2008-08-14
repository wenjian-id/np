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

#include "CXMapSection.hpp"
#include "CXSmartPtr.hpp"
#include "CXRWLock.hpp"
#include "CXStringASCII.hpp"
#include "CXArray.hpp"
#include "CXFile.hpp"
#include "CXRect.hpp"


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXTOCMapContainer {
private:
	E_LOADING_STATUS			m_eLoadStatus;		///< oiu
	CXStringASCII				m_FileName;			///< oiu
	TTOCMapSectionPtr			**m_pTOCSections;	///< oiu
	size_t						m_Width;			///< oiu
	size_t						m_Height;			///< oiu
	mutable CXRWLock			m_RWLock;			///< Synchronization object.
	mutable CXRWLock			m_StatusRWLock;		///< Synchronization object for m_eLoadStatus.
	//-------------------------------------
	CXTOCMapContainer(const CXTOCMapContainer &);							///< Not used.
	const CXTOCMapContainer & operator = (const CXTOCMapContainer &);		///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void Clear();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void Resize(size_t Width, size_t Height);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCMapContainer_CurrentVersion(CXFile & rFile, unsigned char ZoomLevel, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCZoom_CurrentVersion(CXFile & rFile, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCZoom(CXFile & rFile, t_uint32 Key);
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
	E_LOADING_STATUS GetLoadStatus() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void SetLoadStatus(E_LOADING_STATUS eStatus);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool Load(const CXStringASCII & FileName, unsigned char ZoomLevel, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void GetMapSections(const tDRect &Rect, CXArray<TTOCMapSectionPtr> & rResult);
};

typedef CXSmartPtr<CXTOCMapContainer> TTOCMapContainerPtr;
typedef CXArray<TTOCMapContainerPtr> TTOCMapContainerPtrArray;


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
