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

#ifndef __CXNAVIDATA_HPP__
#define __CXNAVIDATA_HPP__

#include "CXMutex.hpp"
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
	//-------------
	// position stuff
	//-------------
	double				m_dLon;				///< grad.dec
	double				m_dLat;				///< grad.dec
	double				m_dHeight;			///< height
	int					m_nSat;				///< nr satellites
	CXCoor				m_Coor;				///< coordinate
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
	double				m_TargetDist;		///< distance to target
	double				m_TargetCos;		///< oiu 0 grad = east
	double				m_TargetSin;		///< oiu 0 grad = east
	//-------------
	// general stuff
	//-------------
	bool				m_oChanged;			///< data has been changed
	mutable CXMutex		m_Mutex;		
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
	double GetLon() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLon(double dLon);
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
	void SetLat(double dLat);
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
	int GetnSat() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetnSat(int nSat);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXCoor GetCoor() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetCoor(const CXCoor &Coor);
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
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetTargetDist(double Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetTargetDist() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetTargetCos(double Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetTargetCos() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetTargetSin(double Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetTargetSin() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ClearChangedFlag();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetChangedFlag();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool Changed() const;
};

#endif // __CXNAVIDATA_H_
