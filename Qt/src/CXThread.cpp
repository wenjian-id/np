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

#include "CXThread.hpp"
#include <CXMutexLocker.hpp>

//-------------------------------------
CXThread::CXThreadHelper::CXThreadHelper(CXThread *pThread) :
	m_pThread(pThread)
{
}

//-------------------------------------
CXThread::CXThreadHelper::~CXThreadHelper() {
}

//-------------------------------------
void CXThread::CXThreadHelper::run() {
	if(m_pThread != NULL)
		m_pThread->ThreadFunc();
}

//-------------------------------------
void CXThread::CXThreadHelper::DoSleep(size_t dwMilliSeconds) {
	msleep(dwMilliSeconds);
}

//-------------------------------------
CXThread::CXThread() :
	m_ThreadHelper(this)
{
}

//-------------------------------------
CXThread::~CXThread() {
	/// \todo check !IsRunning()
}

//-------------------------------------
bool CXThread::CreateThread() {
	/// \todo check !IsRunning()
	m_ThreadHelper.start();
	return true;
}

//-------------------------------------
bool CXThread::WaitForThreadExit(size_t dwMilliSeconds) {
	return m_ThreadHelper.wait(dwMilliSeconds);
}

//-------------------------------------
void CXThread::DoSleep(size_t dwMilliSeconds) {
	m_ThreadHelper.DoSleep(dwMilliSeconds);
}

