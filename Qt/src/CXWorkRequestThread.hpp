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

#ifndef __CXWORKREQUESTTHREAD_HPP__
#define __CXWORKREQUESTTHREAD_HPP__

#include <IWorkRequestThread.hpp>

#include <qwaitcondition.h>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXWorkRequestThread : public IWorkRequestThread {
private:
	QWaitCondition	m_WaitCondition;	///< oiu
	QMutex			m_Mutex;			///< Synchronization object.
	//-------------------------------------
	CXWorkRequestThread(const CXWorkRequestThread &);							///< Not used.
	const CXWorkRequestThread & operator = (const CXWorkRequestThread &);		///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DoWait();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void Wakeup();
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXWorkRequestThread();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXWorkRequestThread();
};


#endif // __CXWORKREQUESTTHREAD_HPP__
