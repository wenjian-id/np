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

#ifndef __CXRECT_HPP__
#define __CXRECT_HPP__

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
template<class tClass> class CXRect {
private:
	tClass		m_Left;		///< oiu
	tClass		m_Top;		///< oiu
	tClass		m_Right;	///< oiu
	tClass		m_Bottom;	///< oiu
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void CopyFrom(const CXRect &rOther);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRect();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRect(const tClass &Left, const tClass &Top, const tClass &Right, const tClass &Bottom);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRect(const CXRect &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXRect();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXRect & operator = (const CXRect &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass GetTop() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetTop(const tClass & NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass GetLeft() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLeft(const tClass & NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass GetBottom() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetBottom(const tClass & NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass GetRight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetRight(const tClass & NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass GetWidth() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass GetHeight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void OffsetRect(const tClass & dx, const tClass & dy);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool Contains(const tClass & x, const tClass & y);
};

typedef CXRect<int> tIRect;

//-------------------------------------
template<class tClass> CXRect<tClass> ::CXRect() {
	// leave values uninitialized
}

//-------------------------------------
template<class tClass> CXRect<tClass> ::CXRect(const tClass &Left, const tClass &Top, const tClass &Right, const tClass &Bottom) :
	m_Left(Left),
	m_Top(Top),
	m_Right(Right),
	m_Bottom(Bottom)
{
}

//-------------------------------------
template<class tClass> CXRect<tClass> ::CXRect(const CXRect &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
template<class tClass> CXRect<tClass> ::~CXRect() {
}

//-------------------------------------
template<class tClass> const CXRect<tClass> & CXRect<tClass> ::operator = (const CXRect &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
template<class tClass> void CXRect<tClass> ::CopyFrom(const CXRect &rOther) {
	m_Left = rOther.m_Left;
	m_Top = rOther.m_Top;
	m_Right = rOther.m_Right;
	m_Bottom = rOther.m_Bottom;
}

//-------------------------------------
template<class tClass> tClass CXRect<tClass> ::GetTop() const {
	return m_Top;
}

//-------------------------------------
template<class tClass> void CXRect<tClass> ::SetTop(const tClass & NewValue) {
	m_Top = NewValue;
}

//-------------------------------------
template<class tClass> tClass CXRect<tClass> ::GetLeft() const {
	return m_Left;
}

//-------------------------------------
template<class tClass> void CXRect<tClass> ::SetLeft(const tClass & NewValue) {
	m_Left = NewValue;
}

//-------------------------------------
template<class tClass> tClass CXRect<tClass> ::GetBottom() const {
	return m_Bottom;
}

//-------------------------------------
template<class tClass> void CXRect<tClass> ::SetBottom(const tClass & NewValue) {
	m_Bottom = NewValue;
}

//-------------------------------------
template<class tClass> tClass CXRect<tClass> ::GetRight() const {
	return m_Right;
}

//-------------------------------------
template<class tClass> void CXRect<tClass> ::SetRight(const tClass & NewValue) {
	m_Right = NewValue;
}

//-------------------------------------
template<class tClass> tClass CXRect<tClass> ::GetWidth() const {
	return m_Right - m_Left;
}

//-------------------------------------
template<class tClass> tClass CXRect<tClass> ::GetHeight() const {
	return m_Bottom - m_Top;
}

//-------------------------------------
template<class tClass> void CXRect<tClass> ::OffsetRect(const tClass & dx, const tClass & dy) {
	m_Left += dx;
	m_Top += dy;
	m_Right += dx;
	m_Bottom += dy;
}

//-------------------------------------
template<class tClass> bool CXRect<tClass> ::Contains(const tClass & x, const tClass & y) {
	return (m_Left <= x) && (x <= m_Right) && (m_Top <= y) && (y <= m_Bottom);
}

#endif // __CXRECT_HPP__
