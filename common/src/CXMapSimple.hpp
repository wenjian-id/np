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
//-------------------------------------
/**
 * \brief oiu
 *
 */
template<class tKey> class CXPOSMapSimple {
public:
	tKey		m_key;	///< oiu
	size_t		m_pos;	///< oiu
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXPOSMapSimple() {
		// m_key = 0;
		m_pos = 0;
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPOSMapSimple(size_t Pos) :
		m_pos(Pos)
	{
		// m_key = 0;
	}
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXPOSMapSimple(const CXPOSMapSimple &rOther) {
		m_key = rOther.m_key;
		m_pos = rOther.m_pos;
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXPOSMapSimple() {
	}
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXPOSMapSimple & operator = (const CXPOSMapSimple &rOther) {
		m_key = rOther.m_key;
		m_pos = rOther.m_pos;
		return *this;
	}
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if equal.
	 */
	bool operator == (const CXPOSMapSimple & rOther) {
		return m_pos == rOther.m_pos;
	}
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if not equal.
	 */
	bool operator != (const CXPOSMapSimple & rOther) {
		return ! operator ==(rOther);
	}
};

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tKey, class tValue> class CXMapSimple {
public:
	static const CXPOSMapSimple<tKey>	NPOS;				///< oiu
	static const CXPOSMapSimple<tKey>	START;				///< oiu
private:
	CXBuffer< CXKeyVal<tKey, tValue> *>	m_Data;				///< oiu
	//-------------------------------------
	CXMapSimple(const CXMapSimple &);						///< Not used.
	const CXMapSimple & operator = (const CXMapSimple &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXKeyVal<tKey, tValue> *Find(const tKey & Key, size_t & rIndex) const;
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapSimple();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapSimple();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void RemoveAll();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t GetSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetAt(const tKey & Key, const tValue & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void RemoveAt(const tKey & Key);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool Lookup(const tKey & Key, tValue & Result) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPOSMapSimple<tKey> GetStart() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXPOSMapSimple<tKey> GetNext(CXPOSMapSimple<tKey> & Pos, tValue &rValue) const;
};

template<class tKey, class tValue> const CXPOSMapSimple<tKey> CXMapSimple<tKey, tValue>::NPOS  =  CXPOSMapSimple<tKey>(~(size_t(0)));
template<class tKey, class tValue> const CXPOSMapSimple<tKey> CXMapSimple<tKey, tValue>::START =  CXPOSMapSimple<tKey>(~(size_t(1)));


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
template<class tKey, class tValue> size_t CXMapSimple<tKey, tValue> ::GetSize() const {
	return m_Data.GetSize();
}

//-------------------------------------
template<class tKey, class tValue> CXKeyVal<tKey, tValue> * CXMapSimple<tKey, tValue> ::Find(const tKey & Key, size_t & rIndex) const {
	rIndex = 0;
	// iterate through all elements and search for the one with key tKey
	for(size_t i=0; i<m_Data.GetSize(); i++) {
		CXKeyVal<tKey, tValue> *pResult = m_Data[i];
		if(pResult->m_Key == Key) {
			// found
			rIndex = i;
			return pResult;
		}
	}
	return NULL;
}

//-------------------------------------
template<class tKey, class tValue> void CXMapSimple<tKey, tValue> ::SetAt(const tKey & Key, const tValue & Value) {
	// check if already exists
	size_t Index = 0;
	CXKeyVal<tKey, tValue> *pS = Find(Key, Index);
	if(pS != NULL) {
		// already exists overwrite
		pS->m_Value = Value;
	} else {
		// does not exist yet
		m_Data.Append(new CXKeyVal<tKey, tValue>(Key, Value));
	}
}

//-------------------------------------
template<class tKey, class tValue> void CXMapSimple<tKey, tValue> ::RemoveAt(const tKey & Key) {
	// check if exists
	size_t Index = 0;
	CXKeyVal<tKey, tValue> *pS = Find(Key, Index);
	if(pS == NULL) {
		// Does not exist
		return;
	}
	delete m_Data[Index];
	m_Data.RemoveAt(Index);
}

//-------------------------------------
template<class tKey, class tValue> bool CXMapSimple<tKey, tValue> ::Lookup(const tKey &Key, tValue & Result) const {
	// check if exists
	size_t Index = 0;
	CXKeyVal<tKey, tValue> *pS = Find(Key, Index);
	if(pS != NULL) {
		// exists
		Result = pS->m_Value;
		return true;
	}
	// does not exist
	return false;
}

//-------------------------------------
template<class tKey, class tValue> CXPOSMapSimple<tKey> CXMapSimple<tKey, tValue> ::GetStart() const {
	return START;
}

//-------------------------------------
template<class tKey, class tValue> CXPOSMapSimple<tKey> CXMapSimple<tKey, tValue> ::GetNext(CXPOSMapSimple<tKey> & Pos, tValue &rValue) const {
	if(Pos == NPOS) {
		return Pos;
	}
	if(Pos == START) {
		Pos.m_pos = 0;
	} else {
		Pos.m_pos++;
	}
	if(Pos.m_pos >= m_Data.GetSize()) {
		Pos = NPOS;
		return Pos;
	}
	rValue = m_Data[Pos.m_pos]->m_Value;
	Pos.m_key = m_Data[Pos.m_pos]->m_Key;
	return Pos;
}

#endif //__CXMAPSIMPLE_HPP__
