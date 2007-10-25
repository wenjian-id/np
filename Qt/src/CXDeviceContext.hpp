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

#ifndef __CXDEVICECONTEXT_HPP__
#define __CXDEVICECONTEXT_HPP__

#include <IDeviceContext.hpp>
#include <TargetIncludes.hpp>

class QPainter;

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXDeviceContext : public IDeviceContext {
private:
	QPainter	*m_pPainter;		///< oiu
	//-------------------------------------
	CXDeviceContext();													///< Not used.
	CXDeviceContext(int Width, int Height);								///< Not used.
	CXDeviceContext(const CXDeviceContext &);							///< Not used.
	const CXDeviceContext & operator = (const CXDeviceContext &);		///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXDeviceContext(QPainter *pPainter);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXDeviceContext();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	QPainter *GetPainter() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void Draw(CXBitmap *pBmp, int OffsetX, int OffsetY);
};

#endif // __IDEVICECONTEXT_HPP__
