/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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

#include "Utils.hpp"

#include  <stdlib.h>

//-------------------------------------
bool ReadLineASCII(CXFile & rInFile, CXStringASCII & rNewLine) {
	unsigned char c;
	// reset value
	rNewLine.Empty();
	for(;;){
		// read next character
		if(!ReadB(rInFile, c)) {
			if(rNewLine.IsEmpty()) {
				return false;
			}
			// OK, we have a new line
			return true;
		}
		// check for end line
		if(c == '\n') {
			// end of line reached
			return true;
		}
		// do not append '\r'
		if(c != '\r') {
			rNewLine.Append(static_cast<char>(c));
		}
	}
	// something went wrong.
	return false;
}

//-------------------------------------
bool ReadB(CXFile & rInFile, unsigned char & rValue) {
	// reset value
	rValue = 0;
	size_t r = 0;
	// try to read one byte
	if(rInFile.Read(&rValue, 1, r) != CXFile::E_OK) {
		// read failed
		return false;
	}
	// check if one byte read
	return r == 1;
}

//-------------------------------------
bool ReadUL32(CXFile & rInFile, unsigned long & rValue) {
	// reset value
	rValue = 0;
	unsigned char buf[4];
	size_t r = 0;
	// try to read 4 bytes
	if(rInFile.Read(buf, 4, r) != CXFile::E_OK) {
		// read failed
		return false;
	}
	if(r != 4) {
		// no 4 bytes read
		return false;
	}
	// compute result in a platform independant way
	rValue = 0;
	rValue = (rValue << 8) + buf[0];
	rValue = (rValue << 8) + buf[1];
	rValue = (rValue << 8) + buf[2];
	rValue = (rValue << 8) + buf[3];
	// everything ok
	return true;
}

//-------------------------------------
bool ReadI64(CXFile & rInFile, t_uint64 & rValue) {
	// reset value
	rValue = 0;
	unsigned char buf[8];
	size_t r = 0;
	// try to read 8 bytes
	if(rInFile.Read(buf, 8, r) != CXFile::E_OK) {
		// read failed
		return false;
	}
	if(r != 8) {
		// no 8 bytes read
		return false;
	}
	// compute result in a platform independant way
	rValue = 0;
	rValue = (rValue << 8) + buf[0];
	rValue = (rValue << 8) + buf[1];
	rValue = (rValue << 8) + buf[2];
	rValue = (rValue << 8) + buf[3];
	rValue = (rValue << 8) + buf[4];
	rValue = (rValue << 8) + buf[5];
	rValue = (rValue << 8) + buf[6];
	rValue = (rValue << 8) + buf[7];
	// everything ok
	return true;
}

//-------------------------------------
bool ReadStringUTF8(CXFile & rInFile, CXStringUTF8 & rValue) {
	unsigned char c = 0;
	// reset value
	rValue.Empty();
	do {
		// read next byte
		if(!ReadB(rInFile, c)) {
			// read error
			return false;
		}
		// check for terminating 0
		if(c!=0) {
			// Normal data. Append to string data.
			rValue.Append(c);
		}
	} while(c!=0);
	// everything ok
	return true;
}

//-------------------------------------
bool ExtractGGAData(const CXStringASCII &Line, double & rLon, double & rLat, double & rHeight, int &rnSat) {
	// check if this line contains a GGA packet

	// length must be greater than 11 $ G P G G A * x x CR LF
	if(Line.GetSize() < 11)
		return false;

	// the first 6 characters must be "$CPGGA"
	if(Line.Find("$GPGGA") != 0) {
		return false;
	}

	// count colons
	int iCount = 0;
	for(size_t i=0; i<Line.GetSize(); i++)
		if(Line[i] == ',')
			iCount++;
	if(iCount != 14)
		return false;

	// now check CRC
	int iCRC = 0;
	// CRC are te last two characters before CRLF, starting after '$'
	for(size_t j=1; j<Line.GetSize()-3; j++)
		iCRC ^= Line[j];

	// read CRC from packet
	int iReadCRC = 0;
	char tmp[3] = {Line[Line.GetSize()-2], Line[Line.GetSize()-1], 0};
	sscanf(tmp, "%x", &iReadCRC);
	if(iCRC != iReadCRC) {
		// CRC error
		return false;
	}

	// OK, GGA-Paket seems to be complete
	// now extract data
	CXStringASCII s = Line;
	// remove $GGA
	ExtractFirstToken(s, ',');
	// UTC
	ExtractFirstToken(s, ',');
	// read latitude
	CXStringASCII SLat = ExtractFirstToken(s, ',');
	double dLat = 0;
	sscanf(SLat.c_str(), "%lf", &dLat);
	CXStringASCII strLat = ExtractFirstToken(s, ',');
	if((strLat != "N") && (strLat != "n") && (strLat != "S") && (strLat != "s"))
		return false;
	// read longitude
	CXStringASCII SLon = ExtractFirstToken(s, ',');
	double dLon = 0;
	sscanf(SLon.c_str(), "%lf", &dLon);
	CXStringASCII strLon = ExtractFirstToken(s, ',');
	if((strLon != "E") && (strLon != "e") && (strLon != "W") && (strLon != "w"))
		return false;

	// quality
	int quality = atoi(ExtractFirstToken(s, ',').c_str());
	// nr satellites
	rnSat = atoi(ExtractFirstToken(s, ',').c_str());
	// HDOP
	ExtractFirstToken(s, ',');
	// height
	sscanf(ExtractFirstToken(s, ',').c_str(), "%lf", &rHeight);
	// ignore
	ExtractFirstToken(s, ',');
	// HOG
	ExtractFirstToken(s, ',');
	// ignore
	ExtractFirstToken(s, ',');
	// DGPSTime
	ExtractFirstToken(s, ',');
	// StationID
	ExtractFirstToken(s, ',');

	unsigned char cLat = strLat[0];
	if((cLat == 's') || (cLat == 'S'))
		dLat = -dLat;
	unsigned char cLon = strLon[0];
	if((cLon == 'w') || (cLon == 'W'))
		dLon = -dLon;
	
	// transform to decimal degrees
	LLGMDToG(dLon, dLat, rLon, rLat);

	bool oReturn = true;
	// check for invalid quality
	if(quality == 0)
		oReturn = false;

	return oReturn;
}

//-------------------------------------
CXStringASCII ExtractFirstToken(CXStringASCII &rString, const char cTokenChar) {
	CXStringASCII result;
	// find first occurence of token delimiter
	size_t pos = rString.Find(cTokenChar);
	if(pos == CXStringASCII::NPOS) {
		// Not found. Take complete string.
		result = rString;
		// empty rString
		rString.Empty();
	} else {
		// take first pos characters
		result = rString.Left(pos);
		// delete from rString including delimiter
		rString.DeleteFirst(pos+1);
	}
	return result;
}

//-------------------------------------
void LLGMDToG(const double dLon, const double dLat, double & rdLon, double & rdLat) {
	// convert latitude
	long lDeg = static_cast<long>(dLat/100);
	double dMinute = dLat - (lDeg * 100);
	rdLat = lDeg + (dMinute / 60); 
	// convert longitude
	lDeg = static_cast<long>(dLon/100);
	dMinute = dLon - (lDeg * 100);
	rdLon = lDeg + (dMinute / 60); 
}
