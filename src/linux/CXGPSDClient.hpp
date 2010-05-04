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


#ifndef __CXGPSDCLIENT_HPP__
#define __CXGPSDCLIENT_HPP__

#include <gps.h>

#if (GPSD_API_MAJOR_VERSION < 3)
	#error Version 2.x or 1.x
#elif (GPSD_API_MAJOR_VERSION == 3)
	#include "CXGPSDClient3.hpp"
#elif (GPSD_API_MAJOR_VERSION == 4)
	#include "CXGPSDClient4.hpp"
#else
	#error Version > 4.x
#endif


#endif // __CXGPSDCLIENT_HPP__
