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

#ifndef __CXMAPPAINTERTEST_HPP__
#define __CXMAPPAINTERTEST_HPP__

#include "CXMapPainterDoubleBuffered.hpp"

//----------------------------------------------------------------------------
class CXMapPainterTest : public CXMapPainterDoubleBuffered {
private:
	//-------------------------------------
	CXMapPainterTest(const CXMapPainterTest&);						///< Not used.
	const CXMapPainterTest & operator = (const CXMapPainterTest &);	///< Not used.
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnInternalPaint(IBitmap *pBMP, int Width, int Height);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void PaintPackground(IBitmap *pBMP, int Width, int Height);
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXMapPainterTest();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXMapPainterTest();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual bool ZoomIn();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual bool ZoomOut();
};

#endif // __CXMAPPAINTERTEST_HPP__
