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

#include "ISerial.hpp"

//-------------------------------------
CXSerialPortConfig::CXSerialPortConfig() :
    m_ulBaudrate(4800),
    m_ucDataBits(8),
    m_eParity(SCP_NONE),
    m_eStopBits(SCS_ONE)
{
}

//-------------------------------------
CXSerialPortConfig::CXSerialPortConfig(const CXStringASCII &SerialPort, unsigned long  ulBaudrate, unsigned char  ucDataBits, E_SERCOMMPARITY  eParity, E_SERCOMMSTOPBITS  eStopBits) :
    m_Port(SerialPort),
    m_ulBaudrate(ulBaudrate),
    m_ucDataBits(ucDataBits),
    m_eParity(eParity),
    m_eStopBits(eStopBits)
{
}

//-------------------------------------
CXSerialPortConfig::CXSerialPortConfig(const CXSerialPortConfig &rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
CXSerialPortConfig::~CXSerialPortConfig() {
}

//-------------------------------------
const CXSerialPortConfig & CXSerialPortConfig::operator = (const CXSerialPortConfig & rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXSerialPortConfig::CopyFrom(const CXSerialPortConfig & rOther) {
    m_Port = rOther.m_Port;
    m_ulBaudrate = rOther.m_ulBaudrate;
    m_ucDataBits = rOther.m_ucDataBits;
    m_eParity = rOther.m_eParity;
    m_eStopBits = rOther.m_eStopBits;
}

//-------------------------------------
CXStringASCII CXSerialPortConfig::GetPort() const {
    return m_Port;
}

//-------------------------------------
void CXSerialPortConfig::SetPort(const CXStringASCII & Port) {
    m_Port = Port;
}

//-------------------------------------
unsigned long CXSerialPortConfig::GetBaudrate() const {
    return m_ulBaudrate;
}

//-------------------------------------
void CXSerialPortConfig::SetBaudrate(unsigned long Baudrate) {
    m_ulBaudrate = Baudrate;
}

//-------------------------------------
unsigned char CXSerialPortConfig::GetDataBits() const {
    return m_ucDataBits;
}

//-------------------------------------
void CXSerialPortConfig::SetDataBits(unsigned char DataBits) {
    m_ucDataBits = DataBits;
}

//-------------------------------------
CXSerialPortConfig::E_SERCOMMPARITY CXSerialPortConfig::GetParity() const {
    return m_eParity;
}

//-------------------------------------
void CXSerialPortConfig::SetParity(const CXStringASCII & ParityString) {
    m_eParity = SCP_NONE;
    CXStringASCII tmp = ParityString.ToUpper();
    if(tmp == "N") {
        m_eParity = SCP_NONE;
    } else if(tmp == "E") {
        m_eParity = SCP_EVEN;
    } else if(tmp == "O") {
        m_eParity = SCP_ODD;
    } else if(tmp == "M") {
        m_eParity = SCP_MARK;
    }
}

//-------------------------------------
CXSerialPortConfig::E_SERCOMMSTOPBITS CXSerialPortConfig::GetStopBits() const {
    return m_eStopBits;
}

//-------------------------------------
void CXSerialPortConfig::SetStopBits(const CXStringASCII & StopBitsString) {
    m_eStopBits = SCS_ONE;
    if(StopBitsString == "1") {
        m_eStopBits = SCS_ONE;
    } else if(StopBitsString == "1.5") {
        m_eStopBits = SCS_ONEFIVE;
    } else if(StopBitsString == "2") {
        m_eStopBits = SCS_TWO;
    }
}
