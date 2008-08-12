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

#ifndef __CXBUFFER_HPP__
#define __CXBUFFER_HPP__

#include <TargetIncludes.hpp>

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tClass> class CXBuffer {
public:
	static const size_t NPOS;				///< Identifier for "No POSition".
private:
	tClass			*m_pBuffer;				///< Internal buffer.
	size_t			m_ulBufferSize;			///< Number of used entries in internal buffer.
	size_t			m_ulAllocatedSize;		///< Number of allocated entries in internal buffer.
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXBuffer & rOther);
	//-------------------------------------
	/**
	 * \brief Grow internal buffer to a new size.
	 *
	 * Grow internal buffer to a new size. Memory is reallocated 
	 * and content copied.
	 * \param	ulNewSize	New number of entries.
	 */
	void GrowTo(size_t ulNewSize);
	//-------------------------------------
	/**
	 * \brief Grow internal buffer to a new size.
	 *
	 * Grow internal buffer to a new size. Memory is reallocated 
	 * and content copied.
	 * \param	ulNewSize	New number of entries.
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
	CXBuffer();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor. Memory is freed.
	 */
	virtual ~CXBuffer();
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXBuffer(const CXBuffer & rOther);
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXBuffer & operator = (const CXBuffer & rOther);
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if equal.
	 */
	bool operator == (const CXBuffer & rOther) const;
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if this instance < other instance.
	 */
	bool operator < (const CXBuffer & rOther) const;
	//-------------------------------------
	/**
	 * \brief Comparison operator.
	 *
	 * Compares this instance with other instance.
	 * \param	rOther	Instance to compare with.
	 * \return			True if this instance > other instance.
	 */
	bool operator > (const CXBuffer & rOther) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const tClass *GetBuffer() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	tClass *GetBufferWritable();
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
	size_t GetAllocatedSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Append(const tClass *pbData, size_t ulDataSize);
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
	void InsertAt(size_t Index, const tClass & c);
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
	void DeleteFirst(size_t ulCount);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void DeleteLast(size_t ulCount);
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
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t Find(const tClass * pc, size_t Len) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t Find(const tClass & c) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t ReverseFind(const tClass & c) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXBuffer Left(size_t ulCount) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool CompareBegin(const tClass *pBuf, size_t ulCount) const;
};

typedef CXBuffer<unsigned char>		tUCBuffer;
typedef CXBuffer<char>				tCBuffer;
typedef CXBuffer<unsigned short>	tUSBuffer;

static const size_t BUFFER_GROWSIZE = 16;
template<class tClass> const size_t CXBuffer<tClass> ::NPOS = ~(size_t(0));

//-------------------------------------
template<class tClass> CXBuffer<tClass> ::CXBuffer() :
	m_pBuffer(NULL),
	m_ulBufferSize(0),
	m_ulAllocatedSize(0)
{
}

//-------------------------------------
template<class tClass> CXBuffer<tClass> ::CXBuffer(const CXBuffer<tClass> & rOther) :
	m_pBuffer(NULL),
	m_ulBufferSize(0),
	m_ulAllocatedSize(0)
{
	CopyFrom(rOther);
}

//-------------------------------------
template<class tClass> CXBuffer<tClass> ::~CXBuffer() {
	Clear();
}

//-------------------------------------
template<class tClass> const CXBuffer<tClass> & CXBuffer<tClass> ::operator = (const CXBuffer<tClass> & rOther) {
	if(this != &rOther) {
		CopyFrom(rOther);
	}
	return *this;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::CopyFrom(const CXBuffer<tClass> & rOther) {
	delete [] m_pBuffer;
	m_pBuffer = NULL;
	m_ulAllocatedSize = rOther.m_ulAllocatedSize;
	m_ulBufferSize = rOther.m_ulBufferSize;
	if(m_ulAllocatedSize > 0) {
		m_pBuffer = new tClass [m_ulAllocatedSize];
		memcpy(m_pBuffer, rOther.m_pBuffer, m_ulBufferSize*sizeof(tClass));
	}
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::GetMultipleOfGrowSize(size_t NewSize) {
	if(NewSize == 0)
		return 0;
	return (((NewSize-1) / BUFFER_GROWSIZE) + 1) * BUFFER_GROWSIZE;
}

//-------------------------------------
template<class tClass> const tClass * CXBuffer<tClass> ::GetBuffer() const {
	return m_pBuffer;
}

//-------------------------------------
template<class tClass> tClass * CXBuffer<tClass> ::GetBufferWritable() {
	return m_pBuffer;
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::GetSize() const {
	return m_ulBufferSize;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::Resize(size_t ulNewSize) {
	GrowTo(ulNewSize);
	// adjust size
	m_ulBufferSize = ulNewSize;
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::GetAllocatedSize() const {
	return m_ulAllocatedSize;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::GrowTo(size_t ulNewSize) {
	// multiple of BUFFER_GROWSIZE
	ulNewSize = GetMultipleOfGrowSize(ulNewSize);
	if(ulNewSize > m_ulAllocatedSize) {
		m_ulAllocatedSize = ulNewSize;
		tClass *pNewBuffer = new tClass [m_ulAllocatedSize];
		memmove(pNewBuffer, m_pBuffer, m_ulBufferSize*sizeof(tClass));
		delete [] m_pBuffer;
		m_pBuffer = pNewBuffer;
	}
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::ShrinkTo(size_t ulNewSize) {
	// multiple of BUFFER_GROWSIZE
	ulNewSize = GetMultipleOfGrowSize(ulNewSize);
	if(ulNewSize < m_ulAllocatedSize) {
		m_ulAllocatedSize = ulNewSize;
		tClass *pNewBuffer = NULL;
		if(m_ulAllocatedSize > 0) {
			// at least one element left
			pNewBuffer = new tClass [m_ulAllocatedSize];
			memmove(pNewBuffer, m_pBuffer, m_ulBufferSize*sizeof(tClass));
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
template<class tClass> void CXBuffer<tClass> ::RemoveAt(size_t Index, size_t Count) {
	if(Index >= m_ulBufferSize)
		// wrong index
		return;
	if(Index + Count > m_ulBufferSize)
		return;
	// move data around
	m_ulBufferSize -= Count;
	memmove(&(m_pBuffer[Index]), &(m_pBuffer[Index+Count]), (m_ulBufferSize-Index)*sizeof(tClass));
	// shrink
	ShrinkTo(m_ulBufferSize);
}


//-------------------------------------
template<class tClass> bool CXBuffer<tClass> ::operator == (const CXBuffer & rOther) const {
	// check if buffer allocated
	if((m_pBuffer == NULL) || (rOther.m_pBuffer == NULL))
		return false;
	// check size
	if(m_ulBufferSize != rOther.m_ulBufferSize)
		return false;
	// check data
	return memcmp(m_pBuffer, rOther.m_pBuffer, m_ulBufferSize*sizeof(tClass)) == 0;
}

//-------------------------------------
template<class tClass> bool CXBuffer<tClass> ::operator < (const CXBuffer & rOther) const {
	// check if buffer allocated
	if((m_pBuffer == NULL) || (rOther.m_pBuffer == NULL))
		return false;
	// check data
	return memcmp(m_pBuffer, rOther.m_pBuffer, m_ulBufferSize*sizeof(tClass)) < 0;
}

//-------------------------------------
template<class tClass> bool CXBuffer<tClass> ::operator > (const CXBuffer & rOther) const {
	// check if buffer allocated
	if((m_pBuffer == NULL) || (rOther.m_pBuffer == NULL))
		return false;
	// check data
	return memcmp(m_pBuffer, rOther.m_pBuffer, m_ulBufferSize*sizeof(tClass)) > 0;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::Clear() {
	delete [] m_pBuffer;
	m_pBuffer = NULL;
	m_ulBufferSize = 0;
	m_ulAllocatedSize = 0;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::Append(const tClass *pbData, size_t ulDataSize) {
	// new size
	size_t NewSize = m_ulBufferSize + ulDataSize;
	// grow
	GrowTo(NewSize);
	// append data
	memmove(&(m_pBuffer[m_ulBufferSize]), pbData, ulDataSize*sizeof(tClass));
	m_ulBufferSize = NewSize;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::Append(const tClass & c) {
	Append(&c, 1);
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::InsertAt(size_t Index, const tClass & c) {
	if(Index >= m_ulBufferSize)
		// wrong index
		return;
	// new size
	size_t NewSize = m_ulBufferSize + 1;
	// grow
	GrowTo(NewSize);
	// move data arround
	memmove(&(m_pBuffer[Index+1]), &(m_pBuffer[Index]), (m_ulBufferSize-Index)*sizeof(tClass));
	m_pBuffer[Index] = c;
	m_ulBufferSize = NewSize;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::RemoveAt(size_t Index) {
	RemoveAt(Index, 1);
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::DeleteFirst(size_t ulCount) {
	RemoveAt(0, ulCount);
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::DeleteLast(size_t ulCount) {
	if(ulCount >= m_ulBufferSize) {
		return;
	}
	RemoveAt(m_ulBufferSize-ulCount, ulCount);
}

//-------------------------------------
template<class tClass> bool CXBuffer<tClass> ::IsEmpty() const {
	return m_ulBufferSize == 0;
}

//-------------------------------------
template<class tClass> tClass & CXBuffer<tClass> ::operator[] (size_t ulPos) {
	return m_pBuffer[ulPos];
}

//-------------------------------------
template<class tClass> const tClass & CXBuffer<tClass> ::operator[] (size_t ulPos) const {
	return m_pBuffer[ulPos];
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::Find(const tClass * pc, size_t Len) const {
	/// \todo implement fast search
	if(Len > m_ulBufferSize)
		return NPOS;
	for(size_t i = 0; i <= m_ulBufferSize-Len; i++) {
		if(memcmp(m_pBuffer+i, pc, Len*sizeof(tClass)) == 0)
			return i;
	}
	return NPOS;
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::Find(const tClass & c) const {
	for(size_t i = 0; i<m_ulBufferSize; i++)
		if(m_pBuffer[i] == c)
			return i;
	return NPOS;
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::ReverseFind(const tClass & c) const {
	size_t Found = NPOS;
	for(size_t i = 0; i<m_ulBufferSize; i++)
		if(m_pBuffer[i] == c)
			Found = i;
	return Found;
}

//-------------------------------------
template<class tClass> CXBuffer<tClass> CXBuffer<tClass> ::Left(size_t ulCount) const {
	CXBuffer Result;
	Result.Append(m_pBuffer, ulCount);
	return Result;
}

//-------------------------------------
template<class tClass> bool CXBuffer<tClass> ::CompareBegin(const tClass *pbBuf, size_t ulCount) const {
	// check if valid pointer
	if(pbBuf == NULL)
		return false;
	// check if enaugh data
	if(ulCount > m_ulBufferSize)
		return false;
	return memcmp(m_pBuffer, pbBuf, ulCount*sizeof(tClass)) == 0;
}


#endif // __CXBUFFER_HPP__
