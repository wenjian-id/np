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

#include "CXRGB.hpp"

//-------------------------------------
CXRGB::CXRGB() :
    m_R(0),
    m_G(0),
    m_B(0)
{
}

//-------------------------------------
CXRGB::CXRGB(unsigned char R, unsigned char G, unsigned char B) :
    m_R(R),
    m_G(G),
    m_B(B)
{
}

//-------------------------------------
CXRGB::CXRGB(const CXRGB &rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
CXRGB::~CXRGB() {
}

//-------------------------------------
const CXRGB & CXRGB::operator = (const CXRGB & rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
void CXRGB::CopyFrom(const CXRGB &rOther) {
    m_R = rOther.m_R;
    m_G = rOther.m_G;
    m_B = rOther.m_B;
}

//-------------------------------------
unsigned char CXRGB::GetR() const {
    return m_R;
}

//-------------------------------------
unsigned char CXRGB::GetG() const {
    return m_G;
}

//-------------------------------------
unsigned char CXRGB::GetB() const  {
    return m_B;
}

//-------------------------------------
void CXRGB::SetR(unsigned char R) {
    m_R = R;
}

//-------------------------------------
void CXRGB::SetG(unsigned char G) {
    m_G = G;
}

//-------------------------------------
void CXRGB::SetB(unsigned char B) {
    m_B = B;
}
