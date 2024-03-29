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

#ifndef __CXBITMAP_HPP__
#define __CXBITMAP_HPP__

#include <IBitmap.hpp>
#include "TargetIncludes.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXBitmap : public IBitmap {
private:
    HDC         m_hDC;              ///< oiu
    HBITMAP     m_hBMP;             ///< oiu
    HFONT       m_hFont;            ///< oiu
    HFONT       m_hGlowFont;        ///< oiu
    POINT       *m_pLinePoints;     ///< oiu
    size_t      m_LinePointsSize;   ///< oiu
    //-------------------------------------
    CXBitmap(const CXBitmap &);                         ///< Not used.
    const CXBitmap & operator = (const CXBitmap &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXBitmap();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXBitmap();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual bool Create(IDeviceContext *pDC, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Destroy();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual bool IsNull();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    HDC GetDC() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawRect(const tIRect &TheRect, const CXRGB & PenColor, const CXRGB & BrushColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual tIRect CalcTextRectASCII(const CXStringASCII & Text, int AddWidth, int AddHeight);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual tIRect CalcTextRectUTF8(const CXStringUTF8 & Text, int AddWidth, int AddHeight);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawGlowTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & GlowColor, int GlowSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawLine(int x0, int y0, int x1, int y1);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawLine(size_t Count, const int *pX, const int *pY);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawCircle(int x, int y, int r, const CXRGB &PenColor, const CXRGB &FillColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Polygon(int *pX, int *pY, size_t Count, const CXRGB &PenColor, const CXRGB &FillColor);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void SetPen(const CXPen &Pen);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void SetFont(int FontHeight, bool Bold);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual bool LoadFromFile(const CXStringASCII & FileName);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Draw(IBitmap *pBmp, int OffsetX, int OffsetY);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Blend(IBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void DrawTransparent(IBitmap *pBmp, int XTarget, int YTarget, int XSource, int YSource, int Width, int Height, const CXRGB & TrColor);
};

#endif // __IBITMAP_HPP__
