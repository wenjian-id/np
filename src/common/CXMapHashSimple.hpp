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
#define tPos CXPOSMapSort

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
template<class tKey> class CXPOSMapHashSimple {
public:
    unsigned short  idx;    ///< oiu
    tPos<tKey>      pos;    ///< oiu
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXPOSMapHashSimple() {
        idx = 0;
        pos = 0;
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXPOSMapHashSimple(unsigned short Idx, const tPos<tKey> & Pos) :
        idx(Idx),
        pos(Pos)
    {
    }
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXPOSMapHashSimple(const CXPOSMapHashSimple &rOther) {
        idx = rOther.idx;
        pos = rOther .pos;
    }
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXPOSMapHashSimple() {
    }
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXPOSMapHashSimple & operator = (const CXPOSMapHashSimple &rOther) {
        idx = rOther.idx;
        pos = rOther.pos;
        return *this;
    }
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if equal.
     */
    bool operator == (const CXPOSMapHashSimple & rOther) const {
        return (idx == rOther.idx) && (pos == rOther.pos);
    }
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if not equal.
     */
    bool operator != (const CXPOSMapHashSimple & rOther) const {
        return ! operator ==(rOther);
    }
};

static const size_t DataSize = 256; ///< oiu

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tKey, class tValue> class CXMapHashSimple {
public:
    static CXPOSMapHashSimple<tKey>     NPOS;       ///< oiu
    static CXPOSMapHashSimple<tKey>     START;      ///< oiu
private:
    tMap<tKey, tValue>  *m_pData[DataSize]; ///< oiu
    //-------------------------------------
    CXMapHashSimple(const CXMapHashSimple &);                       ///< Not used.
    const CXMapHashSimple & operator = (const CXMapHashSimple &);   ///< Not used.
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
    CXPOSMapHashSimple<tKey> GetPos(const tKey &Key) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXPOSMapHashSimple<tKey> GetStart() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXPOSMapHashSimple<tKey> GetNext(CXPOSMapHashSimple<tKey> & Pos, tValue &rValue) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tValue GetValue(const CXPOSMapHashSimple<tKey> & Pos) const;
};

template<class tKey, class tValue> CXPOSMapHashSimple<tKey> CXMapHashSimple<tKey, tValue> ::NPOS = CXPOSMapHashSimple<tKey>(0xffff, tPos<tKey>(~(size_t(0))));
template<class tKey, class tValue> CXPOSMapHashSimple<tKey> CXMapHashSimple<tKey, tValue> ::START = CXPOSMapHashSimple<tKey>(0xffff, tPos<tKey>(~(size_t(1))));


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
    size_t Dummy = 0;
    return m_pData[idx]->Find(Key, Dummy);
}

//-------------------------------------
template<class tKey, class tValue> void CXMapHashSimple<tKey, tValue> ::SetAt(const tKey & Key, const tValue & Value) {
    // check if already exists
    unsigned char idx = Hash(Key);
    m_pData[idx]->SetAt(Key, Value);
}

//-------------------------------------
template<class tKey, class tValue> void CXMapHashSimple<tKey, tValue> ::RemoveAt(const tKey & Key) {
    // check if already exists
    unsigned char idx = Hash(Key);
    m_pData[idx]->RemoveAt(Key);
}

//-------------------------------------
template<class tKey, class tValue> bool CXMapHashSimple<tKey, tValue> ::Lookup(const tKey &Key, tValue & Result) const {
    // check if exists
    unsigned char idx = Hash(Key);
    return m_pData[idx]->Lookup(Key, Result);
}

//-------------------------------------
template<class tKey, class tValue> CXPOSMapHashSimple<tKey> CXMapHashSimple<tKey, tValue> ::GetPos(const tKey &Key) const {
    CXPOSMapHashSimple<tKey> Result = NPOS;
    tValue Dummy;
    if(Lookup(Key, Dummy)) {
        Result.idx = Hash(Key);
        Result.pos = m_pData[Result.idx]->GetPos(Key);
    }
    return Result;
}

//-------------------------------------
template<class tKey, class tValue> CXPOSMapHashSimple<tKey> CXMapHashSimple<tKey, tValue> ::GetStart() const {
    return START;
}


//-------------------------------------
template<class tKey, class tValue> CXPOSMapHashSimple<tKey> CXMapHashSimple<tKey, tValue> ::GetNext(CXPOSMapHashSimple<tKey> & Pos, tValue &rValue) const {
    if(Pos == NPOS) {
        return Pos;
    }
    if(Pos == START) {
        Pos.idx = 0;
        Pos.pos = tMap<tKey, tValue>::START;
    }
    Pos.pos = m_pData[Pos.idx]->GetNext(Pos.pos, rValue);
    while(Pos.pos == tMap<tKey, tValue>::NPOS) {
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
        Pos.pos = m_pData[Pos.idx]->GetNext(Pos.pos, rValue);
    }
    return Pos;
}

//-------------------------------------
template<class tKey, class tValue> tValue CXMapHashSimple<tKey, tValue> ::GetValue(const CXPOSMapHashSimple<tKey> & Pos) const {
    tValue Result;
    if(Pos != NPOS)
        Result = m_pData[Pos.idx]->GetValue(Pos.pos);
    return Result;
}


#endif //__CXMAPHASHSIMPLE_HPP__
