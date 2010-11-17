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

#include "IBitmap.hpp"
#include "IDeviceContext.hpp"

//-------------------------------------
IBitmap::IBitmap() :
    m_Width(0),
    m_Height(0)
{
}

//-------------------------------------
IBitmap::~IBitmap() {
}

//-------------------------------------
void IBitmap::SetWidth(int NewValue) {
    m_Width = NewValue;
}

//-------------------------------------
void IBitmap::SetHeight(int NewValue) {
    m_Height = NewValue;
}

//-------------------------------------
void IBitmap::SetFileName(const CXStringASCII & FileName) {
    m_FileName = FileName;
}

//-------------------------------------
int IBitmap::GetWidth() const {
    return m_Width;
}

//-------------------------------------
int IBitmap::GetHeight() const {
    return m_Height;
}

//-------------------------------------
CXStringASCII IBitmap::GetFileName() const {
    return m_FileName;
}

//-------------------------------------
void IBitmap::Resize(IDeviceContext *pDC, int Width, int Height) {
    // destroy old bitmap
    Destroy();
    if(pDC == NULL)
        return;
    m_Width = Width;
    m_Height = Height;
    // create new bitmap
    Create(pDC, Width, Height);
}
