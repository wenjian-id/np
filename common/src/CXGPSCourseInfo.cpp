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

#include "CXGPSCourseInfo.hpp"

//-------------------------------------
CXGPSCourseInfo::CXGPSCourseInfo() :
	m_oFix(false),
	m_dSpeed(0.0),
	m_dCourse(0.0)
{
}

//-------------------------------------
CXGPSCourseInfo::CXGPSCourseInfo(const CXStringASCII &UTC, bool oFix, double dSpeed, double dCourse) :
	m_UTC(UTC),
	m_oFix(oFix),
	m_dSpeed(dSpeed),
	m_dCourse(dCourse)
{
}

//-------------------------------------
CXGPSCourseInfo::CXGPSCourseInfo(const CXGPSCourseInfo & rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXGPSCourseInfo::~CXGPSCourseInfo() {
}

//-------------------------------------
const CXGPSCourseInfo & CXGPSCourseInfo::operator = (const CXGPSCourseInfo & rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXGPSCourseInfo::CopyFrom(const CXGPSCourseInfo &rOther) {
	m_UTC = rOther.m_UTC;
	m_oFix = rOther.m_oFix;
	m_dSpeed = rOther.m_dSpeed;
	m_dCourse = rOther.m_dCourse;
}

//-------------------------------------
CXStringASCII CXGPSCourseInfo::GetUTC() const {
	return m_UTC;
}

//-------------------------------------
bool CXGPSCourseInfo::GetFix() const {
	return m_oFix;
}

//-------------------------------------
double CXGPSCourseInfo::GetSpeed() const {
	return m_dSpeed;
}

//-------------------------------------
double CXGPSCourseInfo::GetCourse() const {
	return m_dCourse;
}
