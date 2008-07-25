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
#include <TargetIncludes.hpp>

#include <qthread.h>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXThread : public IThread {
friend class CXThreadHelper;
private:
	//---------------------------------------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	class CXThreadHelper : public QThread {
	private:
		CXThread		*m_pThread;		///< oiu
		//-------------------------------------
		CXThreadHelper(const CXThreadHelper &);							///< Not used.
		const CXThreadHelper & operator = (const CXThreadHelper &);		///< Not used.
	protected:
	public:
		//-------------------------------------
		/**
		 * \brief oiu
		 *
		 */
		CXThreadHelper(CXThread *pThread);
		//-------------------------------------
		/**
		 * \brief Destructor.
		 *
		 * Destructor.
		 */
		virtual ~CXThreadHelper();
		//-------------------------------------
		/**
		 * \brief oiu
		 *
		 */
		void run();
		//-------------------------------------
		/**
		 * \brief oiu
		 *
		 */
		void DoSleep(size_t dwMilliSeconds);
	};
private:
	CXThreadHelper		m_ThreadHelper;		///< oiu
	//-------------------------------------
	CXThread(const CXThread &);							///< Not used.
	const CXThread & operator = (const CXThread &);		///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DoSleep(size_t dwMilliSeconds);
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
	bool WaitForThreadExit(size_t dwMilliSeconds);
};


#endif // __CXTHREAD_HPP__
