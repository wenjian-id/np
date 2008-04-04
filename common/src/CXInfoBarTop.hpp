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

#ifndef __CXINFOBARTOP_HPP__
#define __CXINFOBARTOP_HPP__

#include "CXInfoBar.hpp"
#include "CXNaviData.hpp"
#include "CXBitmap.hpp"

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXInfoBarTop : public CXInfoBar {
private:
	CXNaviData			m_NaviData;		///< oiu
	CXBitmap			m_InfoBmp;		///< oiu
	CXBitmap			m_QuitBmp;		///< oiu
	CXBitmap			m_SaveOnBmp;	///< oiu
	CXBitmap			m_SaveOffBmp;	///< oiu
	CXBitmap			m_MinimizeBmp;	///< oiu
	tIRect				m_InfoRect;		///< oiu
	tIRect				m_QuitRect;		///< oiu
	tIRect				m_SatRect;		///< oiu
	tIRect				m_SaveRect;		///< oiu
	tIRect				m_MinimizeRect;	///< oiu
	//-------------------------------------
	CXInfoBarTop(const CXInfoBarTop &);						///< Not used.
	const CXInfoBarTop & operator = (const CXInfoBarTop &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual E_COMMAND OnInternalMouseDown(int X, int Y);
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXInfoBarTop();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXInfoBarTop();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void PositionChanged(const CXNaviData & NewData);
};

#endif // __CXINFOBARTOP_HPP__
