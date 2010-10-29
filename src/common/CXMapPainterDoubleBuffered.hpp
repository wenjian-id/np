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

#ifndef __CXMAPPAINTERDOUBLEBUFFERED_HPP__
#define __CXMAPPAINTERDOUBLEBUFFERED_HPP__

#include "CXMapPainter.hpp"
#include "CXBitmap.hpp"

class CXDeviceContext;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapPainterDoubleBuffered : public CXMapPainter {
private:
    // internal painting stuff
    int                 m_Width;                ///< oiu
    int                 m_Height;               ///< oiu
    CXBitmap            m_Bitmap1;              ///< oiu
    CXBitmap            m_Bitmap2;              ///< oiu
    CXBitmap            *m_pDrawBitmap;         ///< oiu
    CXBitmap            *m_pFinishedBitmap;     ///< oiu
    int                 m_iSwitchFlag;          ///< oiu
    mutable CXRWLock    m_RWLock;               ///< Synchronization object.
    //-------------------------------------
    CXMapPainterDoubleBuffered(const CXMapPainterDoubleBuffered &);                     ///< Not used.
    const CXMapPainterDoubleBuffered & operator = (const CXMapPainterDoubleBuffered &); ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SwitchBuffers();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CreateBuffers(CXDeviceContext *pDC, int Width, int Height);
protected:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnInternalPaint(IBitmap *pBMP, int Width, int Height) = 0;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void PaintPackground(IBitmap *pBMP, int Width, int Height) = 0;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnDoWork();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnBuffersCreated(CXDeviceContext *pDC, int Width, int Height);
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXMapPainterDoubleBuffered();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXMapPainterDoubleBuffered();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void Resize(int Width, int Height);
};

#endif // __CXMAPPAINTERDOUBLEBUFFERED_HPP__
