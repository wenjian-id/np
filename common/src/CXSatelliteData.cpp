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
#include "math.h"


CXSatelliteData * CXSatelliteData::m_pInstance = NULL;


//----------------------------------------------------------------------------
//-------------------------------------
CXSatelliteData::CXSatelliteData() :
	m_NrSat(0),
	m_LastReceivedGSVTel(0),
	m_TmpNrSat(0),
	m_HDOP(0),
	m_VDOP(0),
	m_oRMCDataReceived(false),
	m_oGGADataReceived(false),
	m_oGSADataReceived(false),
	m_oGSVDataReceived(false),
	m_oHDOPReceived(false),
	m_oVDOPReceived(false)
{
}

//-------------------------------------
CXSatelliteData::~CXSatelliteData() {
	CXWriteLocker WL(&m_RWLock);
	ClearBuffer(m_SatInfo);
	ClearBuffer(m_TmpSatInfo);
}

//-------------------------------------
CXSatelliteData *CXSatelliteData::Instance() {
	if(m_pInstance == NULL)
		m_pInstance = new CXSatelliteData();
	return m_pInstance;
}

//-------------------------------------
void CXSatelliteData::ClearBuffer(CXBuffer<CXGSVSatelliteInfo *> & rBuffer) {
	for(size_t i=0; i<rBuffer.GetSize(); i++)
		delete rBuffer[i];
	rBuffer.Clear();
}

//-------------------------------------
void CXSatelliteData::SetRMCReceived() {
	CXWriteLocker WL(&m_RWLock);
	m_oRMCDataReceived = true;
}

//-------------------------------------
void CXSatelliteData::SetNrSatGGA(int NrSatGGA) {
	CXWriteLocker WL(&m_RWLock);
	m_NrSat = NrSatGGA;
	m_oGGADataReceived = true;
}

//-------------------------------------
int CXSatelliteData::GetNrSat() const {
	CXReadLocker RL(&m_RWLock);
	return m_NrSat;
}

//-------------------------------------
void CXSatelliteData::SetActiveSatellites(const CXBuffer<int> &ActiveSatellites) {
	CXWriteLocker WL(&m_RWLock);
	m_ActiveSatellites = ActiveSatellites;
	// set nr satellites
	m_NrSat = m_ActiveSatellites.GetSize();
	m_oGSADataReceived = true;
}

//-------------------------------------
void CXSatelliteData::SetGSVData(	int NTelegrams, int NCurrentTelegram, int NSat, int NInfos, 
									const CXGSVSatelliteInfo &Info1, const CXGSVSatelliteInfo &Info2,
									const CXGSVSatelliteInfo &Info3, const CXGSVSatelliteInfo &Info4)
{
	CXWriteLocker WL(&m_RWLock);
	m_oGSVDataReceived = true;
	// check if we are in sync
	if(NCurrentTelegram != m_LastReceivedGSVTel+1) {
		// not in sync. reset and discard
		ClearBuffer(m_TmpSatInfo);
		m_LastReceivedGSVTel = 0;
		return;
	}
	if((m_TmpNrSat != 0) && (m_TmpNrSat != NSat)) {
		// not in sync? reset and discard
		ClearBuffer(m_TmpSatInfo);
		m_LastReceivedGSVTel = 0;
		return;
	}

	// OK. Probably in sync
	m_TmpNrSat = NSat;
	// append received data
	if(NInfos >= 1)
		m_TmpSatInfo.Append(new CXGSVSatelliteInfo(Info1));
	if(NInfos >= 2)
		m_TmpSatInfo.Append(new CXGSVSatelliteInfo(Info2));
	if(NInfos >= 3)
		m_TmpSatInfo.Append(new CXGSVSatelliteInfo(Info3));
	if(NInfos >= 4)
		m_TmpSatInfo.Append(new CXGSVSatelliteInfo(Info4));
	if(NTelegrams == NCurrentTelegram) {
		// this was the last telegram
		// transfer data from m_TmpSatInfo to m_SatInfo
		ClearBuffer(m_SatInfo);
		for(size_t i=0; i<m_TmpSatInfo.GetSize(); i++)
			m_SatInfo.Append(m_TmpSatInfo[i]);
		m_TmpSatInfo.Clear();
		// reset m_LastReceivedGSVTel and m_TmpNrSat
		m_LastReceivedGSVTel = 0;
		m_TmpNrSat = 0;
	} else {
		// other telegrams to follow
		m_LastReceivedGSVTel = NCurrentTelegram;
	}
}

//-------------------------------------
void CXSatelliteData::SetHDOP(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_HDOP = NewValue;
	m_oHDOPReceived = true;
}

//-------------------------------------
void CXSatelliteData::SetVDOP(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_VDOP = NewValue;
	m_oVDOPReceived = true;
}

//-------------------------------------
void CXSatelliteData::Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY, int Width, int Height) {
	CXReadLocker RL(&m_RWLock);

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
	Bmp.Create(pDC, rect.GetWidth(), rect.GetHeight());
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
	size_t SatCount = m_SatInfo.GetSize();
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
			CXGSVSatelliteInfo *pSatInfo = m_SatInfo[i];
			int PRN = pSatInfo->GetPRN();
			char buf[10];
			snprintf(buf, sizeof(buf), "%d", PRN);
			// check if satellite is active
			bool Active = false;
			for(size_t j=0; j<m_ActiveSatellites.GetSize(); j++) {
				if(PRN == m_ActiveSatellites[j]) {
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
			tIRect SatNameRect = Bmp.CalcTextRectASCII(buf, 2, 2);
			tIRect Dest = SatNameRect;
			Dest.OffsetRect(SatRect.GetLeft() + SatRect.GetWidth()/2 - Dest.GetWidth()/2,
							SatBgRect.GetTop());
			Bmp.DrawTextASCII(buf, Dest, LineColor, SatBgColor);
			// draw satellite
			double alpha = (90 - pSatInfo->GetAzimuth())*deg2rad;
			double r = (1 - pSatInfo->GetElevation()/90.0)*Radius;
			int XSat = static_cast<int>(CX + r*cos(alpha));
			int YSat = static_cast<int>(CY - r*sin(alpha));
			Bmp.DrawCircle(XSat, YSat, SatRadius, SatColor, SatColor);
			// draw satellite name
			Dest = SatNameRect;
			Dest.OffsetRect(XSat - SatNameRect.GetWidth() / 2, YSat + SatRadius + 2);
			Bmp.DrawTextASCII(buf, Dest, SatColor, BgColor);
			x += dx;
			x += SatWidth;
		}
	}

	tIRect RMCRect = Bmp.CalcTextRectUTF8("GPRMC", 2, 2);
	tIRect GGARect = Bmp.CalcTextRectUTF8("GPGGA", 2, 2);
	tIRect GSARect = Bmp.CalcTextRectUTF8("GPGSA", 2, 2);
	tIRect GSVRect = Bmp.CalcTextRectUTF8("GPGSV", 2, 2);
	char HDOPbuf[25];
	snprintf(HDOPbuf, sizeof(HDOPbuf), "HDOP: %0.2f", m_HDOP);
	tIRect HDOPRect = Bmp.CalcTextRectASCII(HDOPbuf, 2, 2);
	char VDOPbuf[25];
	snprintf(VDOPbuf, sizeof(VDOPbuf), "VDOP: %0.2f", m_VDOP);
	tIRect VDOPRect = Bmp.CalcTextRectASCII(VDOPbuf, 2, 2);
	int DOPWidth = Max(HDOPRect.GetWidth(), VDOPRect.GetWidth());
	// move rectangles
	GGARect.OffsetRect(0, RMCRect.GetHeight());
	GSARect.OffsetRect(0, RMCRect.GetHeight() + GGARect.GetHeight());
	GSVRect.OffsetRect(0, RMCRect.GetHeight() + GGARect.GetHeight() + GSARect.GetHeight());
	HDOPRect.OffsetRect(Width - DOPWidth, 0);
	VDOPRect.OffsetRect(Width - DOPWidth, HDOPRect.GetHeight());
	CXRGB TextColor = TelegramNotReceivedColor;

	if(m_oRMCDataReceived) {
		TextColor = TelegramReceivedColor;
	} else {
		TextColor = TelegramNotReceivedColor;
	}
	// draw
	Bmp.DrawTextUTF8("GPRMC", RMCRect, TextColor, BgColor);
	if(m_oGGADataReceived) {
		TextColor = TelegramReceivedColor;
	} else {
		TextColor = TelegramNotReceivedColor;
	}
	// draw
	Bmp.DrawTextUTF8("GPGGA", GGARect, TextColor, BgColor);

	if(m_oGSADataReceived) {
		TextColor = TelegramReceivedColor;
	} else {
		TextColor = TelegramNotReceivedColor;
	}
	// draw
	Bmp.DrawTextUTF8("GPGSA", GSARect, TextColor, BgColor);

	if(m_oGSVDataReceived) {
		TextColor = TelegramReceivedColor;
	} else {
		TextColor = TelegramNotReceivedColor;
	}
	// draw
	Bmp.DrawTextUTF8("GPGSV", GSVRect, TextColor, BgColor);
	if(m_oHDOPReceived) {
		TextColor = TelegramReceivedColor;
	} else {
		TextColor = TelegramNotReceivedColor;
	}
	// draw
	Bmp.DrawTextUTF8(HDOPbuf, HDOPRect, TextColor, BgColor);
	if(m_oVDOPReceived) {
		TextColor = TelegramReceivedColor;
	} else {
		TextColor = TelegramNotReceivedColor;
	}
	// draw
	Bmp.DrawTextUTF8(VDOPbuf, VDOPRect, TextColor, BgColor);

	pDC->Draw(&Bmp, OffsetX, OffsetY);

}

