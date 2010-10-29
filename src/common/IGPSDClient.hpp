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


#ifndef __IGPSDCLIENT_HPP__
#define __IGPSDCLIENT_HPP__

#include "CXStringASCII.hpp"
#include "CXGPSPosInfo.hpp"
#include "CXGPSCourseInfo.hpp"
#include "CXGPSQualityInfo.hpp"
#include "CXMutex.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSDConfig {
private:
    CXStringASCII   m_Address;      ///< oiu;
    CXStringASCII   m_Port;         ///< oiu;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CopyFrom(const CXGPSDConfig & rOther);
protected:
public:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXGPSDConfig();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXGPSDConfig(const CXGPSDConfig &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual ~CXGPSDConfig();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    const CXGPSDConfig & operator = (const CXGPSDConfig &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetAddress(const CXStringASCII & Address);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII GetAddress() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetPort(const CXStringASCII & Port);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII GetPort() const;
};



//----------------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class IGPSDClient {
private:
    CXGPSDConfig        m_Config;           ///< oiu
    //-------------------------------------
    IGPSDClient(const IGPSDClient &);                       ///< Not used.
    const IGPSDClient & operator = (const IGPSDClient &);   ///< Not used.
protected:
    CXGPSPosInfo        m_GPSPosInfo;               ///< oiu
    CXGPSCourseInfo     m_GPSCourseInfo;            ///< oiu
    CXGPSQualityInfo    m_GPSQualityInfo;           ///< oiu
    bool                m_oGPSPosInfoChanged;       ///< oiu
    bool                m_oGPSCourseInfoChanged;    ///< oiu
    bool                m_oGPSQualityInfoChanged;   ///< oiu
    mutable CXMutex     m_Mutex;                    ///< Synchronisation object
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * The default constructor.
     */
    IGPSDClient();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * The destructor.
     */
    virtual ~IGPSDClient();
    //-------------------------------------
    /**
     * \brief Open connection to gpsd.
     *
     * Open the connection to gpsd. Has to be implemented in derived classes.
     * \return      true on success.
     */
    virtual bool Open() = 0;
    //-------------------------------------
    /**
     * \brief Close connection to gpsd.
     *
     * Close the connection to gpsd. Has to be implemented in derived classes.
     * \return      true on success.
     */
    virtual bool Close() = 0;
    //-------------------------------------
    /**
     * \brief Check if connection is open.
     *
     * Check if the connection is open. Has to be implemented in derived classes.
     * \return      true if open.
     */
    virtual bool IsOpen() = 0;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    virtual void Read() = 0;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void SetConfig(const CXGPSDConfig &Config);
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    CXGPSDConfig GetConfig() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    bool GPSPosInfoChanged() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    CXGPSPosInfo GetGPSPosInfo() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void ResetGPSPosInfoChanged();
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    bool GPSCourseInfoChanged() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    CXGPSCourseInfo GetGPSCourseInfo() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void ResetGPSCourseInfoChanged();
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    bool GPSQualityInfoChanged() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    CXGPSQualityInfo GetGPSQualityInfo() const;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void ResetGPSQualityInfoChanged();
};

#endif // __IGPSDCLIENT_HPP__
