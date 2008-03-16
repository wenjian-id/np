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

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"
#include "CXFile.hpp"
#include "CXRGB.hpp"

class CXCoor;
class CXGSVSatelliteInfo;

template <class t> t Max(const t &a, const t&b) {
	if(a < b)
		return b;
	return a;
}

template <class t> t Min(const t &a, const t&b) {
	if(a < b)
		return a;
	return b;
}

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

const CXRGB COLOR_TRANSPARENT(0xFF, 0x22, 0xEE);

static const size_t MaxPOITypes = 8; ///< oiu

const unsigned char DegUTF8[2] = {0xC2, 0xB0};


//-------------------------------------
/*
 * \brief Possible command.
 *
 * Possible command.
 */
enum E_COMMAND {
	e_CmdNone,		///< No command.
	e_CmdQuit,		///< Quit.
	e_CmdInfo,		///< Info.
	e_CmdSave,		///< Toggle save.
	e_CmdZoomIn,	///< Zoom in
	e_CmdZoomOut,	///< Zoom out
	e_CmdSat,		///< Sat info.
};


//-------------------------------------
/*
 * \brief Read one ASCII line from a file.
 *
 * Read a line consisting of ASCII characters from a file.
 * Both Unix and Windows line end styles should be recognised and 
 * hadled properly. The end line character(s) are not part of the
 * result.
 * \param	rInFile     The file to read from.
 * \param	rNewLine	String to read into.
 * \return				true if successfull.
 */
bool ReadLineASCII(CXFile & rInFile, CXStringASCII & rNewLine);

//-------------------------------------
/*
 * \brief Read one byte from a file.
 *
 * Read a byte (unsigned char) from a file.
 * \param	rInFile     The file to read from.
 * \param	rValue		Byte to read into.
 * \return				true if successfull.
 */
bool ReadB(CXFile & rInFile, unsigned char & rValue);

//-------------------------------------
/*
 * \brief Read a 32 bit unsigned integer from a file.
 *
 * Read a 32 bit unsigned integer from a file.
 * \todo	use platform independent type
 * \param	rInFile     The file to read from.
 * \param	rValue		Value to fill with data.
 * \return				true if successfull.
 */
bool ReadUI32(CXFile & rInFile, t_uint32 & rValue);

//-------------------------------------
/*
 * \brief Read a 64 bit unsigned integer from a file.
 *
 * Read a 64 bit unsigned integer from a file.
 * \param	rInFile     The file to read from.
 * \param	rValue		Value to fill with data.
 * \return				true if successfull.
 */
bool ReadUI64(CXFile & rInFile, t_uint64 & rValue);

//-------------------------------------
/*
 * \brief Read one UTF8 encoded string from a file.
 *
 * Read one UTF8 encoded string from a file. Strings have to 
 * terminated with a 0 character.
 * \param	rInFile     The file to read from.
 * \param	rValue		UTF8 String to read into.
 * \return				true if successfull.
 */
bool ReadStringUTF8(CXFile & rInFile, CXStringUTF8 & rValue);

//-------------------------------------
/*
 * \brief Check if CRC of NMEA packet is correct.
 *
 * Check if CRC of NMEA packet is correct.
 * \param	NMEAPacket		String containing the NMEA packet including CR LF 
 * \return					true if CRC s OK.
 */
bool CheckNMEACRC(const CXStringASCII &NMEAPacket);

//-------------------------------------
/*
 * \brief Extract information from a GGA packet.
 *
 * Extract information from a GGA packet. The information extracted
 * consists of longitude, latitude and number of sattelites.
 * \param	NMEAPacket	String containing the NMEA packet including CR LF 
 * \param	rLon		Extracted longitude [decimal degrees]
 * \param	rLat		Extracted latitude [decimal degrees]
 * \param	rHeight		Extracted height [m]
 * \param	rnSat		Extracted number of sattelites.
 * \return				true if successfull.
 */
bool ExtractGGAData(const CXStringASCII &NMEAPacket, double & rLon, double & rLat, double & rHeight, int &rnSat);

//-------------------------------------
/*
 * \brief Extract information from a GSA packet.
 *
 * Extract information from a GSA packet. The information extracted
 * consists of an array of the PRN of active satellites.
 * \param	NMEAPacket		String containing the NMEA packet including CR LF 
 * \param	rSatellites		Buffer with PRN of active satellites
 * \return					true if successfull.
 */
bool ExtractGSAData(const CXStringASCII &NMEAPacket, CXBuffer<int> &rSatellites);

//-------------------------------------
/*
 * \brief Extract information from a GSV packet.
 *
 * Extract information from a GSV packet. The information extracted
 * consists of 
 * \param	NMEAPacket			String containing the NMEA packet including CR LF 
 * \param	rNTelegrams			Number of GSV telegrams
 * \param	rNCurrentTelegram	Number of current telegram
 * \param	rNSat				Number of visible staellites
 * \param	rNInfos				Number of staellite infos received
 * \param	rInfo1				Satellite info 1
 * \param	rInfo2				Satellite info 2
 * \param	rInfo3				Satellite info 3
 * \param	rInfo4				Satellite info 4
 * \return						true if successfull.
 */
bool ExtractGSVData(const CXStringASCII &NMEAPacket, int &rNTelegrams, int & rNCurrentTelegram, 
					int &rNSat, int &rNInfos, 
					CXGSVSatelliteInfo &rInfo1, CXGSVSatelliteInfo &rInfo2,
					CXGSVSatelliteInfo &rInfo3, CXGSVSatelliteInfo &rInfo4);

//-------------------------------------
/*
 * \brief Extract first token from a string.
 *
 * Extract first token from a string. The first token consists of the string part
 * between the first character (including it) and the first occurence of the
 * token delimiter (not including it). If the token delimiter is not found, the whole string
 * is returned. The returned string (plus token delimiter) is deleted from the string.
 * \param	rString		The string to 
 * \param	cTokenChar	Token delimiter.
 * \return				The first extracted token.
 */
CXStringASCII ExtractFirstToken(CXStringASCII &rString, const char cTokenChar);

//-------------------------------------
/*
 * \brief Convert lon / lat from deGreesMinute.Decimal to decimal deGrees.
 *
 * Convert lon / lat from deGreesMinute.Decimal to decimal deGrees.
 * \param	dLon	Longitude to convert [GM.D]
 * \param	dLat	Latitude to convert [GM.D]
 * \param	rLon	Converted longitude [decimal degrees]
 * \param	rLat	Converted latitude [decimal degrees]
 */
void LLGMDToG(const double dLon, const double dLat, double & rdLon, double & rdLat);

//-------------------------------------
/*
 * \brief Compute distance between two coordinates.
 *
 * Compute distance between two coordinates.
 * \param	Coor1	First coordinate.
 * \param	Coor2	Second coordinate.
 * \return	Distance between coordinates
 */
double CalcDistance(const CXCoor &Coor1, const CXCoor &Coor2);

#endif // __UTILS_HPP__
