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

#include "CXExactTime.hpp"


//-------------------------------------
CXExactTime::CXExactTime() {
    SetNow();
}

//-------------------------------------
CXExactTime::CXExactTime(const CXExactTime &rOther) :
    IExactTime()
{
    CopyFrom(rOther);
}

//-------------------------------------
CXExactTime::~CXExactTime() {
}

//-------------------------------------
const CXExactTime & CXExactTime::operator = (const CXExactTime & rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXExactTime::CopyFrom(const CXExactTime & rOther) {
    m_Time = rOther.m_Time;
}

//-------------------------------------
void CXExactTime::SetNow() {
    m_Time = QDateTime::currentDateTime();
}

//-------------------------------------
unsigned long CXExactTime::operator - (const CXExactTime & rOther) const {
    if(m_Time < rOther.m_Time)
        return 0;
    // compute difference in seconds
    return rOther.m_Time.time().msecsTo(m_Time.time());
}

//-------------------------------------
int CXExactTime::GetYear() const {
    return m_Time.date().year();
}

//-------------------------------------
int CXExactTime::GetMonth() const {
    return m_Time.date().month();
}

//-------------------------------------
int CXExactTime::GetDay() const {
    return m_Time.date().day();
}

//-------------------------------------
int CXExactTime::GetHour() const {
    return m_Time.time().hour();
}

//-------------------------------------
int CXExactTime::GetMinute() const {
    return m_Time.time().minute();
}

//-------------------------------------
int CXExactTime::GetSecond() const {
    return m_Time.time().second();
}
