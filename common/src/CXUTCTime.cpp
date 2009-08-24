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
	m_UTCTime(0)
{
}

//-------------------------------------
CXUTCTime::CXUTCTime(double UTCTime) :
	m_UTCTime(UTCTime)
{
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
	m_UTCTime = rOther.m_UTCTime;
}

//-------------------------------------
void CXUTCTime::FromString(const CXStringASCII &Value) {
	if(Value.GetSize() < 6) {
		m_UTCTime = 0;
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
	m_UTCTime = (dHours + (dMinutes + (dSeconds+dFractions)/60)/60)/24;
}

//-------------------------------------
double CXUTCTime::GetUTCTime() const {
	return m_UTCTime;
}

//-------------------------------------
void CXUTCTime::SetUTCTime(double NewValue) {
	m_UTCTime = NewValue;
}

//-------------------------------------
void CXUTCTime::SetUTCTime(const CXStringASCII & NewValue) {
	FromString(NewValue);
}

//-------------------------------------
CXUTCTime CXUTCTime::operator - (const CXUTCTime & rOther) const {
	if(m_UTCTime < rOther.m_UTCTime)
		return 1 + m_UTCTime - rOther.m_UTCTime;
	// compute difference in seconds
	return m_UTCTime - rOther.m_UTCTime;
}
