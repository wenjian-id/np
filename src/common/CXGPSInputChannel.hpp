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

#ifndef __CXGPSINPUTCHANNEL_HPP__
#define __CXGPSINPUTCHANNEL_HPP__

#include "CXGPSPosInfo.hpp"
#include "CXGPSCourseInfo.hpp"
#include "CXGPSQualityInfo.hpp"
#include "Utils.hpp"


//----------------------------------------------------------------------------
/**
 * \brief Base class for a GPS input channel.
 *
 * This class is the base class for a GPS input channel. It has methods to open,
 * close and read data.
 */
class CXGPSInputChannel {
private:
    size_t      m_ForcedTimeout;        ///< Forced timout. Used to stop processing data if new UTC read.
    //-------------------------------------
    CXGPSInputChannel(const CXGPSInputChannel &);                       ///< Not used.
    const CXGPSInputChannel & operator = (const CXGPSInputChannel &);   ///< Not used.
protected:
    //-------------------------------------
    /**
     * \brief Set forced timeout.
     *
     * Set forced timeout in ms.
     * \param   NewValue    New timeout [ms].
     */
    void SetForcedTimeout(int NewValue);
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * The default constructor.
     */
    CXGPSInputChannel();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * The destructor.
     */
    virtual ~CXGPSInputChannel();
    //-------------------------------------
    /**
     * \brief Open channel.
     *
     * Open the GPS input channel. Has to be implemented in derived classes.
     * \return      true on success.
     */
    virtual bool Open()=0;
    //-------------------------------------
    /**
     * \brief Close channel.
     *
     * Close the GPS input channel. Has to be implemented in derived classes.
     * \return      true on success.
     */
    virtual bool Close()=0;
    //-------------------------------------
    /**
     * \brief Check if channel is open.
     *
     * Check if input channel is open. Has to be implemented in derived classes.
     * \return      true if open.
     */
    virtual bool IsOpen()=0;
    //-------------------------------------
    /**
     * \brief Read configuration.
     *
     * Read configuration. Has to be implemented in derived classes.
     * \return      true on success.
     */
    virtual bool ReadConfiguration() = 0;
    //-------------------------------------
    /**
     * \brief Check if flush allowed.
     *
     * Check if flush allowed. Has to be implemented in derived classes.
     * \return      true if allowed.
     */
    virtual bool CanFlush()=0;
    //-------------------------------------
    /**
     * \brief Read data into a buffer.
     *
     * Read some data into a buffer. Has to be implemented in derived classes.
     * \param       pbBuffer    Buffer for data.
     * \param       Size        Size of buffer.
     * \param       ReadSize    Size of actually read data.
     * \return      true on success. 0 bytes read is also OK.
     */
    virtual bool Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize) = 0;
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    virtual bool Read(CXGPSPosInfo &rGPSPosInfo, bool & roGPSPosInfoChanged, CXGPSCourseInfo &rGPSCourseInfo, bool & roGPSCourseInfoChanged, CXGPSQualityInfo &rGPSQualityInfo, bool & roGPSQualityInfoChanged) = 0;
    //-------------------------------------
    /**
     * \brief Get forced timeout.
     *
     * get forced timeout in ms.
     * \return      Timeout [ms].
     */
    size_t GetForcedTimeout() const;
};

#endif // __CXGPSINPUTCHANNEL_HPP__
