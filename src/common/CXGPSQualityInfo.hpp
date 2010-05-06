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

#ifndef __CXGPSQUALITYINFO_HPP__
#define __CXGPSQUALITYINFO_HPP__

#include "CXStringASCII.hpp"
#include "CXTimeStampData.hpp"

//----------------------------------------------------------------------------
/**
 * \brief Class containing GPS quality information.
 *
 * Class containing GPS qualityn information: HDOP VDOP.
 */
class CXGPSQualityInfo {
private:
	double		m_dHDOP;	///< HDOP.
	double		m_dVDOP;	///< VDOP.
	//-------------------------------------
	/**
	 * \brief Copy from other instance.
	 *
	 * Copy data from other instance.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXGPSQualityInfo &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSQualityInfo();
	//-------------------------------------
	/**
	 * \brief Constructor.
	 *
	 * A Constructor.
	 * \param	dHDOP		HDOP.
	 * \param	dVDOP		VDOP.
	 */
	CXGPSQualityInfo(double dHDOP, double dVDOP);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * The copy constructor.
	 * \param	rOther		Instance to copy from.
	 */
	CXGPSQualityInfo(const CXGPSQualityInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSQualityInfo();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * The assignment operator.
	 * \param	rOther		Instance to copy from..
	 * \return				Const pointer to self.
	 */
	const CXGPSQualityInfo & operator = (const CXGPSQualityInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Get HDOP.
	 *
	 * Get HDOP value.
	 * \return	HDOP.
	 */
	double GetHDOP() const;
	//-------------------------------------
	/**
	 * \brief Set HDOP.
	 *
	 * Set HDOP value.
	 * \param	Newvalue	HDOP.
	 */
	void SetHDOP(double NewValue);
	//-------------------------------------
	/**
	 * \brief Get VDOP.
	 *
	 * Get VDOP value.
	 * \return	HDOP.
	 */
	double GetVDOP() const;
	//-------------------------------------
	/**
	 * \brief Set VDOP.
	 *
	 * Set VDOP value.
	 * \param	Newvalue	VDOP.
	 */
	void SetVDOP(double NewValue);
};

typedef CXTimeStampData<CXGPSQualityInfo> tTimeStampedGPSQualityInfo;

#endif // __CXGPSQUALITYINFO_HPP__
