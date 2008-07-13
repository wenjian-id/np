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

#ifndef __CXSTRINGUTF8_HPP__
#define __CXSTRINGUTF8_HPP__

#include <TargetIncludes.hpp>
#include "CXBuffer.hpp"

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class  CXStringUTF8 : public tUCBuffer {
private:
	mutable wchar_t			*m_wbuf;	///< oiu
	mutable unsigned char	*m_ucbuf;	///< oiu
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8(const CXStringUTF8 &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8(const char *pcChar);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringUTF8(const char *pcChar, size_t Len);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXStringUTF8();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXStringUTF8 & operator = (const CXStringUTF8 &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXStringUTF8 & operator = (const tUCBuffer &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator == (const CXStringUTF8 &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator != (const CXStringUTF8 &rOther);
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
	wchar_t *w_str() const ;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	unsigned char *uc_str() const;
};

#endif // __CXSTRINGUTF8_HPP__
