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

#ifndef __CXFILE_HPP__
#define __CXFILE_HPP__

#include <TargetIncludes.hpp>
#include <CXStringASCII.hpp>
#include <stdio.h>

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXFile {
public:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    enum E_RESULTCODE {
        E_OK,                       ///< oiu
        E_INVALID_ARG,              ///< oiu
        E_UNSUPPORTED_OPENMODE,     ///< oiu
        E_OPEN_ERROR,               ///< oiu
        E_FILE_NOT_OPEN,            ///< oiu
        E_FILE_OPEN,                ///< oiu
        E_SEEK_ERROR,               ///< oiu
    };
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    enum E_OPENMODE {
        E_READ,         ///< oiu
        E_WRITE,        ///< oiu
    };
private:
    FILE            *m_File;            ///< oiu
    unsigned char   *m_pBuffer;         ///< oiu
    size_t          m_ReadAheadSize;    ///< oiu
    size_t          m_BufferedSize;     ///< oiu
    size_t          m_BufferOffset;     ///< oiu
    //-------------------------------------
    CXFile(const CXFile &);                         ///< Not used.
    const CXFile & operator = (const CXFile &);     ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Clear();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void ReallocateReadAheadBuffer();
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXFile();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXFile();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_RESULTCODE SetReadAheadSize(size_t ReadAheadSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_RESULTCODE Open(const char *pcFileName, E_OPENMODE eMode);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Close();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool IsOpen() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_RESULTCODE Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_RESULTCODE Write(const unsigned char *pbBuffer, size_t Size, size_t &WriteSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_RESULTCODE Seek(size_t Offset);
};

#endif // __CXFILE_HPP__
