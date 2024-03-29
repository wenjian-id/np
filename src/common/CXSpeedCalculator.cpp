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

#include "CXSpeedCalculator.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"
#include "Utils.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const size_t LASTUTCBUFFERSIZE = 3;
const double MINUTCDIFF = 0.1/60/60/24; ///< 0.1 seconds [days]

//-------------------------------------
CXSpeedCalculator::CXSpeedCalculator(size_t BufferSize) :
    m_iBufferSize(BufferSize),
    m_pBuffer(NULL),
    m_eSpeedSource(e_GGA_Packet),
    m_iCurrentUTMZone(UTMZoneNone),
    m_dRMCSpeed(0),
    m_oValidSpeed(false),
    m_oNewDataArrived(false),
    m_SpeedThreshold(1)
{
    m_pBuffer = new CXTimeStampData<CXCoor>*[m_iBufferSize];
    for(size_t i=0; i<m_iBufferSize; i++)
        m_pBuffer[i] = NULL;
}

//-------------------------------------
CXSpeedCalculator::~CXSpeedCalculator() {
    ClearBuffer();
    // delete buffer
    delete [] m_pBuffer;
    m_pBuffer = NULL;
}

//-------------------------------------
void CXSpeedCalculator::ClearBuffer() {
    // delete single data
    for(size_t i=0; i<m_iBufferSize; i++) {
        if(m_pBuffer[i] != NULL) {
            delete m_pBuffer[i];
        }
    }
}

//-------------------------------------
void CXSpeedCalculator::SetData(const CXUTCTime &UTC, const CXTimeStampData<CXCoor> &Coor) {
    CXWriteLocker WL(&m_RWLock);
    // check if m_iCurrentUTMZone changes
    if(m_iCurrentUTMZone != Coor.Data().GetUTMZone()) {
        /// yes it cahnged. Recompute all UTM coords and force them to m_iCurrentUTMZone
        for(size_t i=0; i<m_iBufferSize; i++) {
            if(m_pBuffer[i] != NULL) {
                m_pBuffer[i]->Data().RelocateUTM(m_iCurrentUTMZone);
            }
        }
    }
    // check, if we must delete last Value in m_pBuffer
    if(m_pBuffer[m_iBufferSize-1] != NULL) {
        // yes, throw away last value
        delete m_pBuffer[m_iBufferSize-1];
        m_pBuffer[m_iBufferSize-1] = NULL;
    }
    // fifo
    for(size_t i=m_iBufferSize-1; i>0; i--)
        m_pBuffer[i] = m_pBuffer[i-1];
    // set first value
    m_pBuffer[0] = new CXTimeStampData<CXCoor>(Coor);
    // adjust UTC time
    m_pBuffer[0]->SetUTCTime(UTC);
    // now calculate speed
    size_t count = 0;
    for(size_t j=0; j<m_iBufferSize; j++)
        if(m_pBuffer[j] != NULL)
            count++;
    if(count > 1) {
        // compute speed
        double X1 = 0, X2 = 0, Y1 = 0, Y2 = 0;
        size_t dt1 = 0, dt2 = 0;
        double dUTCt1 = 0, dUTCt2 = 0;
        // take care, when more than one second between measurements
        CXExactTime StartTime = m_pBuffer[count-1]->TimeStamp();
        CXUTCTime UTCStartTime = m_pBuffer[count-1]->UTCTime();
        for(size_t i=0; i<count; i++) {
            if(i != count-1) {
                X1 = X1 + m_pBuffer[i]->Data().GetUTMEasting();
                Y1 = Y1 + m_pBuffer[i]->Data().GetUTMNorthing();
                dt1 = dt1 + (m_pBuffer[i]->TimeStamp()-StartTime);
                dUTCt1 = dUTCt1 + (m_pBuffer[i]->UTCTime()-UTCStartTime).GetUTCTimeAsDouble();
            }
            if(i != 0) {
                X2 = X2 + m_pBuffer[i]->Data().GetUTMEasting();
                Y2 = Y2 + m_pBuffer[i]->Data().GetUTMNorthing();
                dt2 = dt2 + (m_pBuffer[i]->TimeStamp()-StartTime);
                dUTCt2 = dUTCt2 + (m_pBuffer[i]->UTCTime()-UTCStartTime).GetUTCTimeAsDouble();
            }
        }
        X1 = X1/(count-1);
        Y1 = Y1/(count-1);
        dt1 = dt1/(count-1);
        dUTCt1 = dUTCt1/(count-1);
        X2 = X2/(count-1);
        Y2 = Y2/(count-1);
        dt2 = dt2/(count-1);
        dUTCt2 = dUTCt2/(count-1);
        // OK we have x,y, and time
        double dx = X1 - X2;
        double dy = Y1 - Y2;
        double dUTCt = dUTCt1 - dUTCt2;
        // convert to seconds
        dUTCt = dUTCt*24*60*60;
        // compute speed
        double dUTCSpeed = 0;
        double dUnnormedSpeed = 0;
        if(fabs(dUTCt) >= MINUTCDIFF) {
            dUnnormedSpeed = sqrt(dx*dx+dy*dy);
            // normate to m/s
            dUTCSpeed = dUnnormedSpeed/dUTCt;
        }
        switch(m_eSpeedSource) {
            case e_GGA_Packet:  break;
            case e_RMC_Packet:  dUTCSpeed = m_dRMCSpeed; break;
        }
        // now set speed
        m_Speed.SetSpeed(dUTCSpeed);
        // now check if we have a standstill. Take rmc speed into account
        if(dUTCSpeed < m_SpeedThreshold) {
            // standstill. Do not touch direction to avoid turning map around
        } else {
            // moving. Set direction.
            // compute direction
            // 0 is east, so use dx and dy, if they are correct
            if((dx != 0) && (dy != 0) && (fabs(dUnnormedSpeed) > EPSILON)) {
                m_Speed.SetDirection(CXDirection(dx / dUnnormedSpeed, dy / dUnnormedSpeed));
            } else {
                // something went wrong. Do not touch direction
            }
        }

        m_LastValidSpeed = m_Speed;
        m_oValidSpeed = true;
    } else {
        // not enaugh data
    }
}

//-------------------------------------
void CXSpeedCalculator::SetGGAData(const CXUTCTime &UTC, const CXTimeStampData<CXCoor> &Coor) {
    double dUTC = UTC.GetUTCTimeAsDouble();
    bool oNew = true;
    for(size_t i=0; i< m_LastUTCs.GetSize(); i++) {
        if(fabs(m_LastUTCs[i] - dUTC) <= MINUTCDIFF) {
            oNew = false;
            break;
        }
    }
    if(oNew) {
        if(m_LastUTCs.GetSize() >= LASTUTCBUFFERSIZE) {
            m_LastUTCs.RemoveAt(0);
        }
        // new coordinates arrived
        SetData(UTC, Coor);
        m_oNewDataArrived = true;
        m_LastUTCs.Append(dUTC);
    }
}

//-------------------------------------
void CXSpeedCalculator::SetRMCData(const CXUTCTime &UTC, const CXTimeStampData<CXCoor> &Coor, double dRMCSpeed) {
    // set speed source
    m_eSpeedSource = e_RMC_Packet;
    // and RMC speed
    m_dRMCSpeed = dRMCSpeed;
    double dUTC = UTC.GetUTCTimeAsDouble();
    bool oNew = true;
    for(size_t i=0; i< m_LastUTCs.GetSize(); i++) {
        if(fabs(m_LastUTCs[i] - dUTC) <= MINUTCDIFF) {
            oNew = false;
            break;
        }
    }
    if(oNew) {
        if(m_LastUTCs.GetSize() >= LASTUTCBUFFERSIZE) {
            m_LastUTCs.RemoveAt(0);
        }
        // new coordinates arrived
        SetData(UTC, Coor);
        m_oNewDataArrived = true;
        m_LastUTCs.Append(dUTC);
    }
}

//-------------------------------------
void CXSpeedCalculator::ResetData() {
    CXWriteLocker WL(&m_RWLock);
    ClearBuffer();

    m_LastValidSpeed.Reset();

    m_eSpeedSource = e_GGA_Packet;
    m_iCurrentUTMZone = UTMZoneNone;
    m_Speed.Reset();
    m_dRMCSpeed = 0;
    m_oValidSpeed = false;
    m_oNewDataArrived = false;
    m_LastValidSpeed.Reset();
    m_SpeedThreshold = 1;
    m_LastUTCs.Clear();
}

//-------------------------------------
CXUTMSpeed CXSpeedCalculator::GetSpeed() const {
    CXReadLocker RL(&m_RWLock);
    CXUTMSpeed Result;
    if(m_oValidSpeed) {
        // take speed
        Result = m_Speed;
    } else {
        // no valid current speed. try last valid speed
        Result = m_LastValidSpeed;
    }
    return Result;
}

//-------------------------------------
void CXSpeedCalculator::SetSpeedThreshold(double NewValue) {
    CXWriteLocker WL(&m_RWLock);
    m_SpeedThreshold = fabs(NewValue);
}

//-------------------------------------
bool CXSpeedCalculator::NewDataArrived() const {
    CXReadLocker RL(&m_RWLock);
    return m_oNewDataArrived;
}

//-------------------------------------
void CXSpeedCalculator::ResetNewDataArrivedFlag() {
    CXWriteLocker WL(&m_RWLock);
    m_oNewDataArrived = false;
}
