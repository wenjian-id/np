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
#include "CXDeviceContext.hpp"
#include "TargetIncludes.hpp"
#include <qpainter.h>


//-------------------------------------
CXWindow::CXWindow() {
	setAutoFillBackground(false);
}

//-------------------------------------
CXWindow::~CXWindow() {
}

//-------------------------------------
void CXWindow::RequestRepaint() {
	update();
	/// \todo Check why a second update is needed to fix bug #1826737
	update();
}

//-------------------------------------
void CXWindow::paintEvent(QPaintEvent * /*event*/) {
	OnPaint();
}

//-------------------------------------
void CXWindow::resizeEvent(QResizeEvent *event) {
	QWidget::resizeEvent(event);
	OnResize(event->size().width(), event->size().height());
}

//-------------------------------------
void CXWindow::keyPressEvent(QKeyEvent * event) {
	QWidget::keyPressEvent(event);
	OnKeyDown(event->key());
}

//-------------------------------------
void CXWindow::keyReleaseEvent(QKeyEvent * event) {
	QWidget::keyReleaseEvent(event);
	OnKeyUp(event->key());
}

//-------------------------------------
void CXWindow::mousePressEvent(QMouseEvent * event) {
	QWidget::mousePressEvent(event);
	OnMouseDown(event->x(), event->y());
}

//-------------------------------------
void CXWindow::mouseReleaseEvent(QMouseEvent * event) {
	QWidget::mouseReleaseEvent(event);
	OnMouseUp(event->x(), event->y());
}

//-------------------------------------
void CXWindow::ShowMaximized() {
	showMaximized();
	update();
}

//-------------------------------------
void CXWindow::ShowNormal() {
	showNormal();
	update();
}

//-------------------------------------
void CXWindow::ShowFullScreen() {
	showFullScreen();
}

//-------------------------------------
void CXWindow::ShowMinimized() {
	showMinimized();
}

