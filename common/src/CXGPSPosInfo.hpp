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

#ifndef __CXGPSPOSINFO_HPP__
#define __CXGPSPOSINFO_HPP__

#include "CXStringASCII.hpp"
#include "CXTimeStampData.hpp"

//----------------------------------------------------------------------------
/**
 * \brief Class containing GPS position information.
 *
 * Class containing GPS position information: UTC, position number of satellites.
 */
class CXGPSPosInfo {
private:
	CXStringASCII	m_UTC;		///< UTC.
	bool			m_oFix;		///< Fix.
	double			m_dLon;		///< Longitude [deg].
	double			m_dLat;		///< Latitude [deg].
	double			m_dHeight;	///< Height [m].
	int				m_NSat;		///< Number of satellites
	//-------------------------------------
	/**
	 * \brief Copy from other instance.
	 *
	 * Copy data from other instance.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXGPSPosInfo &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSPosInfo();
	//-------------------------------------
	/**
	 * \brief Constructor.
	 *
	 * A Constructor.
	 * \param	UTC			UTC time.
	 * \param	oFix		Fix.
	 * \param	dLon		Longitude [deg].
	 * \param	dLat		Latitude [deg].
	 * \param	dHeight		Height [m].
	 * \param	NSat		Number of satellites.
	 */
	CXGPSPosInfo(const CXStringASCII &UTC, bool oFix, double dLon, double dLat, double dHeight, int NSat);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * The copy constructor.
	 * \param	rOther		Instance to copy from.
	 */
	CXGPSPosInfo(const CXGPSPosInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSPosInfo();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * The assignment operator.
	 * \param	rOther		Instance to copy from..
	 * \return				Const pointer to self.
	 */
	const CXGPSPosInfo & operator = (const CXGPSPosInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Get UTC.
	 *
	 * Get UTC time.
	 * \return	UTC time as string.
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/**
	 * \brief Check if GPS fix.
	 *
	 * Check if GPS fix or not.
	 * \return	true if fix.
	 */
	bool HasFix() const;
	//-------------------------------------
	/**
	 * \brief Get longitude.
	 *
	 * Get the longitude.
	 * \return	Longitude [deg].
	 */
	double GetLon() const;
	//-------------------------------------
	/**
	 * \brief Get latitude.
	 *
	 * Get the latitude.
	 * \return	Latitude [deg].
	 */
	double GetLat() const;
	//-------------------------------------
	/**
	 * \brief Get height.
	 *
	 * Get the height.
	 * \return	Height [m].
	 */
	double GetHeight() const;
	//-------------------------------------
	/**
	 * \brief Get number of satellites.
	 *
	 * Get the number of satellites.
	 * \return	Number of satellites.
	 */
	int GetNSat() const;
};

typedef CXTimeStampData<CXGPSPosInfo> tTimeStampedGPSPosInfo;

#endif // __CXGPSPOSINFO_HPP__
