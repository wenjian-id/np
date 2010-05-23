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


#ifndef __CXGPSDCLIENTNOVERSION_HPP__
#define __CXGPSDCLIENTNOVERSION_HPP__

#include <gps.h>

#ifndef GPSD_API_MAJOR_VERSION

#include "CXGPSDClientBase.hpp"
#include "CXLoopThread.hpp"
#include "CXMutex.hpp"

class CXGPSDClient;

class CXGPSDThread : public CXLoopThread {
private:
	CXGPSDClient	*m_pClient;		///< oiu
	gps_data_t		*m_pGPSData;	///< oiu
	CXMutex			m_Mutex;		///< Synchronisation object
	CXGPSDThread();
	CXGPSDThread(const CXGPSDThread &);
	const CXGPSDThread & operator = (const CXGPSDThread&);
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
	 * \brief oiu
	 *
	 */
	CXGPSDThread(CXGPSDClient *pClient);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual ~CXGPSDThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsOpen();
};

//----------------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class CXGPSDClient : public CXGPSDClientBase {
private:
	CXGPSDThread		*m_pThread;					///< oiu
	bool				m_oTerminating;				///< oiu
	mutable CXMutex		m_Mutex;					///< Synchronisation object
	//-------------------------------------
	CXGPSDClient(const CXGPSDClient &);						///< Not used.
	const CXGPSDClient & operator = (const CXGPSDClient &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	bool IsTerminating() const;
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void SetTerminating();
protected:
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void ReadSatelliteData(gps_data_t *pGPSData, CXBuffer<CXSatelliteInfo *> & rSatInfos, CXBuffer<int> & rActiveSats);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSDClient();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSDClient();
	//-------------------------------------
	/**
	 * \brief Open connection to gpsd.
	 *
	 * Open the connection to gpsd. Has to be implemented in derived classes.
	 * \return		true on success.
	 */
	virtual bool Open();
	//-------------------------------------
	/**
	 * \brief Close connection to gpsd.
	 *
	 * Close the connection to gpsd. Has to be implemented in derived classes.
	 * \return		true on success.
	 */
	virtual bool Close();
	//-------------------------------------
	/**
	 * \brief Check if connection is open.
	 *
	 * Check if the connection is open. Has to be implemented in derived classes.
	 * \return		true if open.
	 */
	virtual bool IsOpen();
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void ProcessData(gps_data_t *pGPSData);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual void Read();
};


#endif // GPSD_API_MAJOR_VERSION

#endif // __CXGPSDCLIENTNOVERSION_HPP__
