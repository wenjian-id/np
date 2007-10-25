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

#include "CXThread.hpp"
#include <CXMutexLocker.hpp>

//-------------------------------------
CXThread::CXThread() :
	m_Handle(NULL),
	m_ThreadID(0)
{
}


//-------------------------------------
CXThread::~CXThread() {
	/// \todo check !IsRunning()
}


//-------------------------------------
DWORD WINAPI CXThread::thrfunc(LPVOID lpParameter) {
	if(lpParameter == NULL)
		return -1;
	CXThread *pThr = (CXThread *)lpParameter;
	return pThr->ThreadFunc();
}

//-------------------------------------
bool CXThread::CreateThread() {
	CXMutexLocker L(&m_Mutex);
	/// \todo check !IsRunning()
	/// \todo check m_Handle == NULL;
	m_Handle = ::CreateThread(	NULL,
								0,
								CXThread::thrfunc,
								this,
								0,
								&m_ThreadID
							);
	/// \todo check m_Handle != NULL ?
	return m_Handle != NULL;
}

//-------------------------------------
void CXThread::SetHandle(HANDLE NewHandle) {
	CXMutexLocker L(&m_Mutex);
	m_Handle = NewHandle;
}


//-------------------------------------
HANDLE CXThread::GetHandle() const {
	CXMutexLocker L(&m_Mutex);
	return m_Handle;
}

//-------------------------------------
bool CXThread::WaitForThreadExit(size_t dwMilliSeconds) {
	HANDLE ThreadHandle = GetHandle();
	// get m_Handle in a safe way
	if(ThreadHandle != NULL) {
		// wait
		MsgWaitForMultipleObjects(1, &ThreadHandle, FALSE, dwMilliSeconds, QS_ALLEVENTS);
	}
	SetHandle(NULL);
	return true;
}

//-------------------------------------
void CXThread::DoSleep(size_t dwMilliseconds) {
	MsgWaitForMultipleObjects(0, NULL, FALSE, dwMilliseconds, QS_ALLEVENTS);
}

