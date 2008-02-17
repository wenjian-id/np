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

#include "CXDeviceContext.hpp"
#include "CXBitmap.hpp"

#include <qpainter.h>
#include <qbitmap.h>

//-------------------------------------
CXDeviceContext::CXDeviceContext(QPainter *pPainter) :
	m_pPainter(pPainter)
{
}

//-------------------------------------
CXDeviceContext::~CXDeviceContext() {
}

//-------------------------------------
QPainter *CXDeviceContext::GetPainter() const {
	return m_pPainter;
}

//-------------------------------------
void CXDeviceContext::Draw(CXBitmap *pBmp, int OffsetX, int OffsetY) {
	if(m_pPainter == NULL)
		return;
	if(pBmp == NULL)
		return;
	QRect src(0, 0, pBmp->GetWidth(), pBmp->GetHeight());
	QRect tgt(OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight());
	m_pPainter->drawImage(tgt, *pBmp->GetImage(), src);
}

//-------------------------------------
void CXDeviceContext::Blend(CXBitmap *pBmp, int OffsetX, int OffsetY, unsigned char Alpha) {
	if(m_pPainter == NULL)
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
void CXDeviceContext::DrawTransparent(CXBitmap *pBmp, int OffsetX, int OffsetY, const CXRGB & TrColor) {
	if(m_pPainter == NULL)
		return;
	if(pBmp == NULL)
		return;
	QImage cpy = *pBmp->GetImage();
	QImage mask = cpy.createMaskFromColor(qRgb(TrColor.GetR(), TrColor.GetG(), TrColor.GetB()), Qt::MaskOutColor);
	cpy.setAlphaChannel(mask);
	QRect src(0, 0, pBmp->GetWidth(), pBmp->GetHeight());
	QRect tgt(OffsetX, OffsetY, pBmp->GetWidth(), pBmp->GetHeight());
	m_pPainter->drawImage(tgt, cpy, src);
}
