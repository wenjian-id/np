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

#include "CXGPSProtocolNMEA.hpp"
#include "CXSatelliteData.hpp"
#include "CXNMEA.hpp"

//-------------------------------------
CXGPSProtocolNMEA::CXGPSProtocolNMEA():
	CXGPSProtocol(),
	m_LastReceivedGSVTel(0),
	m_TmpNrSat(0)
{
}

//-------------------------------------
CXGPSProtocolNMEA::~CXGPSProtocolNMEA() {
	ClearBuffer(m_TmpGSVSatInfo);
}

//-------------------------------------
void CXGPSProtocolNMEA::ClearBuffer(CXBuffer<CXSatelliteInfo *> & rBuffer) {
	for(size_t i=0; i<rBuffer.GetSize(); i++)
		delete rBuffer[i];
	rBuffer.Clear();
}

//-------------------------------------
bool CXGPSProtocolNMEA::AfterOpen() {
	// clear buffer
	m_Buffer.Clear();
	return true;
}

//-------------------------------------
bool CXGPSProtocolNMEA::BeforeClose() {
	// clear buffer
	m_Buffer.Clear();
	return true;
}

//-------------------------------------
bool CXGPSProtocolNMEA::OnReadAndProcessData() {
	if(m_Buffer.GetSize() < 100) {
		// buffer needs to be filled
		size_t ReadSize = 0;
		unsigned char buf[512];
		if(!m_pInputChannel->Read(buf, sizeof(buf), ReadSize))
			return false;
		if(ReadSize > 0) {
			// data arrived. Append it
			m_Buffer.Append(buf, ReadSize);
			// and save it
			SaveRawData(buf, ReadSize);
		}
	}
	// now process data
	// check if complete Packet arrived
	while(!m_Buffer.IsEmpty() && (m_Buffer[0] != '$')) {
		m_Buffer.DeleteFirst(1);
	}
	// check if empty
	if(m_Buffer.IsEmpty())
		return false;
	// OK, starts with $
	// check, if 0x0a inside
	unsigned long pos = m_Buffer.Find(0x0a);
	if(pos == tUCBuffer::NPOS)
		return false;
	// extract payload
	tUCBuffer Packet = m_Buffer.Left(pos-1);
	// delete from input buffer
	m_Buffer.DeleteFirst(pos+1);
	Packet.Append(0x00);
	CXStringASCII NMEAPacket(reinterpret_cast<const char *>(Packet.GetBuffer()));
	// process packet
	CXGGAPacket GGAPacket;
	CXRMCPacket RMCPacket;
	CXGSAPacket GSAPacket;
	int NTelegrams = 0;
	int NCurrentTelegram = 0;
	int NSat = 0;
	int NInfos = 0;
	CXSatelliteInfo Info1;
	CXSatelliteInfo Info2;
	CXSatelliteInfo Info3;
	CXSatelliteInfo Info4;
	if(ExtractGGAData(NMEAPacket, GGAPacket)) {
		SetGPSPosInfo(CXGPSPosInfo(GGAPacket.GetUTC(), GGAPacket.HasFix(), GGAPacket.GetLon(), GGAPacket.GetLat(), GGAPacket.GetHeight(), GGAPacket.GetNSat()));
		// save gpx data
		SaveGPXData(GGAPacket.GetLon(), GGAPacket.GetLat(), GGAPacket.GetHeight());
	} else if(ExtractRMCData(NMEAPacket, RMCPacket)) {
		SetGPSCourseInfo(CXGPSCourseInfo(RMCPacket.GetUTC(), RMCPacket.GetSpeed(), RMCPacket.GetCourse()));
		CXSatellites::Instance()->SetRMCReceived();
	} else if(ExtractGSAData(NMEAPacket, GSAPacket)) {
		SetGPSQualityInfo(CXGPSQualityInfo(GSAPacket.GetHDOP(), GSAPacket.GetVDOP()));
		CXSatellites::Instance()->SetActiveSatellites(GSAPacket.GetSatellites());
	} else if(ExtractGSVData(NMEAPacket, NTelegrams, NCurrentTelegram, NSat, NInfos, Info1, Info2, Info3, Info4)) {
		// check if we are in sync
		if(NCurrentTelegram != m_LastReceivedGSVTel+1) {
			// not in sync. reset and discard
			ClearBuffer(m_TmpGSVSatInfo);
			m_LastReceivedGSVTel = 0;
			return false;
		}
		if((m_TmpNrSat != 0) && (m_TmpNrSat != NSat)) {
			// not in sync? reset and discard
			ClearBuffer(m_TmpGSVSatInfo);
			m_LastReceivedGSVTel = 0;
			return false;
		}
		// OK. Probably in sync
		m_TmpNrSat = NSat;
		// append received data
		if(NInfos >= 1)
			m_TmpGSVSatInfo.Append(new CXSatelliteInfo(Info1));
		if(NInfos >= 2)
			m_TmpGSVSatInfo.Append(new CXSatelliteInfo(Info2));
		if(NInfos >= 3)
			m_TmpGSVSatInfo.Append(new CXSatelliteInfo(Info3));
		if(NInfos >= 4)
			m_TmpGSVSatInfo.Append(new CXSatelliteInfo(Info4));
		if(NTelegrams == NCurrentTelegram) {
			// this was the last telegram
			// transfer data from m_TmpGSVSatInfo to m_SatInfo
			CXSatellites::Instance()->SetGSVData(m_TmpGSVSatInfo);
			ClearBuffer(m_TmpGSVSatInfo);
			// reset m_LastReceivedGSVTel and m_TmpNrSat
			m_LastReceivedGSVTel = 0;
			m_TmpNrSat = 0;
		} else {
			// other telegrams to follow
			m_LastReceivedGSVTel = NCurrentTelegram;
		}
	}
	return true;
}