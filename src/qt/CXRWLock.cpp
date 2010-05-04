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

#include "CXRWLock.hpp"

//-------------------------------------
CXRWLock::CXRWLock() {
}

//-------------------------------------
CXRWLock::~CXRWLock() {
}

//-------------------------------------
void CXRWLock::LockRead() {
	// lock for read
	m_RWLock.lockForRead();
}

//-------------------------------------
void CXRWLock::LockWrite() {
	// lock for write
	m_RWLock.lockForWrite();
}

//-------------------------------------
void CXRWLock::UnlockRead() {
	// unlock
	m_RWLock.unlock();
}

//-------------------------------------
void CXRWLock::UnlockWrite() {
	// unlock
	m_RWLock.unlock();
}
