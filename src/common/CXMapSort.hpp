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

#ifndef __CXMAPSORT_HPP__
#define __CXMAPSORT_HPP__

#include "CXBuffer.hpp"
#include "CXKeyVal.hpp"
#include <TargetIncludes.hpp>

//----------------------------------------------------------------------------
//-------------------------------------
/**
 * \brief oiu
 *
 */
template<class tKey> class CXPOSMapSort {
public:
    tKey        m_key;  ///< oiu
    size_t      m_pos;  ///< oiu
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXPOSMapSort() {
        // m_key = 0;
        m_pos = 0;
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXPOSMapSort(size_t Pos) :
        m_pos(Pos)
    {
        // m_key = 0;
    }
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXPOSMapSort(const CXPOSMapSort &rOther) {
        m_key = rOther.m_key;
        m_pos = rOther.m_pos;
    }
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXPOSMapSort() {
    }
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXPOSMapSort & operator = (const CXPOSMapSort &rOther) {
        m_key = rOther.m_key;
        m_pos = rOther.m_pos;
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
    bool operator == (const CXPOSMapSort & rOther) const {
        return m_pos == rOther.m_pos;
    }
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if not equal.
     */
    bool operator != (const CXPOSMapSort & rOther) const {
        return ! operator ==(rOther);
    }
};


//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tKey, class tValue> class CXMapSort {
public:
    static const CXPOSMapSort<tKey>     NPOS;   ///< oiu
    static const CXPOSMapSort<tKey>     START;  ///< oiu
private:
    CXBuffer< CXKeyVal<tKey, tValue> *> m_Data;         ///< oiu
    //-------------------------------------
    CXMapSort(const CXMapSort &);                       ///< Not used.
    const CXMapSort & operator = (const CXMapSort &);   ///< Not used.
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
    CXMapSort();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXMapSort();
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
    CXPOSMapSort<tKey> GetStart() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXPOSMapSort<tKey> GetNext(CXPOSMapSort<tKey> & Pos, tValue &rValue) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tValue GetValue(const CXPOSMapSort<tKey> & Pos) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXPOSMapSort<tKey> GetPos(const tKey &Key) const;
};

template<class tKey, class tValue> const CXPOSMapSort<tKey> CXMapSort<tKey, tValue>::NPOS =  CXPOSMapSort<tKey>(~(size_t(0)));
template<class tKey, class tValue> const CXPOSMapSort<tKey> CXMapSort<tKey, tValue>::START = CXPOSMapSort<tKey>(~(size_t(1)));


//-------------------------------------
template<class tKey, class tValue> CXMapSort<tKey, tValue> ::CXMapSort() {
}

//-------------------------------------
template<class tKey, class tValue> CXMapSort<tKey, tValue> ::~CXMapSort() {
    RemoveAll();
}

//-------------------------------------
template<class tKey, class tValue> void CXMapSort<tKey, tValue> ::RemoveAll() {
    // delete all elements
    size_t Size = m_Data.GetSize();
    for(size_t i=0; i<Size; i++)
        delete m_Data[i];
    m_Data.Clear();
}

//-------------------------------------
template<class tKey, class tValue> size_t CXMapSort<tKey, tValue> ::GetSize() const {
    return m_Data.GetSize();
}

//-------------------------------------
template<class tKey, class tValue> CXKeyVal<tKey, tValue> * CXMapSort<tKey, tValue> ::Find(const tKey & Key, size_t & rIndex) const {
    rIndex = 0;
    if(m_Data.GetSize() == 0) {
        return NULL;
    } else if (m_Data[0]->m_Key > Key) {
        return NULL;
    } else if (m_Data[m_Data.GetSize()-1]->m_Key < Key) {
        return NULL;
    } else {
        // find element with key tKey
        size_t IdxStart = 0;
        size_t IdxStop = m_Data.GetSize();
        size_t IdxCmp = (IdxStop - IdxStart)/2;
        size_t IdxCmpOld = IdxCmp;
        bool oContinue = true;
        bool oFound = false;
        CXKeyVal<tKey, tValue> *pResult = NULL;
        while(oContinue) {
            IdxCmpOld = IdxCmp;
            // check if current item is correct
            pResult = m_Data[IdxCmp];
            if(pResult->m_Key == Key) {
                // found
                oFound = true;
                oContinue = false;
                rIndex = IdxCmp;
            } else if(pResult->m_Key > Key) {
                // go to left
                IdxStop = IdxCmp;
            } else {
                // go to right
                IdxStart = IdxCmp;
            }
            // check if we can continue the search
            if(oContinue) {
                // now compute the new index
                IdxCmp = (IdxStop + IdxStart)/2;
                // we must terminate search if IdxCmp has not changed
                if(IdxCmpOld == IdxCmp) {
                    // terminate search
                    oContinue = false;
                }
            }
        }
        if(oFound) {
            return pResult;
        }
    }
    return NULL;
}


//-------------------------------------
template<class tKey, class tValue> void CXMapSort<tKey, tValue> ::SetAt(const tKey & Key, const tValue & Value) {
    // check if already exists
    size_t TmpIndex = 0;
    CXKeyVal<tKey, tValue> *pS = Find(Key, TmpIndex);
    if(pS != NULL) {
        // already exists overwrite
        pS->m_Value = Value;
    } else {
        // does not exist yet
        // get position to insert
        if(m_Data.GetSize() == 0) {
            m_Data.Append(new CXKeyVal<tKey, tValue>(Key, Value));
        } else if (m_Data[0]->m_Key > Key) {
            m_Data.InsertAt(0, new CXKeyVal<tKey, tValue>(Key, Value));
        } else if (m_Data[m_Data.GetSize()-1]->m_Key < Key) {
            m_Data.Append(new CXKeyVal<tKey, tValue>(Key, Value));
        } else {
            size_t IdxStart = 0;
            size_t IdxStop = m_Data.GetSize();
            size_t IdxCmp = (IdxStop - IdxStart)/2;
            size_t IdxCmpOld = IdxCmp;
            size_t Index = 0;
            bool oContinue = true;
            bool oInsert = false;
            CXKeyVal<tKey, tValue> *pResult = NULL;
            while(oContinue) {
                IdxCmpOld = IdxCmp;
                // check if current item is correct
                pResult = m_Data[IdxCmp];
                bool oRight = false;
                if(pResult->m_Key == Key) {
                    // found
                    oContinue = false;
                } else if(pResult->m_Key > Key) {
                    // go to left
                    IdxStop = IdxCmp;
                } else {
                    // go to right
                    oRight = true;
                    IdxStart = IdxCmp;
                }
                // check if we can continue the search
                if(oContinue) {
                    // now compute the new index
                    IdxCmp = (IdxStop + IdxStart)/2;
                    // we must terminate search if IdxCmp has not changed
                    if(IdxCmpOld == IdxCmp) {
                        // terminate search
                        oInsert = true;
                        oContinue = false;
                        Index = IdxCmpOld;
                        // check to see if we must append data
                        if(oRight) {
                            // insert on next position
                            Index++;
                        }
                    }
                }
            }

            // and insert
            if(Index == m_Data.GetSize()) {
                // append
                m_Data.Append(new CXKeyVal<tKey, tValue>(Key, Value));
            } else {
                // insert
                m_Data.InsertAt(Index, new CXKeyVal<tKey, tValue>(Key, Value));
            }
        }
    }
}

//-------------------------------------
template<class tKey, class tValue> void CXMapSort<tKey, tValue> ::RemoveAt(const tKey & Key) {
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
template<class tKey, class tValue> bool CXMapSort<tKey, tValue> ::Lookup(const tKey &Key, tValue & Result) const {
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
template<class tKey, class tValue> CXPOSMapSort<tKey> CXMapSort<tKey, tValue>::GetStart() const {
    return START;
}

//-------------------------------------
template<class tKey, class tValue> CXPOSMapSort<tKey> CXMapSort<tKey, tValue> ::GetNext(CXPOSMapSort<tKey> & Pos, tValue &rValue) const {
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

//-------------------------------------
template<class tKey, class tValue> tValue CXMapSort<tKey, tValue> ::GetValue(const CXPOSMapSort<tKey> & Pos) const {
    return m_Data[Pos.m_pos]->m_Value;
}

//-------------------------------------
template<class tKey, class tValue> CXPOSMapSort<tKey> CXMapSort<tKey, tValue> ::GetPos(const tKey &Key) const {
    CXPOSMapSort<tKey> Result = NPOS;
    size_t Idx = 0;
    if(Find(Key, Idx)) {
        Result.m_key = Key;
        Result.m_pos = Idx;
    }
    return Result;
}

#endif //__CXMAPSORT_HPP__
