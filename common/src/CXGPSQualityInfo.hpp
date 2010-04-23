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
 * \brief oiu
 *
 */
class CXGPSQualityInfo {
private:
	double			m_dHDOP;	///< oiu
	double			m_dVDOP;		///< oiu
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void CopyFrom(const CXGPSQualityInfo &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSQualityInfo();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSQualityInfo(double dHDOP, double dVDOP);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	CXGPSQualityInfo(const CXGPSQualityInfo & rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSQualityInfo();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	const CXGPSQualityInfo & operator = (const CXGPSQualityInfo & rOther);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetHDOP() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	double GetVDOP() const;
};

typedef CXTimeStampData<CXGPSQualityInfo> tTimeStampedGPSQualityInfo;

#endif // __CXGPSQUALITYINFO_HPP__
