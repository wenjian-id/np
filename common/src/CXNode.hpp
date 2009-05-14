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

#ifndef __CXNODE_HPP__
#define __CXNODE_HPP__

#include "Utils.hpp"
#include "CXCoor.hpp"
#include "CXMapHashSimple.hpp"

class CXWay;
class CXTransformationMatrix2D;

//---------------------------------------------------------------------
/**
 * \brief This class encapsulates data and functionality for a node.
 *
 * This class encapsulates data and functionality for a node.
 */
class CXNode {
private:
	CXCoor		m_Coor;			///< Coordinate of node
	int			m_DisplayX;		///< X coordinate on display [pixel];
	int			m_DisplayY;		///< Y coordinate on display [pixel];
	bool		m_oTerminator;	///< oiu
	//-------------------------------------
	CXNode();										///< Not used.
	const CXNode & operator = (const CXNode &);		///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Constructor.
	 *
	 *	Constructor.
	 *	\param	Lon				Longitude of node [deg].
	 *	\param	Lat				Latitude of node [deg].
	 */
	CXNode(double Lon, double Lat);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 *	Copy constructor.
	 *	\param	rOther	Node to copy.
	 */
	CXNode(const CXNode &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXNode();
	//-------------------------------------
	/**
	 * \brief Get longitude.
	 *
	 *	Get longitude.
	 *	\return		Longitude [deg]
	 */
	double GetLon() const;
	//-------------------------------------
	/**
	 * \brief Get latitude.
	 *
	 *	Get latitude.
	 *	\return		Latitude [deg]
	 */
	double GetLat() const;
	//-------------------------------------
	/**
	 * \brief Get UTM easting.
	 *
	 *	Get UTM easting.
	 *	\return		UTM easting.
	 */
	double GetUTME() const;
	//-------------------------------------
	/**
	 * \brief Get UTM northing.
	 *
	 *	Get UTM northing.
	 *	\return		UTM northing.
	 */
	double GetUTMN() const;
	//-------------------------------------
	/**
	 * \brief Relocate UTM coordinates to new UTM zone.
	 * 
	 * Relocate UTM coordinates to new UTM zone.
	 * \param	NewUTMZone	New UTM Zone.
	 */
	void RelocateUTM(int NewUTMZone);
	//-------------------------------------
	/**
	 * \brief Get X coordinate on display.
	 *
	 *	Get X coordinate on display.
	 *	\return		X coordinate on display [pixel].
	 */
	int GetDisplayX() const;
	//-------------------------------------
	/**
	 * \brief Set X coordinate on display.
	 *
	 *	Set X coordinate on display.
	 *	\param	X	X coordinate on display [pixel].
	 */
	void SetDisplayX(int X);
	//-------------------------------------
	/**
	 * \brief Get Y coordinate on display.
	 *
	 *	Get Y coordinate on display.
	 *	\return		Y coordinate on display [pixel].
	 */
	int GetDisplayY() const;
	//-------------------------------------
	/**
	 * \brief Set Y coordinate on display.
	 *
	 *	Set Y coordinate on display.
	 *	\param	Y	Y coordinate on display [pixel].
	 */
	void SetDisplayY(int Y);
	//-------------------------------------
	/**
	 * \brief Check if node is terminator node.
	 *
	 *	Check if node is terminator node.
	 *	\return		true if terminator node
	 */
	bool IsTerminator() const;
	//-------------------------------------
	/**
	 * \brief Set terminator flag.
	 *
	 *	Set terminator flag.
	 */
	void SetTerminator();
};

typedef CXBuffer<CXNode *>						TNodeBuffer;	///< oiu


//---------------------------------------------------------------------
/**
 * \brief This class encapsulates data and functionality for a node.
 *
 * This class encapsulates data and functionality for a node.
 */
class CXPOINode : public CXNode {
private:
	CXStringUTF8			m_Name;		///< oiu
	CXBuffer<E_POI_TYPE>	m_POITypes;	///< POI 1 flags.
	//-------------------------------------
	CXPOINode();										///< Not used.
	CXPOINode(const CXPOINode &);						///< Not used.
	const CXPOINode & operator = (const CXPOINode &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Constructor.
	 *
	 *	Constructor.
	 *	\param	Lon		Longitude of node [deg].
	 *	\param	Lat		Latitude of node [deg].
	 */
	CXPOINode(double Lon, double Lat);
	//-------------------------------------
	/**
	 * \brief Constructor.
	 *
	 *	Constructor.
	 *	\param	rNode	Node to copy from.
	 */
	CXPOINode(const CXNode &rNode);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXPOINode();
	//-------------------------------------
	/**
	 * \brief Get POI type count.
	 *
	 *	Get POI type count.
	 *	\return				POI flag.
	 */
	size_t GetPOITypeCount() const;
	//-------------------------------------
	/**
	 * \brief Get POI type at specific index.
	 *
	 *	Get POI type at specific index.
	 *	\param		Index	Index of POI type.
	 *	\return				POI type.
	 */
	E_POI_TYPE GetPOIType(size_t Index) const;
	//-------------------------------------
	/**
	 * \brief Set POI flag.
	 *
	 *	Set POI flag.
	 *	\param		NewValue	New POI type.
	 */
	void SetPOIType(E_POI_TYPE NewValue);
	//-------------------------------------
	/**
	 * \brief Set name.
	 *
	 *	Set name.
	 *	\param	NewValue	New value.
	 */
	void SetName(const CXStringUTF8 &NewValue);
	//-------------------------------------
	/**
	 * \brief Get name.
	 *
	 *	Get name.
	 *	\return	Name.
	 */
	CXStringUTF8 GetName() const;
};

typedef CXBuffer<CXPOINode *>						TPOINodeBuffer;		///< oiu

#endif // __CXNODE_HPP__
