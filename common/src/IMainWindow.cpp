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

#include "IMainWindow.hpp"
#include <CXNaviPOWM.hpp>

//-------------------------------------
IMainWindow::IMainWindow() :
	m_pNaviPOWM(NULL)
{
	m_pNaviPOWM = new CXNaviPOWM();
}

//-------------------------------------
IMainWindow::~IMainWindow() {
	delete m_pNaviPOWM;
	m_pNaviPOWM = NULL;
}

//-------------------------------------
CXNaviPOWM *IMainWindow::GetNaviPOWM() const {
	return m_pNaviPOWM;
}

//-------------------------------------
bool IMainWindow::Init() {
	if(m_pNaviPOWM == NULL)
		return false;
	return m_pNaviPOWM->Init(this);
}

//-------------------------------------
bool IMainWindow::StartThreads() {
	if(m_pNaviPOWM == NULL)
		return false;
	return m_pNaviPOWM->StartThreads();
}

//-------------------------------------
void IMainWindow::StopThreads() {
	if(m_pNaviPOWM == NULL)
		return;
	m_pNaviPOWM->StopThreads();
}

//-------------------------------------
void IMainWindow::OnResize(int Width, int Height) {
	if(m_pNaviPOWM != NULL)
		m_pNaviPOWM->Resize(Width, Height);
}

//-------------------------------------
void IMainWindow::OnChar(int TheChar) {
	if(m_pNaviPOWM != NULL)
		m_pNaviPOWM->OnChar(TheChar);
}

//-------------------------------------
void IMainWindow::OnKeyDown(int TheChar) {
	if(m_pNaviPOWM != NULL)
		m_pNaviPOWM->OnKeyDown(TheChar);
}

//-------------------------------------
void IMainWindow::OnKeyUp(int TheChar) {
	if(m_pNaviPOWM != NULL)
		m_pNaviPOWM->OnKeyUp(TheChar);
}

//-------------------------------------
void IMainWindow::OnMouseDown(int X, int Y) {
	if(m_pNaviPOWM != NULL)
		m_pNaviPOWM->OnMouseDown(X, Y);
}
