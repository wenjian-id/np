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

#ifndef __CXMAPSIMPLE_HPP__
#define __CXMAPSIMPLE_HPP__

#include "CXBuffer.hpp"
#include "CXKeyVal.hpp"
#include <TargetIncludes.hpp>

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
template<class tKey, class tValue> class CXMapSimple {
public:
	static const size_t NPOS;				///< oiu
	static const size_t START;				///< oiu
private:
	CXBuffer< CXKeyVal<tKey, tValue> *>	m_Data;			///< oiu
	//-------------------------------------
	CXMapSimple(const CXMapSimple &);						///< Not used.
	const CXMapSimple & operator = (const CXMapSimple &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXKeyVal<tKey, tValue> *Find(const tKey & Key) const;
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXMapSimple();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXMapSimple();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void RemoveAll();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetAt(const tKey & Key, const tValue & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool Lookup(const tKey & Key, tValue & Result) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetStart() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetNext(size_t & Pos, tValue &rValue) const;
};

template<class tKey, class tValue> const size_t CXMapSimple<tKey, tValue> ::NPOS = ~(size_t(0));
template<class tKey, class tValue> const size_t CXMapSimple<tKey, tValue> ::START = ~(size_t(1));


//-------------------------------------
template<class tKey, class tValue> CXMapSimple<tKey, tValue> ::CXMapSimple() {
}

//-------------------------------------
template<class tKey, class tValue> CXMapSimple<tKey, tValue> ::~CXMapSimple() {
	RemoveAll();
}

//-------------------------------------
template<class tKey, class tValue> void CXMapSimple<tKey, tValue> ::RemoveAll() {
	// delete all elements
	for(size_t i=0; i<m_Data.GetSize(); i++)
		delete m_Data[i];
	m_Data.Clear();
}

//-------------------------------------
template<class tKey, class tValue> CXKeyVal<tKey, tValue> * CXMapSimple<tKey, tValue> ::Find(const tKey & Key) const {
	// iterate through all elements and search for the one with key tKey
	for(size_t i=0; i<m_Data.GetSize(); i++) {
		CXKeyVal<tKey, tValue> *pResult = m_Data[i];
		if(pResult->m_Key == Key)
			// found
			return pResult;
	}
	return NULL;
}

//-------------------------------------
template<class tKey, class tValue> void CXMapSimple<tKey, tValue> ::SetAt(const tKey & Key, const tValue & Value) {
	// check if already exists
	CXKeyVal<tKey, tValue> *pS = Find(Key);
	if(pS != NULL) {
		// already exists overwrite
		pS->m_Value = Value;
	} else {
		// does not exist yet
		m_Data.Append(new CXKeyVal<tKey, tValue>(Key, Value));
	}
}

//-------------------------------------
template<class tKey, class tValue> bool CXMapSimple<tKey, tValue> ::Lookup(const tKey &Key, tValue & Result) const {
	// check if exists
	CXKeyVal<tKey, tValue> *pS = Find(Key);
	if(pS != NULL) {
		// exists
		Result = pS->m_Value;
		return true;
	}
	// does not exist
	return false;
}

//-------------------------------------
template<class tKey, class tValue> size_t CXMapSimple<tKey, tValue> ::GetStart() const {
	return START;
}

//-------------------------------------
template<class tKey, class tValue> size_t CXMapSimple<tKey, tValue> ::GetNext(size_t & Pos, tValue &rValue) const {
	if(Pos == NPOS) {
		return Pos;
	}
	if(Pos == START) {
		Pos = 0;
	} else {
		Pos++;
	}
	if(Pos >= m_Data.GetSize()) {
		Pos = NPOS;
		return Pos;
	}
	rValue = m_Data[Pos]->m_Value;
	return Pos;
}

#endif //__CXMAPSIMPLE_HPP__
