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

#ifndef __CXDIRECTION_HPP__
#define __CXDIRECTION_HPP__

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 * From east geometric direction (counter clockwise)
 */
class CXDirection {
private:
	double	m_dCos;		///< oiu
	double	m_dSin;		///< oiu
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXDirection &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXDirection();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXDirection(double dCos, double dSin);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXDirection(const CXDirection &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXDirection();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXDirection & operator = (const CXDirection &rOther);
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if equal.
	 */
	bool operator == (const CXDirection & rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXDirection operator - () const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetCos() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSin() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Reset();
};

#endif // __CXDIRECTION_HPP__


