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

#include "CXMainWindow.hpp"
#include "CXOptions.hpp"
#include <OSSpecific.hpp>
#include <resource.h>
#include "CXRect.hpp"
#include <locale.h>

#define MAX_LOADSTRING 100


//-------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass) {
	WNDCLASS	wc;

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= CXMainWindow::WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(ID_MAINICON));
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;

	return RegisterClass(&wc);
}

//-------------------------------------
BOOL IsFirstInstance(HINSTANCE /*hInstance*/, LPTSTR szWindowClass) {

	HWND pWndPrev = NULL;
	// Determine if another window with our class name exists...
	pWndPrev = ::FindWindow(szWindowClass,NULL);
	if(pWndPrev != NULL) {
		// If iconic, restore the main window
		::ShowWindow(pWndPrev, SW_RESTORE);

		// Bring the main window or its popup to
		// the foreground
		::SetForegroundWindow(pWndPrev);

		// and we are done activating the previous one.
		return false;
	} else
	// First instance. Proceed as normal.
	return true;
}


//-------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int /*nCmdShow*/, CXMainWindow *pMainWnd) {
	HWND	hWnd;
	TCHAR	szWindowClass[MAX_LOADSTRING];		// The window class name

	if(!IsFirstInstance(hInstance, szWindowClass))
		return FALSE;

	MyRegisterClass(hInstance, szWindowClass);

	DWORD dwStyle =	WS_BORDER | WS_VISIBLE | WS_SIZEBOX | 
					WS_SYSMENU| WS_MAXIMIZEBOX | WS_MINIMIZEBOX;

	hWnd = CreateWindow(szWindowClass, "NaviPOWM", 
						dwStyle,
						CW_USEDEFAULT, CW_USEDEFAULT, // x, y
						CW_USEDEFAULT, CW_USEDEFAULT, // width , height
						NULL, NULL, hInstance, NULL);

	if(hWnd == NULL) {	
		return FALSE;
	}

	pMainWnd->SetHWND(hWnd);

	UpdateWindow(hWnd);

	return TRUE;
}

//-------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpCmdLine*/, int nCmdShow) {

	// set locale for numeric conversions
	setlocale(LC_NUMERIC, "C");

	char buf[1000];
	GetModuleFileName(NULL, buf, 1000);
	CXStringASCII Path(buf);
	int idx = Path.ReverseFind(PATHDELIMITER);
	if(idx >= 0)
		Path = Path.Left(idx+1);
	CXOptions::Instance()->SetStartPath(Path);

	// read configuration file
	CXStringASCII IniFileName = Path;
	IniFileName += "navipowm.ini";
	if(!CXOptions::Instance()->ReadFromFile(IniFileName.c_str())) {
		CXStringASCII ErrorMsg("Error reading from file: ");
		ErrorMsg += IniFileName;
		DoOutputErrorMessage(ErrorMsg.c_str());
	}

	CXMainWindow *pMainWnd = new CXMainWindow();
	pMainWnd->Init();
	pMainWnd->StartThreads();

	try {
		MSG msg;
		HACCEL hAccelTable = 0;

		// Perform application initialization:
		if (!InitInstance (hInstance, nCmdShow, pMainWnd)) {
			return FALSE;
		}


		// check if we must show it maximized
		if(CXOptions::Instance()->IsFullScreen()) {
			pMainWnd->ShowFullScreen();
		} else {
			pMainWnd->ShowNormal();
		}

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0)) {
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return msg.wParam;
	} catch(...) {
		MessageBox(NULL, "uncaught exception", "ERROR", MB_OK);
	}
	pMainWnd->StopThreads();
	delete pMainWnd;
	return 0;
}
