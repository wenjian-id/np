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

#ifndef __CXGPSINPUTCHANNELGPSD_HPP__
#define __CXGPSINPUTCHANNELGPSD_HPP__

#include "CXGPSInputChannel.hpp"
#include "CXGPSDClient.hpp"

//----------------------------------------------------------------------------
/**
 * \brief Class for reading data from GPSD.
 *
 * This class is used for reading data from GPSD.
 */
class CXGPSInputChannelGPSD : public CXGPSInputChannel {
private:
	CXGPSDClient		m_GPSDClient;	///< GPSD client
	//-------------------------------------
	CXGPSInputChannelGPSD(const CXGPSInputChannelGPSD &);						///< Not used.
	const CXGPSInputChannelGPSD & operator = (const CXGPSInputChannelGPSD &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSInputChannelGPSD();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSInputChannelGPSD();
	//-------------------------------------
	/**
	 * \brief Open channel.
	 *
	 * Open the GPS input channel.
	 * \return		true on success.
	 */
	virtual bool Open();
	//-------------------------------------
	/**
	 * \brief Close channel.
	 *
	 * Close the GPS input channel.
	 * \return		true on success.
	 */
	virtual bool Close();
	//-------------------------------------
	/**
	 * \brief Check if channel is open.
	 *
	 * Check if input channel is open.
	 * \return		true if open.
	 */
	virtual bool IsOpen();
	//-------------------------------------
	/**
	 * \brief Read configuration.
	 *
	 * Read the configuration.
	 * \return		true on success.
	 */
	virtual bool ReadConfiguration();
	//-------------------------------------
	/**
	 * \brief Check if flush allowed.
	 *
	 * Check if flush allowed. It is.
	 * \return		Always false.
	 */
	virtual bool CanFlush();
	//-------------------------------------
	/**
	 * \brief Read data.
	 *
	 * Read some data. Always return false
	 * \param		pbBuffer	Buffer for data.
	 * \param		Size		Size of buffer.
	 * \param		ReadSize	Size of actually read data.
	 * \return		true on success. 0 bytes read is also OK.
	 */
	virtual bool Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize);
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	virtual bool Read(CXGPSPosInfo &rGPSPosInfo, bool & roGPSPosInfoChanged, CXGPSCourseInfo &rGPSCourseInfo, bool & roGPSCourseInfoChanged, CXGPSQualityInfo &rGPSQualityInfo, bool & roGPSQualityInfoChanged);
};

#endif // __CXGPSINPUTCHANNELGPSD_HPP__
