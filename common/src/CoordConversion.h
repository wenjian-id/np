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
 ***************************************************************************
 *   Code for datum and UTM conversion was adapted from C++ code written   *
 *   by Chuck Gantz (chuck.gantz@globalstar.com) taken from                *
 *   http://www.gpsy.com/gpsinfo/geotoutm/                                 *
 *   This URL has also many other references to information about          *
 *   conversion between different coordinate systems                       *
 ***************************************************************************/

/// \todo check correctness of trnasformations

#include "CoordConstants.h"

#ifndef LATLONGCONV
#define LATLONGCONV

//-------------------------------------
void LLtoUTM(int ReferenceEllipsoid, const double Long, const double Lat, const int ForceZoneNumber, int &ZoneNumber, char & UTMLetter, double &UTMEasting, double &UTMNorthing);
//-------------------------------------
void UTMtoLL(int ReferenceEllipsoid, const double UTMEasting, const double UTMNorthing, const int ZoneNumber, const char UTMLetter, double& Lon,  double& Lat);
//-------------------------------------
char UTMLetterDesignator(double Lat);
//-------------------------------------
void LLtoSwissGrid(const double Lat, const double Long, double &SwissNorthing, double &SwissEasting);
//-------------------------------------
void SwissGridtoLL(const double SwissNorthing, const double SwissEasting, double& Lat, double& Long);

//-------------------------------------
class Ellipsoid {
public:
	Ellipsoid(){};
	Ellipsoid(int Id, const char* name, double radius, double ecc) {
		id = Id;
		ellipsoidName = name; 
		EquatorialRadius = radius;
		eccentricitySquared = ecc;
	}

	int id;
	const char* ellipsoidName;
	double EquatorialRadius; 
	double eccentricitySquared;  
};


#endif
