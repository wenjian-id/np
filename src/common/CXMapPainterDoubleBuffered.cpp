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

#include "CXMapPainterDoubleBuffered.hpp"
#include "CXDeviceContext.hpp"
#include "CXExactTime.hpp"
#include "CXOptions.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"

#include <stdio.h>

//-------------------------------------
CXMapPainterDoubleBuffered::CXMapPainterDoubleBuffered() :
    m_Width(1),
    m_Height(1),
    m_pDrawBitmap(&m_Bitmap1),
    m_pFinishedBitmap(&m_Bitmap2),
    m_iSwitchFlag(1)
{
}

//-------------------------------------
CXMapPainterDoubleBuffered::~CXMapPainterDoubleBuffered() {
}

//-------------------------------------
void CXMapPainterDoubleBuffered::Resize(int Width, int Height) {
    CXWriteLocker WL(&m_RWLock);
    m_Width = Width;
    m_Height = Height;
    m_Bitmap1.Destroy();
    m_Bitmap2.Destroy();
}


//-------------------------------------
void CXMapPainterDoubleBuffered::OnDoWork() {
    {
        // start read locker
        CXReadLocker RL(&m_RWLock);
        // check if we can paint
        if(m_pDrawBitmap == NULL)
            return;
        if(m_Bitmap1.IsNull())
            return;
        CXNaviData Data = GetPosition();
        if(!CXOptions::Instance()->MustShowLogo()) {
            // call internal painting routine, since we must not display logo
            OnInternalPaint(m_pDrawBitmap, m_Width, m_Height);
        }
        // end read locker
    }
    // now switch buffers
    SwitchBuffers();
    // set flag
    SetMustRepaint(true);
}

//-------------------------------------
void CXMapPainterDoubleBuffered::SwitchBuffers() {
    CXWriteLocker WL(&m_RWLock);
    if(m_iSwitchFlag == 1) {
        m_pDrawBitmap = &m_Bitmap2;
        m_pFinishedBitmap = &m_Bitmap1;
        m_iSwitchFlag = 2;
    } else {
        m_pDrawBitmap = &m_Bitmap1;
        m_pFinishedBitmap = &m_Bitmap2;
        m_iSwitchFlag = 1;
    }
}

//-------------------------------------
void CXMapPainterDoubleBuffered::OnBuffersCreated(CXDeviceContext * /*pDC*/, int /*Width*/, int /*Height*/) {
    // do nothing
}

//-------------------------------------
void CXMapPainterDoubleBuffered::CreateBuffers(CXDeviceContext *pDC, int Width, int Height) {
    m_Bitmap1.Destroy();
    m_Bitmap2.Destroy();
    m_Bitmap1.Create(pDC, Width, Height);
    m_Bitmap2.Create(pDC, Width, Height);
    OnBuffersCreated(pDC, Width, Height);
}

//-------------------------------------
void CXMapPainterDoubleBuffered::Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY) {
    // protect from switching buffers
    CXReadLocker RL(&m_RWLock);
    if(pDC == NULL)
        return;
    if(m_Bitmap1.IsNull()) {
        // no internal buffers. create them
        CreateBuffers(pDC, m_Width, m_Height);
        CXNaviData Data = GetPosition();
        if(CXOptions::Instance()->MustShowLogo()) {
            // load logo
            m_pFinishedBitmap->LoadFromFile(CXOptions::Instance()->GetLogoFileName());
            m_pDrawBitmap->LoadFromFile(CXOptions::Instance()->GetLogoFileName());
        } else {
            PaintPackground(m_pFinishedBitmap, m_Width, m_Height);
        }
    }
    // bitblt internal paint buffer
    if(!m_pFinishedBitmap->IsNull())
        pDC->Draw(m_pFinishedBitmap, OffsetX, OffsetY);
    // reset flag
    SetMustRepaint(false);
}
