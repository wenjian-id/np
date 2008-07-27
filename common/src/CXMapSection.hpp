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

#ifndef __CXMAPSECTION_HPP__
#define __CXMAPSECTION_HPP__

#include "CXWay.hpp"
#include "CXNode.hpp"
#include "CXMutex.hpp"
#include "CXSmartPtr.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapSection {
private:
	TNodeMap			m_NodeMap;				///< Map with all nodes.
	TPOINodeMap			m_POINodes;				///< POIs. No need to delete the elements: they will be deleted from m_NodeMap.
	CXBuffer<TWayMap *>	m_WayMapBuffer;			///< Ways sorted by layer.
	// synchronisation
	mutable CXMutex		m_Mutex;				///< Synchronization object.
	//-------------------------------------
	/**
	 * \brief Load map current version
	 *
	 *	Load map current version
	 *	\param	InFile		File with map data.
	 *	\return				true on success
	 */
	bool LoadMap_CurrentVersion(CXFile & InFile);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapSection();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapSection();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const TPOINodeMap & GetPOINodeMap() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool LoadMap(CXFile & InFile);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXWay *GetWay(t_uint64 ID);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void RunOSMVali();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void ComputeDisplayCoordinates(const CXTransformationMatrix2D & TM);
};

typedef CXSmartPtr<CXMapSection> TMapSectionPtr;


#endif // __CXMAPSECTION_HPP__
