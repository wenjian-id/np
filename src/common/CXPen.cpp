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

#include "CXPen.hpp"

//-------------------------------------
CXPen::CXPen(E_STYLE eStyle, int Width, const CXRGB & Color) :
    m_eStyle(eStyle),
    m_iWidth(Width),
    m_Color(Color)
{
}

//-------------------------------------
CXPen::CXPen(const CXPen&rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
const CXPen & CXPen::operator = (const CXPen & rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
CXPen::~CXPen() {
}

//-------------------------------------
void CXPen::CopyFrom(const CXPen &rOther) {
    m_eStyle = rOther.m_eStyle;
    m_iWidth = rOther.m_iWidth;
    m_Color = rOther.m_Color;
}

//-------------------------------------
CXPen::E_STYLE CXPen::GetStyle() const {
    return m_eStyle;
}

//-------------------------------------
void CXPen::SetStyle(E_STYLE NewValue) {
    m_eStyle = NewValue;
}

//-------------------------------------
int CXPen::GetWidth() const {
    return m_iWidth;
}

//-------------------------------------
void CXPen::SetWidth(int NewValue) {
    m_iWidth = NewValue;
}

//-------------------------------------
CXRGB CXPen::GetColor() const {
    return m_Color;
}

//-------------------------------------
void CXPen::SetColor(const CXRGB & NewValue) {
    m_Color = NewValue;
}
