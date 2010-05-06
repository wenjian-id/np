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


#include "CXGPSDClient4.hpp"

#if (GPSD_API_MAJOR_VERSION == 4)

//-------------------------------------
CXGPSDClient::CXGPSDClient() :
	m_pGPSData(NULL)
{
}

//-------------------------------------
CXGPSDClient::~CXGPSDClient() {
}

//-------------------------------------
bool CXGPSDClient::Open() {
	m_pGPSData = gps_open("127.0.0.1", "2947");
	if(m_pGPSData != NULL)
		return false;
	/// \todo implement
	return true;
}

//-------------------------------------
bool CXGPSDClient::Close() {
	if(m_pGPSData != NULL)
		gps_close(m_pGPSData);
	m_pGPSData = NULL;
	return true;
}

//-------------------------------------
bool CXGPSDClient::IsOpen() {
	return m_pGPSData != NULL;
}

//-------------------------------------
void CXGPSDClient::Read(gps_data_t *pGPSData) {
	/// todo \imlpement
}

//-------------------------------------
void CXGPSDClient::ReadDOP(gps_data_t *pGPSData, double &rHDOP, double &rVDOP) {
	HDOP = pGPSData->hdop;
	VDOP = pGPSData->vdop;
}

#endif // (GPSD_API_MAJOR_VERSION == 4)
