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

#ifndef __CXMAPPAINTER_HPP__
#define __CXMAPPAINTER_HPP__

#include "CXNaviData.hpp"
#include "CXRWLock.hpp"

class CXDeviceContext;

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapPainter {
private:
	CXNaviData			m_NaviData;			///< oiu
	bool				m_oMustRepaint;		///< oiu
	mutable CXRWLock	m_RWLock;			///< Synchronization object.
	//-------------------------------------
	CXMapPainter(const CXMapPainter &);						///< Not used.
	const CXMapPainter & operator = (const CXMapPainter &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnDoWork() = 0;
protected:
	//-------------------------------------
	CXNaviData GetPosition() const;
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapPainter();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapPainter();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustRepaint() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMustRepaint(bool Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void PositionChanged(const CXNaviData &NewNaviData);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool ZoomIn() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool ZoomOut() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void Resize(int Width, int Height) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DoWork();
};

#endif // __CXMAPPAINTER_HPP__
