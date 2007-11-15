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

#ifndef __CXNAVIPOWM_HPP__
#define __CXNAVIPOWM_HPP__

#include "CXRect.hpp"
#include "CXMutex.hpp"


#include "CXInfoBar.hpp"
#include "CXBitmap.hpp"

class CXGPSRecvThread;
class CXLocatorThread;
class CXMapThread;
class IMainWindow;
class CXDeviceContext;
class CXNaviData;
class CXInfoBarBottom;
class CXInfoBarTop;


//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 * \todo THIS IS A QUICK AND DIRTY HACK TO FIX 1828282 : Implement zoom buttons
 *
 */
class CXZoomBtn  : public CXInfoBar {
private:
	CXBitmap		m_Bmp;		///< oiu
	E_COMMAND		m_eCommand;	///< oiu
	//-------------------------------------
	CXZoomBtn();										///< Not used.
	CXZoomBtn(const CXZoomBtn &);						///< Not used.
	const CXZoomBtn & operator = (const CXZoomBtn &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnPaint(CXDeviceContext *pDC, int OffsetX, int OffsetY);
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual E_COMMAND OnInternalMouseDown(int X, int Y);
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXZoomBtn(E_COMMAND eCommand);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXZoomBtn();
};


//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXNaviPOWM {
private:
	IMainWindow			*m_pMainWindow;				///< oiu
	CXGPSRecvThread		*m_pGPSRecvThread;			///< oiu
	CXLocatorThread		*m_pLocatorThread;			///< oiu
	CXMapThread			*m_pMapThread;				///< oiu
	CXInfoBarBottom		*m_pInfoBarBottom;			///< oiu
	CXInfoBarTop		*m_pInfoBarTop;				///< oiu
	int					m_iWidth;					///< oiu
	int					m_iHeight;					///< oiu
	tIRect				m_InfoBarTopPos;			///< oiu
	tIRect				m_InfoBarBottomPos;			///< oiu
	tIRect				m_ZoomInPos;				///< oiu
	tIRect				m_ZoomOutPos;				///< oiu
	bool				m_oShowInfo;				///< oiu
	CXZoomBtn			m_ZoomInBtn;				///< oiu
	CXZoomBtn			m_ZoomOutBtn;				///< oiu
	mutable CXMutex		m_Mutex;					///< oiu
	//-------------------------------------
	CXNaviPOWM(const CXNaviPOWM &);						///< Not used.
	const CXNaviPOWM & operator = (const CXNaviPOWM &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetWidth() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetWidth(int Width);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetHeight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetHeight(int Height);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXNaviPOWM();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXNaviPOWM();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool Init(IMainWindow *pMainWindow);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool StartThreads();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void StopThreads();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void RequestRepaint();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Paint(CXDeviceContext *pDC);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Resize(int Width, int Height);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnChar(int TheChar);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnKeyDown(int TheChar);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnKeyUp(int TheChar);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnMouseDown(int X, int Y);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void PositionChanged(const CXNaviData & NewData);
};

#endif // __CXNAVIPOWM_HPP__
