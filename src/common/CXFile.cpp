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

#include "CXFile.hpp"

static const size_t MaxBufferSize = 100000;
static const size_t MinBufferSize = 10;


//----------------------------------------------------------------------------
//-------------------------------------
CXFile::CXFile() :
	m_File(NULL),
	m_pBuffer(NULL),
	m_ReadAheadSize(MinBufferSize),
	m_BufferedSize(0),
	m_BufferOffset(0)
{
}

//-------------------------------------
CXFile::~CXFile() {
	Clear();
}

//-------------------------------------
void CXFile::Clear() {
	delete [] m_pBuffer;
	m_pBuffer = NULL;
	Close();
}

//-------------------------------------
void CXFile::ReallocateReadAheadBuffer() {
	// delete old buffer
	delete [] m_pBuffer;
	m_pBuffer = NULL;
	// reallocate buffer
	m_pBuffer = new unsigned char [m_ReadAheadSize];
}

//-------------------------------------
CXFile::E_RESULTCODE CXFile::SetReadAheadSize(size_t ReadAheadSize) {
	// check if open
	if(IsOpen())
		return E_FILE_OPEN;
	// check argument
	if((ReadAheadSize > MaxBufferSize) || (ReadAheadSize < MinBufferSize))
		return E_INVALID_ARG;
	if(ReadAheadSize == m_ReadAheadSize)
		return E_OK;
	// set new value
	m_ReadAheadSize = ReadAheadSize;
	// and reallocate buffer
	ReallocateReadAheadBuffer();
	return E_OK;
}

//-------------------------------------
CXFile::E_RESULTCODE CXFile::Open(const char *pcFileName, E_OPENMODE eMode) {
	// check if already open
	if(IsOpen())
		return E_FILE_OPEN;
	// check argument
	if(pcFileName == NULL)
		return E_INVALID_ARG;
	// try to open
	const char *pcMode = "";
	switch(eMode) {
		case E_READ:	pcMode = "rb"; break;
		case E_WRITE:	pcMode = "wb"; break;
		default:		return E_UNSUPPORTED_OPENMODE;
	}
	// check if read ahead buffer has to be allocated
	if(m_pBuffer == NULL)
		ReallocateReadAheadBuffer();
	// open the file
	m_File = fopen(pcFileName, pcMode);
	// check result
	if(m_File == NULL)
		return E_OPEN_ERROR;
	fseek(m_File, 0, SEEK_SET);
	// everything seems to be OK
	return E_OK;
}

//-------------------------------------
void CXFile::Close() {
	if(m_File != NULL) {
		fclose(m_File);
	}
	m_File = NULL;
}

//-------------------------------------
bool CXFile::IsOpen() const {
	return m_File != NULL;
}

//-------------------------------------
CXFile::E_RESULTCODE CXFile::Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize) {
	// check already open
	if(!IsOpen())
		return E_FILE_NOT_OPEN;
	// check argument
	if(pbBuffer == NULL)
		return E_INVALID_ARG;
	ReadSize = 0;
	size_t BufferOffset = 0;
	// read and copy data
	bool Loop = Size > 0;
	while(Loop) {
		// compute amount to copy from buffered data
		size_t CopySize = 0;
		if(Size <= m_BufferedSize) {
			// enaugh data in buffer
			CopySize = Size;
		} else {
			// not enaugh data in buffer
			CopySize = m_BufferedSize;
		}
		// copy data from buffer
		memcpy(pbBuffer+BufferOffset, m_pBuffer+m_BufferOffset, CopySize);
		m_BufferedSize -= CopySize;
		m_BufferOffset += CopySize;
		BufferOffset += CopySize;
		ReadSize += CopySize;
		Size -= CopySize;
		// check if more data to be read from file
		if(Size > 0) {
			// more data to copy, so try to read from file to buffer
			size_t ToRead = m_ReadAheadSize;
			/// \todo error handling
			size_t Read = fread(m_pBuffer, sizeof(unsigned char), ToRead, m_File);
			// adjust offsets
			m_BufferOffset = 0;
			m_BufferedSize = Read;
			if(Read == 0)
				// exit loop
				Loop = false;
		}
		// check if exit loop
		Loop = Loop && Size > 0;
	}
	return E_OK;
}

//-------------------------------------
CXFile::E_RESULTCODE CXFile::Write(const unsigned char *pbBuffer, size_t Size, size_t &WriteSize) {
	// check already open
	if(!IsOpen())
		return E_FILE_NOT_OPEN;
	// check argument
	if(pbBuffer == NULL)
		return E_INVALID_ARG;
	/// \todo error handling
	WriteSize = fwrite(pbBuffer, sizeof(unsigned char), Size, m_File);
	return E_OK;
}

//-------------------------------------
CXFile::E_RESULTCODE CXFile::Seek(size_t Offset) {
	if(!IsOpen())
		return E_FILE_NOT_OPEN;
	// invalidate m_pBuffer
	m_BufferedSize = 0;
	// do seek
	if(fseek(m_File, Offset, SEEK_SET) != 0) {
		return E_SEEK_ERROR;
	}
	return E_OK;
}
