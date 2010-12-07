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

#include "CXSaverGPX.hpp"
#include "CXExactTime.hpp"
#include "Utils.hpp"

//-------------------------------------
CXSaverGPX::CXSaverGPX():
    CXSaver("gpx")
{
    m_GPXHeader += "<?xml version=\"1.0\" standalone=\"yes\"?>\r\n";
    m_GPXHeader += "<gpx version=\"1.1\" creator=\"NaviPOWM - http://sourceforge.net/projects/navipowm\"\r\n";
    m_GPXHeader += "   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\r\n";
    m_GPXHeader += "   xmlns=\"http://www.topografix.com/GPX/1/1\"\r\n";
    m_GPXHeader += "   xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">\r\n";
    m_GPXHeader += "<trk>\r\n<trkseg>\r\n";

    m_GPXFooter += "</trkseg>\r\n</trk>\r\n</gpx>\r\n";
}

//-------------------------------------
CXSaverGPX::~CXSaverGPX() {
    // close
    Close();
}

//-------------------------------------
void CXSaverGPX::AfterOpen() {
    // write header
    size_t WriteSize = 0;
    m_File.Write(reinterpret_cast<const unsigned char *>(m_GPXHeader.c_str()), m_GPXHeader.GetSize(), WriteSize);
}

//-------------------------------------
void CXSaverGPX::BeforeClose() {
    // write footer
    size_t WriteSize = 0;
    m_File.Write(reinterpret_cast<const unsigned char *>(m_GPXFooter.c_str()), m_GPXFooter.GetSize(), WriteSize);
}

//-------------------------------------
bool CXSaverGPX::Write(double dLon, double dLat, double dHeight) {
    size_t Written = 0;
    // do save some preparations
    if(!PrepareSaving())
        return false;
    // now save data
    // save trkpt
    CXExactTime Now;
    CXStringASCII Buf = CXStringASCII("<trkpt lon=\"") +
                        FToA<CXStringASCII>(dLon, 1, 6) +  "\" lat=\"" +
                        FToA<CXStringASCII>(dLat, 1, 6) +  "\"> <ele>" +
                        FToA<CXStringASCII>(dHeight, 1, 2) +  "</ele> <time>" +
                        IToA<CXStringASCII>(Now.GetYear(), 4) + "-" +
                        IToA<CXStringASCII>(Now.GetMonth(), 2) + "-" +
                        IToA<CXStringASCII>(Now.GetDay(), 2) + "T" +
                        IToA<CXStringASCII>(Now.GetHour(), 2) + ":" +
                        IToA<CXStringASCII>(Now.GetMinute(), 2) + ":" +
                        IToA<CXStringASCII>(Now.GetSecond(), 2) + "Z</time></trkpt>\r\n";
    if(m_File.Write((const unsigned char *)Buf.c_str(), Buf.GetSize(), Written) != CXFile::E_OK)
        return false;
    return true;
}
