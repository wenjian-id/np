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

#ifndef __IBITMAP_HPP__
#define __IBITMAP_HPP__

#include "CXRect.hpp"
#include "CXRGB.hpp"
#include "CXStringASCII.hpp"
#include "CXStringUTF8.hpp"

class CXDeviceContext;
class CXBitmap;
class CXPen;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class IBitmap {
private:
	int				m_Width;	///< oiu
	int				m_Height;	///< oiu
	CXStringASCII	m_FileName;	///< oiu
	//-------------------------------------
	IBitmap(const IBitmap &);							///< Not used.
	const IBitmap & operator = (const IBitmap &);		///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetWidth(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetHeight(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFileName(const CXStringASCII & FileName);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	IBitmap();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~IBitmap();
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
	CXStringASCII GetFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool Create(CXDeviceContext *pDC, int Width, int Height) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void Destroy() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool IsNull() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void Resize(CXDeviceContext *pDC, int Width, int Height);
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
	virtual tIRect CalcTextRectASCII(const CXStringASCII & Text, int AddWidth, int AddHeight) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual tIRect CalcTextRectUTF8(const CXStringUTF8 & Text, int AddWidth, int AddHeight) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DrawLine(int x0, int y0, int x1, int y1) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void MoveTo(int x, int y) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void LineTo(int x, int y) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool DrawCircle(int x, int y, int r, const CXRGB &PenColor, const CXRGB &FillColor) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool Polygon(int *pX, int *pY, size_t Count, const CXRGB &PenColor, const CXRGB &FillColor) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool PolyLine(int *pX, int *pY, size_t Count) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void SetPen(const CXPen &Pen) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void SetFont(int FontHeight, bool Bold) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual bool LoadFromFile(const CXStringASCII & FileName) = 0;
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
	virtual void Blend(CXBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha) = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void DrawTransparent(CXBitmap *pBmp, int XTarget, int YTarget, int XSource, int YSource, int Width, int Height, const CXRGB & TrColor) = 0;
};

#endif // __IBITMAP_HPP__
