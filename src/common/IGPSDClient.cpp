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


#include "IGPSDClient.hpp"
#include "CXMutexLocker.hpp"

//----------------------------------------------------------------------------
//-------------------------------------
CXGPSDConfig::CXGPSDConfig() {
}

//-------------------------------------
CXGPSDConfig::CXGPSDConfig(const CXGPSDConfig &rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
CXGPSDConfig::~CXGPSDConfig() {
}

//-------------------------------------
const CXGPSDConfig & CXGPSDConfig::operator = (const CXGPSDConfig &rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXGPSDConfig::CopyFrom(const CXGPSDConfig & rOther) {
    m_Address = rOther.m_Address;
    m_Port = rOther.m_Port;
}

//-------------------------------------
void CXGPSDConfig::SetAddress(const CXStringASCII & Address) {
    m_Address = Address;
}

//-------------------------------------
CXStringASCII CXGPSDConfig::GetAddress() const {
    return m_Address;
}

//-------------------------------------
void CXGPSDConfig::SetPort(const CXStringASCII & Port) {
    m_Port = Port;
}

//-------------------------------------
CXStringASCII CXGPSDConfig::GetPort() const {
    return m_Port;
}


//----------------------------------------------------------------------------
//-------------------------------------
IGPSDClient::IGPSDClient() :
    m_oGPSPosInfoChanged(false),
    m_oGPSCourseInfoChanged(false),
    m_oGPSQualityInfoChanged(false)
{
}
//-------------------------------------
IGPSDClient::~IGPSDClient() {
}
//-------------------------------------
void IGPSDClient::SetConfig(const CXGPSDConfig &Config) {
    m_Config = Config;
}
//-------------------------------------
CXGPSDConfig IGPSDClient::GetConfig() const {
    return m_Config;
}

//-------------------------------------
bool IGPSDClient::GPSPosInfoChanged() const {
    CXMutexLocker ML(&m_Mutex);
    return m_oGPSPosInfoChanged;
}

//-------------------------------------
CXGPSPosInfo IGPSDClient::GetGPSPosInfo() const {
    CXMutexLocker ML(&m_Mutex);
    return m_GPSPosInfo;
}

//-------------------------------------
void IGPSDClient::ResetGPSPosInfoChanged() {
    CXMutexLocker ML(&m_Mutex);
    m_oGPSPosInfoChanged = false;
}

//-------------------------------------
bool IGPSDClient::GPSCourseInfoChanged() const {
    CXMutexLocker ML(&m_Mutex);
    return m_oGPSCourseInfoChanged;
}

//-------------------------------------
CXGPSCourseInfo IGPSDClient::GetGPSCourseInfo() const {
    CXMutexLocker ML(&m_Mutex);
    return m_GPSCourseInfo;
}

//-------------------------------------
void IGPSDClient::ResetGPSCourseInfoChanged() {
    CXMutexLocker ML(&m_Mutex);
    m_oGPSCourseInfoChanged = false;
}

//-------------------------------------
bool IGPSDClient::GPSQualityInfoChanged() const {
    CXMutexLocker ML(&m_Mutex);
    return m_oGPSQualityInfoChanged;
}

//-------------------------------------
CXGPSQualityInfo IGPSDClient::GetGPSQualityInfo() const {
    CXMutexLocker ML(&m_Mutex);
    return m_GPSQualityInfo;
}

//-------------------------------------
void IGPSDClient::ResetGPSQualityInfoChanged() {
    CXMutexLocker ML(&m_Mutex);
    m_oGPSQualityInfoChanged = false;
}
