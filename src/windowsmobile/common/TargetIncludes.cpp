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

#include "TargetIncludes.hpp"
#include "Utils.hpp"
#include "CXRGB.hpp"

#include <tchar.h>

static TCHAR buf[1024];

//-------------------------------------
void DoOutputDebugString(const char *pcBuf) {
    if(pcBuf == NULL)
        return;
    for(size_t i=0; i<strlen(pcBuf); i++) {
        wsprintf(buf, _T("%c"), pcBuf[i]);
        OutputDebugString(buf);
    }
}

//-------------------------------------
void DoOutputErrorMessage(const char *pcBuf) {
    if(pcBuf == NULL)
        return;
    ASCII2UCS2(pcBuf, strlen(pcBuf), buf, 1024);
    ::MessageBox(NULL, buf, _T("NaviPOWM error"), MB_OK | MB_ICONERROR);
}

//-------------------------------------
CXRGB COLORREF2CXRGB(const COLORREF & Color) {
    return CXRGB(GetRValue(Color), GetGValue(Color), GetBValue(Color));
}

//-------------------------------------
COLORREF CXRGB2COLORREF(const CXRGB & Color) {
    return RGB(Color.GetR(), Color.GetG(), Color.GetB());
}

//-------------------------------------
void ASCII2UCS2(const char *pcBuffer, size_t InLen, TCHAR *Buf, size_t OutLen) {
    // do some tests
    if(Buf == NULL)
        return;
    if(pcBuffer == NULL) {
        *Buf = 0x00;
        return;
    }
    if((InLen == 0) || (OutLen <= 1)) {
        *Buf = 0x00;
        return;
    }
    size_t L = Min(InLen, OutLen-1);
    for(size_t i=0; i<L; i++)
        Buf[i] = pcBuffer[i];
    Buf[L] = 0x00;
}

//-------------------------------------
void UCS22ASCII(const TCHAR *pusBuffer, size_t InLen, char *Buf, size_t OutLen) {
    // do some tests
    if(pusBuffer == NULL) {
        return;
    if(Buf == NULL)
        *Buf = 0x00;
        return;
    }
    if((InLen == 0) || (OutLen <= 1)) {
        *Buf = 0x00;
        return;
    }
    size_t L = Min(InLen, OutLen-1);
    for(size_t i=0; i<L; i++)
        Buf[i] = (pusBuffer[i] & 0xff);
    Buf[L] = 0x00;
}

