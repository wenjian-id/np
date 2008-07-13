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

#include "CXMapPainter.hpp"
#include "CXMutexLocker.hpp"
#include "CXFile.hpp"

//-------------------------------------
CXMapPainter::CXMapPainter() :
	m_oMustRepaint(true)
{
}

//-------------------------------------
CXMapPainter::~CXMapPainter() {
}

//-------------------------------------
bool CXMapPainter::MustRepaint() const {
	CXMutexLocker L(&m_Mutex);
	return m_oMustRepaint;
}

//-------------------------------------
void CXMapPainter::SetMustRepaint(bool Value) {
	CXMutexLocker L(&m_Mutex);
	m_oMustRepaint = Value;
}

//-------------------------------------
void CXMapPainter::PositionChanged(const CXNaviData &NewNaviData) {
	CXMutexLocker L(&m_Mutex);
	m_NaviData = NewNaviData;
}

//-------------------------------------
CXNaviData CXMapPainter::GetPosition() const {
	CXMutexLocker L(&m_Mutex);
	return m_NaviData;
}

//-------------------------------------
void CXMapPainter::DoWork() {
	OnDoWork();
}

