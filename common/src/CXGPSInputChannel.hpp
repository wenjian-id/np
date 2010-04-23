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

#include "Utils.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSInputChannel {
private:
	size_t		m_ForcedTimeout;		///< oiu
	//-------------------------------------
	CXGPSInputChannel(const CXGPSInputChannel &);						///< Not used.
	const CXGPSInputChannel & operator = (const CXGPSInputChannel &);	///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	void SetForcedTimeout(int NewValue);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGPSInputChannel();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGPSInputChannel();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool Open()=0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool Close()=0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool IsOpen()=0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool ReadConfiguration() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool CanFlush()=0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual bool Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	size_t GetForcedTimeout() const;
};

#endif // __CXGPSINPUTCHANNEL_HPP__
