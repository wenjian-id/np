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

#ifndef __CXMAPPAINTERTHREAD_HPP__
#define __CXMAPPAINTERTHREAD_HPP__

#include "CXNaviData.hpp"
#include "CXWorkRequestThread.hpp"
#include "CXMutex.hpp"

class CXMapPainter;
class CXNaviPOWM;
class CXDeviceContext;

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXMapPainterThread : public CXWorkRequestThread {
private:
	CXMapPainter		*m_pMapPainter;		///< oiu
	CXNaviPOWM			*m_pNaviPOWM;		///< oiu
	mutable CXMutex		m_Mutex;			///< oiu
	//-------------------------------------
	CXMapPainterThread(const CXMapPainterThread &);						///< Not used.
	const CXMapPainterThread & operator = (const CXMapPainterThread &);	///< Not used.
	//-------------------------------------
	virtual void OnWorkFunc();
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXMapPainterThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXMapPainterThread();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetNaviPOWM(CXNaviPOWM *pNaviPOWM);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void PositionChanged(const CXNaviData &NewNaviData);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void Resize(int Width, int Height);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ZoomIn();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ZoomOut();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStarted();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStopped();
};

#endif // __CXMAPPAINTERTHREAD_HPP__
