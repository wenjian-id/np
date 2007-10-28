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

#include "TargetIncludes.hpp"
#include "CXRGB.hpp"

//-------------------------------------
void DoOutputDebugString(const char *pcBuf) {
	OutputDebugString(pcBuf);
}

//-------------------------------------
void DoOutputErrorMessage(const char *pcBuf) {
	::MessageBox(NULL, pcBuf, "NaviPOWM error", MB_OK | MB_ICONERROR);
}

//-------------------------------------
CXRGB COLORREF2CXRGB(const COLORREF & Color) {
	return CXRGB(GetRValue(Color), GetGValue(Color), GetBValue(Color));
}

//-------------------------------------
COLORREF CXRGB2COLORREF(const CXRGB & Color) {
	return RGB(Color.GetR(), Color.GetG(), Color.GetB());
}
