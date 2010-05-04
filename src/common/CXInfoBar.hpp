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

#ifndef __CXINFOBAR_HPP__
#define __CXINFOBAR_HPP__

#include "Utils.hpp"
#include "CXRWLock.hpp"

class CXDeviceContext;

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXInfoBar {
private:
	int					m_Width;		///< oiu
	int					m_Height;		///< oiu
	bool				m_oSizeChanged;	///< oiu
	mutable CXRWLock	m_RWLock;		///< Synchronization object.
	//-------------------------------------
	CXInfoBar(const CXInfoBar &);						///< Not used.
	const CXInfoBar & operator = (const CXInfoBar &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY) = 0;
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetWidth() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool SizeChanged() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual E_COMMAND OnInternalMouseDown(int X, int Y);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXInfoBar();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXInfoBar();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Resize(int Width, int Height);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	E_COMMAND OnMouseDown(int X, int Y);
};

#endif // __CXINFOBAR_HPP__
