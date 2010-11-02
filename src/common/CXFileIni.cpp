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

#include "CXFileIni.hpp"
#include "Utils.hpp"

//-------------------------------------
CXFileIni::CXFileIni() {
}

//-------------------------------------
CXFileIni::~CXFileIni() {
    Clear();
}

//-------------------------------------
void CXFileIni::Clear() {
    // cleanup
    m_Content.RemoveAll();
}

//-------------------------------------
bool CXFileIni::Read(const CXStringASCII & FileName) {
    // first of all clear content
    Clear();
    // open file
    CXFile  TheFile;
    if(TheFile.Open(FileName.c_str(), CXFile::E_READ) != CXFile::E_OK) {
        return false;
    }
    CXStringASCII NewLine;
    CXStringASCII Key;
    CXStringASCII Value;
    while(ReadLineASCII(TheFile, NewLine)) {
        // extract comments
        size_t pos = NewLine.Find("//");
        if(pos != CXStringASCII::NPOS) {
            // throw away comment
            NewLine = NewLine.Left(pos);
        }
        // ok, now check for "="
        pos = NewLine.Find('=');
        if(pos != CXStringASCII::NPOS) {
            // extract key
            Key = NewLine.Left(pos);
            Key.TrimLeft();
            Key.TrimRight();
            // extract value
            Value = NewLine;
            Value.DeleteFirst(pos+1);
            Value.TrimLeft();
            Value.TrimRight();
            // add to m_Content;
            m_Content.SetAt(Key.ToUpper(), Value);
        }
    }
    return true;
}


//-------------------------------------
CXStringASCII CXFileIni::Get(const CXStringASCII & Key, const CXStringASCII & Default) {
    // search for key and value
    CXStringASCII Result;
    if(m_Content.Lookup(Key.ToUpper(), Result))
        // found something
        return Result;
    return Default;
}

//-------------------------------------
CXArray<CXStringASCII> CXFileIni::GetKeysStartingWith(const CXStringASCII & Key) {
    CXArray<CXStringASCII> Result;
    CXStringASCII UpperKey = Key.ToUpper();
    CXPOSMapSimple<CXStringASCII> Pos = m_Content.GetStart();
    CXStringASCII Value;
    while(m_Content.GetNext(Pos, Value) != m_Content.NPOS) {
        if(Pos.m_key.Find(UpperKey) != CXStringASCII::NPOS)
            Result.Append(Pos.m_key);
    }
    return Result;
}
