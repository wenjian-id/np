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

#ifndef __CXMAINWINDOW_HPP__
#define __CXMAINWINDOW_HPP__

#include <IMainWindow.hpp>

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXMainWindow : public IMainWindow {
private:
	static CXMainWindow		*m_pInstance;		/// oiu multiple instances
	//-------------------------------------
	CXMainWindow(const CXMainWindow &);							///< Not used.
	//-------------------------------------
	const CXMainWindow & operator = (const CXMainWindow &);		///< Not used.
protected:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void OnPaint();
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXMainWindow();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXMainWindow();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void RequestTermination();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	LRESULT CALLBACK TheWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


#endif // __CXMAINWINDOW_HPP__
