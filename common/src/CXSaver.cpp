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

#include "CXSaver.hpp"
#include "CXOptions.hpp"
#include "CXExactTime.hpp"

//-------------------------------------
CXSaver::CXSaver(const char *pcSuffix):
	m_oSaving(false),
	m_Suffix(pcSuffix)
{
}

//-------------------------------------
CXSaver::~CXSaver() {
}

//-------------------------------------
bool CXSaver::PrepareSaving() {
	// check to see if state changed
	if(m_oSaving != CXOptions::Instance()->IsSaving()) {
		// yes
		m_oSaving = CXOptions::Instance()->IsSaving();
		if(!m_oSaving) {
			// saving just turned off
			Close();
		} else {
			// saving just turned on
			// reset flag in case of error
			m_oSaving = false;

			// get current time
			CXExactTime Now;
			char buf[100];
			for(int i=0; i<100; i++) {
				snprintf(buf, 100, "%04d%02d%02d%02d.%s", Now.GetYear(), Now.GetMonth(), Now.GetDay(), i, m_Suffix.c_str());
				CXStringASCII FileName(CXOptions::Instance()->GetDirectorySave());
				FileName+=buf;

				// check if file already exists
				if(m_File.Open(FileName.c_str(), CXFile::E_READ) == CXFile::E_OK) {
					// yes. close it again.
					m_File.Close();
				} else {
					// no. open for writing
					m_File.Close();
					m_oSaving = m_File.Open(FileName.c_str(), CXFile::E_WRITE) == CXFile::E_OK;
					if(m_oSaving) {
						AfterOpen();
						break;
					}
				}
			}

		}
	}
	if(m_oSaving != CXOptions::Instance()->IsSaving()) {
		// some error occured
		CXOptions::Instance()->ToggleSaving();
	}
	return m_oSaving;
}

//-------------------------------------
bool CXSaver::Close() {
	if(m_File.IsOpen()) {
		BeforeClose();
		m_File.Close();
	}	
	return true;
}
