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
	
#include "CXUTCTime.hpp"

#include  <stdio.h>

//-------------------------------------
CXUTCTime::CXUTCTime():
	m_UTCTimeDouble(0)
{
	FromDouble(m_UTCTimeDouble);
}

//-------------------------------------
CXUTCTime::CXUTCTime(double UTCTime) {
	FromDouble(UTCTime);
}

//-------------------------------------
CXUTCTime::CXUTCTime(const CXStringASCII & UTCTime) {
	FromString(UTCTime);
}

//-------------------------------------
CXUTCTime::CXUTCTime(const CXUTCTime &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXUTCTime::~CXUTCTime() {
}

//-------------------------------------
const CXUTCTime & CXUTCTime::operator = (const CXUTCTime &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXUTCTime::CopyFrom(const CXUTCTime &rOther) {
	m_UTCTimeDouble = rOther.m_UTCTimeDouble;
	m_UTCTimeString = rOther.m_UTCTimeString;
}

//-------------------------------------
void CXUTCTime::FromString(const CXStringASCII &Value) {
	if(Value.GetSize() < 6) {
		m_UTCTimeDouble = 0;
		m_UTCTimeString.Clear();
		return;
	}
	CXStringASCII Tmp = Value;
	// hours
	CXStringASCII Chunk = Tmp.Left(2);
	double dHours = 0;
	sscanf(Chunk.c_str(), "%lf", &dHours);
	Tmp.DeleteFirst(2);
	// minutes
	Chunk = Tmp.Left(2);
	double dMinutes = 0;
	sscanf(Chunk.c_str(), "%lf", &dMinutes);
	Tmp.DeleteFirst(2);
	// seconds
	Chunk = Tmp.Left(2);
	double dSeconds = 0;
	sscanf(Chunk.c_str(), "%lf", &dSeconds);
	Tmp.DeleteFirst(2);
	// fractions of a second
	double dFractions = 0;
	if(Tmp.GetSize() != 0) {
		Tmp.DeleteFirst(1);
		sscanf(Chunk.c_str(), "%lf", &dFractions);
		for(size_t i=0; i<Tmp.GetSize(); i++)
			dFractions = dFractions/10;
	}
	// now compute value
	m_UTCTimeDouble = (dHours + (dMinutes + (dSeconds+dFractions)/60)/60)/24;
	m_UTCTimeString = Value;
}

//-------------------------------------
void CXUTCTime::FromDouble(double Value) {
	m_UTCTimeDouble = Value;
	char buf[100];
	snprintf(buf, sizeof(buf), "%010.3f", Value);
	m_UTCTimeString = buf;
}

//-------------------------------------
double CXUTCTime::GetUTCTimeAsDouble() const {
	return m_UTCTimeDouble;
}

//-------------------------------------
CXStringASCII CXUTCTime::GetUTCTimeAsString() const {
	return m_UTCTimeString;
}

//-------------------------------------
void CXUTCTime::SetUTCTime(double NewValue) {
	FromDouble(NewValue);
}

//-------------------------------------
void CXUTCTime::SetUTCTime(const CXStringASCII & NewValue) {
	FromString(NewValue);
}

//-------------------------------------
CXUTCTime CXUTCTime::operator - (const CXUTCTime & rOther) const {
	if(m_UTCTimeDouble < rOther.m_UTCTimeDouble)
		return 1 + m_UTCTimeDouble - rOther.m_UTCTimeDouble;
	// compute difference in seconds
	return m_UTCTimeDouble - rOther.m_UTCTimeDouble;
}

//-------------------------------------
bool CXUTCTime::operator == (const CXUTCTime & rOther) const {
	return m_UTCTimeString == rOther.m_UTCTimeString;
}

//-------------------------------------
bool CXUTCTime::operator != (const CXUTCTime & rOther) const {
	return !(*this == rOther);
}
