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

#include "CXGPSInputChannelFile.hpp"
#include "CXOptions.hpp"

//-------------------------------------
CXGPSInputChannelFile::CXGPSInputChannelFile() {
}

//-------------------------------------
CXGPSInputChannelFile::~CXGPSInputChannelFile() {
}

//-------------------------------------
bool CXGPSInputChannelFile::Open() {
	return m_File.Open(m_FileName.c_str(), CXFile::E_READ) == CXFile::E_OK;
}

//-------------------------------------
bool CXGPSInputChannelFile::Close() {
	m_File.Close();
	return true;
}

//-------------------------------------
bool CXGPSInputChannelFile::IsOpen() {
	return m_File.IsOpen();
}

//-------------------------------------
bool CXGPSInputChannelFile::ReadConfiguration() {
	// get file name
	m_FileName = CXOptions::Instance()->GetFileConfig().GetFileName();
	SetForcedTimeout(CXOptions::Instance()->GetFileConfig().GetTimeout());
	return true;
}

//-------------------------------------
bool CXGPSInputChannelFile::CanFlush() {
	return false;
}

//-------------------------------------
bool CXGPSInputChannelFile::Read(unsigned char *pbBuffer, size_t Size, size_t &ReadSize) {
	ReadSize = 0;
	if(pbBuffer == 0)
		return false;
	if(!IsOpen())
		return false;
	// read data
	if(!m_File.Read(pbBuffer, Size, ReadSize) == CXFile::E_OK)
		// read succeeded
		return false;
	if(ReadSize != 0) {
		return true;
	}
	// read failure. reopen file
	Close();
	Open();
	// read again
	return m_File.Read(pbBuffer, Size, ReadSize) == CXFile::E_OK;
}
