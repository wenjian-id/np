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

#ifndef __CXMAPTHREAD_HPP__
#define __CXMAPTHREAD_HPP__

#include "CXNaviData.hpp"
#include "CXWorkRequestThread.hpp"
#include "CXMutex.hpp"

class CXMapPainter;
class CXNaviPOWM;
class CXPOWMMap;
class CXDeviceContext;

//----------------------------------------------------------------------------
class CXMapThread : public CXWorkRequestThread {
private:
	CXMapPainter		*m_pMapPainter;
	CXNaviPOWM			*m_pNaviPOWM;
	mutable CXMutex		m_Mutex;
	//-------------------------------------
	CXMapThread(const CXMapThread &);
	const CXMapThread & operator = (const CXMapThread &);
	//-------------------------------------
	virtual void OnWorkFunc();
protected:
public:
	//-------------------------------------
	CXMapThread();
	//-------------------------------------
	virtual ~CXMapThread();
	//-------------------------------------
	void SetNaviPOWM(CXNaviPOWM *pNaviPOWM);
	//-------------------------------------
	void PositionChanged(const CXNaviData &NewNaviData);
	//-------------------------------------
	virtual void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
	//-------------------------------------
	virtual void Resize(int Width, int Height);
	//-------------------------------------
	void ZoomIn();
	//-------------------------------------
	void ZoomOut();
	//-------------------------------------
	virtual void OnThreadStarted();
	//-------------------------------------
	virtual void OnThreadStopped();
};

#endif // __CXMAPTHREAD_HPP__
