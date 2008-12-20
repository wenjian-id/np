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

#ifndef __CXCACHE_HPP__
#define __CXCACHE_HPP__

#include "CXMapSort.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template <class tKey, class tValue> class CXCache {
private:
	class CXCacheHelper {
	private:
		int					m_Counter;	///< oiu
		CXSmartPtr<tValue>	m_Value;	///< oiu
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		void CopyFrom(const CXCacheHelper &rOther) {
			m_Counter = rOther.m_Counter;
			m_Value = rOther.m_Value;
		}
	protected:
	public:
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		CXCacheHelper(tValue *pValue) :
			m_Counter(1),
			m_Value(pValue, false)
		{
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		CXCacheHelper(const CXCacheHelper &rOther) {
			CopyFrom(rOther);
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		virtual ~CXCacheHelper() {
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		const CXCacheHelper & operator = (const CXCacheHelper &rOther) {
			if(this != &rOther)
				CopyFrom(rOther);
			return *this;
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		int GetCounter() const {
			return m_Counter;
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		void ResetCounter() {
			m_Counter = 0;
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		void IncrementCounter() {
			m_Counter++;
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		CXSmartPtr<tValue> GetValue() const {
			return m_Value;
		};
	};
private:
	size_t								m_NominalCacheSize;		///< oiu
	CXMapSort<tKey, CXCacheHelper *>	m_Values;				///< oiu
	//-------------------------------------
	CXCache();										///< Not used.
	CXCache(const CXCache &);						///< Not used.
	const CXCache & operator = (const CXCache &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXCache(size_t NominalCacheSize) :
		m_NominalCacheSize(NominalCacheSize)
	{
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXCache() {
		// delete all entries
		CXCacheHelper *pDel = NULL;
		CXPOSMapSort<tKey> Pos = m_Values.GetStart();
		while(m_Values.GetNext(Pos, pDel) != m_Values.NPOS) {
			delete pDel;
		}
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXSmartPtr<tValue> GetAt(const tKey & Key) {
		CXCacheHelper *pResult = NULL;
		// check if we have to remove a Element
		if(m_Values.GetSize() >= m_NominalCacheSize) {
			// remove rarely used element
			CXCacheHelper *pTmp = NULL;
			CXCacheHelper *pDel = NULL;
			CXPOSMapSort<tKey> Pos = m_Values.GetStart();
			int MaxCount = -1;
			tKey DelKey;
			while(m_Values.GetNext(Pos, pTmp) != m_Values.NPOS) {
				if(pTmp->GetCounter() > MaxCount) {
					// found new maximum
					DelKey = Pos.m_key;
					MaxCount = pTmp->GetCounter();
					pDel = pTmp;
				}
			}
			// check if we can remove maximum
			if(MaxCount > 2) {
				// now remove maximum
				m_Values.RemoveAt(DelKey);
				// and delete element
				delete pDel;
			}
		}
		// check if value exists
		if(!m_Values.Lookup(Key, pResult)) {
			// value does not exist
			// create new tValue
			tValue *pNewValue = new tValue;
			// save in map
			pResult = new CXCacheHelper(pNewValue);
			m_Values.SetAt(Key, pResult);
			if(m_Values.GetSize() > m_NominalCacheSize) {
				char buf[100];
				snprintf(buf, sizeof(buf), "cache size = %d nominal size = %d\n", m_Values.GetSize(), m_NominalCacheSize);
				DoOutputDebugString(buf);
			}
		}
		// reset counter
		pResult->ResetCounter();
		// and return value
		return pResult->GetValue();
	}
	//-------------------------------------
	/**
	 * \brief oiu.
	 * 
	 * oiu.
	 */
	void IncrementCounters() {
		CXCacheHelper *pTmp = NULL;
		CXPOSMapSort<tKey> Pos = m_Values.GetStart();
		while(m_Values.GetNext(Pos, pTmp) != m_Values.NPOS) {
			pTmp->IncrementCounter();
		}
	}
};

#endif //__CXCACHE_HPP__
