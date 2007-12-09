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

#ifndef __CXINFOBARCOMMON_HPP__
#define __CXINFOBARCOMMON_HPP__

#include "CXInfoBar.hpp"
#include "CXNaviData.hpp"
#include "CXRect.hpp"

class CXBitmap;
class CXStringUTF8;

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXInfoBarCommon : public CXInfoBar {
private:
	CXNaviData			m_NaviData;	///< oiu
	//-------------------------------------
	CXInfoBarCommon(const CXInfoBarCommon &);						///< Not used.
	const CXInfoBarCommon & operator = (const CXInfoBarCommon &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int SetFontHeight(CXBitmap &Bmp, const CXStringUTF8 &Str, tIRect &rRect);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXInfoBarCommon();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXInfoBarCommon();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void PositionChanged(const CXNaviData & NewData);
};

#endif // __CXINFOBARCOMMON_HPP__