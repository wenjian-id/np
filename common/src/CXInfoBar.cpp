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

#include "CXInfoBar.hpp"
#include "CXMutexLocker.hpp"

//-------------------------------------
CXInfoBar::CXInfoBar() :
	m_Width(0),
	m_Height(0),
	m_oSizeChanged(false)
{
}

//-------------------------------------
CXInfoBar::~CXInfoBar() {
}

//-------------------------------------
int CXInfoBar::GetWidth() const {
	CXMutexLocker L(&m_Mutex);
	return m_Width;
}

//-------------------------------------
int CXInfoBar::GetHeight() const {
	CXMutexLocker L(&m_Mutex);
	return m_Height;
}

//-------------------------------------
void CXInfoBar::Resize(int Width, int Height) {
	CXMutexLocker L(&m_Mutex);
	m_Width = Width;
	m_Height = Height;
	m_oSizeChanged = true;
}

//-------------------------------------
bool CXInfoBar::SizeChanged() const {
	CXMutexLocker L(&m_Mutex);
	return m_oSizeChanged;
}

//-------------------------------------
void CXInfoBar::Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
	if(pDC == NULL)
		return;
	OnPaint(pDC, OffsetX, OffsetY);
	{
		// reset size changed flag
		CXMutexLocker L(&m_Mutex);
		m_oSizeChanged = false;
	}
}

//-------------------------------------
E_COMMAND CXInfoBar::OnInternalMouseDown(int /*X*/, int /*Y*/) {
	return e_CmdNone;
}

//-------------------------------------
E_COMMAND CXInfoBar::OnMouseDown(int X, int Y) {
	CXMutexLocker L(&m_Mutex);
	return OnInternalMouseDown(X, Y);
}
