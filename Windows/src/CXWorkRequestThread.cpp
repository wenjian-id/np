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

#include "CXWorkRequestThread.hpp"

//-------------------------------------
CXWorkRequestThread::CXWorkRequestThread() :
	m_hEvent(NULL)
{
	m_hEvent = CreateEvent(	NULL,	// pointer to security attributes
							false,  // flag for manual-reset event
							false,	// flag for initial state
							NULL	// pointer to event-object name
				);
 
}

//-------------------------------------
CXWorkRequestThread::~CXWorkRequestThread() {
}

//-------------------------------------
void CXWorkRequestThread::RequestWork() {
	SetEvent(m_hEvent);
} 

//-------------------------------------
void CXWorkRequestThread::DoWait() {
	HANDLE handles[2];
	handles[0] = GetHandle(); // own handle
	handles[1] = m_hEvent;
	if(handles[0] != NULL) {
		// wait
		WaitForMultipleObjects(2, handles, FALSE, INFINITE);
	}
}
