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
class CXTransformationMatrix2D;

//---------------------------------------------------------------------
/*
 * \brief This class encapsulates data and functionality for a node.
 *
 * This class encapsulates data and functionality for a node.
 */
class CXNode {
private:
	t_uint64	m_ID;			///< ID of node.
	CXCoor		m_Coor;			///< Coordinate of node
	int			m_DisplayX;		///< X coordinate on display [pixel];
	int			m_DisplayY;		///< Y coordinate on display [pixel];
	//-------------------------------------
	CXNode();										///< Not used.
	CXNode(const CXNode &);							///< Not used.
	const CXNode & operator = (const CXNode &);		///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief Constructor.
	 *
	 *	Constructor.
	 *	\param	ID		ID of node.
	 *	\param	Lon		Longitude of node [deg].
	 *	\param	Lat		Latitude of node [deg].
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
	 * \brief Get longitude.
	 *
	 *	Get longitude.
	 *	\return		Longitude [deg]
	 */
	double GetLon() const;
	//-------------------------------------
	/*
	 * \brief Get latitude.
	 *
	 *	Get latitude.
	 *	\return		Latitude [deg]
	 */
	double GetLat() const;
	//-------------------------------------
	/*
	 * \brief Get UTM easting.
	 *
	 *	Get UTM easting.
	 *	\return		UTM easting.
	 */
	double GetUTME() const;
	//-------------------------------------
	/*
	 * \brief Get UTM northing.
	 *
	 *	Get UTM northing.
	 *	\return		UTM northing.
	 */
	double GetUTMN() const;
	//-------------------------------------
	/*
	 * \brief Relocate UTM coordinates to new UTM zone.
	 * 
	 * Relocate UTM coordinates to new UTM zone.
	 * \param	NewUTMZone	New UTM Zone.
	 */
	void RelocateUTM(int NewUTMZone);
	//-------------------------------------
	/*
	 * \brief Get X coordinate on display.
	 *
	 *	Get X coordinate on display.
	 *	\return		X coordinate on display [pixel].
	 */
	int GetDisplayX() const;
	//-------------------------------------
	/*
	 * \brief Set X coordinate on display.
	 *
	 *	Set X coordinate on display.
	 *	\param	X	X coordinate on display [pixel].
	 */
	void SetDisplayX(int X);
	//-------------------------------------
	/*
	 * \brief Get Y coordinate on display.
	 *
	 *	Get Y coordinate on display.
	 *	\return		Y coordinate on display [pixel].
	 */
	int GetDisplayY() const;
	//-------------------------------------
	/*
	 * \brief Set Y coordinate on display.
	 *
	 *	Set Y coordinate on display.
	 *	\param	Y	Y coordinate on display [pixel].
	 */
	void SetDisplayY(int Y);
};

typedef CXMapHashSimple<t_uint64, CXNode *>		TNodeMap;		///< oiu
typedef CXBuffer<CXNode *>						TNodeBuffer;	///< oiu


//---------------------------------------------------------------------
/*
 * \brief This class encapsulates data and functionality for a node.
 *
 * This class encapsulates data and functionality for a node.
 */
class CXPOINode : public CXNode {
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * Order taken from http://etricceline.de/osm/germany/en_stats_amenity.htm
	 * Correctnes taken from http://wiki.openstreetmap.org/index.php/Map_Features
	 */
	enum E_POI_AMENITY1_TYPE {		// must fit the values in the map file!!!
		e_POI_Amenity1_Parking				= 0x0000000000000001,	///< Car park.
		e_POI_Amenity1_Fuel					= 0x0000000000000002,	///< Fuel.
		e_POI_Amenity1_PlaceOfWorhsip		= 0x0000000000000004,	///< Church, temple, etc.
		e_POI_Amenity1_Restaurant			= 0x0000000000000008,	///< Restaurant.
		e_POI_Amenity1_School				= 0x0000000000000010,	///< School.
		e_POI_Amenity1_Recycling			= 0x0000000000000020,	///< Recycling facilities.
		e_POI_Amenity1_Telephone			= 0x0000000000000040,	///< Public telephone
		e_POI_Amenity1_PostBox				= 0x0000000000000080,	///< Post box.
		e_POI_Amenity1_Pharmacy				= 0x0000000000000100,	///< Pharmacy.
		e_POI_Amenity1_Bank					= 0x0000000000000200,	///< Bank.
		e_POI_Amenity1_FastFood				= 0x0000000000000400,	///< Fast food.
		e_POI_Amenity1_PublicBuilding		= 0x0000000000000800,	///< Public building.
		e_POI_Amenity1_Pub					= 0x0000000000001000,	///< Pub.
		e_POI_Amenity1_Hospital				= 0x0000000000002000,	///< Hospital.
		e_POI_Amenity1_University			= 0x0000000000004000,	///< University campus and buildings.
		e_POI_Amenity1_PostOffice			= 0x0000000000008000,	///< Post office.
		e_POI_Amenity1_FireStation			= 0x0000000000010000,	///< Fire station.
		e_POI_Amenity1_Police				= 0x0000000000020000,	///< Police station.
		e_POI_Amenity1_TownHall				= 0x0000000000040000,	///< Town hall.
		e_POI_Amenity1_GraveYard			= 0x0000000000080000,	///< Grave yard.
		e_POI_Amenity1_BusStation			= 0x0000000000100000,	///< Bus station.
		e_POI_Amenity1_Toilets				= 0x0000000000200000,	///< Public toilets.
		e_POI_Amenity1_Cafe					= 0x0000000000400000,	///< Cafe.
		e_POI_Amenity1_Library				= 0x0000000000800000,	///< Library.
		e_POI_Amenity1_Cinema				= 0x0000000001000000,	///< Cinema.
		e_POI_Amenity1_ATM					= 0x0000000002000000,	///< ATM, cash point.
		e_POI_Amenity1_Theatre				= 0x0000000004000000,	///< Theatre or opera.
		e_POI_Amenity1_Biergarten			= 0x0000000008000000,	///< Biergarten.
		e_POI_Amenity1_BicycleParking		= 0x0000000010000000,	///< Parking for bicycles.
		e_POI_Amenity1_BusStop				= 0x0000000020000000,	///< Bus stop.
		e_POI_Amenity1_Courthouse			= 0x0000000040000000,	///< Courthouse.
		e_POI_Amenity1_Prison				= 0x0000000080000000,	///< Prison.
	};
private:
	t_uint64	m_POIAmenity1;	///< POI Amenity1 flags.
	//-------------------------------------
	CXPOINode();										///< Not used.
	CXPOINode(const CXPOINode &);						///< Not used.
	const CXPOINode & operator = (const CXPOINode &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief Constructor.
	 *
	 *	Constructor.
	 *	\param	ID		ID of node.
	 *	\param	Lon		Longitude of node [deg].
	 *	\param	Lat		Latitude of node [deg].
	 */
	CXPOINode(t_uint64 ID, double Lon, double Lat);
	//-------------------------------------
	/*
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXPOINode();
	//-------------------------------------
	/*
	 * \brief Check if point is POI of specific Amenity1 type.
	 *
	 *	Check if point is POI of specific Amenity1 type.
	 *	\param	eType	type to be checked.
	 *	\return			true if it is of this type.
	 */
	bool IsPOIAmenity1Type(E_POI_AMENITY1_TYPE eType) const;
	//-------------------------------------
	/*
	 * \brief Check if point is POI of Amenity1 type.
	 *
	 *	Check if point is POI of Amenity1.
	 *	\return			true if it is of this type.
	 */
	bool IsPOIAmenity1() const;
	//-------------------------------------
	/*
	 * \brief Get POI Amenity1 flag.
	 *
	 *	Get POI Amenity1 flag.
	 *	\return		POI Amenity1 flag.
	 */
	t_uint64 GetPOIAmenity1Type() const;
	//-------------------------------------
	/*
	 * \brief Set POI Amenity1 flag.
	 *
	 *	Set POI Amenity1 flag.
	 *	\param	NewValue	New value
	 */
	void SetPOIAmenity1Type(t_uint64 NewValue);
	//-------------------------------------
	/*
	 * \brief Compute position in bitmap (row, column) of the most important amenity only.
	 *
	 *	Compute position in bitmap (row, column) of the most important amenity only.
	 *	\param	rRow		Computed row.
	 *	\param	rCol		Computed column.
	 */
	void ComputeAmenity1PosInBMP(int & rRow, int & rCol);
};

typedef CXMapHashSimple<t_uint64, CXPOINode *>		TPOINodeMap;		///< oiu
typedef CXBuffer<CXPOINode *>						TPOINodeBuffer;		///< oiu


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
		e_Unknown		=  0,	///< oiu
		e_Motorway		=  1,	///< oiu
		e_MotorwayLink	=  2,	///< oiu
		e_Trunk			=  3,	///< oiu
		e_TrunkLink		=  4,	///< oiu
		e_Primary		=  5,	///< oiu
		e_PrimaryLink	=  6,	///< oiu
		e_Secondary		=  7,	///< oiu
		e_Tertiary		=  8,	///< oiu
		e_Unclassified	=  9,	///< oiu
		e_Track			= 10,	///< oiu
		e_Residential	= 11,	///< oiu
		e_Service		= 12,	///< oiu
		e_Bridleway		= 13,	///< oiu
		e_Cycleway		= 14,	///< oiu
		e_Footway		= 15,	///< oiu
		e_Pedestrian	= 16,	///< oiu
		e_Steps			= 17,	///< oiu
		e_EnumCount		= 18,	///< oiu
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
	// maps
	TNodeMap			m_NodeMap;				///< oiu
	TPOINodeMap			m_POINodes;				///< POIs. No need to delete the elements: they will be deleted from m_NodeMap.
	TWayMap				m_WayMap;				///< oiu
	CXTrackLog			m_TrackLog;				///< oiu
	// synchronisation
	mutable CXMutex		m_Mutex;				///< oiu
	//-------------------------------------
	CXPOWMMap(const CXPOWMMap &);						///< Not used.
	const CXPOWMMap & operator = (const CXPOWMMap &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief Load map version 0.1.2
	 *
	 *	Load map version 0.1.2
	 *	\param	InFile		File whith map data.
	 *	\param	FileName	File name for map file (used for error messages).
	 *	\return				true on success
	 */
	bool LoadMap0_1_2(CXFile & InFile, const CXStringASCII & FileName);
	//-------------------------------------
	/*
	 * \brief Load map version 0.1.1
	 *
	 *	Load map version 0.1.1
	 *	\param	InFile		File whith map data.
	 *	\param	FileName	File name for map file (used for error messages).
	 *	\return				true on success
	 */
	bool LoadMap0_1_1(CXFile & InFile, const CXStringASCII & FileName);
	//-------------------------------------
	/*
	 * \brief Load map current version
	 *
	 *	Load map current version
	 *	\param	InFile		File whith map data.
	 *	\param	FileName	File name for map file (used for error messages).
	 *	\return				true on success
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
	TPOINodeMap &GetPOINodeMap();
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
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ComputeDisplayCoordinates(const CXTransformationMatrix2D & TM);
};

#endif // __CXPOWMMAP_HPP__
