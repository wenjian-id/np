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

#include "CXPOWMMap.hpp"
#include "CXOptions.hpp"
#include "CXExactTime.hpp"
#include "CXDebugInfo.hpp"
#include "CXTransformationMatrix.hpp"


//----------------------------------------------------------------------------
CXPOWMMap *CXPOWMMap::m_pInstance = NULL;

//-------------------------------------
CXPOWMMap::CXPOWMMap() :
    m_pMapLoaderThread(NULL)
{
}

//-------------------------------------
CXPOWMMap::~CXPOWMMap() {
}

//-------------------------------------
CXPOWMMap *CXPOWMMap::Instance() {
    if(m_pInstance == NULL)
        m_pInstance = new CXPOWMMap();
    return m_pInstance;
}

//-------------------------------------
void CXPOWMMap::SetMapLoaderThread(CXMapLoaderThread *pMapLoaderThread) {
    m_pMapLoaderThread = pMapLoaderThread;
}

//-------------------------------------
TMapSectionPtrArray CXPOWMMap::GetMapSectionsDisplay(const CXVisibleMapSectionDescr &Descr) {
    return m_pMapLoaderThread->GetMapSectionsDisplay(Descr);
}

//-------------------------------------
TMapSectionPtrArray CXPOWMMap::GetMapSectionsLocator(const CXVisibleMapSectionDescr &Descr) {
    return m_pMapLoaderThread->GetMapSectionsLocator(Descr);
}
