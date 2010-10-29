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

#ifndef __CXWINDOW_HPP__
#define __CXWINDOW_HPP__

#include <IWindow.hpp>
#include <TargetIncludes.hpp>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXWindow : public IWindow {
private:
    HWND                    m_hWnd;
    //-------------------------------------
    CXWindow(const CXWindow &);                         ///< Not used.
    //-------------------------------------
    const CXWindow & operator = (const CXWindow &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXWindow();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXWindow();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetHWND(HWND hWnd);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    HWND GetHWND() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void ShowMaximized();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void ShowNormal();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void ShowFullScreen();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void ShowMinimized();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual void RequestRepaint();
};


#endif // __CXWINDOW_HPP__
