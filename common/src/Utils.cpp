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

#include "Utils.hpp"
#include "CXCoor.hpp"
#include "CXNMEA.hpp"
#include "OSSpecific.hpp"

#include  <stdlib.h>
#include  <math.h>

static const char *pcGGABEGIN			= "$GPGGA";
static const char *pcRMCBEGIN			= "$GPRMC";
static const char *pcGSABEGIN			= "$GPGSA";
static const char *pcGSVBEGIN			= "$GPGSV";

//-------------------------------------
CXStringASCII CreateAbsolutePath(const CXStringASCII & StartPath, const CXStringASCII &Path) {
	CXStringASCII Result = CreateAbsoluteFileName(StartPath, Path);
	// append PATHDELIMITER if neccessary
	if((Result.GetSize() > 0) && (Result[Result.GetSize()-1] != PATHDELIMITER)) {
		Result+=PATHDELIMITER;
	}
	return Result;
}

//-------------------------------------
CXStringASCII CreateAbsoluteFileName(const CXStringASCII & StartPath, const CXStringASCII &FileName) {
	CXStringASCII Result;
	if((FileName.GetSize() >= 1) && (FileName[0] == PATHDELIMITER)) {
		// FileName is an absolute name already. use it
		Result = FileName;
	} else {
		// FileName is a relative path. Append to StartPath.
		Result = StartPath;
		Result += FileName;
	}
	return Result;
}


//-------------------------------------
bool ReadLineASCII(CXFile & rInFile, CXStringASCII & rNewLine) {
	unsigned char c;
	// reset value
	rNewLine.Empty();
	for(;;){
		// read next character
		if(!ReadUI8(rInFile, c)) {
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
bool ReadUI(CXFile & rInFile, E_BIT_COUNT eBitCount, t_uint32 & rValue) {
	bool Result = false;
	switch(eBitCount) {
		case e_BC_8:	{
							unsigned char cValue = 0;
							Result = ReadUI8(rInFile, cValue);
							rValue = cValue;
							break;
						}
		case e_BC_16:	{
							t_uint16 usValue = 0;
							Result = ReadUI16(rInFile, usValue);
							rValue = usValue;
							break;
						}
		case e_BC_24:	Result = ReadUI24(rInFile, rValue); break;
		case e_BC_32:	Result = ReadUI32(rInFile, rValue); break;
	}
	return Result;
}


//-------------------------------------
bool ReadUI8(CXFile & rInFile, unsigned char & rValue) {
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
bool ReadUI16(CXFile & rInFile, t_uint16 & rValue) {
	// reset value
	rValue = 0;
	unsigned char buf[2];
	size_t r = 0;
	// try to read 2 bytes
	if(rInFile.Read(buf, 2, r) != CXFile::E_OK) {
		// read failed
		return false;
	}
	if(r != 2) {
		// no 2 bytes read
		return false;
	}
	// compute result in a platform independant way
	rValue = 0;
	rValue = (rValue << 8) + buf[0];
	rValue = (rValue << 8) + buf[1];
	// everything ok
	return true;
}

//-------------------------------------
bool ReadUI24(CXFile & rInFile, t_uint32 & rValue) {
	// reset value
	rValue = 0;
	unsigned char buf[3];
	size_t r = 0;
	// try to read 4 bytes
	if(rInFile.Read(buf, 3, r) != CXFile::E_OK) {
		// read failed
		return false;
	}
	if(r != 3) {
		// no 3 bytes read
		return false;
	}
	// compute result in a platform independant way
	rValue = 0;
	rValue = (rValue << 8) + buf[0];
	rValue = (rValue << 8) + buf[1];
	rValue = (rValue << 8) + buf[2];
	// everything ok
	return true;
}

//-------------------------------------
bool ReadUI32(CXFile & rInFile, t_uint32 & rValue) {
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
bool WriteUI32(CXFile & rOutFile, t_uint32 Value) {
	unsigned char buf[4];
	buf[0] = static_cast<unsigned char>((Value & 0xff000000) >> 24);
	buf[1] = static_cast<unsigned char>((Value & 0x00ff0000) >> 16);
	buf[2] = static_cast<unsigned char>((Value & 0x0000ff00) >> 8);
	buf[3] = static_cast<unsigned char>(Value & 0x000000ff);
	size_t WriteSize=0;
	if(rOutFile.Write(buf, sizeof(buf), WriteSize) != CXFile::E_OK)
		return false;
	if(WriteSize != sizeof(buf))
		return false;
	return true;
}

//-------------------------------------
bool ReadUI64(CXFile & rInFile, t_uint64 & rValue) {
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
		if(!ReadUI8(rInFile, c)) {
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
bool CheckNMEACRC(const CXStringASCII &NMEAPacket) {
	// now check CRC
	int iCRC = 0;
	// CRC are te last two characters before CRLF, starting after '$'
	for(size_t j=1; j<NMEAPacket.GetSize()-3; j++)
		iCRC ^= NMEAPacket[j];

	// read CRC from packet
	int iReadCRC = 0;
	char tmp[3] = {NMEAPacket[NMEAPacket.GetSize()-2], NMEAPacket[NMEAPacket.GetSize()-1], 0};
	sscanf(tmp, "%x", &iReadCRC);
	if(iCRC != iReadCRC) {
		// CRC error
		return false;
	}
	return true;
}

//-------------------------------------
bool ExtractGGAData(const CXStringASCII &NMEAPacket, CXGGAPacket & rGGAPacket) {
	// check if this NMEAPacket contains a GGA packet
	rGGAPacket.SetFix(false);
	bool oFix = false;

	// length must be greater than 11 $ G P G G A * x x CR LF
	if(NMEAPacket.GetSize() < 11)
		return false;

	// the first 6 characters must be "$CPGGA"
	if(NMEAPacket.Find(pcGGABEGIN) != 0) {
		return false;
	}

	// count colons
	int iCount = 0;
	for(size_t i=0; i<NMEAPacket.GetSize(); i++)
		if(NMEAPacket[i] == ',')
			iCount++;
	if(iCount != 14)
		return false;

	if(!CheckNMEACRC(NMEAPacket))
		return false;

	// OK, GGA-Paket seems to be complete
	// now extract data
	CXStringASCII s = NMEAPacket;
	// remove $GGA
	ExtractFirstToken(s, ',');
	// UTC
	rGGAPacket.SetUTC(ExtractFirstToken(s, ','));
	// read latitude
	CXStringASCII SLat = ExtractFirstToken(s, ',');
	double dLat = 0;
	sscanf(SLat.c_str(), "%lf", &dLat);
	CXStringASCII strLat = ExtractFirstToken(s, ',');
	if((strLat != "N") && (strLat != "n") && (strLat != "S") && (strLat != "s"))
		oFix = false;
	// read longitude
	CXStringASCII SLon = ExtractFirstToken(s, ',');
	double dLon = 0;
	sscanf(SLon.c_str(), "%lf", &dLon);
	CXStringASCII strLon = ExtractFirstToken(s, ',');
	if((strLon != "E") && (strLon != "e") && (strLon != "W") && (strLon != "w"))
		oFix = false;

	// quality
	int quality = atoi(ExtractFirstToken(s, ',').c_str());
	// nr satellites
	int NSat = atoi(ExtractFirstToken(s, ',').c_str());
	rGGAPacket.SetNSat(NSat);
	// HDOP
	CXStringASCII SHDOP = ExtractFirstToken(s, ',');
	double dHDOP = 0;
	sscanf(SHDOP.c_str(), "%lf", &dHDOP);
	rGGAPacket.SetHDOP(dHDOP);
	// height
	double Height = 0;
	sscanf(ExtractFirstToken(s, ',').c_str(), "%lf", &Height);
	rGGAPacket.SetHeight(Height);
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

	if((strLat == "s") || (strLat == "S"))
		dLat = -dLat;
	if((strLon == "w") || (strLon == "W"))
		dLon = -dLon;
	
	// transform to decimal degrees
	double dLonDeg = 0, dLatDeg = 0;
	LLGMDToG(dLon, dLat, dLonDeg, dLatDeg);
	rGGAPacket.SetLon(dLonDeg);
	rGGAPacket.SetLat(dLatDeg);

	// set fix
	if((quality != 0) && (NSat > 0))
		oFix = true;

	rGGAPacket.SetFix(oFix);

	return true;
}

//-------------------------------------
bool ExtractRMCData(const CXStringASCII &NMEAPacket, CXRMCPacket & rRMCPacket) {
	// check if this NMEAPacket contains a RMC packet
	rRMCPacket.SetFix(false);
	bool oFix = false;

	// length must be greater than 11 $ G P R M C * x x CR LF
	if(NMEAPacket.GetSize() < 11)
		return false;

	// the first 6 characters must be "$CPRMC"
	if(NMEAPacket.Find(pcRMCBEGIN) != 0) {
		return false;
	}

	// count colons
	int iCount = 0;
	for(size_t i=0; i<NMEAPacket.GetSize(); i++)
		if(NMEAPacket[i] == ',')
			iCount++;
	if(iCount != 12)
		return false;

	if(!CheckNMEACRC(NMEAPacket))
		return false;

	// OK, RMC-Paket seems to be complete
	// now extract data
	CXStringASCII s = NMEAPacket;
	// remove $GGA
	ExtractFirstToken(s, ',');
	// UTC
	rRMCPacket.SetUTC(ExtractFirstToken(s, ','));
	// fix status
	CXStringASCII Fix = ExtractFirstToken(s, ',');
	// read latitude
	CXStringASCII SLat = ExtractFirstToken(s, ',');
	double dLat = 0;
	sscanf(SLat.c_str(), "%lf", &dLat);
	CXStringASCII strLat = ExtractFirstToken(s, ',');
	if((strLat != "N") && (strLat != "n") && (strLat != "S") && (strLat != "s"))
		oFix = false;
	// read longitude
	CXStringASCII SLon = ExtractFirstToken(s, ',');
	double dLon = 0;
	sscanf(SLon.c_str(), "%lf", &dLon);
	CXStringASCII strLon = ExtractFirstToken(s, ',');
	if((strLon != "E") && (strLon != "e") && (strLon != "W") && (strLon != "w"))
		oFix = false;

	// speed
	CXStringASCII SSpeed = ExtractFirstToken(s, ',');
	double dSpeed = 0;
	sscanf(SSpeed.c_str(), "%lf", &dSpeed);
	// convert to m/s
	dSpeed = 0.51444*dSpeed;
	rRMCPacket.SetSpeed(dSpeed);
	// course
	CXStringASCII SCourse = ExtractFirstToken(s, ',');
	double dCourse = 0;
	sscanf(SCourse.c_str(), "%lf", &dCourse);
	rRMCPacket.SetCourse(dCourse);

	if((strLat == "s") || (strLat == "S"))
		dLat = -dLat;
	if((strLon == "w") || (strLon == "W"))
		dLon = -dLon;
	
	// transform to decimal degrees
	double dLonDeg = 0, dLatDeg = 0;
	LLGMDToG(dLon, dLat, dLonDeg, dLatDeg);
	rRMCPacket.SetLon(dLonDeg);
	rRMCPacket.SetLat(dLatDeg);

	// check for valid fix
	if((Fix == "a") || (Fix == "A"))
		oFix = true;

	rRMCPacket.SetFix(oFix);
	return true;
}

//-------------------------------------
bool ExtractGSAData(const CXStringASCII &NMEAPacket, CXGSAPacket & rGSAPacket) {
	// check if this NMEAPacket contains a GSA packet

	// length must be greater than 11 $ G P G S A * x x CR LF
	if(NMEAPacket.GetSize() < 11)
		return false;

	// the first 6 characters must be "$CPGSA"
	if(NMEAPacket.Find(pcGSABEGIN) != 0) {
		return false;
	}

	// count colons
	int iCount = 0;
	for(size_t i=0; i<NMEAPacket.GetSize(); i++)
		if(NMEAPacket[i] == ',')
			iCount++;
	if(iCount != 17)
		return false;

	if(!CheckNMEACRC(NMEAPacket))
		return false;

	// OK, GSA-Paket seems to be complete
	// now extract data
	CXStringASCII s = NMEAPacket;
	// remove $GSA
	ExtractFirstToken(s, ',');

	// selection mode
	ExtractFirstToken(s, ',');
	// fix
	ExtractFirstToken(s, ',');
	// now extract 12 satellite PRN
	rGSAPacket.ClearSatellites();
	for(size_t j=0; j<12; j++) {
		CXStringASCII SPRN = ExtractFirstToken(s, ',');
		if(!SPRN.IsEmpty())
			rGSAPacket.AddSatellite(atoi(SPRN.c_str()));
	}
	// PDOP
	ExtractFirstToken(s, ',');
	// HDOP
	CXStringASCII SHDOP = ExtractFirstToken(s, ',');
	double dHDOP = 0;
	sscanf(SHDOP.c_str(), "%lf", &dHDOP);
	rGSAPacket.SetHDOP(dHDOP);
	// VDOP
	CXStringASCII SVDOP = ExtractFirstToken(s, ',');
	double dVDOP = 0;
	sscanf(SVDOP.c_str(), "%lf", &dVDOP);
	rGSAPacket.SetVDOP(dVDOP);
	return true;
}


//-------------------------------------
bool ExtractGSVData(const CXStringASCII &NMEAPacket, int &rNTelegrams, int & rNCurrentTelegram, 
					int &rNSat, int &rNInfos, CXGSVSatelliteInfo &rInfo1, CXGSVSatelliteInfo &rInfo2,
					CXGSVSatelliteInfo &rInfo3, CXGSVSatelliteInfo &rInfo4)
{
	// check if this NMEAPacket contains a GSV packet

	// length must be greater than 11 $ G P G S V * x x CR LF
	if(NMEAPacket.GetSize() < 11)
		return false;

	// the first 6 characters must be "$CPGSV"
	if(NMEAPacket.Find(pcGSVBEGIN) != 0) {
		return false;
	}

	// we can not count colons since packet length is variable

	// check CRC
	if(!CheckNMEACRC(NMEAPacket))
		return false;

	// OK, GSV-Paket seems to be complete
	// now extract data
	CXStringASCII s = NMEAPacket;
	// remove $GSA
	ExtractFirstToken(s, ',');
	// number of GSV telegram
	rNTelegrams = atoi(ExtractFirstToken(s, ',').c_str());
	// current GSV telegram
	rNCurrentTelegram = atoi(ExtractFirstToken(s, ',').c_str());
	// number of visible satellites
	rNSat = atoi(ExtractFirstToken(s, ',').c_str());

	// remove until '*'
	s = ExtractFirstToken(s, '*');

	// now extract satellite infos
	while(!s.IsEmpty()) {
		rNInfos++;
		CXGSVSatelliteInfo *pInfo = &rInfo1;
		switch(rNInfos) {
			case 1 : pInfo = &rInfo1; break;
			case 2 : pInfo = &rInfo2; break;
			case 3 : pInfo = &rInfo3; break;
			case 4 : pInfo = &rInfo4; break;
		}
		// read an set data
		pInfo->SetPRN(atoi(ExtractFirstToken(s, ',').c_str()));
		pInfo->SetElevation(atoi(ExtractFirstToken(s, ',').c_str()));
		pInfo->SetAzimuth(atoi(ExtractFirstToken(s, ',').c_str()));
		pInfo->SetSNR(atoi(ExtractFirstToken(s, ',').c_str()));
	}
	return true;
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

//-------------------------------------
double CalcDistance(const CXCoor &Coor1, const CXCoor &Coor2) {
	// check if in same UTMZone
	double Result = 0;
	if(Coor1.GetUTMZone() != Coor2.GetUTMZone()) {
		// no, so create a temporary coordinate from Coor2
		CXCoor tmp(Coor2);
		// and relocate it to UTMZone from Coor1
		tmp.RelocateUTM(Coor1.GetUTMZone());
		// now compute distance
		Result = CalcDistance(Coor1, tmp);
	} else {
		double x1 = Coor1.GetUTMEasting();
		double y1 = Coor1.GetUTMNorthing();
		double x2 = Coor2.GetUTMEasting();
		double y2 = Coor2.GetUTMNorthing();
		Result = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
	}
	return Result;
}

//-------------------------------------
void ComputeRelativeUTMAngle(const CXCoor &BaseCoor, const CXCoor &TargetCoor, CXDirection & rDir) {
	// check if in same UTMZone
	if(BaseCoor.GetUTMZone() != TargetCoor.GetUTMZone()) {
		// no, so create a temporary coordinate from TargetCoor
		CXCoor tmp(TargetCoor);
		// and relocate it to UTMZone from BaseCoor
		tmp.RelocateUTM(BaseCoor.GetUTMZone());
		// now compute angle
		ComputeRelativeUTMAngle(BaseCoor, tmp, rDir);
	} else {
		double d = CalcDistance(BaseCoor, TargetCoor);
		double dx = TargetCoor.GetUTMEasting() - BaseCoor.GetUTMEasting();
		double dy = TargetCoor.GetUTMNorthing() - BaseCoor.GetUTMNorthing();
		rDir = CXDirection(dx/d, dy/d);
	}
}

//-------------------------------------
double ConvertSavedUI32(t_uint32 Value) {
	double Result = 1.0;
	if((Value & 0x80000000) != 0) {
		// negative coordinate
		Result = -1;
		Value &= 0x7FFFFFFF;
	}
	// now scale back
	Result = Result*Value/SCALE_FACTOR_UI32;
	return Result;
}

//-------------------------------------
void ComputePOIBMP(E_POI_TYPE ePOIType, size_t & BMPIdx, size_t & rRow, size_t & rCol) {
	BMPIdx = ePOIType >> 8;
	rRow = (ePOIType & 0xF0) >> 4;
	rCol = ePOIType & 0x0F;
}

//-------------------------------------
E_BACKGROUND_TYPE Str2BGType(const CXStringASCII & Value) {
	if(Value.ToUpper() == "AREA")
		return e_BG_AREA;
	else if(Value.ToUpper() == "GLOW")
		return e_BG_GLOW;
	else
		return e_BG_AREA;
}

//-------------------------------------
E_WAY_TYPE WayType012ToCurrentWayType(E_WAY_TYPE_0_1_2 Value) {
	E_WAY_TYPE Result = e_Way_Unknown;
	switch(Value) {
		case e_Way_Fading_0_1_2:			Result = e_Way_Fading; break;
		case e_Way_Unknown_0_1_2:			Result = e_Way_Unknown; break;
		case e_Way_Motorway_0_1_2:			Result = e_Way_Motorway; break;
		case e_Way_MotorwayLink_0_1_2:		Result = e_Way_MotorwayLink; break;
		case e_Way_Trunk_0_1_2:				Result = e_Way_Trunk; break;
		case e_Way_TrunkLink_0_1_2:			Result = e_Way_TrunkLink; break;
		case e_Way_Primary_0_1_2:			Result = e_Way_Primary; break;
		case e_Way_PrimaryLink_0_1_2:		Result = e_Way_PrimaryLink; break;
		case e_Way_Secondary_0_1_2:			Result = e_Way_Secondary; break;
		case e_Way_Tertiary_0_1_2:			Result = e_Way_Tertiary; break;
		case e_Way_Unclassified_0_1_2:		Result = e_Way_Unclassified; break;
		case e_Way_Track_0_1_2:				Result = e_Way_Track; break;
		case e_Way_Residential_0_1_2:		Result = e_Way_Residential; break;
		case e_Way_Service_0_1_2:			Result = e_Way_Service; break;
		case e_Way_Bridleway_0_1_2:			Result = e_Way_Bridleway; break;
		case e_Way_Cycleway_0_1_2:			Result = e_Way_Cycleway; break;
		case e_Way_Footway_0_1_2:			Result = e_Way_Footway; break;
		case e_Way_Pedestrian_0_1_2:		Result = e_Way_Pedestrian; break;
		case e_Way_Steps_0_1_2:				Result = e_Way_Steps; break;
		case e_Way_LivingStreet_0_1_2:		Result = e_Way_LivingStreet; break;
		case e_Way_NationalBorder_0_1_2:	Result = e_Way_BorderThick; break;
		case e_Way_Railway_Thick_0_1_2:		Result = e_Way_Railway_Thick; break;
		case e_Way_Railway_Thin_0_1_2:		Result = e_Way_Railway_Thin; break;
		case e_Way_Water_Thick_0_1_2:		Result = e_Way_Water_Thick; break;
		case e_Way_Water_Thin_0_1_2:		Result = e_Way_Water_Thin; break;
	}
	return Result;
}
