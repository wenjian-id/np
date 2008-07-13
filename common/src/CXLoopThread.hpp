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

#ifndef __CXLOOPTHREAD_HPP__
#define __CXLOOPTHREAD_HPP__

#include <CXMutex.hpp>
#include <CXThread.hpp>

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXLoopThread : public CXThread {
private:
	size_t				m_SleepTime;	///< oiu
	mutable CXMutex		m_Mutex;		///< oiu
	//-------------------------------------
	CXLoopThread(const CXLoopThread &);							///< Not used.
	const CXLoopThread & operator = (const CXLoopThread &);		///< Not used.
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
	virtual void OnThreadLoop() = 0;
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSleepTime(size_t SleepTime);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetSleepTime() const;
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXLoopThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXLoopThread();
};


#endif // __CXLOOPTHREAD_HPP__
