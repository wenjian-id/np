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

#ifndef __CXPEN_H__
#define __CXPEN_H__

#include "CXRGB.hpp"

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXPen {
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	enum E_STYLE {
		e_Solid,		///< oiu
	};
private:
	E_STYLE		m_eStyle;	///< oiu
	int			m_iWidth;	///< oiu
	CXRGB		m_Color;	///< oiu
	//-------------------------------------
	CXPen();											///< Not used.
	//-------------------------------------
	/*
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXPen &rOther);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXPen(E_STYLE eStyle, int Width, const CXRGB & Color);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXPen(const CXPen &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXPen & operator = (const CXPen & rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXPen();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	E_STYLE GetStyle() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetStyle(E_STYLE NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetWidth() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetWidth(int NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRGB GetColor() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetColor(const CXRGB & NewValue);
};

#endif //__CXPEN_H__
