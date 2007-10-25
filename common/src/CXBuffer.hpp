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

#ifndef __CXBUFFER_HPP__
#define __CXBUFFER_HPP__

#include <TargetIncludes.hpp>

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
template<class tClass> class CXBuffer {
public:
	static const size_t NPOS;				///< oiu
private:
	tClass			*m_pBuffer;				///< oiu
	size_t			m_ulBufferSize;			///< oiu
	size_t			m_ulAllocatedSize;		///< oiu
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void _CopyFrom(const CXBuffer &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void GrowTo(size_t ulNewSize);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ShrinkTo(size_t ulNewSize);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetMultipleOfGrowSize(size_t NewSize);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXBuffer();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXBuffer();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXBuffer(const CXBuffer &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXBuffer & operator = (const CXBuffer &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool operator == (const CXBuffer &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const tClass *GetBuffer() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetSize() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t GetAllocatedSize() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Append(const tClass *pbData, size_t ulDataSize);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Append(const tClass &c);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Clear();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void DeleteFirst(size_t ulCount);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void DeleteLast(size_t ulCount);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsEmpty() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	tClass & operator[] (size_t ulPos);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const tClass & operator[] (size_t ulPos) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t Find(const tClass * pc, size_t Len) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t Find(const tClass & c) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	size_t ReverseFind(const tClass & c) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXBuffer Left(size_t ulCount) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool CompareBegin(tClass *pBuf, size_t ulCount) const;
};

typedef CXBuffer<unsigned char>		tUCBuffer;
typedef CXBuffer<char>				tCBuffer;
typedef CXBuffer<unsigned short>	tUSBuffer;

static const size_t GROWSIZE = 16;
template<class tClass> const size_t CXBuffer<tClass> ::NPOS = ~(size_t(0));

//-------------------------------------
template<class tClass> CXBuffer<tClass> ::CXBuffer() :
	m_pBuffer(NULL),
	m_ulBufferSize(0),
	m_ulAllocatedSize(0)
{
}

//-------------------------------------
template<class tClass> CXBuffer<tClass> ::CXBuffer(const CXBuffer<tClass> &rOther) :
	m_pBuffer(NULL),
	m_ulBufferSize(0),
	m_ulAllocatedSize(0)
{
	_CopyFrom(rOther);
}

//-------------------------------------
template<class tClass> CXBuffer<tClass> ::~CXBuffer() {
	Clear();
}

//-------------------------------------
template<class tClass> const CXBuffer<tClass> & CXBuffer<tClass> ::operator = (const CXBuffer<tClass> &rOther) {
	if(this != &rOther) {
		_CopyFrom(rOther);
	}
	return *this;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::_CopyFrom(const CXBuffer<tClass> &rOther) {
	delete [] m_pBuffer;
	m_ulAllocatedSize = rOther.m_ulAllocatedSize;
	m_ulBufferSize = rOther.m_ulBufferSize;
	m_pBuffer = new tClass [m_ulAllocatedSize];
	memcpy(m_pBuffer, rOther.m_pBuffer, m_ulBufferSize*sizeof(tClass));
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::GetMultipleOfGrowSize(size_t NewSize) {
	return ((NewSize / GROWSIZE) + 1) * GROWSIZE;
}

//-------------------------------------
template<class tClass> const tClass * CXBuffer<tClass> ::GetBuffer() const {
	return m_pBuffer;
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::GetSize() const {
	return m_ulBufferSize;
}

//-------------------------------------
template<class tClass> size_t CXBuffer<tClass> ::GetAllocatedSize() const {
	return m_ulAllocatedSize;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::GrowTo(size_t ulNewSize) {
	// multiple of GROWSIZE
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
	// multiple of GROWSIZE
	ulNewSize = GetMultipleOfGrowSize(ulNewSize);
	if(ulNewSize < m_ulAllocatedSize) {
		m_ulAllocatedSize = ulNewSize;
		tClass *pNewBuffer = new tClass [m_ulAllocatedSize];
		memmove(pNewBuffer, m_pBuffer, m_ulBufferSize*sizeof(tClass));
		delete [] m_pBuffer;
		m_pBuffer = pNewBuffer;
	}
}

//-------------------------------------
template<class tClass> bool CXBuffer<tClass> ::operator == (const CXBuffer &rOther) {
	// check if buffer allocated
	if((m_pBuffer == NULL) || (rOther.m_pBuffer == NULL))
		return false;
	// check size
	if(m_ulBufferSize != rOther.m_ulBufferSize)
		return false;
	// check data
	return memcmp(m_pBuffer, rOther.m_pBuffer, m_ulBufferSize) == 0;
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
	// check if it fits in allocated memory
	size_t NewSize = m_ulBufferSize + ulDataSize;
	if(NewSize > m_ulAllocatedSize) {
		// no, we must grow the buffer
		GrowTo(m_ulBufferSize + ulDataSize);
	}
	// append data
	memmove(&(m_pBuffer[m_ulBufferSize]), pbData, ulDataSize*sizeof(tClass));
	m_ulBufferSize = NewSize;
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::Append(const tClass & c) {
	Append(&c, 1);
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::DeleteFirst(size_t ulCount) {
	// check
	if(ulCount >= m_ulBufferSize) {
		// delete all
		Clear();
	} else {
		// delete part
		size_t NewSize = GetMultipleOfGrowSize(m_ulBufferSize - ulCount);
		if(NewSize < m_ulAllocatedSize) {
			// allocate new block
			m_ulAllocatedSize = NewSize;
			tClass *pNewBuffer = new tClass [m_ulAllocatedSize];
			m_ulBufferSize = m_ulBufferSize - ulCount;
			memmove(pNewBuffer, &(m_pBuffer[ulCount]), m_ulBufferSize*sizeof(tClass));
			delete [] m_pBuffer;
			m_pBuffer = pNewBuffer;
		} else {
			// use existing block
			m_ulBufferSize = m_ulBufferSize - ulCount;
			memmove(m_pBuffer, &(m_pBuffer[ulCount]), m_ulBufferSize*sizeof(tClass));
		}
	}
}

//-------------------------------------
template<class tClass> void CXBuffer<tClass> ::DeleteLast(size_t ulCount) {
	if(ulCount >= m_ulBufferSize) {
		// delete all
		Clear();
	} else {
		// delete part
		// check
		size_t NewSize = GetMultipleOfGrowSize(m_ulBufferSize - ulCount);
		if(NewSize < m_ulAllocatedSize) {
			// allocate new block
			m_ulAllocatedSize = NewSize;
			tClass *pNewBuffer = new tClass [m_ulAllocatedSize];
			m_ulBufferSize = m_ulBufferSize - ulCount;
			memmove(pNewBuffer, m_pBuffer, m_ulBufferSize*sizeof(tClass));
			delete [] m_pBuffer;
			m_pBuffer = pNewBuffer;
		} else {
			// use existing block
			m_ulBufferSize = m_ulBufferSize - ulCount;
		}
	}
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
	for(size_t i = 0; i<m_ulBufferSize-Len; i++) {
		if(memcmp(m_pBuffer+i, pc, Len) == 0)
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
template<class tClass> bool CXBuffer<tClass> ::CompareBegin(tClass *pbBuf, size_t ulCount) const {
	// check if valid pointer
	if(pbBuf == NULL)
		return false;
	// check if enaugh data
	if(ulCount > m_ulBufferSize)
		return false;
	return memcmp(m_pBuffer, pbBuf, ulCount) == 0;
}


#endif // __CXBUFFER_HPP__
