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

#ifndef __CXEXACTTIME_HPP__
#define __CXEXACTTIME_HPP__

#include "IExactTime.hpp"

#include <qdatetime.h>

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXExactTime : public IExactTime {
private:
	//-------------------------------------
	QDateTime		m_Time;			///< oiu
	//-------------------------------------
	/*
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXExactTime & rOther);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXExactTime();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXExactTime(const CXExactTime&rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	~CXExactTime();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXExactTime & operator = (const CXExactTime & rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual void SetNow();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual unsigned long operator - (const CXExactTime & rOther) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int GetYear() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int GetMonth() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int GetDay() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int GetHour() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int GetMinute() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual int GetSecond() const;
};

#endif //__CXEXACTTIME_HPP__
