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

#include "CXSemaphore.hpp"

//-------------------------------------
CXSemaphore::CXSemaphore(size_t MaxCount) :
	ISemaphore(MaxCount),
	m_hSemaphore(NULL)
{
	/// \todo implement error checking
	m_hSemaphore = CreateSemaphore(NULL, MaxCount, MaxCount, NULL);
}

//-------------------------------------
CXSemaphore::~CXSemaphore() {
	/// \todo implement error checking
	::CloseHandle(m_hSemaphore);
    m_hSemaphore = NULL;
}

//-------------------------------------
void CXSemaphore::Lock() {
	/// \todo implement error checking
	::WaitForSingleObject(m_hSemaphore, INFINITE);
}

//-------------------------------------
void CXSemaphore::Unlock() {
	/// \todo implement error checking
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
}

