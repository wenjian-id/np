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

#include "Utils.hpp"
#include "CXWay.hpp"
#include "CXNode.hpp"
#include "CXMutex.hpp"
#include "CXRWLock.hpp"
#include "CXRect.hpp"
#include "CXArray.hpp"
#include "CXSmartPtr.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXTOCMapSection {
private:
	t_uint64		m_UID;			///< oiu
	double			m_dLonMin;		///< oiu
	double			m_dLonMax;		///< oiu
	double			m_dLatMin;		///< oiu
	double			m_dLatMax;		///< oiu
	CXStringASCII	m_FileName;		///< oiu
	t_uint32		m_Offset;		///< oiu
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXTOCMapSection & rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXTOCMapSection();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXTOCMapSection(t_uint64 UID, double dLonMin, double dLonMax, 
					double dLatMin, double dLatMax, 
					const CXStringASCII & FileName, t_uint32 Offset);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXTOCMapSection(const CXTOCMapSection &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXTOCMapSection();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXTOCMapSection & operator = (const CXTOCMapSection &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	t_uint64 GetUID() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLonMin() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLonMax() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLatMin() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLatMax() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	t_uint32 GetOffset() const;
};


typedef CXSmartPtr<CXTOCMapSection> TTOCMapSectionPtr;
typedef CXArray<TTOCMapSectionPtr> TTOCMapSectionPtrArray;


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapSection {
private:
	E_LOADING_STATUS		m_eLoadStatus;			///< oiu
	int						m_UTMZone;				///< oiu
	TNodeMap				m_NodeMap;				///< Map with all nodes.
	TPOINodeBuffer			m_POINodes;				///< POIs. No need to delete the elements: they will be deleted from m_NodeMap.
	CXBuffer<TWayMap *>		m_WayMapBuffer;			///< Ways sorted by layer.
	CXTOCMapSection			m_TOC;					///< oiu
	// synchronisation
	mutable CXMutex			m_Mutex;				///< Synchronization object.
	mutable CXRWLock		m_StatusRWLock;			///< Synchronization object for m_eLoadStatus.
	//-------------------------------------
	CXMapSection(const CXMapSection &);							///< Not used.
	const CXMapSection & operator = (const CXMapSection &);		///< Not used.
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
	E_LOADING_STATUS GetLoadStatus() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLoadStatus(E_LOADING_STATUS eStatus);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const TPOINodeBuffer & GetPOINodeMap() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool LoadMap();
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
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Lock() {
		m_Mutex.Lock();
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Unlock() {
		m_Mutex.Unlock();
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	TWayMap *GetWayMap(char Layer) {
		return m_WayMapBuffer[Layer-MINLAYER];
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXTOCMapSection GetTOC() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetTOC(const CXTOCMapSection &TOC);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void RelocateUTM(int NewZone);
};

typedef CXSmartPtr<CXMapSection> TMapSectionPtr;
typedef CXArray<TMapSectionPtr> TMapSectionPtrArray;


#endif // __CXMAPSECTION_HPP__
