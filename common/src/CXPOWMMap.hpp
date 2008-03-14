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
#include "Utils.hpp"

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
	//Order taken from http://etricceline.de/osm/germany/en_stats_amenity.htm
	// Correctness taken from http://wiki.openstreetmap.org/index.php/Map_Features
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 *	oiu
	 */
	enum E_POI1_TYPE {		// must fit the values in the map file!!!
		// amenities
		e_POI1_Parking				= 0x00000001,	///< Car park.
		e_POI1_Fuel					= 0x00000002,	///< Fuel.
		e_POI1_PlaceOfWorhsip		= 0x00000004,	///< Church, temple, etc.
		e_POI1_Restaurant			= 0x00000008,	///< Restaurant.
		e_POI1_School				= 0x00000010,	///< School.
		e_POI1_Recycling			= 0x00000020,	///< Recycling facilities.
		e_POI1_Telephone			= 0x00000040,	///< Public telephone
		e_POI1_PostBox				= 0x00000080,	///< Post box.
		e_POI1_Pharmacy				= 0x00000100,	///< Pharmacy.
		e_POI1_Bank					= 0x00000200,	///< Bank.
		e_POI1_FastFood				= 0x00000400,	///< Fast food.
		e_POI1_PublicBuilding		= 0x00000800,	///< Public building.
		e_POI1_Pub					= 0x00001000,	///< Pub.
		e_POI1_Hospital				= 0x00002000,	///< Hospital.
		e_POI1_University			= 0x00004000,	///< University campus and buildings.
		e_POI1_PostOffice			= 0x00008000,	///< Post office.
		e_POI1_FireStation			= 0x00010000,	///< Fire station.
		e_POI1_Police				= 0x00020000,	///< Police station.
		e_POI1_TownHall				= 0x00040000,	///< Town hall.
		e_POI1_GraveYard			= 0x00080000,	///< Grave yard.
		e_POI1_BusStation			= 0x00100000,	///< Bus station.
		e_POI1_Toilets				= 0x00200000,	///< Public toilets.
		e_POI1_Cafe					= 0x00400000,	///< Cafe.
		e_POI1_Library				= 0x00800000,	///< Library.
		e_POI1_Cinema				= 0x01000000,	///< Cinema.
		e_POI1_ATM					= 0x02000000,	///< ATM, cash point.
		e_POI1_Theatre				= 0x04000000,	///< Theatre or opera.
		e_POI1_Biergarten			= 0x08000000,	///< Biergarten.
		e_POI1_BicycleParking		= 0x10000000,	///< Parking for bicycles.
		e_POI1_Courthouse			= 0x20000000,	///< Courthouse.
		e_POI1_Prison				= 0x40000000,	///< Prison.
		e_POI1_College				= 0x80000000,	///< College.
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI2_TYPE {		// must fit the values in the map file!!!
		// amenities
		e_POI2_Taxi					= 0x00000001,	///< Taxi.
		// highway
		e_POI2_Stop					= 0x00000002,	///< Stop sign
		e_POI2_TrafficSignals		= 0x00000004,	///< Traffic signals
		e_POI2_MotorwayJunction		= 0x00000008,	///< Motorway junction
		e_POI2_BusStop				= 0x00000010,	///< Bus stop.
		// railway
		e_POI2_RailwayStation		= 0x00000020,	///< Railway station.
		e_POI2_RailwayHalt			= 0x00000040,	///< Railway halt.
		e_POI2_TramStop				= 0x00000080,	///< Tram stop.
		e_POI2_SubwayEntrance		= 0x00000100,	///< Subway entrance
		e_POI2_RWCrossing			= 0x00000200,	///< Crossing
		e_POI2_LevelCrossing		= 0x00000400,	///< Level crossing
		// aeroway
		e_POI2_Aerodrome			= 0x00000800,	///< Aerodrome
		e_POI2_Helipad				= 0x00001000,	///< Helipad
		// power
		e_POI2_PowerTower			= 0x00002000,	///< Power tower.
		e_POI2_PowerSubStation		= 0x00004000,	///< Power sub station.
		// tourism
		e_POI2_Hotel				= 0x00008000,	///< Hotel.
		e_POI2_Attraction			= 0x00010000,	///< Attraction.
		e_POI2_Hostel				= 0x00020000,	///< Hostel.
		e_POI2_CampSite				= 0x00040000,	///< Camp site.
		e_POI2_ViewPoint			= 0x00080000,	///< Viewpoint.
		e_POI2_Information			= 0x00100000,	///< Information.
		e_POI2_Zoo					= 0x00200000,	///< Zoo.
		e_POI2_GuestHouse			= 0x00400000,	///< Guest house
		e_POI2_PicnicSite			= 0x00800000,	///< Picninc site.
		e_POI2_ThemePark			= 0x01000000,	///< Theme park.
		e_POI2_CaravanSite			= 0x02000000,	///< Caravan site.
		e_POI2_Motel				= 0x04000000,	///< Motel.
		e_POI2_Museum				= 0x08000000,	///< Museum.
		e_POI2_Artwork				= 0x10000000,	///< Artwork.
		// shop
		e_POI2_Supermarket			= 0x20000000,	///< Supermarket.
		e_POI2_ShopBakery			= 0x40000000,	///< Bakery
		e_POI2_ShopButcher			= 0x80000000,	///< Butcher.
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI3_TYPE {		// must fit the values in the map file!!!
		e_POI3_Kiosk				= 0x00000001,	///< Kiosk.
		e_POI3_ShopConvenience		= 0x00000002,	///< Shop convenience
		e_POI3_ShopDoItYourself		= 0x00000004,	///< Shop "do it yourself"
		e_POI3_ShopBicycle			= 0x00000008,	///< Shop bicycle.
		e_POI3_ShopOutdoor			= 0x00000010,	///< Shop Outdoor.
		// leisure
		// historic
		// military
		// natural
		// 
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI4_TYPE {		// must fit the values in the map file!!!
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI5_TYPE {		// must fit the values in the map file!!!
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI6_TYPE {		// must fit the values in the map file!!!
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI7_TYPE {		// must fit the values in the map file!!!
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_POI8_TYPE {		// must fit the values in the map file!!!
	};
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 * oiu
	 */
	enum E_PLACE_TYPE {		// must fit the values in the map file!!!
		e_Place_Continent	= 0x0001,	///< Continent.
		e_Place_Coutry		= 0x0002,	///< Country.
		e_Place_State		= 0x0004,	///< State.
		e_Place_Region		= 0x0008,	///< Region.
		e_Place_County		= 0x0010,	///< Country.
		e_Place_City		= 0x0020,	///< City.
		e_Place_Town		= 0x0040,	///< Town.
		e_Place_Village		= 0x0080,	///< Village.
		e_Place_Hamlet		= 0x0100,	///< Hamlet.
		e_Place_Suburb		= 0x0200,	///< Suburb.
		e_Place_Locality	= 0x0400,	///< Locality
		e_Place_Island		= 0x0800,	///< Island.
	};

private:
	t_uint32	m_POI[MaxPOITypes];	///< POI 1 flags.
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
	 * \brief Check if point is POI of POI1 type.
	 *
	 *	Check if point is POI of POI1.
	 *	\param		Index	Index of POI type [1-8].
	 *	\return				true if it is of this type.
	 */
	bool IsPOI(size_t Index) const;
	//-------------------------------------
	/*
	 * \brief Get POI1 flag.
	 *
	 *	Get POI1 flag.
	 *	\param		Index	Index of POI type [1-8].
	 *	\return				POI flag.
	 */
	t_uint32 GetPOIType(size_t Index) const;
	//-------------------------------------
	/*
	 * \brief Set POI flag.
	 *
	 *	Set POI flag.
	 *	\param		Index		Index of POI type [1-8].
	 *	\param		NewValue	New value
	 */
	void SetPOIType(size_t Index, t_uint32 NewValue);
	//-------------------------------------
	/*
	 * \brief Compute position in bitmap (row, column) of the most important POI only.
	 *
	 *	Compute position in bitmap (row, column) of the most important POI only.
	 *	\param	POI			oiu
	 *	\param	rRow		Computed row.
	 *	\param	rCol		Computed column.
	 */
	void ComputePOIPosInBMP(t_uint32 POI, int & rRow, int & rCol);
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
		e_LivingStreet	= 18,	///< oiu
		e_EnumCount		= 19,	///< oiu
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
