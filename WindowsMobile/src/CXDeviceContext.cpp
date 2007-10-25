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

#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"

//-------------------------------------
CXDeviceContext::CXDeviceContext(HDC hDC) :
	m_hDC(hDC)
{
}

//-------------------------------------
CXDeviceContext::~CXDeviceContext() {
}

//-------------------------------------
HDC CXDeviceContext::GetDC() const {
	return m_hDC;
}

//-------------------------------------
void CXDeviceContext::Draw(CXBitmap *pBmp, int OffsetX, int OffsetY) {
	if(m_hDC == NULL)
		return;
	if(pBmp == NULL)
		return;
	if(pBmp->GetDC() == NULL)
		return;
	::BitBlt(m_hDC, OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight(), pBmp->GetDC(), 0, 0, SRCCOPY);
}
