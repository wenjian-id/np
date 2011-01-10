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

#include "IWorkRequestThread.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"

//-------------------------------------
IWorkRequestThread::IWorkRequestThread() :
    m_oWorkRequestFlag(false)
{
}


//-------------------------------------
IWorkRequestThread::~IWorkRequestThread() {
}

//-------------------------------------
void IWorkRequestThread::SetWorkRequestFlag(bool NewValue) {
    CXWriteLocker WL(&m_RWLock);
    m_oWorkRequestFlag = NewValue;
}

//-------------------------------------
bool IWorkRequestThread::GetWorkRequestFlag() const {
    CXReadLocker RL(&m_RWLock);
    return m_oWorkRequestFlag;
}

//-------------------------------------
void IWorkRequestThread::StopThread() {
    CXThread::StopThread();
    Wakeup();
}

//-------------------------------------
void IWorkRequestThread::RequestWork() {
    SetWorkRequestFlag(true);
    Wakeup();
}

//-------------------------------------
int IWorkRequestThread::OnThreadFunc() {
    // main loop
    do {
        if(!GetWorkRequestFlag()) {
            // wait for a wakeup call
            DoWait();
        }
        if(!MustStopThread()) {
            if(GetWorkRequestFlag()) {
                // do work
                SetWorkRequestFlag(false);
                OnWorkFunc();
            }
        }
    } while(!MustStopThread());

    return 0;
}

