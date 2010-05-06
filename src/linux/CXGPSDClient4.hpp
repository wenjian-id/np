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


#ifndef __CXGPSDCLIENT4_HPP__
#define __CXGPSDCLIENT4_HPP__

#include <gps.h>

#if (GPSD_API_MAJOR_VERSION == 4)

#include "CXGPSDClientBase.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class CXGPSDClient : public CXGPSDClientBase {
private:
	gps_data_t		*m_pGPSData;	///< oiu
	//-------------------------------------
	CXGPSDClient(const CXGPSDClient &);						///< Not used.
	const CXGPSDClient & operator = (const CXGPSDClient &);	///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void ReadNumberOfVisibleSatellites(gps_data_t *pGPSData, int &rNVisibleSat);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSDClient();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSDClient();
	//-------------------------------------
	/**
	 * \brief Open connection to gpsd.
	 *
	 * Open the connection to gpsd. Has to be implemented in derived classes.
	 * \return		true on success.
	 */
	virtual bool Open();
	//-------------------------------------
	/**
	 * \brief Close connection to gpsd.
	 *
	 * Close the connection to gpsd. Has to be implemented in derived classes.
	 * \return		true on success.
	 */
	virtual bool Close();
	//-------------------------------------
	/**
	 * \brief Check if connection is open.
	 *
	 * Check if the connection is open. Has to be implemented in derived classes.
	 * \return		true if open.
	 */
	virtual bool IsOpen();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void Read();
};


#endif // (GPSD_API_MAJOR_VERSION == 4)

#endif // __CXGPSDCLIENT4_HPP__
