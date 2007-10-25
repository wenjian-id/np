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

#ifndef __CXLOCATORTHREAD_HPP__
#define __CXLOCATORTHREAD_HPP__

#include "CXLoopThread.hpp"
#include "CXBuffer.hpp"
#include "CXNaviData.hpp"
#include "CXExactTime.hpp"
#include "CXSpeedCalculator.hpp"

class CXNaviPOWM;

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXLocatorThread : public CXLoopThread {
private:
	tUCBuffer			m_InputBufferGPS;	///< oiu
	bool				m_oNewDataGPS;		///< oiu
	CXSpeedCalculator	m_SpeedCalculator;	///< oiu
	CXExactTime			mLastReceivedGPS;	///< oiu
	CXNaviData			m_NaviData;			///< oiu
	CXNaviPOWM			*m_pNaviPOWM;		///< oiu
	CXExactTime			m_StartTime;		///< starting time
	mutable CXMutex		m_MutexInputData;	///< oiu
	mutable CXMutex		m_Mutex;			///< oiu
	//-------------------------------------
	CXLocatorThread(const CXLocatorThread&);						///< Not used.
	const CXLocatorThread & operator = (const CXLocatorThread&);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetFlag_NewDataGPS(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool GetFlag_NewDataGPS() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tUCBuffer GetGPSDataGGA() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void OnNewDataGPS(const tUCBuffer & Buffer);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool Locate(t_uint64 &rProxWay);
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStarted();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnThreadLoop();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStopped();
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXLocatorThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXLocatorThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetGPSDataGGA(const tUCBuffer & Buffer);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetNaviPOWM(CXNaviPOWM *pNaviPOWM);
};


#endif // __CXLOCATORTHREAD_HPP__
