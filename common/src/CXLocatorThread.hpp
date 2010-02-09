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

#ifndef __CXLOCATORTHREAD_HPP__
#define __CXLOCATORTHREAD_HPP__

#include "CXLoopThread.hpp"
#include "CXTimeStampData.hpp"
#include "CXBuffer.hpp"
#include "CXNaviData.hpp"
#include "CXExactTime.hpp"
#include "CXStringASCII.hpp"
#include "CXSpeedCalculator.hpp"
#include "CXMutex.hpp"

class CXNaviPOWM;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXLocatorThread : public CXLoopThread {
private:
	CXTimeStampData<tUCBuffer>		m_InputBufferGPSGGA;		///< oiu
	CXTimeStampData<tUCBuffer>		m_InputBufferGPSRMC;		///< oiu
	bool							m_oConnected;				///< oiu
	bool							m_oNewDataConnection;		///< oiu
	bool							m_oNewDataGPSGGA;			///< oiu
	bool							m_oNewDataGPSRMC;			///< oiu
	CXSpeedCalculator				m_SpeedCalculator;			///< oiu
	CXExactTime						m_LastReceivedPosition;		///< oiu
	CXNaviData						m_NaviData;					///< oiu
	CXCoor							m_LastReceivedCoor;			///< oiu
	CXCoor							m_StartCoordinates;			///< oiu
	bool							m_oGPSFixAtLeastOnce;		///< oiu
	bool							m_oStartCoordinatesValid;	///< oiu
	CXNaviPOWM						*m_pNaviPOWM;				///< oiu
	CXExactTime						m_StartTime;				///< starting time
	mutable CXMutex					m_MutexInputData;			///< Synchronization object for input data.
	mutable CXMutex					m_Mutex;					///< Synchronization object.
	//-------------------------------------
	CXLocatorThread(const CXLocatorThread&);						///< Not used.
	const CXLocatorThread & operator = (const CXLocatorThread&);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFlag_NewDataConnection(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFlag_NewDataGPSGGA(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFlag_NewDataGPSRMC(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool GetFlag_NewDataConnection() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool GetFlag_NewDataGPSGGA() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool GetFlag_NewDataGPSRMC() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXTimeStampData<tUCBuffer> GetGPSDataGGA() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXTimeStampData<tUCBuffer> GetGPSDataRMC() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Locate();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool LoadStartGPSCoordinates();
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStarted();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadLoop();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStopped();
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXLocatorThread();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXLocatorThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsConnected() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetConnected(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetGPSDataGGA(const tUCBuffer & Buffer);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetGPSDataRMC(const tUCBuffer & Buffer);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetGPSDataGSA(const tUCBuffer & Buffer);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetGPSDataGSV(const tUCBuffer & Buffer);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetNaviPOWM(CXNaviPOWM *pNaviPOWM);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SaveLastReceivedGPSCoordinate();
};


#endif // __CXLOCATORTHREAD_HPP__
