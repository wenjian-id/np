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

#include "CXMainWindow.hpp"
#include "CXNaviPOWM.hpp"
#include "CXDeviceContext.hpp"
#include "CXOptions.hpp"

CXMainWindow *CXMainWindow::m_pInstance = NULL;

//-------------------------------------
CXMainWindow::CXMainWindow() {
    m_pInstance = this;
}

//-------------------------------------
CXMainWindow::~CXMainWindow() {
    m_pInstance = NULL;
}

//-------------------------------------
void CXMainWindow::OnPaint() {
    HWND hWnd = GetHWND();
    if(hWnd == NULL)
        return;

    // init painting
    RECT rt;
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    GetClientRect(hWnd, &rt);
    int Width=rt.right + 1 - rt.left;
    int Height=rt.bottom + 1 - rt.top;

    // create MemDC
    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, Width, Height);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, bmp);

    // do painting
    CXDeviceContext DC(hMemDC);

    if(GetNaviPOWM() != NULL)
        GetNaviPOWM()->Paint(&DC);

    // copy painted data to dc
    BitBlt(hdc, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);

    // cleanup
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(bmp);
    DeleteDC(hMemDC);
    EndPaint(hWnd, &ps);
}

//-------------------------------------
void CXMainWindow::RequestTermination() {
    PostQuitMessage(0);
}

//-------------------------------------
LRESULT CALLBACK CXMainWindow::WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return m_pInstance->TheWndProc(hWnd, message, wParam, lParam);
}

//-------------------------------------
LRESULT CALLBACK CXMainWindow::TheWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_PAINT:
            {
                // now do paint
                if(m_pInstance != NULL)
                    m_pInstance->OnPaint();
                break;
            }
        case WM_ERASEBKGND:     return 1;
        case WM_SIZE:
            {
                int Width = LOWORD(lParam);
                int Height = HIWORD(lParam);
                if(m_pInstance != NULL)
                    m_pInstance->OnResize(Width, Height);
                break;
            }
        case WM_CHAR:           m_pInstance->OnChar(wParam); break;
        case WM_KEYDOWN:        m_pInstance->OnKeyDown(wParam); break;
        case WM_KEYUP:          m_pInstance->OnKeyUp(wParam); break;
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                break;
            }
        case WM_LBUTTONDOWN:
            {
                int X = LOWORD(lParam);
                int Y = HIWORD(lParam);
                if(m_pInstance != NULL)
                    m_pInstance->OnMouseDown(X, Y);
                break;
            }
        case WM_LBUTTONUP:
            {
                int X = LOWORD(lParam);
                int Y = HIWORD(lParam);
                if(m_pInstance != NULL)
                    m_pInstance->OnMouseUp(X, Y);
                break;
            }
        case WM_MOUSEMOVE:
            {
                int X = LOWORD(lParam);
                int Y = HIWORD(lParam);
                if(m_pInstance != NULL)
                    m_pInstance->OnMouseMove(X, Y);
                break;
            }
        case WM_ACTIVATE:
            {
                // call DefWindowProc
                DefWindowProc(hWnd, message, wParam, lParam);
                // now do own stuff
                if(LOWORD(wParam) != WA_INACTIVE) {
                    if(CXOptions::Instance()->IsFullScreen()) {
                        ShowFullScreen();
                    } else {
                        ShowNormal();
                    }
                }
                break;
            }
        default:            return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
