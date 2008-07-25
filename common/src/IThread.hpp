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

#ifndef __ITHREAD_HPP__
#define __ITHREAD_HPP__

#include <CXMutex.hpp>

//---------------------------------------------------------------------
/**
 * \brief Interface for thread class.
 *
 * Interface for thread class. Has to be implemented target specific
 */
class IThread {
private:
	bool			m_oRunning;		///< Flag indicating if thread is running
	bool			m_oStopThread;	///< Flag indicating that thread must stop ASAP
	mutable CXMutex	m_Mutex;		///< Synchronization object.
	//-------------------------------------
	IThread(const IThread&);						///< Not used.
	const IThread & operator = (const IThread&);	///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief Check if thread has to be stopped.
	 *
	 * Check if thread has to be stopped.
	 * \return	true if thread must stop.
	 */
	bool MustStopThread() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStarted() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int OnThreadFunc() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStopped() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DoSleep(size_t dwMilliSeconds) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int ThreadFunc();
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	IThread();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~IThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void StopThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool CreateThread() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool IsRunning() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void SetRunning(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool WaitForThreadExit(size_t dwMilliSeconds) = 0;
};


#endif // __ITHREAD_HPP__
