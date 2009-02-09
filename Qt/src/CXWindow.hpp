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

#include <qwidget.h>
#include <qevent.h>

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXWindow : public IWindow, public QWidget {
private:
	//-------------------------------------
	CXWindow(const CXWindow &);							///< Not used.
	const CXWindow & operator = (const CXWindow &);		///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void paintEvent(QPaintEvent *event);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void resizeEvent(QResizeEvent *event);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void keyPressEvent(QKeyEvent * event);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void keyReleaseEvent(QKeyEvent * event);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void mousePressEvent(QMouseEvent * event);
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
