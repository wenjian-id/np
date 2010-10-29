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
CXRWLock::CXRWLock() :
    m_Semaphore(32)
{
}

//-------------------------------------
CXRWLock::~CXRWLock() {
}

//-------------------------------------
void CXRWLock::LockRead() {
    m_Semaphore.Lock();
}

//-------------------------------------
void CXRWLock::LockWrite() {
    m_Mutex.Lock();
    for(size_t i=0; i<m_Semaphore.GetMaxCount(); i++)
        m_Semaphore.Lock();
    m_Mutex.Unlock();
}

//-------------------------------------
void CXRWLock::UnlockRead() {
    m_Semaphore.Unlock();
}

//-------------------------------------
void CXRWLock::UnlockWrite() {
    for(size_t i=0; i<m_Semaphore.GetMaxCount(); i++)
        m_Semaphore.Unlock();
}
