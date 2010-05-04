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

#ifndef __CXGPSINPUTCHANNELFILE_HPP__
#define __CXGPSINPUTCHANNELFILE_HPP__

#include "CXGPSInputChannel.hpp"
#include "CXStringASCII.hpp"
#include "CXFile.hpp"

//----------------------------------------------------------------------------
/**
 * \brief Class for reading data from a file.
 *
 * This class is used for reading data from a file.
 */
class CXGPSInputChannelFile : public CXGPSInputChannel {
private:
	CXStringASCII	m_FileName;		///< File name.
	CXFile			m_File;			///< The file.
	//-------------------------------------
	CXGPSInputChannelFile(const CXGPSInputChannelFile &);						///< Not used.
	const CXGPSInputChannelFile & operator = (const CXGPSInputChannelFile &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	CXGPSInputChannelFile();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~CXGPSInputChannelFile();
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
	 * Check if flush allowed. It is not.
	 * \return		Always false.
	 */
	virtual bool CanFlush();
	//-------------------------------------
	/**
	 * \brief Read data.
	 *
	 * Read some data. If we reach the endof the file it will be reopened.
	 * \param		pbBuffer	Buffer for data.
	 * \param		Size		Size of buffer.
	 * \param		ReadSize	Size of actually read data.
	 * \return		true on success. 0 bytes read is also OK.
	 */
	virtual bool Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize);
};

#endif // __CXGPSINPUTCHANNELFILE_HPP__
