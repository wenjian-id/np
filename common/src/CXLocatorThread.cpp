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
#include "CXCoor.hpp"
#include "CXUTMSpeed.hpp"
#include "CXNaviPOWM.hpp"
#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "CXSatelliteData.hpp"
#include "CXDebugInfo.hpp"
#include "TargetIncludes.hpp"
#include "CoordConstants.h"

#include <math.h>

const int TIMEOUT_RECEIVE = 5; // seconds
static const int SQUARE_MIN_SEGMENTSIZE = 25; // 5*5m
static const double SQUARE_MAXDIST = 1600; // 40*40

//---------------------------------------------------------------------
//-------------------------------------
CXLocatorThread::CXLocatorThread() :
	m_oNewDataGPSGGA(false),
	m_oNewDataGPSRMC(false),
	m_SpeedCalculator(4),
	m_eSpeedSource(e_SpeedCalculator),
	m_pNaviPOWM(NULL)
{
}

//-------------------------------------
CXLocatorThread::~CXLocatorThread() {
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewDataGPSGGA(bool NewValue) {
	CXMutexLocker L(&m_MutexInputData);
	m_oNewDataGPSGGA = NewValue;
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewDataGPSRMC(bool NewValue) {
	CXMutexLocker L(&m_MutexInputData);
	m_oNewDataGPSRMC = NewValue;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewDataGPSGGA() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_oNewDataGPSGGA;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewDataGPSRMC() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_oNewDataGPSRMC;
}

//-------------------------------------
void CXLocatorThread::SetGPSDataGGA(const tUCBuffer & Buffer) {
	CXMutexLocker L(&m_MutexInputData);
	// overwrite existing data
	m_InputBufferGPSGGA.SetData(Buffer);
	m_InputBufferGPSGGA.SetNow();
	SetFlag_NewDataGPSGGA(true);
}

//-------------------------------------
void CXLocatorThread::SetGPSDataRMC(const tUCBuffer & Buffer) {
	CXMutexLocker L(&m_MutexInputData);
	// overwrite existing data
	m_InputBufferGPSRMC.SetData(Buffer);
	m_InputBufferGPSRMC.SetNow();
	SetFlag_NewDataGPSRMC(true);
	// oiu put somewhere else
	CXSatelliteData::Instance()->SetRMCReceived();
}

//-------------------------------------
void CXLocatorThread::SetGPSDataGSA(const tUCBuffer & Buffer) {
	CXMutexLocker L(&m_MutexInputData);
	// process GSA packet
	CXBuffer<int> Sat;
	CXStringASCII Line(reinterpret_cast<const char *>(Buffer.GetBuffer()), Buffer.GetSize());
	if(ExtractGSAData(Line, Sat)) {
		// data extracted and OK
		// now set it
		CXSatelliteData::Instance()->SetActiveSatellites(Sat);
		// request repaint
		if(m_pNaviPOWM != NULL)
			m_pNaviPOWM->RequestRepaint(CXNaviPOWM::e_ModeSatInfo);
	}
}

//-------------------------------------
void CXLocatorThread::SetGPSDataGSV(const tUCBuffer & Buffer) {
	CXMutexLocker L(&m_MutexInputData);
	// process GSV packet
	CXStringASCII Line(reinterpret_cast<const char *>(Buffer.GetBuffer()), Buffer.GetSize());
	int NTelegrams = 0;
	int NCurrentTelegram = 0;
	int NSat = 0;
	int NInfos = 0;
	CXGSVSatelliteInfo Info1;
	CXGSVSatelliteInfo Info2;
	CXGSVSatelliteInfo Info3;
	CXGSVSatelliteInfo Info4;
	if(ExtractGSVData(Line, NTelegrams, NCurrentTelegram, NSat, NInfos, Info1, Info2, Info3, Info4)) {
		// data extracted and OK
		// now set it
		CXSatelliteData::Instance()->SetGSVData(NTelegrams, NCurrentTelegram, NSat, NInfos, Info1, Info2, Info3, Info4);
		// request repaint
		if(m_pNaviPOWM != NULL)
			m_pNaviPOWM->RequestRepaint(CXNaviPOWM::e_ModeSatInfo);
	}
}

//-------------------------------------
void CXLocatorThread::SetNaviPOWM(CXNaviPOWM *pNaviPOWM) {
	CXMutexLocker L(&m_Mutex);
	m_pNaviPOWM = pNaviPOWM;
}

//-------------------------------------
CXTimeStampData<tUCBuffer> CXLocatorThread::GetGPSDataGGA() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_InputBufferGPSGGA ;
}

//-------------------------------------
CXTimeStampData<tUCBuffer> CXLocatorThread::GetGPSDataRMC() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_InputBufferGPSRMC;
}

//-------------------------------------
void CXLocatorThread::OnThreadStarted() {
	// nothing to do
}

//-------------------------------------
void CXLocatorThread::OnThreadLoop() {
	// check if new data arriwed
	CXExactTime Now;
	bool NewDataRMC = GetFlag_NewDataGPSRMC();
	bool NewDataGGA = GetFlag_NewDataGPSGGA();
	bool NewDataArrived = false;
	// process new data
	if(NewDataRMC) {
		// process it
		// reset flag
		SetFlag_NewDataGPSRMC(false);
		CXTimeStampData<tUCBuffer> Buffer = GetGPSDataRMC();
		// extract RMC packet if possible
		unsigned long Size = Buffer.Data().GetSize();
		const char *pBuffer = reinterpret_cast<const char *>(Buffer.Data().GetBuffer());
		CXStringASCII Line(pBuffer, Size);
		CXRMCPacket RMCData;
		if(ExtractRMCData(Line, RMCData)) {
			// OK, valid data arrived
			m_LastReceivedPosition.SetNow();
			// set speed source to RMC speed
			m_eSpeedSource = e_RMC_Packet;
			double dLon = RMCData.GetLon();
			double dLat = RMCData.GetLat();
			// remember coordinates
			m_LastReceivedCoor = CXCoor(dLon, dLat);
			
			// check if really new data arrived
			if(RMCData.GetUTC() != m_LastPositionUTC) {
				// UTC differs, so new data
				NewDataArrived = true;
				m_LastPositionUTC = RMCData.GetUTC();
				
				// calculate speed
				m_SpeedCalculator.SetData(CXTimeStampData<CXCoor>(m_LastReceivedCoor, Buffer.TimeStamp()));

				CXUTMSpeed UTMSpeed;
				if(m_SpeedCalculator.HasValidSpeed()) {
					// take speed
					UTMSpeed = m_SpeedCalculator.GetSpeed();
				} else {
					// no valid current speed. try last valid speed
					UTMSpeed = m_SpeedCalculator.GetLastValidSpeed();
				}
				// set speed vector
				m_LastUTMSpeed.SetCos(UTMSpeed.GetCos());
				m_LastUTMSpeed.SetSin(UTMSpeed.GetSin());

			}
			// since e_RMC_Packet has a higher priority than e_SpeedCalculator,
			// the following is done outside the block executed only when really 
			// new data arrived.
			// check which speed to take
			if(m_eSpeedSource == e_RMC_Packet) {
				// set RMC speed
				m_LastUTMSpeed.SetSpeed(RMCData.GetSpeed());
			}
		}
	}
	if(NewDataGGA) {
		// process it
		// reset flag
		SetFlag_NewDataGPSGGA(false);
		// extract GGA packet if possible
		CXTimeStampData<tUCBuffer> Buffer = GetGPSDataGGA();
		unsigned long Size = Buffer.Data().GetSize();
		const char *pBuffer = reinterpret_cast<const char *>(Buffer.Data().GetBuffer());
		CXStringASCII Line(pBuffer, Size);
		CXGGAPacket GGAData;
		if(ExtractGGAData(Line, GGAData)) {
			// OK, valid GGA data arrived
			m_LastReceivedPosition.SetNow();
			// extract data
			double dLon = GGAData.GetLon();
			double dLat = GGAData.GetLat();
			// remember coordinates
			m_LastReceivedCoor = CXCoor(dLon, dLat);

			// set number of satellites
			CXSatelliteData::Instance()->SetNrSatGGA(GGAData.GetNSat());
			// set height
			m_NaviData.SetHeight(GGAData.GetHeight());
			// check if really new data arrived
			if(GGAData.GetUTC() != m_LastPositionUTC) {
				// UTC differs, so new data
				NewDataArrived = true;
				m_LastPositionUTC = GGAData.GetUTC();

				// calculate speed
				m_SpeedCalculator.SetData(CXTimeStampData<CXCoor>(m_LastReceivedCoor, Buffer.TimeStamp()));

				CXUTMSpeed UTMSpeed;
				if(m_SpeedCalculator.HasValidSpeed()) {
					// take speed
					UTMSpeed = m_SpeedCalculator.GetSpeed();
				} else {
					// no valid current speed. try last valid speed
					UTMSpeed = m_SpeedCalculator.GetLastValidSpeed();
				}

				// set speed vector
				m_LastUTMSpeed.SetCos(UTMSpeed.GetCos());
				m_LastUTMSpeed.SetSin(UTMSpeed.GetSin());

				// check if we must set speed
				if(m_eSpeedSource == e_SpeedCalculator) {
					// take computed speed
					m_LastUTMSpeed.SetSpeed(UTMSpeed.GetSpeed());
				}
			}
		}
	}
	if(NewDataArrived) {
		// set private navigation data
		m_NaviData.SetUTMSpeed(m_LastUTMSpeed);
		m_NaviData.SetCoor(m_LastReceivedCoor);
	} else {
		// no data arrived
		unsigned long Delta = Now - m_LastReceivedPosition;
		if(Delta > 1000*TIMEOUT_RECEIVE) {
			// oiu
			CXSatelliteData::Instance()->SetNrSatGGA(0);
			if(m_pNaviPOWM != NULL)
				m_pNaviPOWM->RequestRepaint(CXNaviPOWM::e_ModeMap);
		}
	}
	// check if we must hide logo
	bool LogoHidden = false;
	if(Now - m_StartTime > CXOptions::Instance()->GetLogoTime()) {
		if(CXOptions::Instance()->MustShowLogo())
			LogoHidden = true;
		CXOptions::Instance()->SetShowLogoFlag(false);
	}
	/// \todo change
	if(NewDataArrived || LogoHidden) {
		// data has been changed or logo hidden
		CXPOWMMap *pPOWMMap = CXPOWMMap::Instance();
		// notify listeners
		if((pPOWMMap != NULL)&& (CXSatelliteData::Instance()->GetNrSat() != 0)) {
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
bool CXLocatorThread::Locate(t_uint64 &rProxWay) {

	CXExactTime StartTime;
	StartTime.SetNow();

    // A segment defined by two nodes Node1(Node1x, Node1y) and Node2(Node2x, Node2y)
    // The received coordinate is defined by P(x0, y0).
    // The nearest point to P(x0,y0) lying on the segment PS(PSx, PSy)
  
    double PSx = 0;
    double PSy = 0;
    double dSquareMinDist = -1;	// smallest distance from x0,y0 to a segment
	bool first = true;
    
	CXNode *pNode1 = NULL;
	CXNode *pNode2 = NULL;
    double Node1x = 0;
    double Node1y = 0;
    double Node2x = 0;
    double Node2y = 0;
    double SqSegLen = 0;		// square length of segment
    double dSquareDist = 0;		// distance from x0,y0 to segment
    double dCos = 0;			// cosinus of angle between vector Node1->P and Node1->Node2

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
		CXWay::E_KEYHIGHWAY Type = pWay->GetHighwayType();
		bool oUseWay = false;
		switch(CXOptions::Instance()->GetMode()) {
			case CXOptions::e_ModeCar:
			{
				oUseWay =	(Type == CXWay::e_Motorway) ||
							(Type == CXWay::e_MotorwayLink) ||
							(Type == CXWay::e_Trunk) ||
							(Type == CXWay::e_TrunkLink) ||
							(Type == CXWay::e_Primary) ||
							(Type == CXWay::e_PrimaryLink) ||
							(Type == CXWay::e_Secondary) ||
							(Type == CXWay::e_Tertiary) ||
							(Type == CXWay::e_Unclassified) ||
							(Type == CXWay::e_Residential) ||
							(Type == CXWay::e_Service) ||
							(Type == CXWay::e_LivingStreet);
				break;
			}
			case CXOptions::e_ModeBike:
			{
				// oiu todo
				oUseWay =	(Type == CXWay::e_Motorway) ||
							(Type == CXWay::e_MotorwayLink) ||
							(Type == CXWay::e_Trunk) ||
							(Type == CXWay::e_TrunkLink) ||
							(Type == CXWay::e_Primary) ||
							(Type == CXWay::e_PrimaryLink) ||
							(Type == CXWay::e_Secondary) ||
							(Type == CXWay::e_Tertiary) ||
							(Type == CXWay::e_Unclassified) ||
							(Type == CXWay::e_Track) ||
							(Type == CXWay::e_Residential) ||
							(Type == CXWay::e_Service) ||
							(Type == CXWay::e_Cycleway) ||
							(Type == CXWay::e_Footway) ||
							(Type == CXWay::e_Pedestrian) ||
							(Type == CXWay::e_Steps) ||
							(Type == CXWay::e_LivingStreet);

				break;
			}
			case CXOptions::e_ModePedestrian:
			{
				// take all ways except "unknown"
				oUseWay = (Type != CXWay::e_Unknown);
				break;
			}
			case CXOptions::e_ModeCaching:
			{
				// take all ways except "unknown"
				oUseWay = (Type != CXWay::e_Unknown);
				break;
			}
			case CXOptions::e_ModeMapping:
			{
				// take all ways except "unknown"
				oUseWay = (Type != CXWay::e_Unknown);
				break;
			}
		}
		if(oUseWay) {
			size_t NodeCount = pWay->GetNodeCount();
			// start with 1
			for(size_t i=1; i<NodeCount; i++) {
				// get first node
				pNode1 = pWay->GetNode(i-1);
				// get second node
				pNode2 = pWay->GetNode(i);
    			// get coordinates
    			Node1x = pNode1->GetUTME();
    			Node1y = pNode1->GetUTMN();
    			Node2x = pNode2->GetUTME();
    			Node2y = pNode2->GetUTMN();

				// mx distance from endpoints to current position is 1000 m
				double dMax = 1000;
				if(	(fabs(Node1x - x0) < dMax) && (fabs(Node1y - y0) < dMax) && 
					(fabs(Node2x - x0) < dMax) && (fabs(Node2y - y0) < dMax))
				{
    				// compute SqSegLen
    				SqSegLen = (Node2x-Node1x)*(Node2x-Node1x)+(Node2y-Node1y)*(Node2y-Node1y);
    				// only compute segments with at least SQUARE_MIN_SEGMENTSIZE length
    				if(SqSegLen > SQUARE_MIN_SEGMENTSIZE) {
    					// compute cos of angle
        				dCos = ((x0-Node1x)*(Node2x-Node1x)+(y0-Node1y)*(Node2y-Node1y))/SqSegLen;
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
    				// compute square distance between P and PS
    				dSquareDist = (x0-PSx)*(x0-PSx) + (y0-PSy)*(y0-PSy);
    
    				// check if new best fit
    				if(first || (dSquareDist < dSquareMinDist)) {
						first = false;
    					// yes
    					dSquareMinDist = dSquareDist;
    					rProxWay = pWay->GetID();
    				}
				}
			}
		}
    }

	pPOWMMap->UnlockMap();

	CXExactTime StopTime;
	StopTime.SetNow();

	CXDebugInfo::Instance()->SetLocatorTime(StopTime-StartTime);

    if(first) {
    	// nothing found
    	return false;
    }

    	// if too far from a way return false
    if(dSquareMinDist > SQUARE_MAXDIST) {
    	return false;
	}

	return true;
}
