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

#ifndef __CXARRAY_HPP__
#define __CXARRAY_HPP__

#include <TargetIncludes.hpp>

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tClass> class CXArray {
public:
    static const size_t NPOS;               ///< Identifier for "No POSition".
private:
    tClass          *m_pBuffer;             ///< Internal buffer.
    size_t          m_ulSize;               ///< Number of used entries in internal buffer.
    size_t          m_ulAllocatedSize;      ///< Number of allocated entries in internal buffer.
    //-------------------------------------
    /**
     * \brief Copy from other instance to self.
     *
     * Copy from other instance to self.
     * \param   rOther  Instance to copy from.
     */
    void CopyFrom(const CXArray & rOther);
    //-------------------------------------
    /**
     * \brief Grow internal buffer to a new size.
     *
     * Grow internal buffer to a new size. Memory is reallocated 
     * and content copied.
     * \param   ulNewSize   New number of entries.
     */
    void GrowTo(size_t ulNewSize);
    //-------------------------------------
    /**
     * \brief Grow internal buffer to a new size.
     *
     * Grow internal buffer to a new size. Memory is reallocated 
     * and content copied.
     * \param   ulNewSize   New number of entries.
     */
    void ShrinkTo(size_t ulNewSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t GetMultipleOfGrowSize(size_t NewSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void RemoveAt(size_t Index, size_t Count);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXArray();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor. Memory is freed.
     */
    virtual ~CXArray();
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXArray(const CXArray & rOther);
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXArray & operator = (const CXArray & rOther);
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
    void Resize(size_t ulNewSize);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Append(const tClass & c);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void RemoveAt(size_t Index);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Clear();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool IsEmpty() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tClass & operator[] (size_t ulPos);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    const tClass & operator[] (size_t ulPos) const;
};

static const size_t ARRAY_GROWSIZE = 16;                                    ///< oiu
template<class tClass> const size_t CXArray<tClass> ::NPOS = ~(size_t(0));  ///< oiu

//-------------------------------------
template<class tClass> CXArray<tClass> ::CXArray() :
    m_pBuffer(NULL),
    m_ulSize(0),
    m_ulAllocatedSize(0)
{
}

//-------------------------------------
template<class tClass> CXArray<tClass> ::CXArray(const CXArray<tClass> & rOther) :
    m_pBuffer(NULL),
    m_ulSize(0),
    m_ulAllocatedSize(0)
{
    CopyFrom(rOther);
}

//-------------------------------------
template<class tClass> CXArray<tClass> ::~CXArray() {
    Clear();
}

//-------------------------------------
template<class tClass> const CXArray<tClass> & CXArray<tClass> ::operator = (const CXArray<tClass> & rOther) {
    if(this != &rOther) {
        CopyFrom(rOther);
    }
    return *this;
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::CopyFrom(const CXArray<tClass> & rOther) {
    delete [] m_pBuffer;
    m_pBuffer = NULL;
    m_ulAllocatedSize = rOther.m_ulAllocatedSize;
    m_ulSize = rOther.m_ulSize;
    if(m_ulAllocatedSize > 0) {
        m_pBuffer = new tClass [m_ulAllocatedSize];
        // copy each element using copy construtor
        for(size_t i=0; i<m_ulSize; i++)
            m_pBuffer[i] = rOther.m_pBuffer[i];
    }
}

//-------------------------------------
template<class tClass> size_t CXArray<tClass> ::GetMultipleOfGrowSize(size_t NewSize) {
    if(NewSize == 0)
        return 0;
    return (((NewSize-1) / ARRAY_GROWSIZE) + 1) * ARRAY_GROWSIZE;
}

//-------------------------------------
template<class tClass> size_t CXArray<tClass> ::GetSize() const {
    return m_ulSize;
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::Resize(size_t ulNewSize) {
    GrowTo(ulNewSize);
    // adjust size
    m_ulSize = ulNewSize;
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::GrowTo(size_t ulNewSize) {
    // multiple of ARRAY_GROWSIZE
    ulNewSize = GetMultipleOfGrowSize(ulNewSize);
    if(ulNewSize > m_ulAllocatedSize) {
        m_ulAllocatedSize = ulNewSize;
        tClass *pNewBuffer = new tClass [m_ulAllocatedSize];
        // copy each element using copy construtor
        for(size_t i=0; i<m_ulSize; i++)
            pNewBuffer[i] = m_pBuffer[i];
        delete [] m_pBuffer;
        m_pBuffer = pNewBuffer;
    }
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::ShrinkTo(size_t ulNewSize) {
    // multiple of ARRAY_GROWSIZE
    ulNewSize = GetMultipleOfGrowSize(ulNewSize);
    if(ulNewSize < m_ulAllocatedSize) {
        m_ulAllocatedSize = ulNewSize;
        tClass *pNewBuffer = NULL;
        if(ulNewSize > 0) {
            // at least one element left
            pNewBuffer = new tClass [m_ulAllocatedSize];
            // copy each element using copy construtor
            for(size_t i=0; i<m_ulSize; i++)
                pNewBuffer[i] = m_pBuffer[i];
        } else {
            // no element left
            pNewBuffer = NULL;
        }
        // set new buffer
        delete [] m_pBuffer;
        m_pBuffer = pNewBuffer;
    }
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::Clear() {
    delete [] m_pBuffer;
    m_pBuffer = NULL;
    m_ulSize = 0;
    m_ulAllocatedSize = 0;
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::Append(const tClass & c) {
    // check if it fits in allocated memory
    size_t NewSize = m_ulSize + 1;
    // grow
    GrowTo(NewSize);
    // append data
    m_pBuffer[m_ulSize] = c;
    m_ulSize = NewSize;
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::RemoveAt(size_t Index, size_t Count) {
    if(Index >= m_ulSize)
        // wrong index
        return;
    if(Index + Count > m_ulSize)
        return;
    for(size_t i = Index; i<m_ulSize-Count; i++) {
        m_pBuffer[i] = m_pBuffer[i+Count];
    }
    // check if it fits in allocated memory
    m_ulSize -= Count;
    // shrink
    ShrinkTo(m_ulSize);
}

//-------------------------------------
template<class tClass> void CXArray<tClass> ::RemoveAt(size_t Index) {
    RemoveAt(Index, 1);
}

//-------------------------------------
template<class tClass> bool CXArray<tClass> ::IsEmpty() const {
    return m_ulSize == 0;
}

//-------------------------------------
template<class tClass> tClass & CXArray<tClass> ::operator[] (size_t ulPos) {
    return m_pBuffer[ulPos];
}

//-------------------------------------
template<class tClass> const tClass & CXArray<tClass> ::operator[] (size_t ulPos) const {
    return m_pBuffer[ulPos];
}

#endif // __CXARRAY_HPP__
