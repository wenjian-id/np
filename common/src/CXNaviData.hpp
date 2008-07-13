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

#ifndef __CXNAVIDATA_HPP__
#define __CXNAVIDATA_HPP__

#include "CXRWLock.hpp"
#include "CXCoor.hpp"
#include "CXUTMSpeed.hpp"
#include "CXStringUTF8.hpp"
#include <TargetIncludes.hpp>

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXNaviData {
private:
	bool				m_oFix;				///< oiu
	//-------------
	// position stuff
	//-------------
	double				m_dHeight;			///< height
	CXCoor				m_GPSCoor;			///< coordinate
	CXCoor				m_LocatorCoor;		///< coordinate
	//-------------
	// speed stuff
	//-------------
	CXUTMSpeed			m_UTMSpeed;			///< UTM speed

	CXStringUTF8		m_StreetName;		///< name of street
	CXStringUTF8		m_Ref;				///< ref
	unsigned char		m_MaxSpeed;			///< max. speed
	t_uint64			m_WayID;			///< id of last located way
	bool				m_oLocated;			///< is located on a way or not
	bool				m_oTimeout;			///< timeout occured
	//-------------
	// general stuff
	//-------------
	mutable CXRWLock	m_RWLock;			///< oiu
	//-------------------------------------
	/*
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXNaviData &rOther);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXNaviData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXNaviData(const CXNaviData &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	~CXNaviData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXNaviData & operator = (const CXNaviData &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool HasFix() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetHeight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetHeight(double dHeight);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXCoor GetGPSCoor() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetGPSCoor(const CXCoor &Coor);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXCoor GetLocatorCoor() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLocatorCoor(const CXCoor &Coor);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXUTMSpeed GetUTMSpeed() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetUTMSpeed(const CXUTMSpeed & UTMSpeed);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8 GetStreetName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetStreetName(const CXStringUTF8 & StreetName);
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
	void SetRef(const CXStringUTF8 & Ref);
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
	void SetMaxSpeed(unsigned char MaxSpeed);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	t_uint64 GetWayID() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetWayID(t_uint64);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool GetLocated() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLocated(bool Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsTimeout() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetTimeout(bool Value);
};

#endif // __CXNAVIDATA_H_
