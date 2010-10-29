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


#ifndef __CXGPSDCLIENTBASE_HPP__
#define __CXGPSDCLIENTBASE_HPP__

#include <gps.h>

#include "IGPSDClient.hpp"
#include "CXSatelliteData.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class CXGPSDClientBase : public IGPSDClient {
private:
    //-------------------------------------
    CXGPSDClientBase(const CXGPSDClientBase &);                     ///< Not used.
    const CXGPSDClientBase & operator = (const CXGPSDClientBase &); ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void ClearBuffer(CXBuffer<CXSatelliteInfo *> & rBuffer);
protected:
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void DoProcessData(gps_data_t *pGPSData);
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    virtual void ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP) = 0;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    virtual void ReadSatelliteData(gps_data_t *pGPSData, CXBuffer<CXSatelliteInfo *> & rSatInfos, CXBuffer<int> & rActiveSats) = 0;
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * The default constructor.
     */
    CXGPSDClientBase();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * The destructor.
     */
    virtual ~CXGPSDClientBase();
};


#endif // __CXGPSDCLIENTBASE_HPP__
