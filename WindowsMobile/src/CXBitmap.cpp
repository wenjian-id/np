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

static TCHAR buf[1024];

//-------------------------------------
CXBitmap::CXBitmap() :
	m_hDC(NULL),
	m_hBMP(NULL),
	m_hFont(NULL)
{
}

//-------------------------------------
CXBitmap::~CXBitmap() {
	Destroy();
}

//-------------------------------------
bool CXBitmap::IsNull() {
	return m_hDC == NULL;
}

//-------------------------------------
bool CXBitmap::Create(CXDeviceContext *pDC, int Width, int Height) {
	if(pDC == NULL)
		return false;
	if(m_hDC != NULL)
		return true;
	m_hDC = CreateCompatibleDC(pDC->GetDC());
	SetWidth(Width);
	SetHeight(Height);
	if(m_hDC != NULL) {
		// create new bitmap
		m_hBMP = ::CreateBitmap(GetWidth(), GetHeight(), 1, 32, NULL);
		// and select it
		::SelectObject(m_hDC, m_hBMP);
	} else {
		Destroy();
	}
	return m_hDC != NULL;
}

//-------------------------------------
void CXBitmap::Destroy() {
	if(m_hDC != NULL)
		::DeleteObject(m_hDC);
	if(m_hBMP!=NULL)
		::DeleteObject(m_hBMP);
	if(m_hFont != NULL)
		::DeleteObject(m_hFont);
	m_hDC = NULL;
	m_hBMP = NULL;
	m_hFont = NULL;
}

//-------------------------------------
HDC CXBitmap::GetDC() const {
	return m_hDC;
}

//-------------------------------------
void CXBitmap::DrawRect(const tIRect &TheRect, const CXRGB & PenColor, const CXRGB & BrushColor) {
	if(IsNull())
		return;

	// create new pen and brush
	HPEN NewPen = ::CreatePen(PS_SOLID, 1, CXRGB2COLORREF(PenColor));
	HBRUSH NewBrush = ::CreateSolidBrush(CXRGB2COLORREF(BrushColor));

	// get old pen and brush
	HPEN OldPen = (HPEN)::SelectObject(m_hDC, NewPen); 
	HBRUSH OldBrush = (HBRUSH)::SelectObject(m_hDC, NewBrush);
	// draw rectangle
	::Rectangle(m_hDC, TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetRight(), TheRect.GetBottom());

	// restore old pen and brush
	::SelectObject(m_hDC, OldBrush);
	::SelectObject(m_hDC, OldPen);
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

	ASCII2UCS2(Text.c_str(), Text.GetSize(), buf, 1024);
	int res = ::DrawText(m_hDC, buf, -1, &Rect, DT_CALCRECT); 
	Result = tIRect(Rect.left, Rect.top, Rect.right - Rect.left + AddWidth, Rect.bottom - Rect.top + AddHeight);
	// make sure it starts at 0, 0
	Result.OffsetRect(-Result.GetLeft(), -Result.GetTop());

	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;

	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_hDC, CXRGB2COLORREF(FgColor));
	COLORREF OldBkColor = ::SetBkColor(m_hDC, CXRGB2COLORREF(BgColor));

	// draw text
	RECT tmp;
	tmp.left = TheRect.GetLeft();
	tmp.top = TheRect.GetTop();
	tmp.right = TheRect.GetRight();
	tmp.bottom = TheRect.GetBottom();
	ASCII2UCS2(Text.c_str(), Text.GetSize(), buf, 1024);
	::DrawText(m_hDC, buf, -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 

	// restore old colors
	SetBkColor(m_hDC, OldBkColor);
	SetTextColor(m_hDC, OldTextColor);
}

//-------------------------------------
void CXBitmap::DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor) {
	DrawTextASCII(Text, TheRect, FgColor, COLORREF2CXRGB(::GetBkColor(m_hDC)));
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
	int res = ::DrawTextW(m_hDC, Text.w_str(), -1, &Rect, DT_CALCRECT); 
	Result = tIRect(Rect.left, Rect.top, Rect.right - Rect.left + AddWidth, Rect.bottom - Rect.top + AddHeight);
	// make sure it starts at 0, 0
	Result.OffsetRect(-Result.GetLeft(), -Result.GetTop());

	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;

	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_hDC, CXRGB2COLORREF(FgColor));
	COLORREF OldBkColor = ::SetBkColor(m_hDC, CXRGB2COLORREF(BgColor));

	// draw text
	RECT tmp;
	tmp.left = TheRect.GetLeft();
	tmp.top = TheRect.GetTop();
	tmp.right = TheRect.GetRight();
	tmp.bottom = TheRect.GetBottom();
	::DrawTextW(m_hDC, Text.w_str(), -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 

	// restore old colors
	SetBkColor(m_hDC, OldBkColor);
	SetTextColor(m_hDC, OldTextColor);
}

//-------------------------------------
void CXBitmap::DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor) {
	DrawTextUTF8(Text, TheRect, FgColor, COLORREF2CXRGB(::GetBkColor(m_hDC)));
}

//-------------------------------------
void CXBitmap::DrawLine(int x0, int y0, int x1, int y1) {
	if(IsNull())
		return;
	::MoveToEx(m_hDC, x0, y0, NULL);
	::LineTo(m_hDC, x1, y1);
}

//-------------------------------------
void CXBitmap::MoveTo(int x, int y) {
	if(IsNull())
		return;
	::MoveToEx(m_hDC, x, y, NULL);
}

//-------------------------------------
void CXBitmap::LineTo(int x, int y) {
	if(IsNull())
		return;
	::LineTo(m_hDC, x, y);
}

//-------------------------------------
bool CXBitmap::DrawCircle(int x, int y, int r, const CXRGB &PenColor, const CXRGB &FillColor) {
	if(IsNull())
		return false;
	// get old colors
	COLORREF OldTextColor = ::SetTextColor(m_hDC, CXRGB2COLORREF(PenColor));
	COLORREF OldBkColor = ::SetBkColor(m_hDC, CXRGB2COLORREF(FillColor));

	// create pen & brush 
	HPEN hPen = CreatePen(PS_SOLID, 1, CXRGB2COLORREF(PenColor));
	HBRUSH hBrush = ::CreateSolidBrush(CXRGB2COLORREF(FillColor));

	// select
	HPEN OldPen = (HPEN)::SelectObject(m_hDC, hPen);
	HBRUSH OldBrush = (HBRUSH)::SelectObject(m_hDC, hBrush);

	// draw circle
	::Ellipse(m_hDC, x-r, y-r, x+r, y+r);

	// restore pen & brush
	::SelectObject(m_hDC, OldPen);
	::SelectObject(m_hDC, OldBrush);

	// delete
	::DeleteObject(hPen);
	::DeleteObject(hBrush);

	// restore old colors
	SetBkColor(m_hDC, OldBkColor);
	SetTextColor(m_hDC, OldTextColor);

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
	COLORREF OldTextColor = ::SetTextColor(m_hDC, CXRGB2COLORREF(PenColor));
	COLORREF OldBkColor = ::SetBkColor(m_hDC, CXRGB2COLORREF(FillColor));

	// create pen & brush 
	HPEN hPen = CreatePen(PS_SOLID, 1, CXRGB2COLORREF(PenColor));
	HBRUSH hBrush = ::CreateSolidBrush(CXRGB2COLORREF(FillColor));

	// select
	HPEN OldPen = (HPEN)::SelectObject(m_hDC, hPen);
	HBRUSH OldBrush = (HBRUSH)::SelectObject(m_hDC, hBrush);

	POINT *pPoints = new POINT[Count];
	for(size_t i=0; i<Count; i++) {
		pPoints[i].x = pX[i];
		pPoints[i].y = pY[i];
	}

	// draw polygon
	::Polygon(m_hDC, pPoints, Count);

	delete [] pPoints;

	// restore pen & brush
	::SelectObject(m_hDC, OldPen);
	::SelectObject(m_hDC, OldBrush);

	// delete
	::DeleteObject(hPen);
	::DeleteObject(hBrush);

	// restore old colors
	SetBkColor(m_hDC, OldBkColor);
	SetTextColor(m_hDC, OldTextColor);

	return true;
}

//-------------------------------------
bool CXBitmap::PolyLine(int *pX, int *pY, size_t Count) {
	if(IsNull())
		return false;
	if(pX == NULL)
		return false;
	if(pY == NULL)
		return false;
	if(Count == 0)
		return false;

	POINT *pPoints = new POINT[Count];
	for(size_t i=0; i<Count; i++) {
		pPoints[i].x = pX[i];
		pPoints[i].y = pY[i];
	}

	// draw polyline
	::Polyline(m_hDC, pPoints, Count);

	delete [] pPoints;

	return true;
}

//-------------------------------------
void CXBitmap::SetPen(const CXPen &Pen) {
	if(IsNull())
		return;

	int Style = 0;
	switch(Pen.GetStyle()) {
		case CXPen::e_Solid:	Style = PS_SOLID; break;
	}
	HPEN hPen = CreatePen(Style, Pen.GetWidth(), CXRGB2COLORREF(Pen.GetColor()));

	HPEN OldPen = (HPEN)::SelectObject(m_hDC, hPen);
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
	lf.lfQuality = CLEARTYPE_COMPAT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	m_hFont = CreateFontIndirect(&lf);
	if(m_hFont != NULL) {
		HFONT OldFont = (HFONT)SelectObject(m_hDC, m_hFont);
		DeleteObject(OldFont);
	}
}

//-------------------------------------
bool CXBitmap::LoadFromFile(const CXStringASCII & FileName) {
	if(IsNull())
		return false;

	// load bitmap from file
	ASCII2UCS2(FileName.c_str(), FileName.GetSize(), buf, 1024);
	HANDLE HBmp = SHLoadDIBitmap(buf);
	if(HBmp == NULL)
		return false;

	// get size
	BITMAP bm;
	GetObject(HBmp, sizeof(BITMAP), &bm);

	// draw it
	HDC DC = CreateCompatibleDC(m_hDC);
	if(DC != NULL) {
		// select object
		::SelectObject(DC, HBmp);
		// stretch
		::StretchBlt(m_hDC, 0, 0, GetWidth(), GetHeight(), DC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		// and delete
		::DeleteObject(DC);
	}
	// delete bitmap
	::DeleteObject(HBmp);
	
	return true;
}

//-------------------------------------
void CXBitmap::Draw(CXBitmap *pBmp, int OffsetX, int OffsetY) {
	if(IsNull())
		return;
	if(pBmp == NULL)
		return;
	if(pBmp->GetDC() == NULL)
		return;
	::BitBlt(m_hDC, OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight(), pBmp->GetDC(), 0, 0, SRCCOPY);
}

//-------------------------------------
void CXBitmap::Blend(CXBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha) {
	if(IsNull())
		return;
	if(pBmp == NULL)
		return;
	if(pBmp->GetDC() == NULL)
		return;
/*
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = static_cast<unsigned char>(256.0*Alpha/100);
	bf.AlphaFormat = 0;
	AlphaBlend(	m_hDC, OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight(), 
				pBmp->GetDC(), 0, 0, pBmp->GetWidth(), pBmp->GetHeight(), 
				bf);
*/
	::BitBlt(m_hDC, OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight(), pBmp->GetDC(), 0, 0, SRCCOPY);
}

//-------------------------------------
void CXBitmap::DrawTransparent(CXBitmap *pBmp, int XTarget, int YTarget, int XSource, int YSource, int Width, int Height, const CXRGB & TrColor) {
	if(IsNull())
		return;
	if(pBmp == NULL)
		return;
	if(pBmp->GetDC() == NULL)
		return;
	::TransparentBlt(	m_hDC, XTarget, YTarget, Width, Width, 
						pBmp->GetDC(), XSource, YSource, Width, Height, 
						CXRGB2COLORREF(TrColor));
}
