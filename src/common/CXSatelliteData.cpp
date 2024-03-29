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

#include "CXSatelliteData.hpp"
#include "Utils.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"
#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"
#include "CXPen.hpp"
#include "CoordConstants.h"


CXSatellitesData * CXSatellites::m_pInstance = NULL;


//----------------------------------------------------------------------------
//-------------------------------------
CXSatelliteInfo::CXSatelliteInfo() :
    m_PRN(0),
    m_Elevation(0),
    m_Azimuth(0),
    m_SNR(0)
{
}

//-------------------------------------
CXSatelliteInfo::CXSatelliteInfo(const CXSatelliteInfo &rOther) :
    m_PRN(0),
    m_Elevation(0),
    m_Azimuth(0),
    m_SNR(0)
{
    CopyFrom(rOther);
}

//-------------------------------------
CXSatelliteInfo::~CXSatelliteInfo() {
}

//-------------------------------------
const CXSatelliteInfo & CXSatelliteInfo::operator = (const CXSatelliteInfo &rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXSatelliteInfo::CopyFrom(const CXSatelliteInfo &rOther) {
    m_PRN       = rOther.m_PRN;
    m_Elevation = rOther.m_Elevation;
    m_Azimuth   = rOther.m_Azimuth;
    m_SNR       = rOther.m_SNR;
}

//-------------------------------------
int CXSatelliteInfo::GetPRN() const {
    return m_PRN;
}

//-------------------------------------
void CXSatelliteInfo::SetPRN(int NewValue) {
    m_PRN = NewValue;
}

//-------------------------------------
int CXSatelliteInfo::GetElevation() const {
    return m_Elevation;
}

//-------------------------------------
void CXSatelliteInfo::SetElevation(int NewValue) {
    m_Elevation = NewValue;
}

//-------------------------------------
int CXSatelliteInfo::GetAzimuth() const {
    return m_Azimuth;
}

//-------------------------------------
void CXSatelliteInfo::SetAzimuth(int NewValue) {
    m_Azimuth = NewValue;
}

//-------------------------------------
int CXSatelliteInfo::GetSNR() const {
    return m_SNR;
}

//-------------------------------------
void CXSatelliteInfo::SetSNR(int NewValue) {
    m_SNR = NewValue;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXSatellitesData::CXSatellitesData() :
    m_NrSat(0),
    m_HDOP(0),
    m_VDOP(0),
    m_oRMCDataReceived(false),
    m_oGGADataReceived(false),
    m_oGSADataReceived(false),
    m_oGSVDataReceived(false),
    m_oGPSDDataReceived(false),
    m_oHDOPReceived(false),
    m_oVDOPReceived(false)
{
}

//-------------------------------------
CXSatellitesData::CXSatellitesData(const CXSatellitesData &rOther) :
    m_NrSat(0),
    m_HDOP(0),
    m_VDOP(0),
    m_oRMCDataReceived(false),
    m_oGGADataReceived(false),
    m_oGSADataReceived(false),
    m_oGSVDataReceived(false),
    m_oGPSDDataReceived(false),
    m_oHDOPReceived(false),
    m_oVDOPReceived(false)
{
    CopyFrom(rOther);
}

//-------------------------------------
CXSatellitesData::~CXSatellitesData() {
    CXWriteLocker WL(&m_RWLock);
    ClearBuffer(m_SatInfo);
}

//-------------------------------------
const CXSatellitesData & CXSatellitesData::operator = (const CXSatellitesData &rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXSatellitesData::CopyFrom(const CXSatellitesData &rOther) {
    CXWriteLocker WL(&m_RWLock);
    CXReadLocker RL(&(rOther.m_RWLock));
    // clear data
    ClearBuffer(m_SatInfo);
    // copy data
    m_NrSat = rOther.m_NrSat;
    m_HDOP = rOther.m_HDOP;
    m_VDOP = rOther.m_VDOP;
    m_oRMCDataReceived = rOther.m_oRMCDataReceived;
    m_oGGADataReceived = rOther.m_oGGADataReceived;
    m_oGSADataReceived = rOther.m_oGSADataReceived;
    m_oGSVDataReceived = rOther.m_oGSVDataReceived;
    m_oGPSDDataReceived = rOther.m_oGPSDDataReceived;
    m_oHDOPReceived = rOther.m_oHDOPReceived;
    m_oVDOPReceived = rOther.m_oVDOPReceived;
    // copy buffers
    m_ActiveSatellites = rOther.m_ActiveSatellites;
    for(size_t i=0; i<rOther.m_SatInfo.GetSize(); i++)
        m_SatInfo.Append(new CXSatelliteInfo(*rOther.m_SatInfo[i]));
}

//-------------------------------------
void CXSatellitesData::ClearBuffer(CXBuffer<CXSatelliteInfo *> & rBuffer) {
    for(size_t i=0; i<rBuffer.GetSize(); i++)
        delete rBuffer[i];
    rBuffer.Clear();
}

//-------------------------------------
void CXSatellitesData::SetGGADataReceived() {
    CXWriteLocker WL(&m_RWLock);
    m_oGGADataReceived = true;
}

//-------------------------------------
void CXSatellitesData::SetRMCDataReceived() {
    CXWriteLocker WL(&m_RWLock);
    m_oRMCDataReceived = true;
}

//-------------------------------------
void CXSatellitesData::SetGSADataReceived() {
    CXWriteLocker WL(&m_RWLock);
    m_oGSADataReceived = true;
}

//-------------------------------------
void CXSatellitesData::SetGSVDataReceived() {
    CXWriteLocker WL(&m_RWLock);
    m_oGSVDataReceived = true;
}

//-------------------------------------
void CXSatellitesData::SetGPSDDataReceived() {
    CXWriteLocker WL(&m_RWLock);
    m_oGPSDDataReceived = true;
}

//-------------------------------------
void CXSatellitesData::SetNrSatGGA(int NrSatGGA) {
    CXWriteLocker WL(&m_RWLock);
    m_NrSat = NrSatGGA;
}

//-------------------------------------
int CXSatellitesData::GetNrSat() const {
    CXReadLocker RL(&m_RWLock);
    return m_NrSat;
}

//-------------------------------------
void CXSatellitesData::SetActiveSatellites(const CXBuffer<int> &ActiveSatellites) {
    CXWriteLocker WL(&m_RWLock);
    m_ActiveSatellites = ActiveSatellites;
    // set nr satellites
    m_NrSat = m_ActiveSatellites.GetSize();
}

//-------------------------------------
void CXSatellitesData::SetSatelliteInfos(const CXBuffer<CXSatelliteInfo *>SatInfos) {
    CXWriteLocker WL(&m_RWLock);
    ClearBuffer(m_SatInfo);
    for(size_t i=0; i<SatInfos.GetSize(); i++)
        m_SatInfo.Append(new CXSatelliteInfo(*SatInfos[i]));
}

//-------------------------------------
double CXSatellitesData::GetHDOP() const {
    CXReadLocker RL(&m_RWLock);
    return m_HDOP;
}

//-------------------------------------
void CXSatellitesData::SetHDOP(double NewValue) {
    CXWriteLocker WL(&m_RWLock);
    m_HDOP = NewValue;
    m_oHDOPReceived = true;
}

//-------------------------------------
double CXSatellitesData::GetVDOP() const {
    CXReadLocker RL(&m_RWLock);
    return m_VDOP;
}

//-------------------------------------
void CXSatellitesData::SetVDOP(double NewValue) {
    CXWriteLocker WL(&m_RWLock);
    m_VDOP = NewValue;
    m_oVDOPReceived = true;
}

//-------------------------------------
const CXBuffer<int> &CXSatellitesData::GetActiveSatellites() const {
    return m_ActiveSatellites;
}

//-------------------------------------
const CXBuffer<CXSatelliteInfo *> &CXSatellitesData::SatInfo() const {
    return m_SatInfo;
}

//-------------------------------------
bool CXSatellitesData::WasRMCDataReceived() const {
    CXWriteLocker WL(&m_RWLock);
    return m_oRMCDataReceived;
}

//-------------------------------------
bool CXSatellitesData::WasGGADataReceived() const {
    CXWriteLocker WL(&m_RWLock);
    return m_oGGADataReceived;
}

//-------------------------------------
bool CXSatellitesData::WasGSADataReceived() const {
    CXWriteLocker WL(&m_RWLock);
    return m_oGSADataReceived;
}

//-------------------------------------
bool CXSatellitesData::WasGSVDataReceived() const {
    CXWriteLocker WL(&m_RWLock);
    return m_oGSVDataReceived;
}

//-------------------------------------
bool CXSatellitesData::WasGPSDDataReceived() const {
    CXWriteLocker WL(&m_RWLock);
    return m_oGPSDDataReceived;
}

//-------------------------------------
bool CXSatellitesData::WasHDOPReceived() const {
    CXWriteLocker WL(&m_RWLock);
    return m_oHDOPReceived;
}

//-------------------------------------
bool CXSatellitesData::WasVDOPReceived() const {
    return m_oVDOPReceived;
}


//----------------------------------------------------------------------------
//-------------------------------------
CXSatellites::CXSatellites() {
}

//-------------------------------------
CXSatellites::~CXSatellites() {
}

//-------------------------------------
CXSatellitesData *CXSatellites::Instance() {
    if(m_pInstance == NULL)
        m_pInstance = new CXSatellitesData();
    return m_pInstance;
}

//-------------------------------------
void CXSatellites::Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY, int Width, int Height) {
    // make a copy of sat data
    CXSatellitesData SatData = *Instance();

    CXRGB LineColor(0xFF, 0xFF, 0xFF);
    CXRGB BgColor(0x00,0x00,0x00);
    CXRGB SatBgColor(0x60,0x60,0x60);
    CXRGB SatActiveColor(0x00,0xFF,0x00);
    CXRGB SatInactiveColor(0xFF,0x00,0x00);
    CXRGB OrientationColor(0xFF, 0xFF, 0x00);
    CXRGB TelegramReceivedColor(0x00, 0xFF, 0x00);
    CXRGB TelegramNotReceivedColor(0xFF, 0x00, 0x00);

    // create bitmap
    CXBitmap Bmp;
    tIRect rect(0, 0, Width, Height);
    if(!Bmp.Create(pDC, rect.GetWidth(), rect.GetHeight())) {
        return;
    }
    Bmp.DrawRect(rect, BgColor, BgColor);

    // draw satellites
    const int SatBarHeight = 42;
    const int Margin = 7;
    const int dx = 5;
    const int SatRadius = 6;

    // draw "sky"
    int Radius = Max(10, Min(Width, (Height - SatBarHeight))/2 - Margin);
    int CX = Width / 2;
    int CY = Margin + Radius;
    CXPen Pen(CXPen::e_Solid, 1, LineColor);
    Bmp.SetPen(Pen);
    // circles
    Bmp.DrawCircle(CX, CY, Radius, LineColor, BgColor);
    Bmp.DrawCircle(CX, CY, 5*Radius/6, LineColor, BgColor);
    Bmp.DrawCircle(CX, CY, 4*Radius/6, LineColor, BgColor);
    Bmp.DrawCircle(CX, CY, 3*Radius/6, LineColor, BgColor);
    Bmp.DrawCircle(CX, CY, 2*Radius/6, LineColor, BgColor);
    Bmp.DrawCircle(CX, CY, 1*Radius/6, LineColor, BgColor);
    // lines
    Bmp.DrawLine(CX, CY + Radius, CX, CY - Radius);
    Bmp.DrawLine(CX - Radius, CY, CX + Radius, CY);
    // numbers
    // "45"
    CXStringUTF8 Str("45");
    Str.Append(DegUTF8, sizeof(DegUTF8));
    tIRect StrRect = Bmp.CalcTextRectUTF8(Str, 4, 2);
    StrRect.OffsetRect(CX + 3*Radius/6 - StrRect.GetWidth()/2, CY - StrRect.GetHeight()/2);
    Bmp.DrawTextUTF8(Str, StrRect, OrientationColor, BgColor);
    // "N"
    Str = "N";
    StrRect = Bmp.CalcTextRectUTF8(Str, 4, 2);
    StrRect.OffsetRect(CX - StrRect.GetWidth()/2, CY - Radius - StrRect.GetHeight()/2);
    Bmp.DrawRect(StrRect, BgColor, BgColor);
    Bmp.DrawTextUTF8(Str, StrRect, OrientationColor, BgColor);
    // "E"
    Str = "E";
    StrRect = Bmp.CalcTextRectUTF8(Str, 4, 2);
    StrRect.OffsetRect(CX + Radius - StrRect.GetWidth()/2, CY - StrRect.GetHeight()/2);
    Bmp.DrawRect(StrRect, BgColor, BgColor);
    Bmp.DrawTextUTF8(Str, StrRect, OrientationColor, BgColor);
    // "S"
    Str = "S";
    StrRect = Bmp.CalcTextRectUTF8(Str, 4, 2);
    StrRect.OffsetRect(CX - StrRect.GetWidth()/2, CY + Radius - StrRect.GetHeight()/2);
    Bmp.DrawRect(StrRect, BgColor, BgColor);
    Bmp.DrawTextUTF8(Str, StrRect, OrientationColor, BgColor);
    // "W"
    Str = "W";
    StrRect = Bmp.CalcTextRectUTF8(Str, 4, 2);
    StrRect.OffsetRect(CX - Radius - StrRect.GetWidth()/2, CY - StrRect.GetHeight()/2 );
    Bmp.DrawRect(StrRect, BgColor, BgColor);
    Bmp.DrawTextUTF8(Str, StrRect, OrientationColor, BgColor);

    // now draw satellites
    const CXBuffer<CXSatelliteInfo *> &SatInfo = SatData.SatInfo();
    const CXBuffer<int> &ActiveSatellites = SatData.GetActiveSatellites();
    size_t SatCount = SatInfo.GetSize();
    if(SatCount != 0) {
        // compute width for one satellite
        int SatWidth = (Width - 2*Margin - (SatCount - 1)*dx) / SatCount;
        // compute starting position left
        int X0 = (Width - (SatCount - 1)*dx - SatCount*SatWidth)/2;
        int x = X0;
        for(size_t i=0; i<SatCount; i++) {
            tIRect SatBgRect(0, 0, SatWidth, SatBarHeight);
            SatBgRect.OffsetRect(x, Height - SatBarHeight);
            // draw background
            Bmp.DrawRect(SatBgRect, SatBgColor, SatBgColor);
            // get satellite name
            CXSatelliteInfo *pSatInfo = SatInfo[i];
            int PRN = pSatInfo->GetPRN();
            CXStringASCII PRNString = IToA<CXStringASCII>(PRN);
            // check if satellite is active
            bool Active = false;
            for(size_t j=0; j<ActiveSatellites.GetSize(); j++) {
                if(PRN == ActiveSatellites[j]) {
                    Active = true;
                    break;
                }
            }
            // set color
            CXRGB SatColor = SatInactiveColor;
            if(Active) {
                SatColor = SatActiveColor;
            }
            // draw sat bar background
            tIRect SatRect(SatBgRect);
            // draw sat bar fg
            SatRect.SetTop(SatBgRect.GetBottom() - pSatInfo->GetSNR()*SatBgRect.GetHeight()/100);
            Bmp.DrawRect(SatRect, SatColor, SatColor);
            // draw sat bar name
            tIRect SatNameRect = Bmp.CalcTextRectASCII(PRNString, 2, 2);
            tIRect Dest = SatNameRect;
            Dest.OffsetRect(SatRect.GetLeft() + SatRect.GetWidth()/2 - Dest.GetWidth()/2,
                            SatBgRect.GetTop());
            Bmp.DrawTextASCII(PRNString, Dest, LineColor, SatBgColor);
            // draw satellite
            double alpha = (90 - pSatInfo->GetAzimuth())*deg2rad;
            double r = (1 - pSatInfo->GetElevation()/90.0)*Radius;
            int XSat = static_cast<int>(CX + r*cos(alpha));
            int YSat = static_cast<int>(CY - r*sin(alpha));
            Bmp.DrawCircle(XSat, YSat, SatRadius, SatColor, SatColor);
            // draw satellite name
            Dest = SatNameRect;
            Dest.OffsetRect(XSat - SatNameRect.GetWidth() / 2, YSat + SatRadius + 2);
            Bmp.DrawTextASCII(PRNString, Dest, SatColor, BgColor);
            x += dx;
            x += SatWidth;
        }
    }

    tIRect RMCRect = Bmp.CalcTextRectUTF8("GPRMC", 2, 2);
    tIRect GGARect = Bmp.CalcTextRectUTF8("GPGGA", 2, 2);
    tIRect GSARect = Bmp.CalcTextRectUTF8("GPGSA", 2, 2);
    tIRect GSVRect = Bmp.CalcTextRectUTF8("GPGSV", 2, 2);
    tIRect GPSDRect = Bmp.CalcTextRectUTF8("GPSD", 2, 2);
    CXStringASCII HDOPStr = CXStringASCII("HDOP: ") +
                            FToA<CXStringASCII>(SatData.GetHDOP(), 1, 2);
    tIRect HDOPRect = Bmp.CalcTextRectASCII(HDOPStr, 2, 2);
    CXStringASCII VDOPStr = CXStringASCII("VDOP: ") +
                            FToA<CXStringASCII>(SatData.GetVDOP(), 1, 2);
    tIRect VDOPRect = Bmp.CalcTextRectASCII(VDOPStr, 2, 2);
    int DOPWidth = Max(HDOPRect.GetWidth(), VDOPRect.GetWidth());
    // move rectangles
    GGARect.OffsetRect(0, RMCRect.GetHeight());
    GSARect.OffsetRect(0, RMCRect.GetHeight() + GGARect.GetHeight());
    GSVRect.OffsetRect(0, RMCRect.GetHeight() + GGARect.GetHeight() + GSARect.GetHeight());
    GPSDRect.OffsetRect(0, RMCRect.GetHeight() + GGARect.GetHeight() + GSARect.GetHeight() + GSVRect.GetHeight());
    HDOPRect.OffsetRect(Width - DOPWidth, 0);
    VDOPRect.OffsetRect(Width - DOPWidth, HDOPRect.GetHeight());
    CXRGB TextColor = TelegramNotReceivedColor;

    if(SatData.WasRMCDataReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII("GPRMC", RMCRect, TextColor, BgColor);
    if(SatData.WasGGADataReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII("GPGGA", GGARect, TextColor, BgColor);

    if(SatData.WasGSADataReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII("GPGSA", GSARect, TextColor, BgColor);

    if(SatData.WasGSVDataReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII("GPGSV", GSVRect, TextColor, BgColor);

    if(SatData.WasGPSDDataReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII("GPSD", GPSDRect, TextColor, BgColor);

    if(SatData.WasHDOPReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII(HDOPStr, HDOPRect, TextColor, BgColor);
    if(SatData.WasVDOPReceived()) {
        TextColor = TelegramReceivedColor;
    } else {
        TextColor = TelegramNotReceivedColor;
    }
    // draw
    Bmp.DrawTextASCII(VDOPStr, VDOPRect, TextColor, BgColor);
    pDC->Draw(&Bmp, OffsetX, OffsetY);
}

