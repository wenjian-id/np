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

#include <qapplication.h>
#include <CXMainWindow.hpp>
#include <OSSpecific.hpp>
#include <CXOptions.hpp>

#include <qmessagebox.h>

int main( int argc, char ** argv ) {
	int result = 0;
	try{
		char * p = argv[0];
		CXStringASCII Path(p);
		int idx = Path.ReverseFind(PATHDELIMITER);
		if(idx >= 0)
			Path = Path.Left(idx+1);
		CXOptions::Instance()->SetStartPath(Path);
	
		// read configuration file
		CXStringASCII IniFileName = Path;
		IniFileName += "NAVI.INI";
		if(!CXOptions::Instance()->ReadFromFile(IniFileName.c_str())) {
			/// \todo implement
			// error message
		}
		
		QApplication a(argc, argv);
		a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
		CXMainWindow *pMainWnd = new CXMainWindow();
		pMainWnd->Init();
		pMainWnd->StartThreads();
		pMainWnd->setWindowTitle("NaviPOWM");

		// check if we must show it maximized
		if(CXOptions::Instance()->FullScreen()) {
			pMainWnd->ShowMaximized();
		} else {
			pMainWnd->ShowNormal();
		}
	
		result = a.exec();
		pMainWnd->StopThreads();
		delete pMainWnd;
	
	} catch(std::exception & e) {
		QMessageBox::warning(NULL, "ERROR", e.what(), QMessageBox::Ok, QMessageBox::Ok); 
	}
	
	return result;
}
