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

#ifndef __IWORKREQUESTTHREAD_HPP__
#define __IWORKREQUESTTHREAD_HPP__

#include <CXMutex.hpp>
#include <CXThread.hpp>

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class IWorkRequestThread : public CXThread {
private:
	mutable CXMutex		m_Mutex;			///< oiu
	//-------------------------------------
	IWorkRequestThread(const IWorkRequestThread &);							///< Not used.
	const IWorkRequestThread & operator = (const IWorkRequestThread &);		///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int OnThreadFunc();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnWorkFunc() = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void DoWait() = 0;
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	IWorkRequestThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~IWorkRequestThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 * we must overload it to exit waiting
	 */
	virtual void StopThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void RequestWork() = 0;
};


#endif // __IWORKREQUESTTHREAD_HPP__
