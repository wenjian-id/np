/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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
#include "CXMutexLocker.hpp"
#include "CoordConversion.h"

#include "TargetIncludes.hpp"
#include <stdio.h>

#include <math.h>

const double EPSILON = 0.01;

//-------------------------------------
CXSpeedCalculator::CXSpeedCalculator(size_t BufferSize) :
	m_iBufferSize(BufferSize),
	m_pBuffer(NULL),
	m_oValid(false),
	m_iUTMZone(UTMZoneNone)
{
	m_pBuffer = new CXData*[m_iBufferSize];
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
	for(size_t i=0; i<m_iBufferSize; i++)
		if(m_pBuffer[i] != NULL)
			delete m_pBuffer[i];
}

//-------------------------------------
void CXSpeedCalculator::SetData(double Lon, double Lat, const CXUTMCoor & Coor, const CXExactTime & Time) {
	CXMutexLocker L(&m_Mutex);
	// check if m_iUTMZone changes
	if(m_iUTMZone != Coor.GetUTMZone()) {
		/// \todo implement
		// yes. recompute all UTMN and UTME in m_pBuffer
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
	m_pBuffer[0] = new CXData(Lon, Lat, Coor.GetUTMEasting(), Coor.GetUTMNorthing(), Time);
	// now calculate speed
	size_t count = 0;
	for(size_t j=0; j<m_iBufferSize; j++)
		if(m_pBuffer[j] != NULL)
			count++;
	double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	size_t dt1 = 0, dt2 = 0;
	if(count > 1) {
		// compute speed
		// take care, when more than one second between measurements
		CXExactTime StartTime = m_pBuffer[count-1]->m_Time;
		for(size_t i=0; i<count; i++) {
			if(i != count-1) {
				x1 = x1 + m_pBuffer[i]->m_UTME;
				y1 = y1 + m_pBuffer[i]->m_UTMN;
				dt1 = dt1 + (m_pBuffer[i]->m_Time-StartTime);
			}
			if(i != 0) {
				x2 = x2 + m_pBuffer[i]->m_UTME;
				y2 = y2 + m_pBuffer[i]->m_UTMN;
				dt2 = dt2 + (m_pBuffer[i]->m_Time-StartTime);
			}
		}
		x1 = x1/(count-1);
		y1 = y1/(count-1);
		dt1 = dt1/(count-1);
		x2 = x2/(count-1);
		y2 = y2/(count-1);
		dt2 = dt2/(count-1);
		// OK we have x,y, and time
		double dx = x1 - x2;
		double dy = y1 - y2;
		size_t  dt = dt1 - dt2;
		// compute speed
		double dSpeed = 0;
		if(fabs(dt) >= EPSILON)
			dSpeed = sqrt(dx*dx+dy*dy);
		if(dSpeed < 1) {
			// standstill
			// do not touch direction to avoid turning map around
			m_Speed.SetSpeed(0);
		} else {
			// moving
			// cos, sin
			// 0 is east, so use dx and dy
			double dCos = dx / dSpeed;
			double dSin = dy / dSpeed;
			m_Speed.SetSpeed(dSpeed);
			m_Speed.SetCos(dCos);
			m_Speed.SetSin(dSin);
		}
		m_LastValidSpeed = m_Speed;
		m_oValid = true;
	} else {
		// not enaugh data
	}
}

//-------------------------------------
void CXSpeedCalculator::ResetData() {
	CXMutexLocker L(&m_Mutex);
	ClearBuffer();
	m_oValid = false;
	m_Speed.Reset();
	m_LastValidSpeed.Reset();
}

//-------------------------------------
void CXSpeedCalculator::Timeout() {
	CXMutexLocker L(&m_Mutex);
	ClearBuffer();
	m_oValid = false;
	m_Speed.Reset();
	// do not touch last valid speed
}

//-------------------------------------
bool CXSpeedCalculator::HasValidSpeed() {
	CXMutexLocker L(&m_Mutex);
	return m_oValid;
}

//-------------------------------------
CXUTMSpeed CXSpeedCalculator::GetSpeed() const {
	CXMutexLocker L(&m_Mutex);
	return m_Speed;
}

//-------------------------------------
CXUTMSpeed CXSpeedCalculator::GetLastValidSpeed() const {
	CXMutexLocker L(&m_Mutex);
	return m_LastValidSpeed;
}
