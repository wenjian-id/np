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

#include "CXGPSInputChannelGPSD.hpp"
#include "CXOptions.hpp"

//-------------------------------------
CXGPSInputChannelGPSD::CXGPSInputChannelGPSD() {
}

//-------------------------------------
CXGPSInputChannelGPSD::~CXGPSInputChannelGPSD() {
}

//-------------------------------------
bool CXGPSInputChannelGPSD::Open() {
	return m_GPSDClient.Open();
}

//-------------------------------------
bool CXGPSInputChannelGPSD::Close() {
	return m_GPSDClient.Close();
}

//-------------------------------------
bool CXGPSInputChannelGPSD::IsOpen() {
	return m_GPSDClient.IsOpen();
}

//-------------------------------------
bool CXGPSInputChannelGPSD::ReadConfiguration() {
	m_GPSDClient.SetConfig(CXOptions::Instance()->GetGPSDConfig());
	return true;
}

//-------------------------------------
bool CXGPSInputChannelGPSD::CanFlush() {
	return false;
}

//-------------------------------------
bool CXGPSInputChannelGPSD::Read(unsigned char * /*pbBuffer*/, size_t /*Size*/, size_t &ReadSize) {
	ReadSize = 0;
	return false;
}

//-------------------------------------
bool CXGPSInputChannelGPSD::Read(CXGPSPosInfo &rGPSPosInfo, bool & roGPSPosInfoChanged, CXGPSCourseInfo &rGPSCourseInfo, bool & roGPSCourseInfoChanged, CXGPSQualityInfo &rGPSQualityInfo, bool & roGPSQualityInfoChanged) {
	m_GPSDClient.Read();
	bool oResult = false;
	roGPSPosInfoChanged = false;
	roGPSCourseInfoChanged = false;
	roGPSQualityInfoChanged = false;
	if(m_GPSDClient.GPSPosInfoChanged()) {
		rGPSPosInfo = m_GPSDClient.GetGPSPosInfo();
		m_GPSDClient.ResetGPSPosInfoChanged();
		roGPSPosInfoChanged = true;
		oResult = true;
	}
	if(m_GPSDClient.GPSCourseInfoChanged()) {
		rGPSCourseInfo = m_GPSDClient.GetGPSCourseInfo();
		m_GPSDClient.ResetGPSCourseInfoChanged();
		roGPSCourseInfoChanged = true;
		oResult = true;
	}
	if(m_GPSDClient.GPSQualityInfoChanged()) {
		rGPSQualityInfo = m_GPSDClient.GetGPSQualityInfo();
		m_GPSDClient.ResetGPSQualityInfoChanged();
		roGPSQualityInfoChanged = true;
		oResult = true;
	}
	return oResult;
}
