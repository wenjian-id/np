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

#include "CXTrackLog.hpp"
#include "Utils.hpp"
#include "CXWriteLocker.hpp"
#include "CXReadLocker.hpp"
#include "CXOptions.hpp"

//----------------------------------------------------------------------------
CXTrackLog *CXTrackLog::m_pInstance = NULL;

//-------------------------------------
CXTrackLog::CXTrackLog() :
	m_MaxSize(0),
	m_MinDistance(0),
	m_iCurrentZone(UTMZoneNone)
{
	SetMaxSize(CXOptions::Instance()->GetTrackLogSize());
	SetMinDistance(CXOptions::Instance()->GetTrackLogMinDist());
}

//-------------------------------------
CXTrackLog::~CXTrackLog() {
}

//-------------------------------------
CXTrackLog *CXTrackLog::Instance() {
	if(m_pInstance == NULL)
		m_pInstance = new CXTrackLog();
	return m_pInstance;
}


//-------------------------------------
void CXTrackLog::DeleteSuperfluous() {
	if(m_MaxSize != 0) {
		// check if some data has to be deleted
		if(m_Coordinates.GetSize() > m_MaxSize) {
			size_t Diff = m_Coordinates.GetSize() - m_MaxSize;
			// delete first "Diff" elements
			for(size_t i=0; i<Diff; i++) {
				delete m_Coordinates[i];
				m_Coordinates[i] = NULL;
			}
			m_Coordinates.DeleteFirst(Diff);
		}
	}
}

//-------------------------------------
void CXTrackLog::SetMaxSize(size_t MaxSize) {
	CXWriteLocker WL(&m_RWLock);
	m_MaxSize = MaxSize;
	DeleteSuperfluous();
}

//-------------------------------------
void CXTrackLog::SetMinDistance(unsigned int MinDistance) {
	CXWriteLocker WL(&m_RWLock);
	m_MinDistance = MinDistance;
}

//-------------------------------------
void CXTrackLog::RelocateUTM(int NewUTMZone) {
	CXWriteLocker WL(&m_RWLock);
	if(m_iCurrentZone != NewUTMZone) {
		m_iCurrentZone = NewUTMZone;
		size_t Size = m_Coordinates.GetSize();
		for(size_t i=0; i<Size; i++) {
			CXCoor *pCoor = m_Coordinates[i];
			if(pCoor != NULL)
				pCoor->RelocateUTM(NewUTMZone);
		}
	}
}

//-------------------------------------
const TCoorBuffer & CXTrackLog::GetCoordinates() const {
	return m_Coordinates;
}

//-------------------------------------
CXRWLock & CXTrackLog::GetRWLock() {
	return m_RWLock;
}

//-------------------------------------
void CXTrackLog::AddCoordinate(double dLon, double dLat) {
	CXWriteLocker WL(&m_RWLock);
	CXCoor *pCoor = new CXCoor(dLon, dLat);
	pCoor->RelocateUTM(m_iCurrentZone);
	// check for m_MinDistance
	bool MustAppend = false;
	if(m_Coordinates.GetSize() > 0) {
		// get last coordinate
		CXCoor *pCoorLast = m_Coordinates[m_Coordinates.GetSize()-1];
		double Dist = CalcDistance(*pCoorLast, *pCoor);
		MustAppend = Dist > m_MinDistance;
	} else {
		// will be first coordinate in array
		MustAppend = true;
	}
	if(MustAppend) {
		m_Coordinates.Append(pCoor);
	} else {
		delete pCoor;
	}
	DeleteSuperfluous();
}
