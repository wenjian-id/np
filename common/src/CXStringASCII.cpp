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
	delete [] m_pcstr;
	m_pcstr = NULL;
}

//-------------------------------------
const CXStringASCII & CXStringASCII::operator = (const CXStringASCII &rOther) {
	if(this != &rOther)
		tCBuffer::operator = (rOther);
	return *this;
}

//-------------------------------------
const CXStringASCII & CXStringASCII::operator = (const tCBuffer &rOther) {
	if(this != &rOther)
		tCBuffer::operator = (rOther);
	return *this;
}

//-------------------------------------
bool CXStringASCII::operator == (const CXStringASCII &rOther) {
	return tCBuffer::operator == (rOther);
}

//-------------------------------------
bool CXStringASCII::operator != (const CXStringASCII &rOther) {
	return !(tCBuffer::operator == (rOther));
}

//-------------------------------------
void CXStringASCII::operator += (char c) {
	Append(c);
}

//-------------------------------------
void CXStringASCII::operator += (const CXStringASCII &rOther) {
	Append(rOther.GetBuffer(), rOther.GetSize());
}

//-------------------------------------
size_t CXStringASCII::Find(const char *pcFind) const {
	if(pcFind == NULL)
		return NPOS;
	return tCBuffer::Find(pcFind, strlen(pcFind));
}

//-------------------------------------
size_t CXStringASCII::Find(char cFind) const {
	return tCBuffer::Find(cFind);
}

//-------------------------------------
size_t CXStringASCII::ReverseFind(char cFind) const {
	return tCBuffer::ReverseFind(cFind);
}

//-------------------------------------
void CXStringASCII::TrimLeft() {
	while((GetSize() > 0) && ((*this)[0] == ' '))
		DeleteFirst(1);
}

//-------------------------------------
void CXStringASCII::TrimRight() {
	while((GetSize() > 0) && ((*this)[GetSize()-1] == ' '))
		DeleteLast(1);
}

//-------------------------------------
void CXStringASCII::Empty() {
	Clear();
}

//-------------------------------------
const char *CXStringASCII::c_str() const {
	delete [] m_pcstr;
	size_t Len = GetSize() + 1;
	m_pcstr = new char[Len];
	memset(m_pcstr, 0, Len);
	memcpy(m_pcstr, GetBuffer(), GetSize());
	return m_pcstr;
}
