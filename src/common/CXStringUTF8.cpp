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

#include "CXStringUTF8.hpp"

//-------------------------------------
CXStringUTF8::CXStringUTF8() :
    m_wbuf(NULL),
    m_ucbuf(NULL)
{
}

//-------------------------------------
CXStringUTF8::CXStringUTF8(const CXStringUTF8 &rOther) :
    tUCBuffer(rOther),
    m_wbuf(NULL),
    m_ucbuf(NULL)
{
}

//-------------------------------------
CXStringUTF8::CXStringUTF8(const char *pcChar) :
    m_wbuf(NULL),
    m_ucbuf(NULL)
{
    if(pcChar != NULL) {
        // since ASCII can be convertet 1:1 to UTF-8 we take it
        size_t Len = strlen(pcChar);
        unsigned char *pTmp = new unsigned char[Len];
        memcpy(pTmp, pcChar, Len);
        for(size_t i=0; i<Len; i++)
            pTmp[i] = pTmp[i] & 0x7F;
        tUCBuffer::Append(pTmp, Len);
        delete [] pTmp;
    }
}

//-------------------------------------
CXStringUTF8::CXStringUTF8(const char *pcChar, size_t Len) :
    m_wbuf(NULL),
    m_ucbuf(NULL)
{
    if(pcChar != NULL) {
        // since ASCII can be convertet 1:1 to UTF-8 we take it
        unsigned char *pTmp = new unsigned char[Len];
        memcpy(pTmp, pcChar, Len);
        for(size_t i=0; i<Len; i++)
            pTmp[i] = pTmp[i] & 0x7F;
        tUCBuffer::Append(pTmp, Len);
        delete [] pTmp;
    }
}

//-------------------------------------
CXStringUTF8::~CXStringUTF8() {
    ClearSTRBuffers();
}

//-------------------------------------
void CXStringUTF8::ClearSTRBuffers() {
    delete [] m_wbuf;
    m_wbuf = NULL;
    delete [] m_ucbuf;
    m_ucbuf = NULL;
}

//-------------------------------------
const CXStringUTF8 & CXStringUTF8::operator = (const CXStringUTF8 &rOther) {
    if(this != &rOther) {
        tUCBuffer::operator = (rOther);
        ClearSTRBuffers();
    }
    return *this;
}

//-------------------------------------
const CXStringUTF8 & CXStringUTF8::operator = (const tUCBuffer &rOther) {
    if(this != &rOther) {
        tUCBuffer::operator = (rOther);
        ClearSTRBuffers();
    }
    return *this;
}

//-------------------------------------
bool CXStringUTF8::operator == (const CXStringUTF8 &rOther) {
    return tUCBuffer::operator == (rOther);
}

//-------------------------------------
bool CXStringUTF8::operator != (const CXStringUTF8 &rOther) {
    return !(tUCBuffer::operator == (rOther));
}

//-------------------------------------
void CXStringUTF8::operator += (const CXStringUTF8 &rOther) {
    Append(rOther.GetBuffer(), rOther.GetSize());
    ClearSTRBuffers();
}

//-------------------------------------
CXStringUTF8 CXStringUTF8::operator + (const char *pcString) const {
    CXStringUTF8 Result(*this);
    Result.Append(reinterpret_cast<const unsigned char *>(pcString), strlen(pcString));
    return Result;
}

//-------------------------------------
CXStringUTF8 CXStringUTF8::operator + (const CXStringUTF8 &rOther) const {
    CXStringUTF8 Result(*this);
    Result.Append(rOther.GetBuffer(), rOther.GetSize());
    return Result;
}

//-------------------------------------
void CXStringUTF8::Empty() {
    Clear();
    ClearSTRBuffers();
}

#define     MASKBITS        0x3F
#define     MASKBYTE        0x80
#define     MASK2BYTES      0xC0
#define     MASK3BYTES      0xE0

//-------------------------------------
wchar_t *CXStringUTF8::w_str() const {
    if(m_wbuf == NULL) {
        CXBuffer<wchar_t> tmp;

        const unsigned char *pBuf = GetBuffer();

        for(size_t i=0; i < GetSize();) {
            wchar_t wt = 0;

            // 1110xxxx 10xxxxxx 10xxxxxx
            if((pBuf[i] & MASK3BYTES) == MASK3BYTES) {
                wt = ((pBuf[i] & 0x0F) << 12) | ((pBuf[i+1] & MASKBITS) << 6) | (pBuf[i+2] & MASKBITS);
                i += 3;
            }
            // 110xxxxx 10xxxxxx
            else if((pBuf[i] & MASK2BYTES) == MASK2BYTES) {
                wt = ((pBuf[i] & 0x1F) << 6) | (pBuf[i+1] & MASKBITS);
                i += 2;
            }
            // 0xxxxxxx
            else if(pBuf[i] < MASKBYTE) {
                wt = pBuf[i];
                i += 1;
            }
            else {
                continue;
            }

            tmp.Append(wt);
        }

        // convert to wchar_t.
        size_t Size = tmp.GetSize() + 1;
        m_wbuf = new wchar_t[Size];
        m_wbuf[Size-1] = 0;
        memmove(m_wbuf, tmp.GetBuffer(), tmp.GetSize()*sizeof(wchar_t));
    }
    return m_wbuf;
}

//-------------------------------------
unsigned char *CXStringUTF8::uc_str() const {
    if(m_ucbuf == NULL) {
        size_t Size = GetSize() + 1;
        m_ucbuf = new unsigned char[Size];
        m_ucbuf[Size-1] = 0;
        memmove(m_ucbuf, GetBuffer(), Size-1);
    }
    return m_ucbuf;
}
