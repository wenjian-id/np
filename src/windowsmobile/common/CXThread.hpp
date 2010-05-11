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

#ifndef __CXTHREAD_HPP__
#define __CXTHREAD_HPP__

#include <IThread.hpp>
#include "CXMutex.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXThread : public IThread {
private:
	HANDLE				m_Handle;		///< oiu
	unsigned long		m_ThreadID;		///< oiu
	mutable CXMutex		m_Mutex;		///< Synchronization object.
	//-------------------------------------
	CXThread(const CXThread &);							///< Not used.
	const CXThread & operator = (const CXThread &);		///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	static DWORD WINAPI thrfunc(LPVOID lpParameter);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetHandle(HANDLE NewHandle);
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DoSleep(size_t dwMilliseconds);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXThread();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool CreateThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void KillThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool WaitForThreadExit(size_t dwMilliSeconds);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	HANDLE GetHandle() const;
};


#endif // __CXTHREAD_HPP__
