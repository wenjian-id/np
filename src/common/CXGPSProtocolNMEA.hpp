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

#ifndef __CXGPSPROTOCOLNMEA_HPP__
#define __CXGPSPROTOCOLNMEA_HPP__

#include "CXGPSProtocol.hpp"
#include "CXBuffer.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSProtocolNMEA : public CXGPSProtocol {
private:
    tUCBuffer                       m_Buffer;           ///< oiu
    CXBuffer<CXSatelliteInfo *>     m_TmpGSVSatInfo;    ///< oiu
    int                             m_LastReceivedGSVTel;   ///< oiu
    int                             m_TmpNrSat;             ///< oiu
    //-------------------------------------
    CXGPSProtocolNMEA(const CXGPSProtocolNMEA &);                       ///< Not used.
    const CXGPSProtocolNMEA & operator = (const CXGPSProtocolNMEA &);   ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void ClearBuffer(CXBuffer<CXSatelliteInfo *> & rBuffer);
protected:
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    virtual bool AfterOpen();
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    virtual bool BeforeClose();
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    virtual bool OnReadAndProcessData();
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXGPSProtocolNMEA();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXGPSProtocolNMEA();
};

#endif // __CXGPSPROTOCOLNMEA_HPP__
