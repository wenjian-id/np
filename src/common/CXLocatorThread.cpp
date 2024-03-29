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
#include "CXNaviPOWM.hpp"
#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "CXSatelliteData.hpp"
#include "CXDebugInfo.hpp"
#include "CXTrackLog.hpp"

const int TIMEOUT_RECEIVE = 5; // seconds
static const int SQUARE_MIN_SEGMENTSIZE = 25; // 5*5m
static const double MAXDIST = 50; // 50m
static const char * pcLastCoorFileName = "last.gps";


//---------------------------------------------------------------------
//-------------------------------------
CXLocatorThread::CXLocatorThread() :
    m_oGPSConnected(false),
    m_oNewGPSConnection(false),
    m_oNewGPSPosInfo(false),
    m_oNewGPSCourseInfo(false),
    m_oNewGPSQualityInfo(false),
    m_SpeedCalculator(4),
    m_oGPSFixAtLeastOnce(false),
    m_oStartCoordinatesValid(false),
    m_pNaviPOWM(NULL)
{
    // try to load last received coordinates
    LoadStartGPSCoordinates();
}

//-------------------------------------
CXLocatorThread::~CXLocatorThread() {
    m_pNaviPOWM = NULL;
}

//-------------------------------------
bool CXLocatorThread::IsGPSConnected() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_oGPSConnected;
}

//-------------------------------------
void CXLocatorThread::SetGPSConnected(bool NewValue) {
    CXMutexLocker L(&m_MutexInputData);
    m_oGPSConnected = NewValue;
    SetFlag_NewGPSConnection(true);
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewGPSConnection(bool NewValue) {
    CXMutexLocker L(&m_MutexInputData);
    m_oNewGPSConnection = NewValue;
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewGPSPosInfo(bool NewValue) {
    // synchronisation must be done in caling method
    m_oNewGPSPosInfo = NewValue;
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewGPSCourseInfo(bool NewValue) {
    // synchronisation must be done in caling method
    m_oNewGPSCourseInfo = NewValue;
}

//-------------------------------------
void CXLocatorThread::SetFlag_NewGPSQualityInfo(bool NewValue) {
    // synchronisation must be done in caling method
    m_oNewGPSQualityInfo = NewValue;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewGPSConnection() const {
    // synchronisation must be done in caling method
    return m_oNewGPSConnection;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewGPSPosInfo() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_oNewGPSPosInfo;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewGPSCourseInfo() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_oNewGPSCourseInfo;
}

//-------------------------------------
bool CXLocatorThread::GetFlag_NewGPSQualityInfo() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_oNewGPSQualityInfo;
}

//-------------------------------------
void CXLocatorThread::SetGPSPosInfo(const tTimeStampedGPSPosInfo &PosInfo) {
    CXMutexLocker L(&m_MutexInputData);
    // take data
    m_GPSPosInfo = PosInfo;
    SetFlag_NewGPSPosInfo(true);
}

//-------------------------------------
void CXLocatorThread::SetGPSCourseInfo(const tTimeStampedGPSCourseInfo &CourseInfo) {
    CXMutexLocker L(&m_MutexInputData);
    // take data
    m_GPSCourseInfo = CourseInfo;
    SetFlag_NewGPSCourseInfo(true);
}

//-------------------------------------
void CXLocatorThread::SetGPSQualityInfo(const tTimeStampedGPSQualityInfo &QualityInfo) {
    CXMutexLocker L(&m_MutexInputData);
    m_GPSQualityInfo = QualityInfo;
    SetFlag_NewGPSQualityInfo(true);
}

//-------------------------------------
tTimeStampedGPSPosInfo CXLocatorThread::GetGPSPosInfo() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_GPSPosInfo;
}

//-------------------------------------
tTimeStampedGPSCourseInfo CXLocatorThread::GetGPSCourseInfo() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_GPSCourseInfo;
}

//-------------------------------------
tTimeStampedGPSQualityInfo CXLocatorThread::GetGPSQualityInfo() const {
    CXMutexLocker L(&m_MutexInputData);
    return m_GPSQualityInfo;
}

//-------------------------------------
void CXLocatorThread::SetNaviPOWM(CXNaviPOWM *pNaviPOWM) {
    CXMutexLocker L(&m_Mutex);
    m_pNaviPOWM = pNaviPOWM;
}

//-------------------------------------
void CXLocatorThread::OnThreadStarted() {
    // nothing to do
}

//-------------------------------------
void CXLocatorThread::OnThreadLoop() {
    // check if new data arriwed
    CXExactTime Now;
    bool NewGPSConnection = GetFlag_NewGPSConnection();
    bool NewGPSPosInfo = GetFlag_NewGPSPosInfo();
    bool NewGPSCourseInfo = GetFlag_NewGPSCourseInfo();
    bool NewGPSQualityInfo = GetFlag_NewGPSQualityInfo();
    bool oHasFix = false;
    bool oNewDataNoFix = false;
    SetFlag_NewGPSConnection(false);
    // set connection status in m_NaviData
    m_NaviData.SetConnected(IsGPSConnected());

    if(NewGPSPosInfo) {
        // process it
        // reset flag
        SetFlag_NewGPSPosInfo(false);
        tTimeStampedGPSPosInfo PosInfo = GetGPSPosInfo();
        // set UTC
        m_NaviData.SetUTC(PosInfo.Data().GetUTC());
        oHasFix = PosInfo.Data().HasFix();
        m_LastReceivedPosition.SetNow();
        // set number of satellites
        CXSatellites::Instance()->SetNrSatGGA(PosInfo.Data().GetNSat());
        // check fix
        if(oHasFix) {
            m_oGPSFixAtLeastOnce = true;
            // extract data
            double dLon = PosInfo.Data().GetLon();
            double dLat = PosInfo.Data().GetLat();
            // remember coordinates
            m_LastReceivedCoor = CXCoor(dLon, dLat);
            // set height
            m_NaviData.SetHeight(PosInfo.Data().GetHeight());
            // set data in speed calculator
            m_SpeedCalculator.SetGGAData(PosInfo.Data().GetUTC(), CXTimeStampData<CXCoor>(m_LastReceivedCoor, PosInfo.TimeStamp()));
        } else {
            oNewDataNoFix = true;
        }
    }
    // process new data
    if(NewGPSCourseInfo) {
        // process new course info
        // reset flag
        SetFlag_NewGPSCourseInfo(false);
        tTimeStampedGPSCourseInfo GPSCourseInfo = GetGPSCourseInfo();
        if(GPSCourseInfo.Data().HasFix()) {
            // set data in speed calculator
            m_SpeedCalculator.SetRMCData(GPSCourseInfo.Data().GetUTC(), CXTimeStampData<CXCoor>(m_LastReceivedCoor, GPSCourseInfo.TimeStamp()), GPSCourseInfo.Data().GetSpeed());
        }
    }
    bool oNewDataArrived = m_SpeedCalculator.NewDataArrived() || oNewDataNoFix || NewGPSConnection;

    if(oNewDataArrived) {
        // set speed thresholds for speed calculator
        switch(CXOptions::Instance()->GetMode()) {
            case CXOptions::e_ModeCar:          m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdCar()); break;
            case CXOptions::e_ModeBike:         m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdBike()); break;
            case CXOptions::e_ModePedestrian:   m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdPedestrian()); break;
            case CXOptions::e_ModeCaching:      m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdCaching()); break;
            case CXOptions::e_ModeMapping:      m_SpeedCalculator.SetSpeedThreshold(CXOptions::Instance()->GetSpeedThresholdMapping()); break;
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
                    m_NaviData.SetCorrectedGPSCoor(m_StartCoordinates);
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
        double dE = 1.0*Lag/1000.0*UTMSpeed.GetSpeed()*UTMSpeed.GetDirection().GetCos();
        double dN = 1.0*Lag/1000.0*UTMSpeed.GetSpeed()*UTMSpeed.GetDirection().GetSin();
        CorrectedGPSCoor.OffsetCoor(dE, dN);
        m_NaviData.SetCorrectedGPSCoor(CorrectedGPSCoor);
    } else {
        // no data arrived
        unsigned long Delta = Now - m_LastReceivedPosition;
        if(Delta > 1000*TIMEOUT_RECEIVE) {
            // if still connected reset number of satellites to zero. maybe we are in a tunnel or so.
            // if not connected, do not reset number of satellites
            if(IsGPSConnected()) {
                CXSatellites::Instance()->SetNrSatGGA(0);
            }
            if(m_pNaviPOWM != NULL)
                m_pNaviPOWM->RequestRepaint(CXNaviPOWM::e_ModeMap);
        }
    }
    bool oUpdateSatInfo = false;
    if(NewGPSQualityInfo) {
        oUpdateSatInfo = true;
        // reset flag
        SetFlag_NewGPSQualityInfo(false);
        // new satellite info received
        tTimeStampedGPSQualityInfo QualityInfo = GetGPSQualityInfo();
        CXSatellites::Instance()->SetHDOP(QualityInfo.Data().GetHDOP());
        CXSatellites::Instance()->SetVDOP(QualityInfo.Data().GetVDOP());
    }
    if(oUpdateSatInfo) {
        if(m_pNaviPOWM != NULL)
            m_pNaviPOWM->RequestRepaint(CXNaviPOWM::e_ModeSatInfo);
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
            CXCoor Coor = m_NaviData.GetGPSCoor();
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
            if(!WriteUI32(OutFile, ulLon)) {
                return;
            }
            if(!WriteUI32(OutFile, ulLat)) {
                return;
            }
        } else {
            // open error
        }
    }
}

//-------------------------------------
void CXLocatorThread::LoadStartGPSCoordinates() {
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
}


//-------------------------------------
void CXLocatorThread::Locate() {

    CXUTMSpeed UTMSpeed = m_NaviData.GetUTMSpeed();
    // initialize LocatedCoor
    m_NaviData.SetLocatedCoor(m_NaviData.GetCorrectedGPSCoor());

    if(CXPOWMMap::Instance() == NULL)
        return;

    // A segment defined by two nodes Node1(Node1x, Node1y) and Node2(Node2x, Node2y)
    // The received coordinate is defined by P(X0, Y0).
    // The nearest point to P(X0,Y0) lying on the segment PS(PSx, PSy)

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
    double SqSegLen = 0;        // square length of segment
    double dSquareDist = 0;     // distance from X0,Y0 to segment

    double dLon = m_NaviData.GetCorrectedGPSCoor().GetLon();
    double dLat = m_NaviData.GetCorrectedGPSCoor().GetLat();
    double dLonMin = dLon - 0.01;
    double dLonMax = dLon + 0.01;
    double dLatMin = dLat - 0.01;
    double dLatMax = dLat + 0.01;

    // compute UTM coordinates
    char UTMLetterCurrent = 0;
    double X0 = 0;
    double Y0 = 0;
    int UTMZoneCurrent = UTMZoneNone;
    LLtoUTM(WGS84, dLon, dLat, UTMZoneNone, UTMZoneCurrent, UTMLetterCurrent, X0, Y0);

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
        for(size_t idx1=0; idx1<MapSectionSize; idx1++) {
            if(LockedMapSections[idx1]) {
                CXMapSection *pMapSection = MapSections[idx1].GetPtr();
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
                                    oUseWay =   (Type == e_Way_Motorway) ||
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
                                    /// todo implement
                                    oUseWay =   (Type == e_Way_Motorway) ||
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
                                    if( (fabs(Node1x - X0) < dMax) && (fabs(Node1y - Y0) < dMax) &&
                                        (fabs(Node2x - X0) < dMax) && (fabs(Node2y - Y0) < dMax))
                                    {
                                        // compute square segment length
                                        SqSegLen = (Node2x-Node1x)*(Node2x-Node1x)+(Node2y-Node1y)*(Node2y-Node1y);
                                        // only compute segments with at least SQUARE_MIN_SEGMENTSIZE length
                                        if(SqSegLen > SQUARE_MIN_SEGMENTSIZE) {
                                            // compute factor (Node1->PS)/SegLen = PS.Segment/(SegLen*SegLen)
                                            double dFactor = ((X0-Node1x)*(Node2x-Node1x)+(Y0-Node1y)*(Node2y-Node1y))/SqSegLen;
                                            if(dFactor<0) {
                                                // projection of P on segment lies before Node1 so take Node1
                                                PSx = Node1x;
                                                PSy = Node1y;
                                            } else if (dFactor>1) {
                                                // projection of P on segment lies after Node2 so take Node2
                                                PSx = Node2x;
                                                PSy = Node2y;
                                            } else {
                                                // projection of P on segment lies between Node1 and Node2
                                                PSx = Node1x + dFactor*(Node2x-Node1x);
                                                PSy = Node1y + dFactor*(Node2y-Node1y);
                                            }
                                        } else {
                                            // segment too short, so we take Node1
                                            PSx = Node1x;
                                            PSy = Node1y;
                                        }
                                        // compute square distance between P and PS
                                        dSquareDist = (X0-PSx)*(X0-PSx) + (Y0-PSy)*(Y0-PSy);
                                        if(dSquareDist <= MAXDIST*MAXDIST) {
                                            double dDist = sqrt(dSquareDist);
                                            // compute cos of angle between move vector and segment
                                            double dUTMX = UTMSpeed.GetDirection().GetCos();
                                            double dUTMY = UTMSpeed.GetDirection().GetSin();
                                            // compute cosinus of angle between vector Node1->P and Node1->Node2
                                            double dCos = 0;
                                            dCos = ((Node2x-Node1x)*dUTMX + (Node2y-Node1y)*dUTMY)/sqrt(SqSegLen);
                                            // calc fitness
                                            double dFactor = Max(0.0, 1-dDist/MAXDIST);  // = 0 when far away, 1 if near
                                            // check if we move forward on way
                                            bool oFwdNMove = (dCos >= 0);
                                            // take into account mode for oneways
                                            switch(eOneway) {
                                                case e_Oneway_None:     dCos = fabs(dCos); break;   // no oneway
                                                case e_Oneway_Normal:   break;                      // leave dCos how it is
                                                case e_Oneway_Inverse:  dCos = -dCos; break;        // invert since oneway is in the other direction
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
