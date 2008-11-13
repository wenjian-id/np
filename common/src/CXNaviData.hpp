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
/**
 * \brief oiu
 *
 */
class CXNaviData {
private:
	bool				m_oFix;				///< oiu
	double				m_dHeight;			///< Height [m].
	CXCoor				m_GPSCoor;			///< Received GPS coordinate.
	CXCoor				m_CorrectedGPSCoor;	///< Corrected GPS coordinate.
	CXCoor				m_LocatedCoor;		///< Located coordinate.
	CXUTMSpeed			m_UTMSpeed;			///< UTM speed.
	CXStringUTF8		m_StreetName;		///< Name of street.
	CXStringUTF8		m_Ref;				///< Ref of street.
	unsigned char		m_MaxSpeed;			///< Max. allowed speed.
	bool				m_oLocated;			///< Is located on a way or not.
	mutable CXRWLock	m_RWLock;			///< Synchronization object.
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXNaviData &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXNaviData();
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXNaviData(const CXNaviData &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	~CXNaviData();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXNaviData & operator = (const CXNaviData &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool HasFix() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetHeight(double dHeight);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXCoor GetGPSCoor() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetGPSCoor(const CXCoor &Coor);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXCoor GetCorrectedGPSCoor() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCorrectedGPSCoor(const CXCoor &Coor);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXCoor GetLocatedCoor() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLocatedCoor(const CXCoor &Coor);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXUTMSpeed GetUTMSpeed() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetUTMSpeed(const CXUTMSpeed & UTMSpeed);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringUTF8 GetStreetName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetStreetName(const CXStringUTF8 & StreetName);
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
	void SetRef(const CXStringUTF8 & Ref);
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
	void SetMaxSpeed(unsigned char MaxSpeed);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool GetLocated() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLocated(bool Value);
};

#endif // __CXNAVIDATA_HPP__
