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

#include "CXBitmap.hpp"
#include "CXPen.hpp"
#include "CXDeviceContext.hpp"

//-------------------------------------
CXBitmap::CXBitmap() :
	m_DC(NULL),
	m_BMP(NULL),
	m_hFont(NULL)
{
}

//-------------------------------------
CXBitmap::~CXBitmap() {
	Destroy();
}

//-------------------------------------
bool CXBitmap::IsNull() {
	return m_DC == NULL;
}

//-------------------------------------
bool CXBitmap::Create(CXDeviceContext *pDC, int Width, int Height) {
	if(pDC == NULL)
		return false;
	if(m_DC != NULL)
		return true;
	SetWidth(Width);
	SetHeight(Height);
	m_DC = CreateCompatibleDC(pDC->GetDC());
	if(m_DC != NULL) {
		// create new bitmap
		m_BMP = ::CreateBitmap(GetWidth(), GetHeight(), 1, 32, NULL);
		// and select it
		::SelectObject(m_DC, m_BMP);
	} else {
		Destroy();
	}
	return m_DC != NULL;
}

//-------------------------------------
void CXBitmap::Destroy() {
	if(m_DC != NULL)
		::DeleteObject(m_DC);
	if(m_BMP!=NULL)
		::DeleteObject(m_BMP);
	if(m_hFont != NULL)
		::DeleteObject(m_hFont);
	m_DC = NULL;
	m_BMP = NULL;
	m_hFont = NULL;
}

//-------------------------------------
HDC CXBitmap::GetDC() const {
	return m_DC;
}

//-------------------------------------
void CXBitmap::DrawRect(const tIRect &TheRect, const CXRGB & PenColor, const CXRGB & BrushColor) {
	if(IsNull())
		return;

	// create new pen and brush
	HPEN NewPen = ::CreatePen(PS_SOLID, 1, CXRGB2COLORREF(PenColor));
	HBRUSH NewBrush = ::CreateSolidBrush(CXRGB2COLORREF(BrushColor));

	// get old pen and brush
	HPEN OldPen = (HPEN)::SelectObject(m_DC, NewPen); 
	HBRUSH OldBrush = (HBRUSH)::SelectObject(m_DC, NewBrush);
	// draw rectangle
	::Rectangle(m_DC, TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetRight(), TheRect.GetBottom());

	// restore old pen and brush
	::SelectObject(m_DC, OldBrush);
	::SelectObject(m_DC, OldPen);
	::DeleteObject(NewPen);
	::DeleteObject(NewBrush);
}

//-------------------------------------
tIRect CXBitmap::CalcTextRectASCII(const CXStringASCII & Text, int AddWidth, int AddHeight) {
	tIRect Result(0,0,0,0);

	if(IsNull())
		return Result;

	if(Text.IsEmpty())
		return Result;

	// calc text rect
	RECT Rect;
	Rect.left = 0;
	Rect.top = 0;
	::DrawTextA(m_DC, Text.c_str(), -1, &Rect, DT_CALCRECT); 
	Result = tIRect(Rect.left, Rect.top, Rect.right + AddWidth, Rect.bottom + AddHeight);

	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;

	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_DC, CXRGB2COLORREF(FgColor));
	COLORREF OldBkColor = ::SetBkColor(m_DC, CXRGB2COLORREF(BgColor));

	// draw text
	RECT tmp;
	tmp.left = TheRect.GetLeft();
	tmp.top = TheRect.GetTop();
	tmp.right = TheRect.GetRight();
	tmp.bottom = TheRect.GetBottom();
	::DrawTextA(m_DC, Text.c_str(), -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 

	// restore old colors
	SetBkColor(m_DC, OldBkColor);
	SetTextColor(m_DC, OldTextColor);
}

//-------------------------------------
void CXBitmap::DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor) {
	DrawTextASCII(Text, TheRect, FgColor, COLORREF2CXRGB(::GetBkColor(m_DC)));
}

//-------------------------------------
tIRect CXBitmap::CalcTextRectUTF8(const CXStringUTF8 & Text, int AddWidth, int AddHeight) {
	tIRect Result(0,0,0,0);

	if(IsNull())
		return Result;

	if(Text.IsEmpty())
		return Result;

	// calc text rect
	RECT Rect;
	Rect.left = 0;
	Rect.top = 0;
	::DrawTextW(m_DC, Text.w_str(), -1, &Rect, DT_CALCRECT); 
	Result = tIRect(Rect.left, Rect.top, Rect.right + AddWidth, Rect.bottom + AddHeight);

	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;

	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_DC, CXRGB2COLORREF(FgColor));
	COLORREF OldBkColor = ::SetBkColor(m_DC, CXRGB2COLORREF(BgColor));

	// draw text
	RECT tmp;
	tmp.left = TheRect.GetLeft();
	tmp.top = TheRect.GetTop();
	tmp.right = TheRect.GetRight();
	tmp.bottom = TheRect.GetBottom();
	::DrawTextW(m_DC, Text.w_str(), -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 

	// restore old colors
	SetBkColor(m_DC, OldBkColor);
	SetTextColor(m_DC, OldTextColor);
}

//-------------------------------------
void CXBitmap::DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor) {
	DrawTextUTF8(Text, TheRect, FgColor, COLORREF2CXRGB(::GetBkColor(m_DC)));
}

//-------------------------------------
void CXBitmap::DrawLine(int x0, int y0, int x1, int y1) {
	if(IsNull())
		return;
	::MoveToEx(m_DC, x0, y0, NULL);
	::LineTo(m_DC, x1, y1);
}

//-------------------------------------
void CXBitmap::MoveTo(int x, int y) {
	if(IsNull())
		return;
	::MoveToEx(m_DC, x, y, NULL);
}

//-------------------------------------
void CXBitmap::LineTo(int x, int y) {
	if(IsNull())
		return;
	::LineTo(m_DC, x, y);
}

//-------------------------------------
bool CXBitmap::Circle(int x, int y, int r, const CXRGB &PenColor, const CXRGB &FillColor) {
	if(IsNull())
		return false;
	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_DC, CXRGB2COLORREF(PenColor));
	COLORREF OldBkColor = ::SetBkColor(m_DC, CXRGB2COLORREF(FillColor));

	// create pen & brush 
	HPEN hPen = CreatePen(PS_SOLID, 1, CXRGB2COLORREF(PenColor));
	HBRUSH hBrush = ::CreateSolidBrush(CXRGB2COLORREF(FillColor));

	// select
	HPEN OldPen = (HPEN)::SelectObject(m_DC, hPen);
	HBRUSH OldBrush = (HBRUSH)::SelectObject(m_DC, hBrush);

	// draw circle
	::Ellipse(m_DC, x-r, y-r, x+r, y+r);

	// restore pen & brush
	::SelectObject(m_DC, OldPen);
	::SelectObject(m_DC, OldBrush);

	// delete
	::DeleteObject(hPen);
	::DeleteObject(hBrush);

	// restore old colors
	SetBkColor(m_DC, OldBkColor);
	SetTextColor(m_DC, OldTextColor);

	return true;
}

//-------------------------------------
bool CXBitmap::Polygon(int *pX, int *pY, size_t Count, const CXRGB &PenColor, const CXRGB &FillColor) {
	if(IsNull())
		return false;
	if(pX == NULL)
		return false;
	if(pY == NULL)
		return false;
	if(Count == 0)
		return false;

	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_DC, CXRGB2COLORREF(PenColor));
	COLORREF OldBkColor = ::SetBkColor(m_DC, CXRGB2COLORREF(FillColor));

	// create pen & brush 
	HPEN hPen = CreatePen(PS_SOLID, 1, CXRGB2COLORREF(PenColor));
	HBRUSH hBrush = ::CreateSolidBrush(CXRGB2COLORREF(FillColor));

	// select
	HPEN OldPen = (HPEN)::SelectObject(m_DC, hPen);
	HBRUSH OldBrush = (HBRUSH)::SelectObject(m_DC, hBrush);

	POINT *pPoints = new POINT[Count];
	for(size_t i=0; i<Count; i++) {
		pPoints[i].x = pX[i];
		pPoints[i].y = pY[i];
	}

	// draw polygon
	::Polygon(m_DC, pPoints, Count);

	delete [] pPoints;

	// restore pen & brush
	::SelectObject(m_DC, OldPen);
	::SelectObject(m_DC, OldBrush);

	// delete
	::DeleteObject(hPen);
	::DeleteObject(hBrush);

	// restore old colors
	SetBkColor(m_DC, OldBkColor);
	SetTextColor(m_DC, OldTextColor);

	return true;
}

//-------------------------------------
void CXBitmap::SetPen(CXPen *pPen) {
	if(IsNull())
		return;
	if(pPen == NULL)
		return;

	int Style = 0;
	switch(pPen->GetStyle()) {
		case CXPen::e_Solid:	Style = PS_SOLID; break;
	}
	HPEN hPen = CreatePen(Style, pPen->GetWidth(), CXRGB2COLORREF(pPen->GetColor()));

	HPEN OldPen = (HPEN)::SelectObject(m_DC, hPen);
	if(OldPen != NULL)
		::DeleteObject(OldPen);
}

//-------------------------------------
void CXBitmap::SetFont(int FontHeight, bool Bold) {
	if(IsNull())
		return;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	lf.lfHeight = FontHeight;
	if(Bold)
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;
	lf.lfCharSet =  DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	m_hFont = CreateFontIndirect(&lf);
	if(m_hFont != NULL) {
		HFONT OldFont = (HFONT)SelectObject(m_DC, m_hFont);
		DeleteObject(OldFont);
	}
}

//-------------------------------------
bool CXBitmap::LoadFromFile(const CXStringASCII & FileName) {
	if(IsNull())
		return false;

	// load bitmap from file
	HANDLE HBmp = LoadImage(0, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if(HBmp == NULL)
		return false;

	// get size
	BITMAP bm;
	GetObject(HBmp, sizeof(BITMAP), &bm);

	// draw it
	HDC DC = CreateCompatibleDC(m_DC);
	if(DC != NULL) {
		// select object
		::SelectObject(DC, HBmp);
		// stretch
		::StretchBlt(m_DC, 0, 0, GetWidth(), GetHeight(), DC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		// and delete
		::DeleteObject(DC);
	}
	// delete bitmap
	::DeleteObject(HBmp);
	
	return true;
}
