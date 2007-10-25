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

#ifndef __CXRGB_HPP__
#define __CXRGB_HPP__

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXRGB {
private:
	unsigned char m_R;		///< oiu
	unsigned char m_G;		///< oiu
	unsigned char m_B;		///< oiu
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void CopyFrom(const CXRGB &rOther);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRGB();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRGB(unsigned char R, unsigned char G, unsigned char B);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRGB(const CXRGB &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXRGB();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXRGB & operator = (const CXRGB & rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	unsigned char GetR() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	unsigned char GetG() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	unsigned char GetB() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetR(unsigned char R);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetG(unsigned char G);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetB(unsigned char B);
};

#endif // __CXRECT_HPP__
