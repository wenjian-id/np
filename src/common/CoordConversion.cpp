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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "CoordConstants.h"
#include "CoordConversion.h"

void LLtoUTM(int ReferenceEllipsoid, const double dLon, const double dLat, const int ForceZoneNumber, int &ZoneNumber, char & UTMLetter, double &UTMEasting, double &UTMNorthing) {
    //converts lat/long to UTM coords.  Equations from USGS Bulletin 1532
    //East Longitudes are positive, West longitudes are negative.
    //North latitudes are positive, South latitudes are negative
    //dLat and dLon are in decimal degrees
    //Written by Chuck Gantz- chuck.gantz@globalstar.com

    double a = ellipsoid[ReferenceEllipsoid].EquatorialRadius;
    double eccSquared = ellipsoid[ReferenceEllipsoid].eccentricitySquared;
    double k0 = 0.9996;

    double LongOrigin=0;
    double eccPrimeSquared=0;
    double N=0, T=0, C=0, A=0, M=0;

    //Make sure the longitude is between -180.00 .. 179.9
    double LongTemp = (dLon+180)-int((dLon+180)/360)*360-180; // -180.00 .. 179.9;

    double LatRad = dLat*deg2rad;
    double LongRad = LongTemp*deg2rad;
    double LongOriginRad=0;

    ZoneNumber = int((LongTemp + 180)/6) + 1;

    if( dLat >= 56.0 && dLat < 64.0 && LongTemp >= 3.0 && LongTemp < 12.0 )
        ZoneNumber = 32;

      // Special zones for Svalbard
    if( dLat >= 72.0 && dLat < 84.0 ) {
        if(      LongTemp >= 0.0  && LongTemp <  9.0 )
            ZoneNumber = 31;
        else if( LongTemp >= 9.0  && LongTemp < 21.0 )
            ZoneNumber = 33;
        else if( LongTemp >= 21.0 && LongTemp < 33.0 )
            ZoneNumber = 35;
        else if( LongTemp >= 33.0 && LongTemp < 42.0 )
            ZoneNumber = 37;
     }
    if(ForceZoneNumber != UTMZoneNone) {
        ZoneNumber = ForceZoneNumber;
    }
    LongOrigin = (ZoneNumber - 1)*6 - 180 + 3;  //+3 puts origin in middle of zone
    LongOriginRad = LongOrigin * deg2rad;

    //compute the UTM Zone from the latitude and longitude
    UTMLetter = UTMLetterDesignator(dLat);

    eccPrimeSquared = (eccSquared)/(1-eccSquared);

    N = a/sqrt(1-eccSquared*sin(LatRad)*sin(LatRad));
    T = tan(LatRad)*tan(LatRad);
    C = eccPrimeSquared*cos(LatRad)*cos(LatRad);
    A = cos(LatRad)*(LongRad-LongOriginRad);

    M = a*((1- eccSquared/4- 3*eccSquared*eccSquared/64- 5*eccSquared*eccSquared*eccSquared/256)*LatRad
    - (3*eccSquared/8+ 3*eccSquared*eccSquared/32+ 45*eccSquared*eccSquared*eccSquared/1024)*sin(2*LatRad)
    + (15*eccSquared*eccSquared/256 + 45*eccSquared*eccSquared*eccSquared/1024)*sin(4*LatRad)
    - (35*eccSquared*eccSquared*eccSquared/3072)*sin(6*LatRad));

    UTMEasting = (double)(k0*N*(A+(1-T+C)*A*A*A/6
    + (5-18*T+T*T+72*C-58*eccPrimeSquared)*A*A*A*A*A/120)
    + 500000.0);

    UTMNorthing = (double)(k0*(M+N*tan(LatRad)*(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24
     + (61-58*T+T*T+600*C-330*eccPrimeSquared)*A*A*A*A*A*A/720)));
}

char UTMLetterDesignator(double dLat)
{
    //This routine determines the correct UTM letter designator for the given latitude
    //returns 'Z' if latitude is outside the UTM limits of 84N to 80S
    //Written by Chuck Gantz- chuck.gantz@globalstar.com
    char LetterDesignator;

    if((84 >= dLat) && (dLat >= 72))
        LetterDesignator = 'X';
    else if((72 > dLat) && (dLat >= 64))
        LetterDesignator = 'W';
    else if((64 > dLat) && (dLat >= 56))
        LetterDesignator = 'V';
    else if((56 > dLat) && (dLat >= 48))
        LetterDesignator = 'U';
    else if((48 > dLat) && (dLat >= 40))
        LetterDesignator = 'T';
    else if((40 > dLat) && (dLat >= 32))
        LetterDesignator = 'S';
    else if((32 > dLat) && (dLat >= 24))
        LetterDesignator = 'R';
    else if((24 > dLat) && (dLat >= 16))
        LetterDesignator = 'Q';
    else if((16 > dLat) && (dLat >= 8))
        LetterDesignator = 'P';
    else if(( 8 > dLat) && (dLat >= 0))
        LetterDesignator = 'N';
    else if(( 0 > dLat) && (dLat >= -8))
        LetterDesignator = 'M';
    else if((-8> dLat) && (dLat >= -16))
        LetterDesignator = 'L';
    else if((-16 > dLat) && (dLat >= -24))
        LetterDesignator = 'K';
    else if((-24 > dLat) && (dLat >= -32))
        LetterDesignator = 'J';
    else if((-32 > dLat) && (dLat >= -40))
        LetterDesignator = 'H';
    else if((-40 > dLat) && (dLat >= -48))
        LetterDesignator = 'G';
    else if((-48 > dLat) && (dLat >= -56))
        LetterDesignator = 'F';
    else if((-56 > dLat) && (dLat >= -64))
        LetterDesignator = 'E';
    else if((-64 > dLat) && (dLat >= -72))
        LetterDesignator = 'D';
    else if((-72 > dLat) && (dLat >= -80))
        LetterDesignator = 'C';
    else
        LetterDesignator = 'Z'; //This is here as an error flag to show that the Latitude is outside the UTM limits

    return LetterDesignator;
}


void UTMtoLL(int ReferenceEllipsoid, const double UTMEasting, const double UTMNorthing, const int ZoneNumber, const char UTMLetter, double& rdLon,  double& rdLat) {
    //converts UTM coords to lat/long.  Equations from USGS Bulletin 1532
    //East Longitudes are positive, West longitudes are negative.
    //North latitudes are positive, South latitudes are negative
    //rdLat and rdLon are in decimal degrees.
    //Written by Chuck Gantz- chuck.gantz@globalstar.com

    double k0 = 0.9996;
    double a = ellipsoid[ReferenceEllipsoid].EquatorialRadius;
    double eccSquared = ellipsoid[ReferenceEllipsoid].eccentricitySquared;
    double eccPrimeSquared=0;
    double e1 = (1-sqrt(1-eccSquared))/(1+sqrt(1-eccSquared));
    double N1=0, T1=0, C1=0, R1=0, D=0, M=0;
    double LongOrigin=0;
    double mu=0,  phi1Rad=0;
    double x=0, y=0;

    x = UTMEasting - 500000.0; //remove 500,000 meter offset for longitude
    y = UTMNorthing;

    LongOrigin = (ZoneNumber - 1)*6 - 180 + 3;  //+3 puts origin in middle of zone

    eccPrimeSquared = (eccSquared)/(1-eccSquared);

    M = y / k0;
    mu = M/(a*(1-eccSquared/4-3*eccSquared*eccSquared/64-5*eccSquared*eccSquared*eccSquared/256));

    phi1Rad = mu+ (3*e1/2-27*e1*e1*e1/32)*sin(2*mu)
    + (21*e1*e1/16-55*e1*e1*e1*e1/32)*sin(4*mu)
    +(151*e1*e1*e1/96)*sin(6*mu);

    N1 = a/sqrt(1-eccSquared*sin(phi1Rad)*sin(phi1Rad));
    T1 = tan(phi1Rad)*tan(phi1Rad);
    C1 = eccPrimeSquared*cos(phi1Rad)*cos(phi1Rad);
    R1 = a*(1-eccSquared)/pow(1-eccSquared*sin(phi1Rad)*sin(phi1Rad), 1.5);
    D = x/(N1*k0);

    rdLat = phi1Rad - (N1*tan(phi1Rad)/R1)*(D*D/2-(5+3*T1+10*C1-4*C1*C1-9*eccPrimeSquared)*D*D*D*D/24
    +(61+90*T1+298*C1+45*T1*T1-252*eccPrimeSquared-3*C1*C1)*D*D*D*D*D*D/720);
    rdLat = rdLat * rad2deg;

    rdLon = (D-(1+2*T1+C1)*D*D*D/6+(5-2*C1+28*T1-3*C1*C1+8*eccPrimeSquared+24*T1*T1)
    *D*D*D*D*D/120)/cos(phi1Rad);
    rdLon = LongOrigin + rdLon * rad2deg;
}
