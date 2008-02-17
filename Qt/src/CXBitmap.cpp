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
#include "CXDeviceContext.hpp"
#include "CXPen.hpp"
#include "TargetIncludes.hpp"

#include <qcolor.h>
#include <qpainter.h>
#include <qbitmap.h>

//-------------------------------------
CXBitmap::CXBitmap() :
	m_pImage(NULL),
	m_pPainter(NULL),
	m_LineStartX(0),
	m_LineStartY(0)
{
}

//-------------------------------------
CXBitmap::~CXBitmap() {
	Destroy();
}

//-------------------------------------
void CXBitmap::Destroy() {
	// delete painter and image
	delete m_pPainter;
	delete m_pImage;
	m_pPainter = NULL;
	m_pImage = NULL;
}

//-------------------------------------
bool CXBitmap::IsNull() {
	return ((m_pImage == NULL) || (m_pPainter == NULL));
}

//-------------------------------------
bool CXBitmap::Create(CXDeviceContext * /*pDC*/, int Width, int Height) {
	Destroy();
	// create new image and new painter
	SetWidth(Width);
	SetHeight(Height);
	m_pImage =new QImage(GetWidth(), GetHeight(), QImage::Format_RGB32);
	m_pPainter = new QPainter(m_pImage);
	m_pPainter->setRenderHint(QPainter::Antialiasing, false);
	return true;
}

//-------------------------------------
QImage *CXBitmap::GetImage() const {
	return m_pImage;
}

//-------------------------------------
void CXBitmap::DrawRect(const tIRect &TheRect, const CXRGB & PenColor, const CXRGB & BrushColor) {
	if(IsNull())
		return;

	// get old pen and brush
	QPen OldPen = m_pPainter->pen();
	QBrush OldBrush = m_pPainter->brush();
	
	// create new pen
	QPen NewPen(Qt::SolidLine);
	NewPen.setWidth(1);
	NewPen.setColor(CXRGB2QColor(PenColor));

	// create new brush
	QBrush NewBrush(CXRGB2QColor(BrushColor), Qt::SolidPattern);
	
	// select new pen and brush
	m_pPainter->setBrush(NewBrush);
	m_pPainter->setPen(NewPen);

	// draw rectangle
	m_pPainter->drawRect(TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetRight() - TheRect.GetLeft() - 1, TheRect.GetBottom() - TheRect.GetTop() - 1);

	// restore old pen and brush
	m_pPainter->setPen(OldPen);
	m_pPainter->setBrush(OldBrush);
}

//-------------------------------------
tIRect CXBitmap::CalcTextRectQString(const QString & Text, int AddWidth, int AddHeight) {
	tIRect Result(0,0,0,0);

	if(IsNull())
		return Result;

	// calc text rect
	QRect NullRect(0,0,0,0);
	QRect Res = m_pPainter->boundingRect(NullRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, Text);
	Result = tIRect(Res.left(), Res.top(), Res.right() + AddWidth, Res.bottom() + AddHeight);
	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextQString(const QString & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;

	// get old pen and brush
	QPen OldPen = m_pPainter->pen();
	QBrush OldBrush = m_pPainter->brush();
	
	// create new pen
	QPen NewPen(Qt::SolidLine);
	NewPen.setWidth(1);
	// with BgColor!
	NewPen.setColor(CXRGB2QColor(BgColor));

	// create new brush
	QBrush NewBrush(CXRGB2QColor(BgColor), Qt::SolidPattern);

	// select new pen and brush
	m_pPainter->setBrush(NewBrush);
	m_pPainter->setPen(NewPen);

	// calc and draw rectangle
	QRect Rect(TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetRight() - TheRect.GetLeft() + 1, TheRect.GetBottom() - TheRect.GetTop() + 1);
	QRect Res = m_pPainter->boundingRect(Rect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, Text);
	m_pPainter->drawRect(Res);
	
	// now change color to FgColor
	NewPen.setColor(CXRGB2QColor(FgColor));
	m_pPainter->setPen(NewPen);
	// draw text
	m_pPainter->drawText(Rect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, Text, NULL);
	
	// restore old pen and brush
	m_pPainter->setPen(OldPen);
	m_pPainter->setBrush(OldBrush);
}

//-------------------------------------
tIRect CXBitmap::CalcTextRectASCII(const CXStringASCII & Text, int AddWidth, int AddHeight) {
	tIRect Result(0,0,0,0);

	if(IsNull())
		return Result;

	if(Text.IsEmpty())
		return Result;

	QString S(Text.c_str());
	Result = CalcTextRectQString(S, AddWidth, AddHeight);
	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;
	QString S(Text.c_str());
	DrawTextQString(S, TheRect, FgColor, BgColor);
}

//-------------------------------------
void CXBitmap::DrawTextASCII(const CXStringASCII & Text, const tIRect & TheRect, const CXRGB & FgColor) {
	DrawTextASCII(Text, TheRect, FgColor, QColor2CXRGB(m_pPainter->background().color()));
}

//-------------------------------------
tIRect CXBitmap::CalcTextRectUTF8(const CXStringUTF8 & Text, int AddWidth, int AddHeight) {
	tIRect Result(0,0,0,0);

	if(IsNull())
		return Result;

	if(Text.IsEmpty())
		return Result;

	QString S = QString::fromUtf8(reinterpret_cast<const char *>(Text.uc_str()));
	Result = CalcTextRectQString(S, AddWidth, AddHeight);
	return Result;
}

//-------------------------------------
void CXBitmap::DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
	if(IsNull())
		return;
	QString S = QString::fromUtf8(reinterpret_cast<const char *>(Text.uc_str()));
	DrawTextQString(S, TheRect, FgColor, BgColor);
}

//-------------------------------------
void CXBitmap::DrawTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor) {
	DrawTextUTF8(Text, TheRect, FgColor, QColor2CXRGB(m_pPainter->background().color()));
}

//-------------------------------------
void CXBitmap::DrawLine(int x0, int y0, int x1, int y1) {
	if(IsNull())
		return;

	m_pPainter->drawLine(x0, y0, x1, y1);
}

//-------------------------------------
void CXBitmap::MoveTo(int x, int y) {
	if(IsNull())
		return;
	m_LineStartX = x;
	m_LineStartY = y;
}

//-------------------------------------
void CXBitmap::LineTo(int x, int y) {
	if(IsNull())
		return;
	DrawLine(m_LineStartX, m_LineStartY, x, y);
	m_LineStartX = x;
	m_LineStartY = y;
}

//-------------------------------------
bool CXBitmap::Circle(int x, int y, int r, const CXRGB &PenColor, const CXRGB &FillColor) {
	if(IsNull())
		return false;

	// get old pen and brush
	QPen OldPen = m_pPainter->pen();
	QBrush OldBrush = m_pPainter->brush();
	
	// create new pen
	QPen NewPen(Qt::SolidLine);
	NewPen.setWidth(1);
	NewPen.setColor(CXRGB2QColor(PenColor));

	// create new brush
	QBrush NewBrush(CXRGB2QColor(FillColor), Qt::SolidPattern);
	
	// select new pen and brush
	m_pPainter->setBrush(NewBrush);
	m_pPainter->setPen(NewPen);

	// draw ellipse
	m_pPainter->drawEllipse(x-r, y-r, 2*r, 2*r);

	// restore old pen and brush
	m_pPainter->setPen(OldPen);
	m_pPainter->setBrush(OldBrush);
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

	// get old pen and brush
	QPen OldPen = m_pPainter->pen();
	QBrush OldBrush = m_pPainter->brush();
	
	// create new pen
	QPen NewPen(Qt::SolidLine);
	NewPen.setWidth(1);
	NewPen.setColor(CXRGB2QColor(PenColor));

	// create new brush
	QBrush NewBrush(CXRGB2QColor(FillColor), Qt::SolidPattern);
	
	// select new pen and brush
	m_pPainter->setBrush(NewBrush);
	m_pPainter->setPen(NewPen);

	QPoint *pPoints = new QPoint[Count];
	for(size_t i=0; i<Count; i++) {
		pPoints[i].setX(pX[i]);
		pPoints[i].setY(pY[i]);
	}

	// draw polygon
	m_pPainter->drawPolygon(pPoints, Count);

	delete [] pPoints;

	// restore old pen and brush
	m_pPainter->setPen(OldPen);
	m_pPainter->setBrush(OldBrush);

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

	QPoint *pPoints = new QPoint[Count];
	for(size_t i=0; i<Count; i++) {
		pPoints[i].setX(pX[i]);
		pPoints[i].setY(pY[i]);
	}

	// draw poly line
	m_pPainter->drawPolyline(pPoints, Count);

	delete [] pPoints;

	return true;
}

//-------------------------------------
void CXBitmap::SetPen(const CXPen &Pen) {
	if(IsNull())
		return;

	Qt::PenStyle Style =Qt::NoPen;
	switch(Pen.GetStyle()) {
		case CXPen::e_Solid:	Style = Qt::SolidLine; break;
	}

	QPen qPen;
	qPen.setStyle(Style);
	qPen.setWidth(Pen.GetWidth());
	qPen.setColor(CXRGB2QColor(Pen.GetColor()));

	m_pPainter->setPen(qPen);
}

//-------------------------------------
void CXBitmap::SetFont(int FontHeight, bool Bold) {
	if(IsNull())
		return;
	QFont font = m_pPainter->font();
	font.setPixelSize(FontHeight);
	font.setBold(Bold);
	m_pPainter->setFont(font);
}

//-------------------------------------
bool CXBitmap::LoadFromFile(const CXStringASCII & FileName) {
	if(IsNull())
		return false;

	QImage img;
	if(!img.load(FileName.c_str()))
		return false;
	QRect tgt(0, 0, GetWidth(), GetHeight());
	m_pPainter->drawImage(tgt, img);

	return true;
}

//-------------------------------------
void CXBitmap::Draw(CXBitmap *pBmp, int OffsetX, int OffsetY) {
	if(IsNull())
		return;
	if(pBmp == NULL)
		return;

	QRect src(0, 0, pBmp->GetWidth(), pBmp->GetHeight());
	QRect tgt(OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight());
	m_pPainter->drawImage(tgt, *pBmp->GetImage(), src);
}

//-------------------------------------
void CXBitmap::Blend(CXBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha) {
	if(IsNull())
		return;
	if(pBmp == NULL)
		return;

	QRect src(0, 0, pBmp->GetWidth(), pBmp->GetHeight());
	QRect tgt(OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight());
	qreal Opacity = m_pPainter->opacity();
	m_pPainter->setOpacity(Alpha/100.0);
	m_pPainter->drawImage(tgt, *pBmp->GetImage(), src);
	m_pPainter->setOpacity(Opacity);
}

//-------------------------------------
void CXBitmap::DrawTransparent(CXBitmap *pBmp, int XTarget, int YTarget, int XSource, int YSource, int Width, int Height, const CXRGB & TrColor) {
	if(IsNull())
		return;
	if(pBmp == NULL)
		return;

	QRect src(XSource, YSource, Width, Height);
	QImage cpy = pBmp->GetImage()->copy(src);
	QImage mask = cpy.createMaskFromColor(qRgb(TrColor.GetR(), TrColor.GetG(), TrColor.GetB()), Qt::MaskOutColor);
	cpy.setAlphaChannel(mask);
	src = QRect(0, 0, Width, Height);
	QRect tgt(XTarget, YTarget, Width, Height);
	m_pPainter->drawImage(tgt, cpy, src);
}
