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

#ifndef __CXSATELLITEDATA_HPP__
#define __CXSATELLITEDATA_HPP__

#include "CXBuffer.hpp"
#include "CXNMEA.hpp"
#include "CXRWLock.hpp"

class CXDeviceContext;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSatelliteInfo {
private:
private:
    int     m_PRN;          ///< oiu
    int     m_Elevation;    ///< oiu
    int     m_Azimuth;      ///< oiu
    int     m_SNR;          ///< oiu
    //-------------------------------------
    /**
     * \brief Copy from other instance to self.
     *
     * Copy from other instance to self.
     * \param   rOther  Instance to copy from.
     */
    void CopyFrom(const CXSatelliteInfo &rOther);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXSatelliteInfo();
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXSatelliteInfo(const CXSatelliteInfo &rOther);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXSatelliteInfo();
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXSatelliteInfo & operator = (const CXSatelliteInfo &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetPRN() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetPRN(int NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetElevation() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetElevation(int NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetAzimuth() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetAzimuth(int NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetSNR() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetSNR(int NewValue);
};



//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSatellitesData {
private:
    int                             m_NrSat;                ///< oiu
    CXBuffer<int>                   m_ActiveSatellites;     ///< oiu
    CXBuffer<CXSatelliteInfo *>     m_SatInfo;              ///< oiu
    double                          m_HDOP;                 ///< oiu
    double                          m_VDOP;                 ///< oiu
    bool                            m_oRMCDataReceived;     ///< oiu
    bool                            m_oGGADataReceived;     ///< oiu
    bool                            m_oGSADataReceived;     ///< oiu
    bool                            m_oGSVDataReceived;     ///< oiu
    bool                            m_oGPSDDataReceived;    ///< oiu
    bool                            m_oHDOPReceived;        ///< oiu
    bool                            m_oVDOPReceived;        ///< oiu
    mutable CXRWLock                m_RWLock;               ///< Synchronization object.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CopyFrom(const CXSatellitesData &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void ClearBuffer(CXBuffer<CXSatelliteInfo *> & rBuffer);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXSatellitesData();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXSatellitesData(const CXSatellitesData &rOther);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXSatellitesData();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    const CXSatellitesData & operator = (const CXSatellitesData &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGGADataReceived();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetRMCDataReceived();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGSADataReceived();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGSVDataReceived();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGPSDDataReceived();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetNrSatGGA(int NrSatGGA);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int GetNrSat() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetActiveSatellites(const CXBuffer<int> &ActiveSatellites);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetSatelliteInfos(const CXBuffer<CXSatelliteInfo *>SatInfos);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetHDOP() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetHDOP(double NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetVDOP() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetVDOP(double NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    const CXBuffer<int> &ActiveSatellites() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    const CXBuffer<CXSatelliteInfo *> &SatInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasGGADataReceived() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasRMCDataReceived() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasGSADataReceived() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasGSVDataReceived() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasGPSDDataReceived() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasHDOPReceived() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool WasVDOPReceived() const;
};

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSatellites {
private:
    static CXSatellitesData     *m_pInstance;       ///< oiu
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXSatellites();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXSatellites();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    static CXSatellitesData *Instance();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    static void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY, int Width, int Height);
};

#endif // __CXSATELLITEDATA_HPP__
