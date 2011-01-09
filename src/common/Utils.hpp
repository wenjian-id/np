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

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"
#include "CXFile.hpp"
#include "CXRect.hpp"
#include "CXRGB.hpp"
#include "CXDirection.hpp"

#include <math.h>

class CXCoor;
class CXGGAPacket;
class CXRMCPacket;
class CXGSAPacket;
class CXSatelliteInfo;
class CXBitmap;
class CXArea;
class CXOrderedNodeList;


// Versions
const unsigned int MAPVERSION   = 0x00020000; // 0.2.0
const unsigned int ZOOMVERSION  = 0x00010000; // 0.1.0
const unsigned int SECTVERSION  = 0x00010402; // 0.1.4 dev2

const unsigned int SCALE_FACTOR_UI32 = 1000000;     ///< oiu
const char MINLAYER = -10;                          ///< Minimum value or layer.
const char MAXLAYER = 10;                           ///< Maximum value for layer.

const double EPSILON = 0.01;                        ///< oiu
const unsigned char DegUTF8[2] = {0xC2, 0xB0};      ///< UTF8 characters for degree sign.


// Mapnik colors
const CXRGB MAPBGCOLOR(0xE2, 0xDE, 0xD8);           ///< oiu
const CXRGB MAPFGCOLOR(0x00, 0x00, 0x00);           ///< oiu
const CXRGB MAPPOITEXTCOLOR(0x00, 0x00, 0xA0);      ///< oiu
const CXRGB MAPPOIBGCOLOR(0xE2, 0xDE, 0xD8);        ///< oiu
const CXRGB MAPCITYTEXTCOLOR(0x00, 0x00, 0x00);     ///< oiu
const CXRGB MAPCITYBGCOLOR(0xff, 0xff, 0x00);       ///< oiu

const CXRGB COLOR_TRANSPARENT(0xFF, 0x22, 0xEE);    ///< oiu

//-------------------------------------
/**
 * \brief Compute maximum of two values.
 *
 * Compute maximum of two values.
 * \param   a   First value.
 * \param   b   Second value.
 * \return      Maximum.
 */
template <class t> t Max(const t &a, const t&b) {
    if(a < b)
        return b;
    return a;
}

//-------------------------------------
/**
 * \brief Compute minimum of two values.
 *
 * Compute minimum of two values.
 * \param   a   First value.
 * \param   b   Second value.
 * \return      Minimum.
 */
template <class t> t Min(const t &a, const t&b) {
    if(a < b)
        return a;
    return b;
}

//-------------------------------------
/**
 * \brief Possible command.
 *
 * Possible command.
 */
enum E_COMMAND {
    e_CmdNone,              ///< No command.
    e_CmdQuit,              ///< Quit.
    e_CmdInfo,              ///< Info.
    e_CmdSave,              ///< Toggle save.
    e_CmdZoomIn,            ///< Zoom in
    e_CmdZoomOut,           ///< Zoom out
    e_CmdSat,               ///< Sat info.
    e_CmdMinimize,          ///< Minimize.
    e_CmdAutoZoom,          ///< Auto zoom.
    e_CmdMapMoveManually,   ///< Move map around.
    e_CmdClock,             ///< Switch clock display.
    e_CmdNextTarget,        ///< Switch to next target.
};


//-------------------------------------
/**
 * \brief Loading status.
 *
 * Loading status for map container and map section.
 */
enum E_LOADING_STATUS {
    e_LSNotLoaded,  ///< Not loaded yet.
    e_LSInList,     ///< In list for loading.
    e_LSLoading,    ///< Still loading.
    e_LSLoadError,  ///< Load error.
    e_LSLoaded,     ///< Alerady loaded.
};

//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_BACKGROUND_TYPE {
    e_BG_AREA,      ///< oiu
    e_BG_GLOW,      ///< oiu
};


//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_BIT_COUNT {
    e_BC_8,     ///< oiu
    e_BC_16,    ///< oiu
    e_BC_24,    ///< oiu
    e_BC_32,    ///< oiu
};

//-------------------------------------
/**
 * \brief Enum with tag types.
 */
enum {
    e_TagType_Name              = 0x0001,   ///< Tag of type name.
    e_TagType_Ref               = 0x0002,   ///< Tag of type ref.
    e_TagType_IntRef            = 0x0004,   ///< Tag of type international ref.
    e_TagType_Layer             = 0x0008,   ///< Tag of type layer.
    e_TagType_MaxSpeedForward   = 0x0010,   ///< Tag of type max speed forward.
    e_TagType_MaxSpeedBackward  = 0x0020,   ///< Tag of type max speed backward.
    e_TagType_Oneway            = 0x0040,   ///< Tag of type oneway.
};

//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_ONEWAY_TYPE {
    e_Oneway_None       = 0x00, ///< oiu
    e_Oneway_Normal     = 0x01, ///< oiu
    e_Oneway_Inverse    = 0x02, ///< oiu
};

//-------------------------------------
/**
 * \brief Create an absolute path for directory entries.
 *
 * Create an absolute path for directory entries.
 * If Path is an absolute path (well, a path starting with PATHDELIMITER)
 * already it will be used as result, else the result will be StartPath + Path.
 * If necessary, a PATHDELIMITER will be appended.
 * \param   StartPath   Start path
 * \param   Path        Path to be processed.
 * \return              New absolute path.
 */
CXStringASCII CreateAbsolutePath(const CXStringASCII &StartPath, const CXStringASCII &Path);

//-------------------------------------
/**
 * \brief Create an absolute path for directory entries.
 *
 * Create an absolute filename.
 * If FileName is an absolute file name (well, a file name starting with PATHDELIMITER)
 * already it will be used as result, else the result will be StartPath + FileName.
 * \param   StartPath   Start path
 * \param   FileName    File name to be processed.
 * \return              New absolute path.
 */
CXStringASCII CreateAbsoluteFileName(const CXStringASCII &StartPath, const CXStringASCII &FileName);

//-------------------------------------
/**
 * \brief Read one ASCII line from a file.
 *
 * Read a line consisting of ASCII characters from a file.
 * Both Unix and Windows line end styles should be recognised and
 * hadled properly. The end line character(s) are not part of the
 * result.
 * \param   rInFile     The file to read from.
 * \param   rNewLine    String to read into.
 * \return              true if successfull.
 */
bool ReadLineASCII(CXFile & rInFile, CXStringASCII & rNewLine);

//-------------------------------------
/**
 * \brief Read one byte from a file.
 *
 * Read a byte (unsigned char) from a file.
 * \param   rInFile     The file to read from.
 * \param   rValue      Byte to read into.
 * \return              true if successfull.
 */
bool ReadUI(CXFile & rInFile, E_BIT_COUNT eBitCount, t_uint32 & rValue);

//-------------------------------------
/**
 * \brief Read one byte from a file.
 *
 * Read a byte (unsigned char) from a file.
 * \param   rInFile     The file to read from.
 * \param   rValue      Byte to read into.
 * \return              true if successfull.
 */
bool ReadUI8(CXFile & rInFile, unsigned char & rValue);

//-------------------------------------
/**
 * \brief Read a 16 bit unsigned integer from a file.
 *
 * Read a 16 bit unsigned integer from a file.
 * \param   rInFile     The file to read from.
 * \param   rValue      Value to fill with data.
 * \return              true if successfull.
 */
bool ReadUI16(CXFile & rInFile, t_uint16 & rValue);

//-------------------------------------
/**
 * \brief Read a 24 bit unsigned integer from a file.
 *
 * Read a 24 bit unsigned integer from a file.
 * \param   rInFile     The file to read from.
 * \param   rValue      Value to fill with data.
 * \return              true if successfull.
 */
bool ReadUI24(CXFile & rInFile, t_uint32 & rValue);

//-------------------------------------
/**
 * \brief Read a 32 bit unsigned integer from a file.
 *
 * Read a 32 bit unsigned integer from a file.
 * \param   rInFile     The file to read from.
 * \param   rValue      Value to fill with data.
 * \return              true if successfull.
 */
bool ReadUI32(CXFile & rInFile, t_uint32 & rValue);

//-------------------------------------
/**
 * \brief Write a 32 bit unsigned integer to a file.
 *
 * Write a 32 bit unsigned integer to a file.
 * \param   rOutFile    The file to write to .
 * \param   Value       Value to write.
 * \return              true if successfull.
 */
bool WriteUI32(CXFile & rOutFile, t_uint32 Value);

//-------------------------------------
/**
 * \brief Read a 64 bit unsigned integer from a file.
 *
 * Read a 64 bit unsigned integer from a file.
 * \param   rInFile     The file to read from.
 * \param   rValue      Value to fill with data.
 * \return              true if successfull.
 */
bool ReadUI64(CXFile & rInFile, t_uint64 & rValue);

//-------------------------------------
/**
 * \brief Read one UTF8 encoded string from a file.
 *
 * Read one UTF8 encoded string from a file. Strings have to
 * terminated with a 0 character.
 * \param   rInFile     The file to read from.
 * \param   rValue      UTF8 String to read into.
 * \return              true if successfull.
 */
bool ReadStringUTF8(CXFile & rInFile, CXStringUTF8 & rValue);

//-------------------------------------
/**
 * \brief Check if CRC of NMEA packet is correct.
 *
 * Check if CRC of NMEA packet is correct.
 * \param   NMEAPacket      String containing the NMEA packet including CR LF
 * \return                  true if CRC s OK.
 */
bool CheckNMEACRC(const CXStringASCII &NMEAPacket);

//-------------------------------------
/**
 * \brief Extract information from a GGA packet.
 *
 * Extract information from a GGA packet. The information extracted
 * consists of longitude, latitude and number of satellites.
 * \param   NMEAPacket  String containing the NMEA packet including CR LF
 * \param   rGGAPacket  Extracted data.
 * \return              true if successfull.
 */
bool ExtractGGAData(const CXStringASCII &NMEAPacket, CXGGAPacket & rGGAPacket);

//-------------------------------------
/**
 * \brief Extract information from a RMC packet.
 *
 * Extract information from a RMC packet. The information extracted
 * consists of longitude, latitude and speed and course.
 * \param   NMEAPacket  String containing the NMEA packet including CR LF
 * \param   rRMCPacket  Extracted data.
 * \return              true if successfull.
 */
bool ExtractRMCData(const CXStringASCII &NMEAPacket, CXRMCPacket & rRMCPacket);

//-------------------------------------
/**
 * \brief Extract information from a GSA packet.
 *
 * Extract information from a GSA packet. The information extracted
 * consists of an array of the PRN of active satellites.
 * \param   NMEAPacket      String containing the NMEA packet including CR LF
 * \param   rGSAPacket      Extracted data.
 * \return                  true if successfull.
 */
bool ExtractGSAData(const CXStringASCII &NMEAPacket, CXGSAPacket & rGSAPacket);

//-------------------------------------
/**
 * \brief Extract information from a GSV packet.
 *
 * Extract information from a GSV packet. The information extracted
 * consists of
 * \param   NMEAPacket          String containing the NMEA packet including CR LF
 * \param   rNTelegrams         Number of GSV telegrams
 * \param   rNCurrentTelegram   Number of current telegram
 * \param   rNSat               Number of visible staellites
 * \param   rNInfos             Number of staellite infos received
 * \param   rInfo1              Satellite info 1
 * \param   rInfo2              Satellite info 2
 * \param   rInfo3              Satellite info 3
 * \param   rInfo4              Satellite info 4
 * \return                      true if successfull.
 */
bool ExtractGSVData(const CXStringASCII &NMEAPacket, int &rNTelegrams, int & rNCurrentTelegram,
                    int &rNSat, int &rNInfos,
                    CXSatelliteInfo &rInfo1, CXSatelliteInfo &rInfo2,
                    CXSatelliteInfo &rInfo3, CXSatelliteInfo &rInfo4);

//-------------------------------------
/**
 * \brief Extract first token from a string.
 *
 * Extract first token from a string. The first token consists of the string part
 * between the first character (including it) and the first occurence of the
 * token delimiter (not including it). If the token delimiter is not found, the whole string
 * is returned. The returned string (plus token delimiter) is deleted from the string.
 * \param   rString     The string to process.
 * \param   cTokenChar  Token delimiter.
 * \return              The first extracted token.
 */
CXStringASCII ExtractFirstToken(CXStringASCII &rString, const char cTokenChar);

//-------------------------------------
/**
 * \brief Delete first token from a string.
 *
 * Delete first token from a string. The first token consists of the string part
 * between the first character (including it) and the first occurence of the
 * token delimiter (not including it). If the token delimiter is not found, the whole string
 * is deleted. The found token (plus token delimiter) is deleted from the string.
 * \param   rString     The string to process.
 * \param   cTokenChar  Token delimiter.
 */
void DeleteFirstToken(CXStringASCII &rString, const char cTokenChar);

//-------------------------------------
/**
 * \brief Convert lon / lat from deGreesMinute.Decimal to decimal deGrees.
 *
 * Convert lon / lat from deGreesMinute.Decimal to decimal deGrees.
 * \param   dLon    Longitude to convert [GM.D]
 * \param   dLat    Latitude to convert [GM.D]
 * \param   rLon    Converted longitude [decimal degrees]
 * \param   rLat    Converted latitude [decimal degrees]
 */
void LLGMDToG(const double dLon, const double dLat, double & rdLon, double & rdLat);

//-------------------------------------
/**
 * \brief Compute distance between two coordinates.
 *
 * Compute distance between two coordinates.
 * \param   Coor1   First coordinate.
 * \param   Coor2   Second coordinate.
 * \return  Distance between coordinates
 */
double CalcDistance(const CXCoor &Coor1, const CXCoor &Coor2);

//-------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
void ComputeRelativeUTMAngle(const CXCoor &BaseCoor, const CXCoor &TargetCoor, CXDirection & rDir);

//-------------------------------------
/**
 * \brief Calculate optimal font height for a rect.
 *
 * Calculate optimal font height so that a text fits into a rectangle.
 * Font height is adjusted when coputing!
 * \param   Bmp     Bitmap.
 * \param   Str     String.
 * \param   rRect   The rectangle.
 * \return          Font height.
 */
int CalcFontHeight(CXBitmap &Bmp, const CXStringUTF8 &Str, tIRect &rRect);

//-------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
double ConvertSavedUI32(t_uint32 Value);

//-------------------------------------
/**
 * \brief oiu
 *
 *  oiu
 */
E_BACKGROUND_TYPE Str2BGType(const CXStringASCII & Value);

//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_MAP_PLACE_TYPE {
    e_MapPlace_None             = 0x00,     ///< No place.
    e_MapPlace_Small            = 0x01,     ///< Place small.
    e_MapPlace_Medium           = 0x02,     ///< Place medium.
    e_MapPlace_Large            = 0x03,     ///< Place large.
};

//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_ZOOM_LEVEL {
    e_ZoomLevel_0       = 0,    ///< oiu
    e_ZoomLevel_1       = 1,    ///< oiu
    e_ZoomLevel_2       = 2,    ///< oiu
    e_ZoomLevel_3       = 3,    ///< oiu
    e_ZoomLevel_4       = 4,    ///< oiu
    e_ZoomLevel_5       = 5,    ///< oiu
    e_ZoomLevel_6       = 6,    ///< oiu
    e_ZoomLevel_7       = 7,    ///< oiu
    e_ZoomLevel_Count   = 8,    ///< oiu
};

// Order taken from http://etricceline.de/osm/germany/en_stats_amenity.htm
// Correctness taken from http://wiki.openstreetmap.org/index.php/Map_Features
//-------------------------------------
/**
 * \brief oiu
 *
 *  oiu
 */
enum E_POI_TYPE {       // must fit the values in the map file!!!
    // special values
    e_POI_None                  = 0x0000,   ///< Nothing.
    e_POI_All                   = 0xFFFF,   ///< All.

    e_POI_Parking               = 0x0001,   ///< Car park.
    e_POI_Fuel                  = 0x0002,   ///< Fuel.
    e_POI_PlcOfWrshp_Christian  = 0x0003,   ///< Christian church, temple, etc.
    e_POI_Restaurant            = 0x0004,   ///< Restaurant.
    e_POI_School                = 0x0005,   ///< School.
    e_POI_Telephone             = 0x0006,   ///< Public telephone
    e_POI_PostBox               = 0x0007,   ///< Post box.
    e_POI_Pharmacy              = 0x0008,   ///< Pharmacy.
    e_POI_Pub                   = 0x0009,   ///< Pub.
    e_POI_Hospital              = 0x000A,   ///< Hospital.
    e_POI_PostOffice            = 0x000B,   ///< Post office.
    e_POI_FireStation           = 0x000C,   ///< Fire station.
    e_POI_Police                = 0x000D,   ///< Police station.
    e_POI_BusStation            = 0x000E,   ///< Bus station.
    e_POI_Toilets               = 0x000F,   ///< Public toilets.
    e_POI_Taxi                  = 0x0010,   ///< Taxi.
    e_POI_Stop                  = 0x0011,   ///< Stop sign
    e_POI_TrafficSignals        = 0x0012,   ///< Traffic signals
    e_POI_MotorwayJunction      = 0x0013,   ///< Motorway junction
    e_POI_BusStop               = 0x0014,   ///< Bus stop.
    e_POI_RailwayStation        = 0x0015,   ///< Railway station.
    e_POI_RailwayHalt           = 0x0016,   ///< Railway halt.
    e_POI_TramStop              = 0x0017,   ///< Tram stop.
    e_POI_SubwayEntrance        = 0x0018,   ///< Subway entrance
    e_POI_Crossing              = 0x0019,   ///< Crossing
    e_POI_LevelCrossing         = 0x001A,   ///< Level crossing
    e_POI_Aerodrome             = 0x001B,   ///< Aerodrome
    e_POI_Helipad               = 0x001C,   ///< Helipad
    e_POI_PowerTower            = 0x001D,   ///< Power tower.
    e_POI_PowerSubStation       = 0x001E,   ///< Power sub station.
    e_POI_Hotel                 = 0x001F,   ///< Hotel.
    e_POI_Hostel                = 0x0020,   ///< Hostel.
    e_POI_CampSite              = 0x0021,   ///< Camp site.
    e_POI_Supermarket           = 0x0022,   ///< Supermarket.
    e_POI_PlcOfWrshp_Jewish     = 0x0023,   ///< Jewish church, temple, etc.
    e_POI_PlcOfWrshp_Muslim     = 0x0024,   ///< Muslim church, temple, etc.
    e_POI_PlcOfWrshp_Hindu      = 0x0025,   ///< Hindu church, temple, etc.
    e_POI_PlcOfWrshp_Buddhist   = 0x0026,   ///< Buddhist church, temple, etc.
    e_POI_PlcOfWrshp_Shinto     = 0x0027,   ///< Shinto church, temple, etc.
    e_POI_PlcOfWrshp_Taoist     = 0x0028,   ///< Taoist church, temple, etc.
    e_POI_PlcOfWrshp_Unknown    = 0x0029,   ///< Unknown church, temple, etc.
    e_POI_Shelter               = 0x002A,   ///< Shelter.
    e_POI_College               = 0x002B,   ///< College.
    e_POI_University            = 0x002C,   ///< University.
    e_POI_Bench                 = 0x002D,   ///< Bench.
    e_POI_WasteBasket           = 0x002E,   ///< Waste basket.
    e_POI_ViewPoint             = 0x002F,   ///< View point.
    e_POI_Playground            = 0x0030,   ///< Playground

/*
    e_POI_Recycling             = 0x0006,   ///< Recycling facilities.
    e_POI_Bank                  = 0x000A,   ///< Bank.
    e_POI_FastFood              = 0x000B,   ///< Fast food.
    e_POI_PublicBuilding        = 0x000C,   ///< Public building.
    e_POI_TownHall              = 0x0013,   ///< Town hall.
    e_POI_GraveYard             = 0x0014,   ///< Grave yard.
    e_POI_Cafe                  = 0x0017,   ///< Cafe.
    e_POI_Library               = 0x0018,   ///< Library.
    e_POI_Cinema                = 0x0019,   ///< Cinema.
    e_POI_ATM                   = 0x001A,   ///< ATM, cash point.
    e_POI_Theatre               = 0x001B,   ///< Theatre or opera.
    e_POI_Biergarten            = 0x001C,   ///< Biergarten.
    e_POI_BicycleParking        = 0x001D,   ///< Parking for bicycles.
    e_POI_Courthouse            = 0x001E,   ///< Courthouse.
    e_POI_Prison                = 0x001F,   ///< Prison.
    e_POI_Attraction            = 0x0202,   ///< Attraction.
    e_POI_Information           = 0x0206,   ///< Information.
    e_POI_Zoo                   = 0x0207,   ///< Zoo.
    e_POI_GuestHouse            = 0x0208,   ///< Guest house
    e_POI_PicnicSite            = 0x0209,   ///< Picninc site.
    e_POI_ThemePark             = 0x020A,   ///< Theme park.
    e_POI_CaravanSite           = 0x020B,   ///< Caravan site.
    e_POI_Motel                 = 0x020C,   ///< Motel.
    e_POI_Museum                = 0x020D,   ///< Museum.
    e_POI_Artwork               = 0x020E,   ///< Artwork.
    e_POI_ShopBakery            = 0x0202,   ///< Bakery
    e_POI_ShopButcher           = 0x0203,   ///< Butcher.
    e_POI_Kiosk                 = 0x0204,   ///< Kiosk.
    e_POI_ShopConvenience       = 0x0205,   ///< Shop convenience
    e_POI_ShopDoItYourself      = 0x0206,   ///< Shop "do it yourself"
    e_POI_ShopBicycle           = 0x0207,   ///< Shop bicycle.
    e_POI_ShopOutdoor           = 0x0208,   ///< Shop Outdoor.
*/
};

//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_WAY_TYPE {   // must fit the values in the map file!!!
    e_Way_Fading            = 0x00,     ///< oiu
    e_Way_Unknown           = 0x01,     ///< oiu
    e_Way_Motorway          = 0x02,     ///< oiu
    e_Way_MotorwayLink      = 0x03,     ///< oiu
    e_Way_Trunk             = 0x04,     ///< oiu
    e_Way_TrunkLink         = 0x05,     ///< oiu
    e_Way_Primary           = 0x06,     ///< oiu
    e_Way_PrimaryLink       = 0x07,     ///< oiu
    e_Way_Secondary         = 0x08,     ///< oiu
    e_Way_Tertiary          = 0x09,     ///< oiu
    e_Way_Unclassified      = 0x0A,     ///< oiu
    e_Way_Track             = 0x0B,     ///< oiu
    e_Way_Residential       = 0x0C,     ///< oiu
    e_Way_Service           = 0x0D,     ///< oiu
    e_Way_Bridleway         = 0x0E,     ///< oiu
    e_Way_Cycleway          = 0x0F,     ///< oiu
    e_Way_Footway           = 0x10,     ///< oiu
    e_Way_Pedestrian        = 0x11,     ///< oiu
    e_Way_Steps             = 0x12,     ///< oiu
    e_Way_LivingStreet      = 0x13,     ///< oiu
    e_Way_Railway_Thick     = 0x14,     ///< oiu
    e_Way_Railway_Thin      = 0x15,     ///< oiu
    e_Way_Water_Thick       = 0x16,     ///< oiu
    e_Way_Water_Thin        = 0x17,     ///< oiu
    e_Way_BorderThick       = 0x18,     ///< oiu
    e_Way_BorderMedium      = 0x19,     ///< oiu
    e_Way_BorderThin        = 0x1A,     ///< oiu
    e_Way_Path              = 0x1B,     ///< oiu
    e_Way_EnumCount         = 0x1C,     ///< oiu
};

//-------------------------------------
/**
 * \brief oiu
 *
 */
enum E_AREA_TYPE {  // must fit the values in NaviPOWM!!!
    e_Area_None         = 0x0000,       ///< oiu
    e_Area_Water        = 0x0001,       ///< oiu
    e_Area_Wood         = 0x0002,       ///< oiu
    e_Area_EnumCount    = 0x0003,       ///< oiu
};

//-------------------------------------
/**
 * \brief Compute position in bitmap (row, column) of the most important POI only.
 *
 *  Compute position in bitmap (row, column) of the most important POI only.
 *  \param  ePOIType    POI type
 *  \param  rRow        Computed row.
 *  \param  rCol        Computed column.
 */
void ComputePOIBMP(E_POI_TYPE ePOIType, size_t & BMPIdx, size_t & rRow, size_t & rCol);

//-------------------------------------
/**
 * \brief Convert from coordinate string to coordinate
 *
 * Supported:
 * g.dddd
 * g.mm.ddd
 * g.mm.ss.dddd
 *
 * \param   CoorString  String to convert
 * \return              Coordinte. 0 on error.
 */
double StringToCoor(const CXStringASCII &CoorString);

//-------------------------------------
/**
 * \brief Delete ordered node list including all nodes.
 *
 * \param   pNodeList   Node list to delete.
 */
void DeleteOrderedNodeList(CXOrderedNodeList *pNodeList);

//-------------------------------------
/**
 * \brief Delete area including all node lists and nodes.
 *
 * \param   pArea   Area to delete.
 */
void DeleteArea(CXArea *pArea);

//-------------------------------------
/**
 * \brief Crop ordered node list on a specific X or Y axis.
 *
 * \todo comment
 *
 * \param   pOrderedNodeList    Node list to crop.
 * \param   oHorizontal         true if horizontal line.
 * \param   XY                  Crop limit.
 * \param   oDeleteGreater      Delete nodes with coordinate greater than crop limit.
 */
void CropOrderedNodeListXY(CXOrderedNodeList *pOrderedNodeList, bool oHorizontal, int XY, bool oDeleteGreater);

//-------------------------------------
/**
 * \brief Crop ordered node list to a specific rectangle.
 *
 * A new ordered node list is returned. If completely outside, NULL is returned!
 * It has to be deleted after this call, including its nodes!!!
 *
 * \param   pOrderedNodeList    Node list to crop.
 * \param   XMin                Min X coordinate.
 * \param   YMin                Min Y coordinate.
 * \param   XMax                Max X coordinate.
 * \param   YMax                Max Y coordinate.
 * \return                      New ordered node list. Has to be deleted after this call including its nodes.
 */
CXOrderedNodeList *CropOrderedNodeList(CXOrderedNodeList *pOrderedNodeList, int XMin, int YMin, int XMax, int YMax);

//-------------------------------------
/**
 * \brief Crop area to a specific rectangle.
 *
 * A new area is returned. It has to be deleted after this call
 *
 * \param   pArea   Area to crop.
 * \param   XMin    Min X coordinate.
 * \param   YMin    Min Y coordinate.
 * \param   XMax    Max X coordinate.
 * \param   YMax    Max Y coordinate.
 * \return          New area. Has to be deleted after this call.
 */
CXArea *CropArea(CXArea *pArea, int XMin, int YMin, int XMax, int YMax);

//-------------------------------------
/**
 * \brief Convert from integer value to string.
 *
 * \param   Value   Value to convert.
 * \return          Converted value.
 */
template<class tData> tData IToA(int Value, size_t MinLength = 1) {
    tData Result;
    // check if negative number
    bool oNegative = false;
    if(Value < 0) {
        oNegative = true;
        Value = -Value;
    }
    // create string from end to start
    while(Value != 0) {
        int Rest = Value % 10;
        Value = Value / 10;
        if(Result.GetSize() == 0) {
            // first character, so append
            Result.Append('0'+Rest);
        } else {
            // insert character
            Result.InsertAt(0, '0'+Rest);
        }
    }
    // check if empty string
    while(Result.GetSize() < MinLength) {
        if(Result.GetSize() == 0) {
            // first character, so append
            Result.Append('0');
        } else {
            // insert
            Result.InsertAt(0, '0');
        }
    }
    // check if negative number
    if(oNegative)
        Result.InsertAt(0, '-');
    return Result;
}

//-------------------------------------
/**
 * \brief Convert from double value to string.
 *
 * \param   Value   Value to convert.
 * \return          Converted value.
 */
template<class tData> tData FToA(double Value, size_t MinLength = 1, size_t MinDecimalLength = 1) {
    // check if negative number
    bool oNegative = false;
    if(Value < 0) {
        oNegative = true;
        Value = -Value;
    }
    int Int = static_cast<int>(floor(Value));
    double dRest = Value - Int;
    for(size_t i=0; i<MinDecimalLength; i++) {
        dRest = dRest*10;
    }
    int Rest = static_cast<int>(floor(dRest));
    // convert Int
    tData Result = IToA<tData>(Int, MinLength);
    // convert Rest
    tData ResultRest = IToA<tData>(Rest, MinDecimalLength);
    // Append if necessary
    if(MinDecimalLength != 0) {
        Result = Result + "." + ResultRest;
    }
    // check if negative number
    if(oNegative)
        Result.InsertAt(0, '-');
    return Result;
}

#endif // __UTILS_HPP__
