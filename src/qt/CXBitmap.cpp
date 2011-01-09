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

#include "CXBitmap.hpp"
#include "CXDeviceContext.hpp"
#include "CXPen.hpp"
#include "TargetIncludes.hpp"
#include "Utils.hpp"

#include <qcolor.h>
#include <qpainter.h>
#include <qbitmap.h>

//-------------------------------------
CXBitmap::CXBitmap() :
    m_pImage(NULL),
    m_pPainter(NULL),
    m_pLinePoints(NULL),
    m_LinePointsSize(0)
{
}

//-------------------------------------
CXBitmap::~CXBitmap() {
    Destroy();
    delete [] m_pLinePoints;
    m_pLinePoints = NULL;
    m_LinePointsSize = 0;
}

//-------------------------------------
void CXBitmap::Destroy() {
    // delete painter and image
    delete m_pPainter;
    delete m_pImage;
    m_pPainter = NULL;
    m_pImage = NULL;
    SetFileName("");
}

//-------------------------------------
bool CXBitmap::IsNull() {
    return ((m_pImage == NULL) || (m_pPainter == NULL));
}

//-------------------------------------
bool CXBitmap::Create(IDeviceContext */*pDC*/, int Width, int Height) {
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
    m_pPainter->drawRect(TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetWidth() - 1, TheRect.GetHeight() - 1);

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
    Result = tIRect(0, 0, Res.width() + AddWidth, Res.height() + AddHeight);
    return Result;
}

//-------------------------------------
void CXBitmap::DrawTextQString(const QString & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & BgColor) {
    if(IsNull())
        return;

    // draw background
    DrawRect(TheRect, BgColor, BgColor);

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
    QRect Rect(TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetWidth()-1, TheRect.GetHeight()-1);

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
void CXBitmap::DrawGlowTextUTF8(const CXStringUTF8 & Text, const tIRect & TheRect, const CXRGB & FgColor, const CXRGB & GlowColor, int GlowSize) {
    if(IsNull())
        return;

    /// \todo write optimized version

    // create temporary QImage like in Create()
    QImage TmpImage(GetWidth(), GetHeight(), QImage::Format_RGB32);
    // create painter
    QPainter TmpPainter(&TmpImage);
    TmpPainter.setRenderHint(QPainter::Antialiasing, false);
    QFont font = m_pPainter->font();
    // do not use antialiasing
    font.setStyleStrategy(QFont::NoAntialias);
    TmpPainter.setFont(font);
    // create pen
    QPen TmpPen(Qt::SolidLine);
    TmpPen.setWidth(1);
    // create brush
    QBrush TmpBrush(CXRGB2QColor(COLOR_TRANSPARENT), Qt::SolidPattern);
    // select new pen and brush
    TmpPainter.setPen(TmpPen);
    TmpPainter.setBrush(TmpBrush);
    // create rect
    QRect Rect(0, 0, TheRect.GetWidth()-1, TheRect.GetHeight()-1);
    // create string
    QString qText = QString::fromUtf8(reinterpret_cast<const char *>(Text.uc_str()));

    // draw background in "transparent color"
    TmpPen.setColor(CXRGB2QColor(COLOR_TRANSPARENT));
    TmpPainter.setPen(TmpPen);
    // draw rectangle
    TmpPainter.drawRect(Rect);

    // draw text in glow color on temporary QImage
    TmpPen.setColor(CXRGB2QColor(GlowColor));
    TmpPainter.setPen(TmpPen);
    TmpPainter.drawText(Rect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, qText, NULL);

    // create image mask
    QImage cpy = TmpImage.copy(Rect);
    QImage mask = cpy.createMaskFromColor(qRgb(COLOR_TRANSPARENT.GetR(), COLOR_TRANSPARENT.GetG(), COLOR_TRANSPARENT.GetB()), Qt::MaskOutColor);
    cpy.setAlphaChannel(mask);

    // now create glow
    for(int dx=-GlowSize; dx<=GlowSize; dx++) {
        for(int dy=-GlowSize; dy<=GlowSize; dy++) {
            if((dx != 0) || (dy != 0)) {
                QRect tgt(TheRect.GetLeft()+dx, TheRect.GetTop()+dy, TheRect.GetWidth()-1, TheRect.GetHeight()-1);
                m_pPainter->drawImage(tgt, cpy, Rect);
            }
        }
    }

    // draw text
    TmpPen.setColor(CXRGB2QColor(FgColor));
    TmpPainter.setPen(TmpPen);
    TmpPainter.drawText(Rect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, qText, NULL);
    QRect tgt(TheRect.GetLeft(), TheRect.GetTop(), TheRect.GetWidth()-1, TheRect.GetHeight()-1);
    cpy = TmpImage.copy(Rect);
    cpy.setAlphaChannel(mask);
    m_pPainter->drawImage(tgt, cpy, Rect);
}

//-------------------------------------
void CXBitmap::DrawLine(int x0, int y0, int x1, int y1) {
    if(IsNull())
        return;

    m_pPainter->drawLine(x0, y0, x1, y1);
}

//-------------------------------------
void CXBitmap::DrawLine(size_t Count, const int *pX, const int *pY) {
    if(IsNull())
        return;
    if(Count < 2)
        return;
    if(pX == NULL)
        return;
    if(pY == NULL)
        return;
    if(Count > m_LinePointsSize) {
        delete [] m_pLinePoints;
        m_LinePointsSize = Count;
        m_pLinePoints = new QPoint[m_LinePointsSize];
    }
    for(size_t i=0; i<Count; i++) {
        m_pLinePoints[i].setX(pX[i]);
        m_pLinePoints[i].setY(pY[i]);
    }

    m_pPainter->drawPolyline(m_pLinePoints, Count);
}

//-------------------------------------
void CXBitmap::DrawCircle(int x, int y, int r, const CXRGB &PenColor, const CXRGB &FillColor) {
    if(IsNull()) {
        return;
    }

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
}

//-------------------------------------
void CXBitmap::Polygon(int *pX, int *pY, size_t Count, const CXRGB &PenColor, const CXRGB &FillColor) {
    if(IsNull()) {
        return;
    }
    if(pX == NULL) {
        return;
    }
    if(pY == NULL) {
        return;
    }
    if(Count == 0) {
        return;
    }

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
}

//-------------------------------------
void CXBitmap::SetPen(const CXPen &Pen) {
    if(IsNull())
        return;

    Qt::PenStyle Style =Qt::NoPen;
    switch(Pen.GetStyle()) {
        case CXPen::e_Solid:    Style = Qt::SolidLine; break;
    }

    QPen qPen;
    qPen.setStyle(Style);
    qPen.setWidth(Pen.GetWidth());
    qPen.setColor(CXRGB2QColor(Pen.GetColor()));
//  qPen.setJoinStyle(Qt::RoundJoin);
    qPen.setCapStyle(Qt::RoundCap);

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
    SetFileName(FileName);

    return true;
}

//-------------------------------------
void CXBitmap::Draw(IBitmap *pBmp, int OffsetX, int OffsetY) {
    if(IsNull())
        return;
    if(pBmp == NULL)
        return;
    CXBitmap *pBitmap = dynamic_cast<CXBitmap *>(pBmp);
    if(pBitmap == NULL)
        return;
    QRect src(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
    QRect tgt(OffsetX, OffsetY, pBitmap->GetWidth(), pBitmap->GetHeight());
    m_pPainter->drawImage(tgt, *pBitmap->GetImage(), src);
}

//-------------------------------------
void CXBitmap::Blend(IBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha) {
    if(IsNull())
        return;
    if(pBmp == NULL)
        return;
    CXBitmap *pBitmap = dynamic_cast<CXBitmap *>(pBmp);
    if(pBitmap == NULL)
        return;

    QRect src(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
    QRect tgt(OffsetX, OffsetY, pBitmap->GetWidth(), pBitmap->GetHeight());
    qreal Opacity = m_pPainter->opacity();
    m_pPainter->setOpacity(Alpha/100.0);
    m_pPainter->drawImage(tgt, *pBitmap->GetImage(), src);
    m_pPainter->setOpacity(Opacity);
}

//-------------------------------------
void CXBitmap::DrawTransparent(IBitmap *pBmp, int XTarget, int YTarget, int XSource, int YSource, int Width, int Height, const CXRGB & TrColor) {
    if(IsNull())
        return;
    if(pBmp == NULL)
        return;
    CXBitmap *pBitmap = dynamic_cast<CXBitmap *>(pBmp);
    if(pBitmap == NULL)
        return;

    QRect src(XSource, YSource, Width, Height);
    QImage cpy = pBitmap->GetImage()->copy(src);
    QImage mask = cpy.createMaskFromColor(qRgb(TrColor.GetR(), TrColor.GetG(), TrColor.GetB()), Qt::MaskOutColor);
    cpy.setAlphaChannel(mask);
    src = QRect(0, 0, Width, Height);
    QRect tgt(XTarget, YTarget, Width, Height);
    m_pPainter->drawImage(tgt, cpy, src);
}
