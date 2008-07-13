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

#include "CXUTMSpeed.hpp"

//-------------------------------------
CXUTMSpeed::CXUTMSpeed() {
	Reset();
}

//-------------------------------------
CXUTMSpeed::CXUTMSpeed(const CXUTMSpeed &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXUTMSpeed::~CXUTMSpeed() {
}

//-------------------------------------
const CXUTMSpeed & CXUTMSpeed::operator = (const CXUTMSpeed &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXUTMSpeed::CopyFrom(const CXUTMSpeed &rOther) {
	m_dSpeed = rOther.m_dSpeed;
	m_dCos = rOther.m_dCos;
	m_dSin = rOther.m_dSin;
}

//-------------------------------------
bool CXUTMSpeed::operator == (const CXUTMSpeed &rOther) {
	return	(m_dSpeed == rOther.m_dSpeed) && 
			(m_dCos == rOther.m_dCos) &&
			(m_dSin == rOther.m_dSin);

}

//-------------------------------------
bool CXUTMSpeed::operator != (const CXUTMSpeed &rOther) {
	return ! operator == (rOther);
}

//-------------------------------------
void CXUTMSpeed::Reset() {
	m_dSpeed = 0;
	m_dCos = 0;
	m_dSin = 1;
}

//-------------------------------------
double CXUTMSpeed::GetSpeed() const {
	return m_dSpeed;
}

//-------------------------------------
void CXUTMSpeed::SetSpeed(double dSpeed) {
	m_dSpeed = dSpeed;
}

//-------------------------------------
double CXUTMSpeed::GetCos() const {
	return m_dCos;
}

//-------------------------------------
void CXUTMSpeed::SetCos(double dCos) {
	m_dCos = dCos;
}

//-------------------------------------
double CXUTMSpeed::GetSin() const {
	return m_dSin;
}

//-------------------------------------
void CXUTMSpeed::SetSin(double dSin) {
	m_dSin = dSin;
}
