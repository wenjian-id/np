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

#include "CXGPSInputChannelSerial.hpp"
#include "CXOptions.hpp"

//-------------------------------------
CXGPSInputChannelSerial::CXGPSInputChannelSerial() {
}

//-------------------------------------
CXGPSInputChannelSerial::~CXGPSInputChannelSerial() {
}

//-------------------------------------
bool CXGPSInputChannelSerial::Open() {
    // open channel
    return m_Serial.Open(m_PortConfig) == CXSerial::RC_OK;
}

//-------------------------------------
bool CXGPSInputChannelSerial::Close() {
    // close
    return m_Serial.Close() == CXSerial::RC_OK;
}

//-------------------------------------
bool CXGPSInputChannelSerial::IsOpen() {
    return m_Serial.IsOpen();
}

//-------------------------------------
bool CXGPSInputChannelSerial::ReadConfiguration() {
    // get configuration
    m_PortConfig = CXOptions::Instance()->GetSerialPortConfig();
    return true;
}

//-------------------------------------
bool CXGPSInputChannelSerial::CanFlush() {
    return true;
}

//-------------------------------------
bool CXGPSInputChannelSerial::Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize) {
    ReadSize = 0;
    if(pbBuffer == 0)
        return false;
    if(!IsOpen())
        return false;
    // read data
    unsigned long ulReadSize = 0;
    bool oResult = m_Serial.Receive(Size, pbBuffer, ulReadSize) == CXSerial::RC_OK;
    ReadSize = ulReadSize;
    return oResult;
}

//-------------------------------------
bool CXGPSInputChannelSerial::Read(CXGPSPosInfo &/*rGPSPosInfo*/, bool &/*roGPSPosInfoChanged*/, CXGPSCourseInfo &/*rGPSCourseInfo*/, bool &/*roGPSCourseInfoChanged*/, CXGPSQualityInfo &/*rGPSQualityInfo*/, bool &/*roGPSQualityInfoChanged*/) {
    return false;
}
