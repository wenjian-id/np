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

#ifndef __IDEVICECONTEXT_HPP__
#define __IDEVICECONTEXT_HPP__

#include "CXRect.hpp"

class CXBitmap;
class CXRGB;


//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class IDeviceContext {
private:
    //-------------------------------------
    IDeviceContext(const IDeviceContext &);                         ///< Not used.
    const IDeviceContext & operator = (const IDeviceContext &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    IDeviceContext() {
    }
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~IDeviceContext() {
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Draw(CXBitmap *pBmp, int OffsetX, int OffsetY) = 0;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawRect(const tIRect &TheRect, const CXRGB & PenColor, const CXRGB & BrushColor) = 0;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Blend(CXBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha) = 0;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawTransparent(CXBitmap *pBmp, int OffsetX, int OffsetY, const CXRGB & TrColor) = 0;
};

#endif // __IDEVICECONTEXT_HPP__
