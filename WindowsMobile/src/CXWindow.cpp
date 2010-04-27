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

//#include <aygshell.h>
typedef BOOL (__stdcall *SHFullScreenProc)(HWND, DWORD);
#define SHFS_SHOWTASKBAR            0x0001
#define SHFS_HIDETASKBAR            0x0002
#define SHFS_SHOWSIPBUTTON          0x0004
#define SHFS_HIDESIPBUTTON          0x0008
#define SHFS_SHOWSTARTICON          0x0010
#define SHFS_HIDESTARTICON          0x0020


//-------------------------------------
CXWindow::CXWindow() :
	m_hWnd(NULL)
{
}

//-------------------------------------
CXWindow::~CXWindow() {
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
		// hide windows stuff
		int width = GetDeviceCaps(NULL, HORZRES);
		int height = GetDeviceCaps(NULL, VERTRES);

		bool DllFound = false;
		// try to load aygshell.dll
		HINSTANCE hAygDll = LoadLibrary(L"aygshell.dll");
		if (hAygDll) {
			// try to get procedure SHFullScreen
			SHFullScreenProc procSHFullScreen = (SHFullScreenProc)GetProcAddress(hAygDll, L"SHFullScreen");
			if (procSHFullScreen) {
				// use procedure SHFullScreen
				procSHFullScreen(m_hWnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON | SHFS_HIDESTARTICON);
				MoveWindow(m_hWnd, 0, 0, width, height, TRUE);
				DllFound = true;
			}
			FreeLibrary(hAygDll);
		}
		// don't use aygshell.dll and SHFullScreen
		if (!DllFound) SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
	}
}

//-------------------------------------
void CXWindow::ShowMinimized() {
	if(m_hWnd != NULL) {
		ShowWindow(m_hWnd, SW_MINIMIZE);
	}
}
