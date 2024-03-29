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

#ifndef __CXINFOBARSPEED_HPP__
#define __CXINFOBARSPEED_HPP__

#include "CXInfoBar.hpp"
#include "CXNaviData.hpp"
#include "CXBitmap.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXInfoBarSpeed : public CXInfoBar {
private:
    CXNaviData          m_NaviData;     ///< oiu
    CXBitmap            m_CircleBmp;    ///< oiu
    tIRect              m_TextRect1;    ///< oiu
    tIRect              m_TextRect2;    ///< oiu
    tIRect              m_TextRect3;    ///< oiu
    int                 m_FontSize1;    ///< oiu
    int                 m_FontSize2;    ///< oiu
    int                 m_FontSize3;    ///< oiu
    //-------------------------------------
    CXInfoBarSpeed(const CXInfoBarSpeed &);                     ///< Not used.
    const CXInfoBarSpeed & operator = (const CXInfoBarSpeed &); ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CreateBitmaps(CXDeviceContext *pDC);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CalcFonts(const CXStringASCII &SpeedStr, double WhiteRadius, tIRect & rRect, int & rFontSize);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXInfoBarSpeed();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXInfoBarSpeed();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void PositionChanged(const CXNaviData & NewData);
};

#endif // __CXINFOBARSPEED_HPP__
