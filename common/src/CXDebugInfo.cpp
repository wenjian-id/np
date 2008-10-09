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

#include "CXDebugInfo.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"

CXDebugInfo * CXDebugInfo::m_pInstance = NULL;


//-------------------------------------
CXDebugInfo::CXDebugInfo() :
	m_DrawTime(0),
	m_LocatorTime(0)
{
}

//-------------------------------------
CXDebugInfo::~CXDebugInfo() {
}

//-------------------------------------
CXDebugInfo *CXDebugInfo::Instance() {
	if(m_pInstance == NULL)
		m_pInstance = new CXDebugInfo();
	return m_pInstance;
}

//-------------------------------------
int CXDebugInfo::GetDrawTime() const {
	CXReadLocker RL(&m_RWLock);
	return m_DrawTime;
}

//-------------------------------------
void CXDebugInfo::SetDrawTime(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_DrawTime = NewValue;
}

//-------------------------------------
int CXDebugInfo::GetLocatorTime() const {
	CXReadLocker RL(&m_RWLock);
	return m_LocatorTime;
}

//-------------------------------------
void CXDebugInfo::SetLocatorTime(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_LocatorTime = NewValue;
}
