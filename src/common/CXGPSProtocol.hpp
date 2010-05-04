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

#ifndef __CXGPSPROTOCOL_HPP__
#define __CXGPSPROTOCOL_HPP__

#include "CXGPSInputChannel.hpp"
#include "CXExactTime.hpp"
#include "CXGPSPosInfo.hpp"
#include "CXGPSCourseInfo.hpp"
#include "CXGPSQualityInfo.hpp"
#include "CXSaverRaw.hpp"
#include "CXSaverGPX.hpp"
#include "CXMutex.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSProtocol {
public:
		//-------------------------------------
		/**
		 * \brief oiu
		 *
		 * oiu
		 */
	enum E_RECEIVED_DATA_TYPE {
		e_RcvPosInfo		= 0x01,		///< oiu
		e_RcvCourseInfo		= 0x02,		///< oiu
		e_RcvQualityInfo	= 0x04,		///< oiu
	};
private:
		//-------------------------------------
		/**
		 * \brief oiu
		 *
		 * oiu
		 */
	enum E_BUFFERED_DATA_TYPE {
		e_BufNone,				///< oiu
		e_BufPosInfo,			///< oiu
		e_BufCourseInfo,		///< oiu
	};
private:
	bool						m_oInTimeout;					///< oiu
	unsigned char				m_ReceivedDataTypes;			///< oiu
	E_BUFFERED_DATA_TYPE		m_eBufferedDataType;			///< oiu
	CXStringASCII				m_LastReceivedUTC;				///< oiu
	CXExactTime					m_LastReceivedDataTimeStamp;	///< oiu
	tTimeStampedGPSPosInfo		m_GPSPosInfo;					///< oiu
	CXGPSPosInfo				m_BufferedGPSPosInfo;			///< oiu
	tTimeStampedGPSCourseInfo	m_GPSCourseInfo;				///< oiu
	CXGPSCourseInfo				m_BufferedGPSCourseInfo;		///< oiu
	tTimeStampedGPSQualityInfo	m_GPSQualityInfo;				///< oiu
	CXSaverRaw					m_SaverRaw;						///< oiu
	CXSaverGPX					m_SaverGPX;						///< oiu
	mutable CXMutex				m_Mutex;						///< Synchronization object.
	//-------------------------------------
	CXGPSProtocol(const CXGPSProtocol &);						///< Not used.
	const CXGPSProtocol & operator = (const CXGPSProtocol &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void ProcessGPSPosInfo(const CXGPSPosInfo &GPSPosInfo);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void ProcessGPSCourseInfo(const CXGPSCourseInfo &GPSCourseInfo);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void ProcessGPSQualityInfo(const CXGPSQualityInfo &GPSQualityInfo);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool SavingAllowed(CXFile &rSaveFile, const char *pcSuffix);
protected:
	CXGPSInputChannel	*m_pInputChannel;			///< oiu
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool AfterOpen() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool BeforeClose() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool OnReadAndProcessData() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SetGPSPosInfo(const CXGPSPosInfo &GPSPosInfo);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SetGPSCourseInfo(const CXGPSCourseInfo &GPSCourseInfo);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SetGPSQualityInfo(const CXGPSQualityInfo &GPSQualityInfo);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SaveRawData(unsigned char *pbBuffer, size_t DataLength);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SaveGPXData(double dLon, double dLat, double dHeight);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSProtocol();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSProtocol();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SetInputChannel(CXGPSInputChannel *pInputChannel);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	unsigned char GetReceivedDataTypes() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void ClearReceivedDataType(E_RECEIVED_DATA_TYPE eDataType);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	tTimeStampedGPSPosInfo GetGPSPosInfo() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	tTimeStampedGPSCourseInfo GetGPSCourseInfo() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	tTimeStampedGPSQualityInfo GetGPSQualityInfo() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool Open();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool Close();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool IsOpen();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void FlushInput();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool ReadAndProcessData();
};

#endif // __CXGPSPROTOCOL_HPP__
