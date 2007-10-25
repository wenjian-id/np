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

#include "CXMutex.hpp"

//-------------------------------------
CXMutex::CXMutex() :
	m_hMutex(NULL)
{
	/// \todo error checking
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
}

//-------------------------------------
CXMutex::~CXMutex() {
	/// \todo error checking
	::CloseHandle(m_hMutex);
    m_hMutex = NULL;
}

//-------------------------------------
void CXMutex::Lock() {
	/// \todo error checking
	::WaitForSingleObject(m_hMutex, INFINITE);
}

//-------------------------------------
void CXMutex::Unlock() {
	/// \todo error checking
	ReleaseMutex(m_hMutex);
}

