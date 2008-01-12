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

#ifndef __CXPOWMMAP_HPP__
#define __CXPOWMMAP_HPP__

#include "CXMutex.hpp"
#include "CXBuffer.hpp"
#include "CXStringUTF8.hpp"
#include "CXStringASCII.hpp"
#include "CXMapHashSimple.hpp"
#include "TargetIncludes.hpp"
#include "CXFile.hpp"
#include "CXCoor.hpp"
#include "CXTrackLog.hpp"

class CXWay;

//---------------------------------------------------------------------
/*
 * \brief This class encapsulates data and functionality for a node.
 *
 * This class encapsulates data and functionality for a node.
 */
class CXNode {
private:
	t_uint64	m_ID;		///< ID of node.
	CXCoor		m_Coor;		///< Coordinate of node
	//-------------------------------------
	CXNode();										///< Not used.
	CXNode(const CXNode &);							///< Not used.
	const CXNode & operator = (const CXNode &);		///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXNode(t_uint64 ID, double Lon, double Lat);
	//-------------------------------------
	/*
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXNode();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetLon() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetLat() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetUTME() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetUTMN() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void RelocateUTM(int ForceUTMZone);
};

typedef CXMapHashSimple<t_uint64, CXNode *>		TNodeMap;		///< oiu
typedef CXBuffer<CXNode *>						TNodeBuffer;		///< oiu

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXWay {
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	enum E_KEYHIGHWAY {	// must fit the values in the map file!!!
		eUnknown		=  0,	///< oiu
		eMotorway		=  1,	///< oiu
		eMotorwayLink	=  2,	///< oiu
		eTrunk			=  3,	///< oiu
		eTrunkLink		=  4,	///< oiu
		ePrimary		=  5,	///< oiu
		ePrimaryLink	=  6,	///< oiu
		eSecondary		=  7,	///< oiu
		eTertiary		=  8,	///< oiu
		eUnclassified	=  9,	///< oiu
		eTrack			= 10,	///< oiu
		eResidential	= 11,	///< oiu
		eService		= 12,	///< oiu
		eBridleway		= 13,	///< oiu
		eCycleway		= 14,	///< oiu
		eFootway		= 15,	///< oiu
		ePedestrian		= 16,	///< oiu
		eSteps			= 17,	///< oiu
		eEnumCount		= 18,	///< oiu
	};
private:
	t_uint64		m_ID;				///< oiu
	E_KEYHIGHWAY	m_eHighwayType;		///< oiu
	CXStringUTF8	m_Name;				///< oiu
	CXStringUTF8	m_Ref;				///< oiu
	unsigned char	m_MaxSpeed;			///< oiu 0 means no max speed
	bool			m_oOSMValiFailed;	///< oiu
	TNodeBuffer		m_Nodes;			///< oiu
	//-------------------------------------
	CXWay();									///< Not used.
	CXWay(const CXWay &);						///< Not used.
	const CXWay & operator = (const CXWay &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXWay(t_uint64 ID, E_KEYHIGHWAY eHighwayType, const CXStringUTF8 & Name, const CXStringUTF8 & Ref);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXWay();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	t_uint64 GetID() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	E_KEYHIGHWAY GetHighwayType() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8 GetName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8 GetRef() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetMaxSpeed(unsigned char MaxSpeed);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	unsigned char GetMaxSpeed() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void AddNode(CXNode *pNode);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetNodeCount() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXNode *GetNode(size_t Index) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool GetOSMValiState() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetOSMVali(bool NewValue);
};

typedef CXMapHashSimple<t_uint64, CXWay *>		TWayMap;		///< oiu
typedef CXBuffer<CXWay *>						TWayBuffer;		///< oiu


//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXPOWMMap {
private:
	static CXPOWMMap	*m_pInstance;			///< oiu
	// stuff
	CXStringASCII		m_FileName;				///< oiu
	int					m_iCurrentZone;			///< oiu
	// map
	TNodeMap			m_NodeMap;				///< oiu
	TWayMap				m_WayMap;				///< oiu
	CXTrackLog			m_TrackLog;				///< oiu
	// synchronisation
	mutable CXMutex		m_Mutex;				///< oiu
	//-------------------------------------
	CXPOWMMap(const CXPOWMMap &);						///< Not used.
	const CXPOWMMap & operator = (const CXPOWMMap &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool LoadMap0_1_1(CXFile & InFile, const CXStringASCII & FileName);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool LoadMap_CurrentVersion(CXFile & InFile, const CXStringASCII & FileName);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXPOWMMap();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXPOWMMap();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Clear();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetCurrentZone() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetDataPath(const CXStringASCII & Path);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool LoadMap(const CXStringASCII & FileName);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void PositionChanged(double dLon, double dLat);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void LockMap();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void UnlockMap();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	TNodeMap &GetNodeMap();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	TWayMap &GetWayMap();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXWay *GetWay(t_uint64 ID);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void RunOSMVali();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXTrackLog & GetTrackLog() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	static CXPOWMMap *Instance();
};

#endif // __CXPOWMMAP_HPP__
