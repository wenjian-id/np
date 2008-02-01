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

#ifndef __CXUTMSPEED_HPP__
#define __CXUTMSPEED_HPP__

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXUTMSpeed {
private:
	double	m_dSpeed;		///< oiu
	double	m_dCos;			///< oiu
	double	m_dSin;			///< oiu
	//-------------------------------------
	/*
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXUTMSpeed &rOther);
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXUTMSpeed();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXUTMSpeed(const CXUTMSpeed &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXUTMSpeed();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXUTMSpeed & operator = (const CXUTMSpeed &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator == (const CXUTMSpeed &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator != (const CXUTMSpeed &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Reset();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetSpeed() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSpeed(double dSpeed);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetCos() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetCos(double dCos);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetSin() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSin(double dSin);
};

#endif // __CXUTMSPEED_HPP__
