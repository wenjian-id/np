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

#ifndef __CXMAPHASHSIMPLE_HPP__
#define __CXMAPHASHSIMPLE_HPP__

#include "CXBuffer.hpp"
#include "CXMapSort.hpp"
#include "CXMapSimple.hpp"
#include <TargetIncludes.hpp>

#define tMap CXMapSort

//-------------------------------------
/**
 * \brief oiu
 *
 */
template<class t> unsigned char Hash(const t & Key) {
	return static_cast<unsigned char>(Key % 256);
}

//-------------------------------------
/**
 * \brief oiu
 *
 */
class POS {
public:
	unsigned short	idx;	///< iou
	size_t			pos;	///< oiu
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	POS() {
		idx = 0;
		pos = 0;
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	POS(unsigned short Idx, size_t Pos) {
		idx = Idx;
		pos = Pos;
	}
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	POS(const POS &rOther) {
		idx = rOther.idx;
		pos = rOther .pos;
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~POS() {
	}
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const POS & operator = (const POS &rOther) {
		idx = rOther.idx;
		pos = rOther.pos;
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
	bool operator == (const POS & rOther) {
		return (idx == rOther.idx) && (pos == rOther.pos);
	}
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if not equal.
	 */
	bool operator != (const POS & rOther) {
		return ! operator ==(rOther);
	}
};


//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
static const size_t DataSize = 256; ///< oiu
template<class tKey, class tValue> class CXMapHashSimple {
public:
	static POS NPOS;		///< oiu
	static POS START;		///< oiu
private:
	tMap<tKey, tValue>	*m_pData[DataSize];	///< oiu
	//-------------------------------------
	CXMapHashSimple(const CXMapHashSimple &);						///< Not used.
	const CXMapHashSimple & operator = (const CXMapHashSimple &);	///< Not used.
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXKeyVal<tKey, tValue> *Find(const tKey & Key) const;
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapHashSimple();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapHashSimple();
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
	void SetAt(const tKey & Key, const tValue & Value);
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
	POS GetStart() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	POS GetNext(POS & Pos, tValue &rValue) const;
};

template<class tKey, class tValue> POS CXMapHashSimple<tKey, tValue> ::NPOS = POS(0xffff, tMap<tKey, tValue>::NPOS);
template<class tKey, class tValue> POS CXMapHashSimple<tKey, tValue> ::START = POS(0xffff, tMap<tKey, tValue>::START);


//-------------------------------------
template<class tKey, class tValue> CXMapHashSimple<tKey, tValue> ::CXMapHashSimple() {
	for(size_t i=0; i<DataSize; i++) {
		m_pData[i] = new tMap<tKey, tValue>();
	}
}

//-------------------------------------
template<class tKey, class tValue> CXMapHashSimple<tKey, tValue> ::~CXMapHashSimple() {
	RemoveAll();
	for(size_t i=0; i<DataSize; i++) {
		delete m_pData[i];
		m_pData[i] = NULL;
	}
}

//-------------------------------------
template<class tKey, class tValue> void CXMapHashSimple<tKey, tValue> ::RemoveAll() {
	// delete all elements
	for(size_t i=0; i<DataSize; i++) {
		m_pData[i]->RemoveAll();
	}
}

//-------------------------------------
template<class tKey, class tValue> CXKeyVal<tKey, tValue> * CXMapHashSimple<tKey, tValue> ::Find(const tKey & Key) const {
	unsigned char idx = Hash(Key);
	return m_pData[idx]->Find(Key);
}

//-------------------------------------
template<class tKey, class tValue> void CXMapHashSimple<tKey, tValue> ::SetAt(const tKey & Key, const tValue & Value) {
	// check if already exists
	unsigned char idx = Hash(Key);
	m_pData[idx]->SetAt(Key, Value);
}

//-------------------------------------
template<class tKey, class tValue> bool CXMapHashSimple<tKey, tValue> ::Lookup(const tKey &Key, tValue & Result) const {
	// check if exists
	unsigned char idx = Hash(Key);
	return m_pData[idx]->Lookup(Key, Result);
}

//-------------------------------------
template<class tKey, class tValue> POS CXMapHashSimple<tKey, tValue> ::GetStart() const {
	return START;
}


//-------------------------------------
template<class tKey, class tValue> POS CXMapHashSimple<tKey, tValue> ::GetNext(POS & Pos, tValue &rValue) const {
	if(Pos == NPOS) {
		return Pos;
	}
	if(Pos == START) {
		Pos.idx = 0;
		Pos.pos = tMap<tKey, tValue>::START;
	}
	while((Pos.pos = m_pData[Pos.idx]->GetNext(Pos.pos, rValue)) == tMap<tKey, tValue>::NPOS) {
		// try next idx
		// end of m_pData[Pos.pos] reached
		if (Pos.idx == 255) {
			// end reached
			Pos = NPOS;
			return Pos;
		} else {
			// next idx
			Pos.idx++;
			Pos.pos = tMap<tKey, tValue>::START;
		}
	}
	return Pos;
}

#endif //__CXMAPHASHSIMPLE_HPP__
