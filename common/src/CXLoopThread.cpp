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

#include "CXLoopThread.hpp"
#include "CXMutexLocker.hpp"

//-------------------------------------
CXLoopThread::CXLoopThread() :
	m_SleepTime(10)
{
}


//-------------------------------------
CXLoopThread::~CXLoopThread() {
	// check if it is runnning
	if(IsRunning()) {
		StopThread();
		// wait for thread exit
		WaitForThreadExit(WAIT_INFINITE);
	}
}

//-------------------------------------
void CXLoopThread::SetSleepTime(size_t SleepTime) {
	CXMutexLocker L(&m_Mutex);
	m_SleepTime = SleepTime;
}

//-------------------------------------
size_t CXLoopThread::GetSleepTime() const {
	CXMutexLocker L(&m_Mutex);
	return m_SleepTime;
}

//-------------------------------------
int CXLoopThread::OnThreadFunc() {
	// main loop
	do {
		// do work
		OnThreadLoop();
		// sleep
		DoSleep(GetSleepTime());
	} while(!MustStopThread());

	return 0;
}


