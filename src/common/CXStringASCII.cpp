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

#include "CXStringASCII.hpp"

//-------------------------------------
CXStringASCII::CXStringASCII() :
    m_pcstr(NULL)
{
}

//-------------------------------------
CXStringASCII::CXStringASCII(const CXStringASCII &rOther) :
    tCBuffer(rOther),
    m_pcstr(NULL)
{
}

//-------------------------------------
CXStringASCII::CXStringASCII(const tCBuffer &rOther) :
    tCBuffer(rOther),
    m_pcstr(NULL)
{
}

//-------------------------------------
CXStringASCII::CXStringASCII(const char *pcChar) :
    m_pcstr(NULL)
{
    if(pcChar != NULL)
        tCBuffer::Append(pcChar, strlen(pcChar));
}

//-------------------------------------
CXStringASCII::CXStringASCII(const char *pcChar, size_t Len) :
    m_pcstr(NULL)
{
    if(pcChar != NULL)
        tCBuffer::Append(pcChar, Len);
}

//-------------------------------------
CXStringASCII::~CXStringASCII() {
    ClearSTRBuffers();
}

//-------------------------------------
void CXStringASCII::ClearSTRBuffers() {
    delete [] m_pcstr;
    m_pcstr = NULL;
}

//-------------------------------------
const CXStringASCII & CXStringASCII::operator = (const CXStringASCII &rOther) {
    if(this != &rOther) {
        tCBuffer::operator = (rOther);
        ClearSTRBuffers();
    }
    return *this;
}

//-------------------------------------
const CXStringASCII & CXStringASCII::operator = (const tCBuffer &rOther) {
    if(this != &rOther) {
        tCBuffer::operator = (rOther);
        ClearSTRBuffers();
    }
    return *this;
}

//-------------------------------------
bool CXStringASCII::operator == (const CXStringASCII &rOther) const {
    return tCBuffer::operator == (rOther);
}

//-------------------------------------
bool CXStringASCII::operator != (const CXStringASCII &rOther) const {
    return !(tCBuffer::operator == (rOther));
}

//-------------------------------------
void CXStringASCII::operator += (char c) {
    Append(c);
    ClearSTRBuffers();
}

//-------------------------------------
void CXStringASCII::operator += (const CXStringASCII &rOther) {
    Append(rOther.GetBuffer(), rOther.GetSize());
    ClearSTRBuffers();
}

//-------------------------------------
CXStringASCII CXStringASCII::operator + (const char *pcString) const {
    CXStringASCII Result(*this);
    Result.Append(pcString, strlen(pcString));
    return Result;
}

//-------------------------------------
CXStringASCII CXStringASCII::operator + (const CXStringASCII &rOther) const {
    CXStringASCII Result(*this);
    Result.Append(rOther.GetBuffer(), rOther.GetSize());
    return Result;
}

//-------------------------------------
bool CXStringASCII::operator < (const CXStringASCII &rOther) const {
    return tCBuffer::operator < (rOther);
}

//-------------------------------------
bool CXStringASCII::operator > (const CXStringASCII &rOther) const {
    return tCBuffer::operator > (rOther);
}

//-------------------------------------
size_t CXStringASCII::Find(const char *pcFind) const {
    if(pcFind == NULL)
        return NPOS;
    return tCBuffer::Find(pcFind, strlen(pcFind));
}

//-------------------------------------
size_t CXStringASCII::Find(const CXStringASCII &FindString) const {
    return Find(FindString.c_str());
}

//-------------------------------------
size_t CXStringASCII::Find(char cFind) const {
    return tCBuffer::Find(cFind);
}

//-------------------------------------
size_t CXStringASCII::Count(char cFind) const {
    return tCBuffer::Count(cFind);
}

//-------------------------------------
size_t CXStringASCII::ReverseFind(char cFind) const {
    return tCBuffer::ReverseFind(cFind);
}

//-------------------------------------
void CXStringASCII::TrimLeft() {
    size_t OldSize = GetSize();
    while((GetSize() > 0) && ((*this)[0] == ' '))
        DeleteFirst(1);
    // check if size changed
    if(OldSize != GetSize())
        ClearSTRBuffers();
}

//-------------------------------------
void CXStringASCII::TrimRight() {
    size_t OldSize = GetSize();
    while((GetSize() > 0) && ((*this)[GetSize()-1] == ' '))
        DeleteLast(1);
    // check if size changed
    if(OldSize != GetSize())
        ClearSTRBuffers();
}

//-------------------------------------
void CXStringASCII::Empty() {
    Clear();
    ClearSTRBuffers();
}

//-------------------------------------
CXStringASCII CXStringASCII::ToUpper() const {
    CXStringASCII Result(*this);
    size_t Len = Result.GetSize();
    char * pBuffer = Result.GetBufferWritable();
    for(size_t i=0; i< Len; i++) {
        if((pBuffer[i] >= 'a') && (pBuffer[i] <= 'z'))
            pBuffer[i] = pBuffer[i] - 'a' + 'A';
    }
    return Result;
}


//-------------------------------------
CXStringASCII CXStringASCII::ToLower() const {
    CXStringASCII Result(*this);
    size_t Len = Result.GetSize();
    char * pBuffer = Result.GetBufferWritable();
    for(size_t i=0; i< Len; i++) {
        if((pBuffer[i] >= 'A') && (pBuffer[i] <= 'Z'))
            pBuffer[i] = pBuffer[i] - 'A' + 'a';
    }
    return Result;
}

//-------------------------------------
double CXStringASCII::ToDouble() const {
    double Ret = 0;
    size_t Index = 0;
    bool oDot = false;
    bool oMinus = false;
    double dFactor = 1.0;
    while(Index != GetSize()) {
        char c = (*this)[Index];
        if((c == '.') && !oDot) {
            oDot = true;
        } else if((Index == 0) && (c == '-')) {
            oMinus = true;
        } else if((c < '0') || (c > '9')) {
            return 0;
        }
        char V = c - '0';
        if((c != '.') && (c != '-')) {
            if(!oDot) {
                Ret = Ret*10 + V;
            } else {
                dFactor = dFactor / 10.0;
                Ret = Ret + dFactor*V;

            }
        }
        Index++;
    }
    if(oMinus)
        Ret = -Ret;
    return Ret;
}

//-------------------------------------
int CXStringASCII::ToInt() const {
    int Ret = 0;
    bool oMinus = false;
    size_t Index = 0;
    while(Index != GetSize()) {
        char c = (*this)[Index];
        if((Index == 0) && (c == '-')) {
            oMinus = true;
        } else if((c < '0') || (c > '9')) {
            return 0;
        } else {
            char V = c - '0';
            Ret = Ret*10 + V;
        }
        Index++;
    }
    if(oMinus)
        Ret = -Ret;
    return Ret;
}

//-------------------------------------
int CXStringASCII::ToIntFromHex() const {
    int Ret = 0;
    size_t Index = 0;
    while(Index != GetSize()) {
        char c = (*this)[Index];
        char V = 0;
        if((c >= '0') && (c <= '9')) {
            V = c - '0';
        } else if((c >= 'a') && (c <= 'f')) {
            V = c - 'a' + 10;
        } else if((c >= 'A') && (c <= 'F')) {
            V = c - 'A' + 10;
        } else {
            return 0;
        }
        Ret = Ret*16 + V;
        Index++;
    }
    return Ret;
}

//-------------------------------------
const char *CXStringASCII::c_str() const {
    if(m_pcstr == NULL) {
        size_t Size = GetSize()+1; // + trailing 0
        m_pcstr = new char[Size];
        m_pcstr[Size-1] = 0;
        memmove(m_pcstr, GetBuffer(), Size-1);
    }
    return m_pcstr;
}
