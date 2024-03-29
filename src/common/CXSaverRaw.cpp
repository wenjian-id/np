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

#include "CXSaverRaw.hpp"

//-------------------------------------
CXSaverRaw::CXSaverRaw():
    CXSaver("txt")
{
}

//-------------------------------------
CXSaverRaw::~CXSaverRaw() {
    // close
    Close();
}

//-------------------------------------
void CXSaverRaw::AfterOpen() {
    // nothing to do
}

//-------------------------------------
void CXSaverRaw::BeforeClose() {
    // nothing to do
}

//-------------------------------------
bool CXSaverRaw::Write(const unsigned char *pbBuffer, size_t DataLength) {
    if(pbBuffer == NULL)
        return false;
    if(DataLength == 0)
        return false;
    size_t Written = 0;
    // do save some preparations
    if(!PrepareSaving())
        return false;
    if(m_File.Write(pbBuffer, DataLength, Written) != CXFile::E_OK)
        return false;
    if(DataLength != Written)
        return false;
    return true;
}
