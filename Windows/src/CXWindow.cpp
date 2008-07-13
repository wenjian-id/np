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

#include "CXWindow.hpp"

//-------------------------------------
CXWindow::CXWindow() :
	m_hWnd(NULL)
{
	/// \todo implement
}

//-------------------------------------
CXWindow::~CXWindow() {
	/// \todo implement
}

//-------------------------------------
void CXWindow::SetHWND(HWND hWnd) {
	m_hWnd = hWnd;
}

//-------------------------------------
HWND CXWindow::GetHWND() const {
	return m_hWnd;
}

//-------------------------------------
void CXWindow::RequestRepaint() {
	if(m_hWnd == NULL)
		return;
	InvalidateRect(m_hWnd, NULL, TRUE);
	UpdateWindow(m_hWnd);
}

//-------------------------------------
void CXWindow::OnPaint() {
	if(m_hWnd == NULL)
		return;
	/// \todo needed?
}

//-------------------------------------
void CXWindow::ShowMaximized() {
	if(m_hWnd != NULL) {
		ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
		InvalidateRect(m_hWnd, NULL, true);
	}
}

//-------------------------------------
void CXWindow::ShowNormal() {
	if(m_hWnd != NULL) {
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		InvalidateRect(m_hWnd, NULL, true);
	}
}

//-------------------------------------
void CXWindow::ShowFullScreen() {
	if(m_hWnd != NULL) {
		SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN);
		ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
	}
}

//-------------------------------------
void CXWindow::ShowMinimized() {
	if(m_hWnd != NULL) {
		ShowWindow(m_hWnd, SW_MINIMIZE);
	}
}
