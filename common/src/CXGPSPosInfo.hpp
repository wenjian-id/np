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
 * \brief oiu
 *
 */
class CXGPSPosInfo {
private:
	CXStringASCII	m_UTC;		///< oiu
	bool			m_oFix;		///< oiu
	double			m_dLon;		///< oiu
	double			m_dLat;		///< oiu
	double			m_dHeight;	///< oiu
	int				m_NSat;		///< oiu
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void CopyFrom(const CXGPSPosInfo &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSPosInfo();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSPosInfo(const CXStringASCII &UTC, bool oFix, double dLon, double dLat, double dHeight, int NSat);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSPosInfo(const CXGPSPosInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSPosInfo();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	const CXGPSPosInfo & operator = (const CXGPSPosInfo & rOther);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool GetFix() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetLon() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetLat() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	int GetNSat() const;
};

typedef CXTimeStampData<CXGPSPosInfo> tTimeStampedGPSPosInfo;

#endif // __CXGPSPOSINFO_HPP__
