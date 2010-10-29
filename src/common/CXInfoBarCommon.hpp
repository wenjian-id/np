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

#ifndef __CXINFOBARCOMMON_HPP__
#define __CXINFOBARCOMMON_HPP__

#include "CXInfoBar.hpp"
#include "CXNaviData.hpp"
#include "CXRect.hpp"

class CXBitmap;
class CXStringUTF8;

//----------------------------------------------------------------------------
/**
 * \brief Information bar for common information.
 *
 * This class encapsulates the functionality for displaying common information:
 * position and speed.
 */
class CXInfoBarCommon : public CXInfoBar {
private:
    CXNaviData          m_NaviData;         ///< Navigation data.
    int                 m_TextHeightCoor;   ///< oiu
    int                 m_TextHeightSpeed;  ///< oiu
    //-------------------------------------
    CXInfoBarCommon(const CXInfoBarCommon &);                       ///< Not used.
    const CXInfoBarCommon & operator = (const CXInfoBarCommon &);   ///< Not used.
    //-------------------------------------
    /**
     * \brief Paint.
     *
     * Paint position and speed data to a bitmap.
     * \param   pDC         Pointer to a device context.
     * \param   OffsetX     Offset for painting (X).
     * \param   OffsetY     Offset for painting (Y).
     */
    virtual void OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
    //-------------------------------------
    /**
     * \brief oiu
     *
     * oiu
     */
    void CalcFontHeights(CXDeviceContext *pDC);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * The default constructor.
     */
    CXInfoBarCommon();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * The destructor.
     */
    virtual ~CXInfoBarCommon();
    //-------------------------------------
    /**
     * \brief Position has changed.
     *
     * The position has changed.
     * \param   Newdata     New position.
     */
    void PositionChanged(const CXNaviData & NewData);
};

#endif // __CXINFOBARCOMMON_HPP__
