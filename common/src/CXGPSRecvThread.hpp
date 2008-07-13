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

#ifndef __CXGPSRECVTHREAD_HPP__
#define __CXGPSRECVTHREAD_HPP__

#include "CXLoopThread.hpp"
#include "CXBuffer.hpp"
#include "CXFile.hpp"
#include "CXExactTime.hpp"
#include <CXMutex.hpp>
#include <CXSerial.hpp>

class CXLocatorThread;

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXGPSRecvThread : public CXLoopThread {
private:
	CXSerial			m_Serial;		///< oiu
	bool				m_oDemoMode;	///< oiu
	CXFile				m_DemoFile;		///< oiu
	size_t				m_DemoTimeout;	///< oiu
	CXExactTime			m_LastDemoGGA;	///< oiu
	tUCBuffer			m_Buffer;		///< oiu
	tUCBuffer			m_LastPacket;	///< oiu
	CXLocatorThread		*m_pLocator;	///< oiu
	bool				m_oSaving;		///< oiu
	CXFile				m_SaveFile;		///< oiu
	mutable CXMutex		m_Mutex;		///< oiu
	//-------------------------------------
	CXGPSRecvThread(const CXGPSRecvThread &);						///< Not used.
	const CXGPSRecvThread & operator = (const CXGPSRecvThread &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void OpenSerial();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ReopenSerial();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void CloseSerial();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool ReceiveData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool ProcessData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool CheckGGA();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool CheckRMC();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool CheckGSA();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool CheckGSV();
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
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Save(const tUCBuffer & Buffer);
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXGPSRecvThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXGPSRecvThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsOpen() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLocator(CXLocatorThread *pLocator);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void FlushInput();
};


#endif // __CXGPSRECVTHREAD_HPP__
