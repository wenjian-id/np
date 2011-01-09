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
 ***************************************************************************
 *   Code for datum and UTM conversion was adapted from C++ code written   *
 *   by Chuck Gantz (chuck.gantz@globalstar.com) taken from                *
 *   http://www.gpsy.com/gpsinfo/geotoutm/                                 *
 *   This URL has also many other references to information about          *
 *   conversion between different coordinate systems                       *
 ***************************************************************************/

#include "CoordConstants.h"

#ifndef LATLONGCONV
#define LATLONGCONV

//-------------------------------------
/**
 * \brief Convert longitude and latitude to UTM coordinates.
 *
 *  Convert longitude and latitude to UTM coordinates.
 *  \param  ReferenceEllipsoid      Ellipsoid to use.
 *  \param  dLon                    Longitude [decimal degrees].
 *  \param  dLat                    Latitude [decimal degrees].
 *  \param  ForceZoneNumber         Force coordinates to this zone number. If UTMZoneNone the UTM zone will be computed.
 *  \param  ZoneNumber              Computed UTM zone number.
 *  \param  UTMLetter               Computed UTM letter.
 *  \param  UTMEasting              Computed UTM easting.
 *  \param  UTMNorthing             Computed UTM northing.
 */
void LLtoUTM(int ReferenceEllipsoid, const double dLon, const double dLat, const int ForceZoneNumber, int & ZoneNumber, char & UTMLetter, double & UTMEasting, double & UTMNorthing);

//-------------------------------------
/**
 * \brief Convert UTM coordinates to longitude and latitude.
 *
 *  Convert UTM coordinates to longitude and latitude.
 *  \param  ReferenceEllipsoid      Ellipsoid to use.
 *  \param  UTMEasting              UTM easting.
 *  \param  UTMNorthing             UTM northing.
 *  \param  ZoneNumber              UTM zone number.
 *  \param  rdLon                   Computed longitude [decimal degrees].
 *  \param  rdLat                   Computed Latitude [decimal degrees].
 */
void UTMtoLL(int ReferenceEllipsoid, const double UTMEasting, const double UTMNorthing, const int ZoneNumber, const char UTMLetter, double & rdLon,  double & rdLat);

//-------------------------------------
/**
 * \brief Get UTM letter from latitude.
 *
 * Get UTM letter from latitude.
 */
char UTMLetterDesignator(double dLat);

#endif
