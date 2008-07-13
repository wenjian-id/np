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

#ifndef __TARGETINCLUDES_HPP__
#define __TARGETINCLUDES_HPP__

#include <windows.h>
#include <stdio.h>

#define WAIT_INFINITE INFINITE

#ifndef t_uint32
typedef unsigned __int32 t_uint32;
#endif

#ifndef t_uint64
typedef unsigned __int64 t_uint64;
#endif

#ifndef snprintf
#define snprintf _snprintf
#endif

#define NP_LEFT VK_LEFT
#define NP_RIGHT VK_RIGHT

class CXRGB;

//-------------------------------------
/*
 * \brief oiu
 *
 */
void DoOutputDebugString(const char *pcBuf);

//-------------------------------------
/*
 * \brief oiu
 *
 */
void DoOutputErrorMessage(const char *pcBuf);

//-------------------------------------
/*
 * \brief oiu
 *
 */
CXRGB COLORREF2CXRGB(const COLORREF & Color);

//-------------------------------------
/*
 * \brief oiu
 *
 */
COLORREF CXRGB2COLORREF(const CXRGB & Color);

#endif // __TARGETINCLUDES_HPP__
