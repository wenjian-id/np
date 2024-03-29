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

#ifndef __CXMAPPAINTER2D_HPP__
#define __CXMAPPAINTER2D_HPP__

#include "CXBuffer.hpp"
#include "CXMapPainterDoubleBuffered.hpp"
#include "CXPOWMMap.hpp"
#include "CXPenHolder.hpp"
#include "CXAreaColorHolder.hpp"
#include "CXHysterezis.hpp"

typedef CXMapHashSimple<unsigned short, CXBitmap *> TPOIBMPMap;
typedef CXPOSMapHashSimple<unsigned short> TPOSPOIBMPMap;

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapPainter2D : public CXMapPainterDoubleBuffered {
private:
    double                          m_MeterPerPixel;            ///< Current scale factor.
    double                          m_RequestedMeterPerPixel;   ///< Current scale factor.
    CXPenHolder                     m_PenHolder;                ///< oiu
    CXAreaColorHolder               m_AreaColorHolder;          ///< oiu
    CXBuffer<TWayBuffer *>          m_DrawWays;                 ///< oiu
    CXBuffer<TAreaBuffer *>         m_DrawAreas;                ///< oiu
    CXBuffer<CXBitmap *>            m_POIBMPs;                  ///< oiu
    CXBitmap                        *m_pPlaceBMP;               ///< oiu
    CXBitmap                        *m_pTargetBMP;              ///< oiu
    double                          m_LastSpeed;                ///< oiu
    CXHysterezis<double, double>    m_AutoZoomLevels;           ///< oiu
    mutable CXRWLock                m_RWLock;                   ///< Synchronization object.
    //-------------------------------------
    CXMapPainter2D(const CXMapPainter2D &);                     ///< Not used.
    const CXMapPainter2D & operator = (const CXMapPainter2D &); ///< Not used.
    //-------------------------------------
    /**
     * \brief Check if a way has segments that may be visible.
     *
     *  Check if a way has segments that may be visible.
     *  \param  pWay        Way to check.
     *  \param  Width       Width of screen.
     *  \param  Height      Height of screen.
     *  \return             true if way may be visible.
     */
    bool IsWayPossiblyVisible(CXWay *pWay, int Width, int Height);
    //-------------------------------------
    /**
     * \brief Draw a way.
     *
     *  Draw a way (background an foreground) with correct pen.
     *  \param  pBMP        Pointer to bitmap.
     *  \param  pWay        Way to draw.
     *  \param  Width       Width of screen.
     *  \param  Height      Height of screen.
     *  \return             true if way may be visible.
     */
    void DrawWay(IBitmap *pBMP, CXWay *pWay, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void DrawWaysBg(IBitmap *pBMP, TWayBuffer *pWays, E_WAY_TYPE eWayType, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void DrawWaysFg(IBitmap *pBMP, TWayBuffer *pWays, E_WAY_TYPE eWayType, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void DrawOneways(IBitmap *pBMP, TWayBuffer *pWays, E_WAY_TYPE eWayType, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void DrawAreas(IBitmap *pBMP, IBitmap *pTmpBMP, TAreaBuffer *pAreas, E_AREA_TYPE eAreaType);
    //-------------------------------------
    /**
     * \brief Draw map scale.
     *
     *  Compute and draw map scale.
     *  \param  pBMP            Pointer to bitmap.
     *  \param  ScreenWidth     Width of screen.
     *  \param  ScreenHeight    Height of screen.
     */
    void DrawScale(IBitmap *pBMP, int ScreenWidth, int ScreenHeight);
    //-------------------------------------
    /**
     * \brief Draw POIs.
     *
     *  Draw POIs.
     *  \param  pBMP            Pointer to bitmap.
     *  \param  ScreenWidth     Width of screen.
     *  \param  ScreenHeight    Height of screen.
     */
    void DrawPOIs(IBitmap *pBMP, const TPOINodeBuffer &POINodes, int ScreenWidth, int ScreenHeight);
    //-------------------------------------
    /**
     * \brief Draw Places.
     *
     *  Draw Places.
     *  \param  pBMP            Pointer to bitmap.
     *  \param  ScreenWidth     Width of screen.
     *  \param  ScreenHeight    Height of screen.
     */
    void DrawPlaces(IBitmap *pBMP, const TPOINodeBuffer &PlaceNodes, int ScreenWidth, int ScreenHeight);
    //-------------------------------------
    /**
     * \brief Draw compass.
     *
     *  Draw compass.
     *  \param  pBMP            Pointer to bitmap.
     *  \param  TMCompass       Transformation matrix for compass.
     */
    void DrawCompass(IBitmap *pBMP, const CXTransformationMatrix2D &TMCompass);
    //-------------------------------------
    /**
     * \brief Draw track log.
     *
     *  Draw track log.
     *  \param  pBMP            Pointer to bitmap.
     *  \param  TMMap           Transformation matrix.
     */
    void DrawTrackLog(IBitmap *pBMP, const CXTransformationMatrix2D &TMMap);
    //-------------------------------------
    /**
     * \brief Draw current position.
     *
     *  Draw current position.
     *  \param  pBMP            Pointer to bitmap.
     *  \param  NaviData        Navigation data.
     *  \param  TMCurrentPos    Transformation matrix.
     */
    void DrawCurrentPosition(IBitmap *pBMP, const CXNaviData &NaviData, const CXTransformationMatrix2D &TMCurrentPos);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void ComputeZoomBySpeed(double dSpeed);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double GetRequestedMeterPerPixel();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetRequestedMeterPerPixel(double NewValue);
protected:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnInternalPaint(IBitmap *pBMP, IBitmap *pTmpBMP, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void PaintPackground(IBitmap *pBMP, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void OnBuffersCreated(CXDeviceContext *pDC, int Width, int Height);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void UpdateZoomLevel();
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXMapPainter2D();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXMapPainter2D();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual bool ZoomIn();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual bool ZoomOut();
};

#endif // __CXMAPPAINTER2D_HPP__
