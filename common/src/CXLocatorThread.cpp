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

#include "CXLocatorThread.hpp"
#include "CXMutexLocker.hpp"
#include "CXStringASCII.hpp"
#include "Utils.hpp"
#include "CXUTMCoor.hpp"
#include "CXUTMSpeed.hpp"
#include "CXNaviPOWM.hpp"
#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "TargetIncludes.hpp"

#include <math.h>

const int TIMEOUT_RECEIVE = 5; // seconds
static const int MIN_SEGMENTSIZE = 5;
static const double MAXDIST = 40;

//---------------------------------------------------------------------
//-------------------------------------
CXLocatorThread::CXLocatorThread() :
	m_oNewDataGPS(false),
	m_SpeedCalculator(4),
	m_pNaviPOWM(NULL)
{
}

//-------------------------------------
CXLocatorThread::~CXLocatorThread() {
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewDataGPS(bool NewValue) {
	CXMutexLocker L(&m_MutexInputData);
	m_oNewDataGPS = NewValue;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewDataGPS() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_oNewDataGPS;
}

//-------------------------------------
void CXLocatorThread::SetGPSDataGGA(const tUCBuffer & Buffer) {
	CXMutexLocker L(&m_MutexInputData);
	// overwrite existing data
	m_InputBufferGPS = Buffer;
	SetFlag_NewDataGPS(true);
}

//-------------------------------------
void CXLocatorThread::SetNaviPOWM(CXNaviPOWM *pNaviPOWM) {
	CXMutexLocker L(&m_Mutex);
	m_pNaviPOWM = pNaviPOWM;
}

//-------------------------------------
tUCBuffer CXLocatorThread::GetGPSDataGGA() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_InputBufferGPS ;
}

//-------------------------------------
void CXLocatorThread::OnThreadStarted() {
	// nothing to do
}

//-------------------------------------
void CXLocatorThread::OnThreadLoop() {
	/// \todo implement
	// clear flag for m_NaviData
	m_NaviData.ClearChangedFlag();
	// check if new data arriwed
	bool NewData = GetFlag_NewDataGPS();
	// check if receive timeout
	CXExactTime Now;
	if(NewData) {
		// OK, we have new data
		// process it
		OnNewDataGPS(GetGPSDataGGA());
	} else {
		// no data arrived
		unsigned long Delta = Now - mLastReceivedGPS;
		if(Delta > 1000*TIMEOUT_RECEIVE) {
			m_NaviData.SetnSat(0);
//oiu			m_NaviData.SetUTMSpeed(0);
			// oiu m_SpeedCalculator
		}
	}
	// check if we must hide logo
	bool LogoHidden = false;
	if(Now - m_StartTime > CXOptions::Instance()->GetLogoTime()) {
		if(CXOptions::Instance()->MustShowLogo())
			LogoHidden = true;
		CXOptions::Instance()->ClearShowLogoFlag();
	}
	if(m_NaviData.Changed() || LogoHidden) {
		// data has been changed or logo hidden
		CXPOWMMap *pPOWMMap = CXPOWMMap::Instance();
		// notify listeners
		if((pPOWMMap != NULL)&& (m_NaviData.GetnSat() != 0)) {
			// load map only if valid position

			// check if new map has to be loaded
			char buf[100];
			double dLon = m_NaviData.GetLon();
			double dLat = m_NaviData.GetLat();
			int NameLon = static_cast<int>(floor(fabs(dLon*10)));
			int NameLat = static_cast<int>(floor(fabs(dLat*10)));
			char EW = 'E';
			if(dLon < 0 )
				EW = 'W';
			char NS = 'N';
			if(dLat < 0 )
				NS = 'S';
			snprintf(buf, 100, "%c%04d%c%03d.map", EW, NameLon, NS, NameLat);
			CXStringASCII FileName=CXOptions::Instance()->GetDirectoryMaps();
			FileName+=buf;
			if(pPOWMMap->GetFileName() != FileName) {
				pPOWMMap->LoadMap(FileName);
			}

			pPOWMMap->PositionChanged(m_NaviData.GetLon(), m_NaviData.GetLat());

			t_uint64 ID = 0;
			if(Locate(ID)) {
				m_NaviData.SetLocated(true);
				m_NaviData.SetWayID(ID);
				pPOWMMap->LockMap();
				CXStringUTF8 Name;
				CXStringUTF8 Ref;
				unsigned char MaxSpeed = 0;
				CXWay *pWay = pPOWMMap->GetWay(ID);
				if(pWay != NULL) {
					Name = pWay->GetName();
					Ref = pWay->GetRef();
					MaxSpeed = pWay->GetMaxSpeed();
				}
				m_NaviData.SetStreetName(Name);
				m_NaviData.SetRef(Ref);
				m_NaviData.SetMaxSpeed(MaxSpeed);
				pPOWMMap->UnlockMap();
			} else {
				m_NaviData.SetLocated(false);
				m_NaviData.SetStreetName("");
				m_NaviData.SetRef("");
				m_NaviData.SetMaxSpeed(0);
			}

		}
		if(m_pNaviPOWM != NULL)
			m_pNaviPOWM->PositionChanged(m_NaviData);
	}
}

//-------------------------------------
void CXLocatorThread::OnThreadStopped() {
	// nothing to do
}

//-------------------------------------
void CXLocatorThread::OnNewDataGPS(const tUCBuffer & Buffer) {
	CXMutexLocker L(&m_Mutex);
	// reset flag
	SetFlag_NewDataGPS(false);
	// extract GGA packet if possible
	unsigned long Size = Buffer.GetSize();
	const char *pBuffer = reinterpret_cast<const char *>(Buffer.GetBuffer());
	CXStringASCII Line(pBuffer, Size);
	double Lon = 0, Lat = 0, Height = 0; int nSat = 0;
	if(!ExtractGGAData(Line, Lon, Lat, Height, nSat))
		return;

	// OK, valid GGA data arrived
	mLastReceivedGPS.SetNow();
	CXUTMCoor UTMCoor(Lon, Lat);

	// calculate speed
	CXUTMSpeed Speed;
	m_SpeedCalculator.SetData(UTMCoor, mLastReceivedGPS);

	if(m_SpeedCalculator.HasValidSpeed()) {
		// take speed
		Speed = m_SpeedCalculator.GetSpeed();
	} else {
		// no valid current speed. try last valid speed
		Speed = m_SpeedCalculator.GetLastValidSpeed();
	}

	// set private navigation data
	m_NaviData.SetLon(Lon);
	m_NaviData.SetLat(Lat);
	m_NaviData.SetHeight(Height);
	m_NaviData.SetnSat(nSat);
	m_NaviData.SetUTMSpeed(Speed);
	m_NaviData.SetUTMCoor(UTMCoor);

}

//-------------------------------------
bool CXLocatorThread::Locate(t_uint64 &rProxWay) {

    // A segment defined by two nodes Node1(Node1x, Node1y) and Node2(Node2x, Node2y)
    // The received coordinate is defined by P(x0, y0).
    // The nearest point to P(x0,y0) lying on the segment PS(PSx, PSy)
  
    double PSx = 0;
    double PSy = 0;
    double dMinDist = -1;	// smallest distance from x0,y0 to a segment
	bool first = true;
    
	CXNode *pNode1 = NULL;
	CXNode *pNode2 = NULL;
    double Node1x = 0;
    double Node1y = 0;
    double Node2x = 0;
    double Node2y = 0;
    double SegLen = 0;		// length of segment
    double dDist = 0;		// distance from x0,y0 to segment
    double dCos = 0;		// cosinus of angle between vector Node1->P and Node1->Node2

	CXPOWMMap *pPOWMMap = CXPOWMMap::Instance();
    pPOWMMap->LockMap();

	char UTMLetter = 0;
	double x0 = 0;
	double y0 = 0;
	int NewZone = UTMZoneNone;

	int CurrentZone = pPOWMMap->GetCurrentZone();
	LLtoUTM(WGS84, m_NaviData.GetLon(), m_NaviData.GetLat(), CurrentZone, NewZone, UTMLetter, x0, y0);

    // Iterrate through ways
	TWayMap &Ways = pPOWMMap->GetWayMap();

	POS Pos = Ways.GetStart();
	CXWay *pWay = NULL;
	while (Ways.GetNext(Pos, pWay) != TWayMap::NPOS) {
		size_t NodeCount = pWay->GetNodeCount();
		// start with 1
		for(size_t i=1; i<NodeCount; i++) {
			// get first node
			pNode1 = pWay->GetNode(i-1);
			// get second node
			pNode2 = pWay->GetNode(i);
    		// get coordinates
    		Node1x = pNode1->GetX();
    		Node1y = pNode1->GetY();
    		Node2x = pNode2->GetX();
    		Node2y = pNode2->GetY();
    		// compute SegLen
    		SegLen = sqrt((Node2x-Node1x)*(Node2x-Node1x)+(Node2y-Node1y)*(Node2y-Node1y));

			// mx distance from endpoints to current position is 1000 m
			double dMax = 1000;
			if(	(fabs(Node1x - x0) < dMax) && (fabs(Node1y - y0) < dMax) && 
				(fabs(Node2x - x0) < dMax) && (fabs(Node2y - y0) < dMax))
			{
    			// only compute segments with at least MIN_SEGMENTSIZE length
    			if(SegLen > MIN_SEGMENTSIZE) {
    				// compute cos of angle
        			dCos = ((x0-Node1x)*(Node2x-Node1x)+(y0-Node1y)*(Node2y-Node1y))/(SegLen*SegLen);
    				if(dCos<0) {
    					// projection of P on segment lies before Node1 so take Node1
    					PSx = Node1x;
    					PSy = Node1y;
    				} else if (dCos>1) {
    					// projection of P on segment lies after Node2 so take Node2
    					PSx = Node2x;
    					PSy = Node2y;
    				} else {
    					// projection of P on segment lies between Node1 and Node2
    					PSx = Node1x + dCos*(Node2x-Node1x);
    					PSy = Node1y + dCos*(Node2y-Node1y);
    				}
    			} else {
    				// segment too short, so we take Node1
    				dCos=0;
    				PSx = Node1x;
    				PSy = Node1y;
    			}
    			// compute distance between P and PS
    			dDist = sqrt((x0-PSx)*(x0-PSx) + (y0-PSy)*(y0-PSy));
    
    			// check if new best fit
    			if(first || (dDist < dMinDist)) {
					first = false;
    				// yes
    				dMinDist = dDist;
    				rProxWay = pWay->GetID();
    			}
			}
		}
    }

	pPOWMMap->UnlockMap();

    if(first) {
    	// nothing found
    	return false;
    }

    	// if too far from a way return false
    if(dMinDist > MAXDIST) {
    	return false;
	}

	return true;
}
