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

#ifndef __CXMAPPAINTER2D_HPP__
#define __CXMAPPAINTER2D_HPP__

#include "CXBuffer.hpp"
#include "CXMapPainterDoubleBuffered.hpp"
#include "CXPOWMMap.hpp"
#include "CXTransformationMatrix.hpp"
#include "CXPenHolder.hpp"

class CXCache;

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXMapPainter2D : public CXMapPainterDoubleBuffered {
private:
	double					m_Scale;		///< oiu
	CXPenHolder				m_PenHolder;	///< oiu
	CXBuffer<TWayBuffer *>	m_DrawWays;		///< oiu
	mutable CXMutex			m_Mutex;		///< oiu
	//-------------------------------------
	CXMapPainter2D(const CXMapPainter2D &);						///< Not used.
	const CXMapPainter2D & operator = (const CXMapPainter2D &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void DrawWay(IBitmap *pBMP, CXWay *pWay, const CXTransformationMatrix2D & TM, int Width, int Height);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void DrawWaysBg(IBitmap *pBMP, TWayBuffer *pWays, CXWay::E_KEYHIGHWAY eHighwayType, const CXTransformationMatrix2D & TM, int Width, int Height);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void DrawWaysFg(IBitmap *pBMP, TWayBuffer *pWays, CXWay::E_KEYHIGHWAY eHighwayType, const CXTransformationMatrix2D & TM, int Width, int Height);
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
	void PaintPackground(IBitmap *pBMP, int Width, int Height);
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXMapPainter2D();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXMapPainter2D();
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

#endif // __CXMAPPAINTER2D_HPP__
