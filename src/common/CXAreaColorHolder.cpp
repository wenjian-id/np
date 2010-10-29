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

#include "CXAreaColorHolder.hpp"

//-------------------------------------
CXAreaColorHolder::CXAreaColorHolder() {
    CreateColors();
}

//-------------------------------------
CXAreaColorHolder::~CXAreaColorHolder() {
    DestroyColors();
}

//-------------------------------------
void CXAreaColorHolder::CreateColors() {

    for(size_t i=0; i<e_Way_EnumCount; i++) {
        m_Colors.Append(new CXRGB());
    }

    // now create colors
    // area none
    *m_Colors[e_Area_None]      = CXRGB(0x00, 0x00, 0x00);
    // water
    *m_Colors[e_Area_Water]     = CXRGB(0x00, 0x00, 0xD0);
    // wood
    *m_Colors[e_Area_Wood]      = CXRGB(0x00, 0xFF, 0x00);
}

//-------------------------------------
void CXAreaColorHolder::DestroyColors() {
    for(size_t i=0; i<e_Way_EnumCount; i++) {
        delete m_Colors[i];
    }
    m_Colors.Clear();
}

//-------------------------------------
CXRGB CXAreaColorHolder::GetColor(E_AREA_TYPE eAreaType) const {
    return *m_Colors[eAreaType];
}
