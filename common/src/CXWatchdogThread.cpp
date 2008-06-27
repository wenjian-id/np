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

#include "CXWatchdogThread.hpp"
#include "CXOptions.hpp"
#include "OSSpecific.hpp"

//-------------------------------------
CXWatchdogThread::CXWatchdogThread() {
	int SleepTime = CXOptions::Instance()->GetWatchdogTimeout();
	if(SleepTime != 0) {
		SetSleepTime(SleepTime);
	} else {
		SetSleepTime(5000); // 5 seconds
	}
}


//-------------------------------------
CXWatchdogThread::~CXWatchdogThread() {
}


//-------------------------------------
void CXWatchdogThread::OnThreadStarted() {
	// do nothing
}


//-------------------------------------
void CXWatchdogThread::OnThreadStopped() {
	// do nothing
}

//-------------------------------------
void CXWatchdogThread::OnThreadLoop() {
	// trigger watchdog if neccessary
	if(CXOptions::Instance()->GetWatchdogTimeout() != 0)
		TriggerWatchdog();
}
