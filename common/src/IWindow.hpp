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

#ifndef __IWINDOW_HPP__
#define __IWINDOW_HPP__

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class IWindow {
private:
	//-------------------------------------
	IWindow(const IWindow &);							///< Not used.
	const IWindow & operator = (const IWindow &);		///< Not used.
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnPaint() = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnResize(int Width, int Height) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnChar(int TheChar) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnKeyDown(int TheChar) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnKeyUp(int TheChar) = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnMouseDown(int X, int Y) = 0;
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	IWindow() {
	}
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~IWindow() {
	}
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void ShowMaximized() = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void ShowNormal() = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void ShowFullScreen() = 0;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void RequestRepaint() = 0;
};


#endif // __IWINDOW_HPP__
