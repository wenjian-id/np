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

#ifndef __CXLOCATORTHREAD_HPP__
#define __CXLOCATORTHREAD_HPP__

#include "CXLoopThread.hpp"
#include "CXTimeStampData.hpp"
#include "CXBuffer.hpp"
#include "CXNaviData.hpp"
#include "CXStringASCII.hpp"
#include "CXSpeedCalculator.hpp"
#include "CXGPSPosInfo.hpp"
#include "CXGPSCourseInfo.hpp"
#include "CXGPSQualityInfo.hpp"
#include "CXMutex.hpp"

class CXNaviPOWM;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXLocatorThread : public CXLoopThread {
private:
    tTimeStampedGPSPosInfo          m_GPSPosInfo;               ///< oiu
    tTimeStampedGPSCourseInfo       m_GPSCourseInfo;            ///< oiu
    tTimeStampedGPSQualityInfo      m_GPSQualityInfo;           ///< oiu
    bool                            m_oGPSConnected;            ///< oiu
    bool                            m_oNewGPSConnection;        ///< oiu
    bool                            m_oNewGPSPosInfo;           ///< oiu
    bool                            m_oNewGPSCourseInfo;        ///< oiu
    bool                            m_oNewGPSQualityInfo;       ///< oiu
    CXSpeedCalculator               m_SpeedCalculator;          ///< oiu
    CXExactTime                     m_LastReceivedPosition;     ///< oiu
    CXNaviData                      m_NaviData;                 ///< oiu
    CXCoor                          m_LastReceivedCoor;         ///< oiu
    CXCoor                          m_StartCoordinates;         ///< oiu
    bool                            m_oGPSFixAtLeastOnce;       ///< oiu
    bool                            m_oStartCoordinatesValid;   ///< oiu
    CXNaviPOWM                      *m_pNaviPOWM;               ///< oiu
    CXExactTime                     m_StartTime;                ///< starting time
    mutable CXMutex                 m_MutexInputData;           ///< Synchronization object for input data.
    mutable CXMutex                 m_Mutex;                    ///< Synchronization object.
    //-------------------------------------
    CXLocatorThread(const CXLocatorThread&);                        ///< Not used.
    const CXLocatorThread & operator = (const CXLocatorThread&);    ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetFlag_NewGPSConnection(bool NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetFlag_NewGPSPosInfo(bool NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetFlag_NewGPSCourseInfo(bool NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetFlag_NewGPSQualityInfo(bool NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool GetFlag_NewGPSConnection() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool GetFlag_NewGPSPosInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool GetFlag_NewGPSCourseInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool GetFlag_NewGPSQualityInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tTimeStampedGPSPosInfo GetGPSPosInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tTimeStampedGPSCourseInfo GetGPSCourseInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tTimeStampedGPSQualityInfo GetGPSQualityInfo() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Locate();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void LoadStartGPSCoordinates();
protected:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnThreadStarted();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnThreadLoop();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnThreadStopped();
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXLocatorThread();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXLocatorThread();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool IsGPSConnected() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGPSConnected(bool NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGPSPosInfo(const tTimeStampedGPSPosInfo &PosInfo);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGPSCourseInfo(const tTimeStampedGPSCourseInfo &CourseInfo);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetGPSQualityInfo(const tTimeStampedGPSQualityInfo &QualityInfo);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetNaviPOWM(CXNaviPOWM *pNaviPOWM);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SaveLastReceivedGPSCoordinate();
};


#endif // __CXLOCATORTHREAD_HPP__
