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
	CXTOCMapSection				***m_pTOCSections;	///< oiu
	double						m_dBaseLon;			///< oiu
	double						m_dBaseLat;			///< oiu
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
	bool LoadTOCMapContainer_CurrentVersion(CXFile & rFile, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCZoom_CurrentVersion(CXFile & rFile, t_uint32 Key, E_ZOOM_LEVEL ZoomLevel);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool LoadTOCZoom(CXFile & rFile, t_uint32 Key, E_ZOOM_LEVEL ZoomLevel);
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
	bool Load(const CXStringASCII & FileName, E_ZOOM_LEVEL ZoomLevel, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void GetMapSections(const tDRect &Rect, CXBuffer<CXTOCMapSection*> & rResult);
};

typedef CXSmartPtr<CXTOCMapContainer> TTOCMapContainerPtr;
typedef CXArray<TTOCMapContainerPtr> TTOCMapContainerPtrArray;

#endif // __CXMAPCONTAINER_HPP__
