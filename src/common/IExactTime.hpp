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

#ifndef __IEXACTTIME_H__
#define __IEXACTTIME_H__

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class IExactTime {
private:
	//-------------------------------------
	IExactTime(const IExactTime &);						///< Not used.
	const IExactTime & operator = (const IExactTime &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	IExactTime() {
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~IExactTime() {
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void SetNow() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int GetYear() const = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int GetMonth() const = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int GetDay() const = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int GetHour() const = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int GetMinute() const = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual int GetSecond() const = 0;
};

#endif //__IEXACTTIME_H__
