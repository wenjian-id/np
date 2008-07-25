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

#ifndef __IMAINWINDOW_HPP__
#define __IMAINWINDOW_HPP__

#include <CXWindow.hpp>

class CXNaviPOWM;
class CXDeviceContext;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class IMainWindow : public CXWindow {
private:
	CXNaviPOWM			*m_pNaviPOWM;		///< oiu
	//-------------------------------------
	IMainWindow(const IMainWindow &);							///< Not used.
	const IMainWindow & operator = (const IMainWindow &);		///< Not used.
protected:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnResize(int Width, int Height);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnChar(int TheChar);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnKeyDown(int TheChar);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnKeyUp(int TheChar);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnMouseDown(int X, int Y);
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	IMainWindow();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~IMainWindow();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXNaviPOWM *GetNaviPOWM() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool Init();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool StartThreads();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void StopThreads();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void RequestTermination() = 0;
};


#endif // __IMAINWINDOW_HPP__
