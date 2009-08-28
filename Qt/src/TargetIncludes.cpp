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

#include "TargetIncludes.hpp"
#include "CXRGB.hpp"
#include <stdio.h>

#include <qcolor.h>
#include <qmessagebox.h>

//-------------------------------------
void DoOutputDebugString(const char *pcBuf) {
	// do some tests
	if(pcBuf == NULL)
		return;
	printf("%s", pcBuf);
}

//-------------------------------------
void DoOutputErrorMessage(const char *pcBuf) {
	// do some tests
	if(pcBuf == NULL)
		return;
	QMessageBox::critical(NULL, "NaviPOWM error", pcBuf);
}

//-------------------------------------
QColor CXRGB2QColor(const CXRGB & Color){
	return QColor(Color.GetR(), Color.GetG(), Color.GetB());
}

//-------------------------------------
CXRGB QColor2CXRGB(const QColor & Color) {
	return CXRGB(Color.red(), Color.green(), Color.blue());
}
