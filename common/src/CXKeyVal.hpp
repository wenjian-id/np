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

#ifndef __CXKEYVAL_HPP__
#define __CXKEYVAL_HPP__

//-------------------------------------
/**
 * \brief oiu
 *
 */
template<class tKey, class tValue> class CXKeyVal {
private:
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXKeyVal &rOther) {
		m_Key = rOther.m_Key;
		m_Value = rOther.m_Value;
	}
protected:
public:
	tKey	m_Key;		///< oiu
	tValue	m_Value;	///< oiu
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXKeyVal() {
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXKeyVal(const tKey & Key, const tValue & Value) :
		m_Key(Key),
		m_Value(Value)
	{
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXKeyVal() {
	}
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXKeyVal(const CXKeyVal &rOther) {
		CopyFrom(rOther);
	}
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXKeyVal & operator = (const CXKeyVal & rOther) {
		if(this != &rOther)
			CopyFrom(rOther);
		return *this;
	}
};

#endif // __CXKEYVAL_HPP__
