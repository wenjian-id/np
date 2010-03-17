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

#include "Utils.hpp"
#include "CXLocatorThread.hpp"
#include "CXMutexLocker.hpp"
#include "CXStringASCII.hpp"
#include "CXCoor.hpp"
#include "CXUTMSpeed.hpp"
#include "CXNaviPOWM.hpp"
#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "CXSatelliteData.hpp"
#include "CXDebugInfo.hpp"
#include "TargetIncludes.hpp"
#include "CoordConstants.h"
#include "CXTrackLog.hpp"

#include <math.h>

const int TIMEOUT_RECEIVE = 5; // seconds
static const int SQUARE_MIN_SEGMENTSIZE = 25; // 5*5m
static const double MAXDIST = 50; // 50m
static const char * pcLastCoorFileName = "last.gps";


//---------------------------------------------------------------------
//-------------------------------------
CXLocatorThread::CXLocatorThread() :
	m_oConnected(false),
	m_oNewDataConnection(false),
	m_oNewDataGPSGGA(false),
	m_oNewDataGPSRMC(false),
	m_SpeedCalculator(4),
	m_oGPSFixAtLeastOnce(false),
	m_oStartCoordinatesValid(false),
	m_pNaviPOWM(NULL)
{
	// load last received coordinates
	LoadStartGPSCoordinates();
}

//-------------------------------------
CXLocatorThread::~CXLocatorThread() {
}

//-------------------------------------
bool CXLocatorThread::IsConnected() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_oConnected;
}

//-------------------------------------
void CXLocatorThread::SetConnected(bool NewValue) {
	CXMutexLocker L(&m_MutexInputData);
	m_oConnected = NewValue;
	SetFlag_NewDataConnection(true);
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewDataConnection(bool NewValue) {
	CXMutexLocker L(&m_MutexInputData);
	m_oNewDataConnection = NewValue;
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
bool CXLocatorThread::GetFlag_NewDataConnection() const {
	CXMutexLocker L(&m_MutexInputData);
	return m_oNewDataConnection;
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
	CXGSAPacket GSAPacket;
	CXStringASCII Line(reinterpret_cast<const char *>(Buffer.GetBuffer()), Buffer.GetSize());
	if(ExtractGSAData(Line, GSAPacket)) {
		// data extracted and OK
		// now set it
		CXSatelliteData::Instance()->SetActiveSatellites(GSAPacket.GetSatellites());
		// set HDOP and VDOP
		CXSatelliteData::Instance()->SetHDOP(GSAPacket.GetHDOP());
		CXSatelliteData::Instance()->SetVDOP(GSAPacket.GetVDOP());
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
	bool oHasFix = false;
	bool oNewDataNoFix = false;
	bool oNewDataConnection = GetFlag_NewDataConnection();
	SetFlag_NewDataConnection(false);
	// set connection status in m_NaviData
	m_NaviData.SetConnected(IsConnected());
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
			// set UTC
			m_NaviData.SetUTC(RMCData.GetUTC());
			oHasFix = RMCData.HasFix();
			m_LastReceivedPosition.SetNow();
			// check fix
			if(oHasFix) {
				m_oGPSFixAtLeastOnce = true;
				double dLon = RMCData.GetLon();
				double dLat = RMCData.GetLat();
				// remember coordinates
				m_LastReceivedCoor = CXCoor(dLon, dLat);
				// set data in speed calculator
				m_SpeedCalculator.SetRMCData(RMCData.GetUTC(), CXTimeStampData<CXCoor>(m_LastReceivedCoor, Buffer.TimeStamp()), RMCData.GetSpeed());
			} else {
				oNewDataNoFix = true;
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
			// set UTC
			m_NaviData.SetUTC(GGAData.GetUTC());
			oHasFix = GGAData.HasFix();
			m_LastReceivedPosition.SetNow();
			// set number of satellites
			CXSatelliteData::Instance()->SetNrSatGGA(GGAData.GetNSat());
			// set HDOP
			CXSatelliteData::Instance()->SetHDOP(GGAData.GetHDOP());
			// check fix
			if(oHasFix) {
				m_oGPSFixAtLeastOnce = true;
				// extract data
				double dLon = GGAData.GetLon();
				double dLat = GGAData.GetLat();
				// remember coordinates
				m_LastReceivedCoor = CXCoor(dLon, dLat);
				// set height
				m_NaviData.SetHeight(GGAData.GetHeight());
				// set data in speed calculator
				m_SpeedCalculator.SetGGAData(GGAData.GetUTC(), CXTimeStampData<CXCoor>(m_LastReceivedCoor, Buffer.TimeStamp()));
			} else {
				oNewDataNoFix = true;
			}
		}
	}
	bool oNewDataArrived = m_SpeedCalculator.NewDataArrived() || oNewDataNoFix || oNewDataConnection;

	if(oNewDataArrived) {
		// set speed thresholds for speed calculator
		switch(CXOptions::Instance()->GetMode()) {
			case CXOptions::e_ModeCar:			m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdCar()); break;
			case CXOptions::e_ModeBike:			m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdBike()); break;
			case CXOptions::e_ModePedestrian:	m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdPedestrian()); break;
			case CXOptions::e_ModeCaching:		m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdCaching()); break;
			case CXOptions::e_ModeMapping:		m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdMapping()); break;
		}
		// set private navigation data
		CXUTMSpeed UTMSpeed = m_SpeedCalculator.GetSpeed();
		m_NaviData.SetUTMSpeed(UTMSpeed);
		if(m_oGPSFixAtLeastOnce) {
			// at least one GPS fix. Use last received coordinates
			m_NaviData.SetGPSCoor(m_LastReceivedCoor);
		} else {
			// no GPS fix yet
			if(CXOptions::Instance()->GetStartWithLastPosition() != CXOptions::e_SWLP_None) {
				if(m_oStartCoordinatesValid) {
					// use start cordinates
					m_NaviData.SetGPSCoor(m_StartCoordinates);
				} else {
					// could not load start coordinates
				}
			} else {
				// no fix yet and not starting with last saved coordinates or custom coordinates
			}
		}
		m_NaviData.SetFix(oHasFix);
		// compute and set CorrectedGPSCoor
		CXCoor CorrectedGPSCoor(m_NaviData.GetGPSCoor());
		int GPSReceiverLag = CXOptions::Instance()->GetGPSReceiverLag();
		// add last draw time.
		int Lag = GPSReceiverLag + CXDebugInfo::Instance()->GetDrawTime();
		double dE = 1.0*Lag/1000.0*UTMSpeed.GetSpeed()*UTMSpeed.GetCos();
		double dN = 1.0*Lag/1000.0*UTMSpeed.GetSpeed()*UTMSpeed.GetSin();
		CorrectedGPSCoor.OffsetCoor(dE, dN);
		m_NaviData.SetCorrectedGPSCoor(CorrectedGPSCoor);
	} else {
		// no data arrived
		unsigned long Delta = Now - m_LastReceivedPosition;
		if(Delta > 1000*TIMEOUT_RECEIVE) {
			// if still connected reset number of satellites to zero. maybe we are in a tunnel or so.
			// if not connected, do not reset number of satellites
			if(IsConnected()) {
				CXSatelliteData::Instance()->SetNrSatGGA(0);
			}
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
	if(oNewDataArrived || LogoHidden) {
		// data has been changed or logo hidden
		// reset speed calculator new data flag
		m_SpeedCalculator.ResetNewDataArrivedFlag();
		CXPOWMMap *pPOWMMap = CXPOWMMap::Instance();
		// notify listeners
		if(pPOWMMap != NULL) {
			// position has changed
			CXCoor Coor = m_NaviData.GetCorrectedGPSCoor();
			double dLon = Coor.GetLon();
			double dLat = Coor.GetLat();
			if(oHasFix && CXOptions::Instance()->MustShowTrackLog()) {
				CXTrackLog::Instance()->AddCoordinate(dLon, dLat);
			}
		}
		// locate 
		Locate();
		if(m_pNaviPOWM != NULL)
			m_pNaviPOWM->PositionChanged(m_NaviData);
	}
}

//-------------------------------------
void CXLocatorThread::OnThreadStopped() {
	// do nothing
}

//-------------------------------------
void CXLocatorThread::SaveLastReceivedGPSCoordinate() {
	// check if we can save last received coordinates
	if(m_oGPSFixAtLeastOnce) {
		// at least one fix. use it to save data
		double dLon = m_LastReceivedCoor.GetLon();
		double dLat = m_LastReceivedCoor.GetLat();
		unsigned long ulLon = static_cast<unsigned long>(fabs(dLon)*SCALE_FACTOR_UI32);
		unsigned long ulLat = static_cast<unsigned long>(fabs(dLat)*SCALE_FACTOR_UI32);
		// set neg-bit
		// since 180 is max value for Lon/Lat, the max value for
		// ulLon/ulLat is 0x0ABA9500
		// so we can use msb to mark negative values
		if(dLon < 0) {
			ulLon |= 0x80000000;
		}
		if(dLat < 0) {
			ulLat |= 0x80000000;
		}
		CXFile OutFile;
		CXStringASCII FileName = CXOptions::Instance()->GetDirectorySave();
		FileName += pcLastCoorFileName;
		if(OutFile.Open(FileName.c_str(), CXFile::E_WRITE) == CXFile::E_OK) {
			// write data
			WriteUI32(OutFile, ulLon);
			WriteUI32(OutFile, ulLat);
		} else {
			// open error
		}
	}
}

//-------------------------------------
bool CXLocatorThread::LoadStartGPSCoordinates() {
	m_oStartCoordinatesValid = false;
	if(CXOptions::Instance()->GetStartWithLastPosition() == CXOptions::e_SWLP_LastPos) {
		CXFile InFile;
		CXStringASCII FileName = CXOptions::Instance()->GetDirectorySave();
		FileName += pcLastCoorFileName;
		if(InFile.Open(FileName.c_str(), CXFile::E_READ) == CXFile::E_OK) {
			// read data
			t_uint32 ulLon = 0; 
			t_uint32 ulLat = 0;
			if(ReadUI32(InFile, ulLon) && ReadUI32(InFile, ulLat)) {
				// compute lon
				double dLon = ConvertSavedUI32(ulLon);
				// compute lat
				double dLat = ConvertSavedUI32(ulLat);
				m_StartCoordinates = CXCoor(dLon, dLat);
				m_oStartCoordinatesValid = true;
			} else {
				// read error
				m_oStartCoordinatesValid = false;
			}
		} else {
			// open error
			m_oStartCoordinatesValid = false;
		}
	} else if(CXOptions::Instance()->GetStartWithLastPosition() == CXOptions::e_SWLP_Custom) {
		// start with custom coordinates
		m_StartCoordinates = CXOptions::Instance()->GetStartPosition();
		m_oStartCoordinatesValid = true;
	}
	return m_oStartCoordinatesValid;
}


//-------------------------------------
void CXLocatorThread::Locate() {

	CXUTMSpeed UTMSpeed = m_NaviData.GetUTMSpeed();
	// initialize LocatedCoor
	m_NaviData.SetLocatedCoor(m_NaviData.GetCorrectedGPSCoor());

	if(CXPOWMMap::Instance() == NULL)
		return;

    // A segment defined by two nodes Node1(Node1x, Node1y) and Node2(Node2x, Node2y)
    // The received coordinate is defined by P(x0, y0).
    // The nearest point to P(x0,y0) lying on the segment PS(PSx, PSy)
  
    double PSx = 0;
    double PSy = 0;
    double PSProxx = 0;
    double PSProxy = 0;
    double dMaxFitness = -1;
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

	double dLon = m_NaviData.GetCorrectedGPSCoor().GetLon();
	double dLat = m_NaviData.GetCorrectedGPSCoor().GetLat();
	double dLonMin = dLon - 0.01;
	double dLonMax = dLon + 0.01;
	double dLatMin = dLat - 0.01;
	double dLatMax = dLat + 0.01;

	// compute UTM coordinates
	char UTMLetterCurrent = 0;
	double x0 = 0;
	double y0 = 0;
	int UTMZoneCurrent = UTMZoneNone;
	LLtoUTM(WGS84, dLon, dLat, UTMZoneNone, UTMZoneCurrent, UTMLetterCurrent, x0, y0);

	// now get map sections for locator thread
	CXVisibleMapSectionDescr Descr(dLonMin, dLatMin, dLonMax, dLatMax, e_ZoomLevel_0);
	TMapSectionPtrArray MapSections = CXPOWMMap::Instance()->GetMapSectionsLocator(Descr);

	size_t idx=0;
	// lock and prepare map sections
	CXBuffer<bool> LockedMapSections;
	LockedMapSections.Resize(MapSections.GetSize());
	size_t MapSectionSize = MapSections.GetSize();
	for(idx=0; idx<MapSectionSize; idx++) {
		CXMapSection *pMapSection = MapSections[idx].GetPtr();
		if(pMapSection->GetLoadStatus() == e_LSLoaded) {
			// lock
			pMapSection->Lock();
			// relocate
			pMapSection->RelocateUTM(UTMZoneCurrent);
			LockedMapSections[idx] = true;
		} else {
			LockedMapSections[idx] = false;
		}
	}

	CXExactTime StartTime;
	StartTime.SetNow();

	CXWay *pProxWay = NULL;
	bool oForward = true;
	MapSectionSize = MapSections.GetSize();
	for(char Layer = MINLAYER; Layer <= MAXLAYER; Layer++) {
		for(size_t idx=0; idx<MapSectionSize; idx++) {
			if(LockedMapSections[idx]) {
				CXMapSection *pMapSection = MapSections[idx].GetPtr();
				if(pMapSection != NULL) {
					// prepare locator
					TWayBuffer *pWayBuffer = pMapSection->GetWayBuffer(Layer);
					if(pWayBuffer != NULL) {
						CXWay *pWay = NULL;
						//iterate through ways
						size_t ws = pWayBuffer->GetSize();
						for(size_t w=0; w<ws; w++) {
							pWay = (*pWayBuffer)[w];

							E_WAY_TYPE Type = pWay->GetWayType();
							E_ONEWAY_TYPE eOneway = pWay->GetOneway();
							bool oUseWay = false;
							switch(CXOptions::Instance()->GetMode()) {
								case CXOptions::e_ModeCar:
								{
									oUseWay =	(Type == e_Way_Motorway) ||
												(Type == e_Way_MotorwayLink) ||
												(Type == e_Way_Trunk) ||
												(Type == e_Way_TrunkLink) ||
												(Type == e_Way_Primary) ||
												(Type == e_Way_PrimaryLink) ||
												(Type == e_Way_Secondary) ||
												(Type == e_Way_Tertiary) ||
												(Type == e_Way_Unclassified) ||
												(Type == e_Way_Residential) ||
												(Type == e_Way_Service) ||
												(Type == e_Way_LivingStreet);
									break;
								}
								case CXOptions::e_ModeBike:
								{
									// oiu todo
									oUseWay =	(Type == e_Way_Motorway) ||
												(Type == e_Way_MotorwayLink) ||
												(Type == e_Way_Trunk) ||
												(Type == e_Way_TrunkLink) ||
												(Type == e_Way_Primary) ||
												(Type == e_Way_PrimaryLink) ||
												(Type == e_Way_Secondary) ||
												(Type == e_Way_Tertiary) ||
												(Type == e_Way_Unclassified) ||
												(Type == e_Way_Track) ||
												(Type == e_Way_Residential) ||
												(Type == e_Way_Service) ||
												(Type == e_Way_Cycleway) ||
												(Type == e_Way_Footway) ||
												(Type == e_Way_Pedestrian) ||
												(Type == e_Way_Steps) ||
												(Type == e_Way_LivingStreet);

									break;
								}
								case CXOptions::e_ModePedestrian:
								{
									// take all ways except "unknown"
									oUseWay = (Type != e_Way_Unknown);
									break;
								}
								case CXOptions::e_ModeCaching:
								{
									// take all ways except "unknown"
									oUseWay = (Type != e_Way_Unknown);
									break;
								}
								case CXOptions::e_ModeMapping:
								{
									// take all ways except "unknown"
									oUseWay = (Type != e_Way_Unknown);
									break;
								}
							}
							if(oUseWay) {
								size_t NodeCount = pWay->GetNodeList()->GetNodeCount();
								// start with 1
								for(size_t i=1; i<NodeCount; i++) {
									// get first node
									pNode1 = pWay->GetNodeList()->GetNode(i-1);
									// get second node
									pNode2 = pWay->GetNodeList()->GetNode(i);
    								// get coordinates
    								Node1x = pNode1->GetUTME();
    								Node1y = pNode1->GetUTMN();
    								Node2x = pNode2->GetUTME();
    								Node2y = pNode2->GetUTMN();

									// max distance from endpoints to current position is 1000 m
									double dMax = 1000;
									if(	(fabs(Node1x - x0) < dMax) && (fabs(Node1y - y0) < dMax) && 
										(fabs(Node2x - x0) < dMax) && (fabs(Node2y - y0) < dMax))
									{
    									// compute square segment length
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
										if(dSquareDist <= MAXDIST*MAXDIST) {
											double dDist = sqrt(dSquareDist);
											// compute cos of angle between move vector and segment
											double dUTMX = UTMSpeed.GetCos();
											double dUTMY = UTMSpeed.GetSin();
											dCos = ((Node2x-Node1x)*dUTMX + (Node2y-Node1y)*dUTMY)/sqrt(SqSegLen);
											// calc fitness
											double dFactor = Max(0.0, 1-dDist/MAXDIST);  // = 0 when far away, 1 if near
											// check if we move forward on way
											bool oFwdNMove = (dCos >= 0);
											/// \todo take into account mode for oneways!
											switch(eOneway) {
												case e_Oneway_None:		dCos = fabs(dCos); break;	// no oneway
												case e_Oneway_Normal:	break;						// leave dCos how it is
												case e_Oneway_Inverse:	dCos = -dCos; break;		// invert since oneway is in the other direction
											}
											double dFitness = dFactor*dCos + (1-dFactor)*dFactor;
    										// check if new best fit
    										if(first || (dFitness > dMaxFitness)) {
												first = false;
    											// yes
    											dMaxFitness = dFitness;
    											pProxWay = pWay;
												PSProxx = PSx;
												PSProxy = PSy;
												oForward = oFwdNMove;
    										}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	CXExactTime StopTime;
	StopTime.SetNow();
	CXDebugInfo::Instance()->SetLocatorTime(StopTime-StartTime);

	bool Located = false;
    if(first || (dMaxFitness <= 0)) {
    	// nothing found or too far from a way.
    	Located = false;
    } else {
		Located = true;
	}

	if(Located && (pProxWay != NULL)) {
  		m_NaviData.SetLocated(true);
		UTMtoLL(WGS84, PSProxx, PSProxy, UTMZoneCurrent, UTMLetterCurrent, dLon, dLat);
		m_NaviData.SetLocatedCoor(CXCoor(dLon, dLat));
		/// \todo implement
		CXStringUTF8 Name;
		CXStringUTF8 Ref;
		CXStringUTF8 IntRef;
		unsigned char MaxSpeed = 0;
		Name = pProxWay->GetName();
		Ref = pProxWay->GetRef();
		IntRef = pProxWay->GetIntRef();
		if(oForward)
			MaxSpeed = pProxWay->GetMaxSpeedForward();
		else
			MaxSpeed = pProxWay->GetMaxSpeedBackward();
		m_NaviData.SetStreetName(Name);
		m_NaviData.SetRef(Ref);
		m_NaviData.SetIntRef(IntRef);
		m_NaviData.SetMaxSpeed(MaxSpeed);
	} else {
		m_NaviData.SetLocated(false);
		m_NaviData.SetStreetName("");
		m_NaviData.SetRef("");
		m_NaviData.SetIntRef("");
		m_NaviData.SetMaxSpeed(0);
	}

	// unlockmap sections
	for(idx=0; idx<MapSections.GetSize(); idx++) {
		if(LockedMapSections[idx]) {
			CXMapSection *pMapSection = MapSections[idx].GetPtr();
			// unlock
			pMapSection->Unlock();
		}
	}

}
