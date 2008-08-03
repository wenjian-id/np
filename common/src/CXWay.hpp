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

#ifndef __CXWAY_HPP__
#define __CXWAY_HPP__

#include "CXMutex.hpp"
#include "CXNode.hpp"
#include "CXStringUTF8.hpp"

class CXWay;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXWay {
public:
	//-------------------------------------
	/**
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
	char			m_Layer;			///< oiu
	bool			m_oOSMValiFailed;	///< oiu
	TNodeBuffer		m_Nodes;			///< oiu
	//-------------------------------------
	CXWay();									///< Not used.
	CXWay(const CXWay &);						///< Not used.
	const CXWay & operator = (const CXWay &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXWay(t_uint64 ID, E_KEYHIGHWAY eHighwayType, const CXStringUTF8 & Name, const CXStringUTF8 & Ref);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXWay();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	t_uint64 GetID() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	E_KEYHIGHWAY GetHighwayType() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringUTF8 GetName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringUTF8 GetRef() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMaxSpeed(unsigned char NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	unsigned char GetMaxSpeed() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLayer(char NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	unsigned char GetLayer() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void AddNode(CXNode *pNode);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t GetNodeCount() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXNode *GetNode(size_t Index) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool GetOSMValiState() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetOSMVali(bool NewValue);
};

typedef CXMapHashSimple<t_uint64, CXWay *>		TWayMap;		///< oiu
typedef CXPOSMapHashSimple<t_uint64>			TPOSWayMap;		///< oiu
typedef CXBuffer<CXWay *>						TWayBuffer;		///< oiu
#endif // __CXPOWMMAP_HPP__
