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

#ifndef __TARGETINCLUDES_HPP__
#define __TARGETINCLUDES_HPP__

#include <stddef.h>
#include <string.h>
#include <qglobal.h>

class CXRGB;
class QColor;

#ifndef t_uint32
typedef quint32 t_uint32;
#endif

#ifndef t_uint64
typedef quint64 t_uint64;
#endif

#define WAIT_INFINITE ULONG_MAX

#define NP_LEFT Qt::Key_Left
#define NP_RIGHT Qt::Key_Right

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
QColor CXRGB2QColor(const CXRGB & Color);

//-------------------------------------
/*
 * \brief oiu
 *
 */
CXRGB QColor2CXRGB(const QColor & Color);

#endif // __TARGETINCLUDES_HPP__
