/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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
CXExactTime::CXExactTime(const CXExactTime &rOther) {
	_CopyFrom(rOther);
}

//-------------------------------------
CXExactTime::~CXExactTime() {
}

//-------------------------------------
const CXExactTime & CXExactTime::operator = (const CXExactTime & rOther) {
	if(this != &rOther)
		_CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXExactTime::_CopyFrom(const CXExactTime & rOther) {
	mSystemTime = rOther.mSystemTime;
	mdwMilliSeconds = rOther.mdwMilliSeconds;
}

//-------------------------------------
void CXExactTime::SetNow() {
	GetLocalTime(&mSystemTime); 
	mdwMilliSeconds = GetTickCount();
}

//-------------------------------------
unsigned long CXExactTime::operator - (const CXExactTime & rOther) const {
	if(mdwMilliSeconds < rOther.mdwMilliSeconds)
		return 0;
	return mdwMilliSeconds - rOther.mdwMilliSeconds;
}


//-------------------------------------
int CXExactTime::GetYear() const {
	return mSystemTime.wYear;
}

//-------------------------------------
int CXExactTime::GetMonth() const {
	return mSystemTime.wMonth;
}

//-------------------------------------
int CXExactTime::GetDay() const {
	return mSystemTime.wDay;
}

//-------------------------------------
int CXExactTime::GetHour() const {
	return mSystemTime.wHour;
}

//-------------------------------------
int CXExactTime::GetMinute() const {
	return mSystemTime.wMinute;
}

//-------------------------------------
int CXExactTime::GetSecond() const {
	return mSystemTime.wSecond;
}
