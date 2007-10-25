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

#ifndef __CXSTRINGASCII_HPP__
#define __CXSTRINGASCII_HPP__

#include <TargetIncludes.hpp>
#include "CXBuffer.hpp"

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class  CXStringASCII : public tCBuffer {
private:
	mutable char	*m_pcstr;
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII(const CXStringASCII &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII(const char *pcChar);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII(const char *pcChar, size_t Len);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXStringASCII();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXStringASCII & operator = (const CXStringASCII &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXStringASCII & operator = (const tCBuffer &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator == (const CXStringASCII &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator != (const CXStringASCII &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void operator += (char c);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void operator += (const CXStringASCII &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t Find(const char *pcFind) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t ReverseFind(char cFind) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t Find(char cFind) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void TrimLeft();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void TrimRight();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Empty();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const char *c_str() const;
};

#endif // __CXSTRINGASCII_HPP__
