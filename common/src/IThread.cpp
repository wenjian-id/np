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

#include "IThread.hpp"
#include "CXMutexLocker.hpp"

//-------------------------------------
IThread::IThread() :
	m_oRunning(false),
	m_oStopThread(false)
{
}

//-------------------------------------
IThread::~IThread() {
}

//-------------------------------------
bool IThread::MustStopThread() const {
	CXMutexLocker L(&m_Mutex);
	return m_oStopThread;
}

//-------------------------------------
void IThread::StopThread() {
	CXMutexLocker L(&m_Mutex);
	m_oStopThread = true;
}

//-------------------------------------
bool IThread::IsRunning() const {
	CXMutexLocker L(&m_Mutex);
	return m_oRunning;
}

//-------------------------------------
void IThread::SetRunning(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oRunning = NewValue;
}

//-------------------------------------
int IThread::ThreadFunc() {
	/// \todo check !IsRunning()
	SetRunning(true);
	// tell thread was started
	OnThreadStarted();
	// run specific thread function
	int Result = OnThreadFunc();

	// tell thread was stopped
	OnThreadStopped();

	SetRunning(false);

	return Result;
}


