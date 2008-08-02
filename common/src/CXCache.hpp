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
	template <class tValue> class CXCacheHelper {
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
	size_t										m_MaxCacheSize;		///< oiu
	CXMapSort<tKey, CXCacheHelper<tValue> *>	m_Values;			///< oiu
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
	CXCache(size_t MaxCacheSize) :
		m_MaxCacheSize(MaxCacheSize)
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
		CXCacheHelper<tValue> *pDel = NULL;
		CXMapSort<tKey, CXCacheHelper<tValue> *>::POS Pos = m_Values.GetStart();
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
		IncrementCounters();
		CXCacheHelper<tValue> *pResult = NULL;
		// check if value exists
		if(!m_Values.Lookup(Key, pResult)) {
			// check if we have to remove a Element
			if(m_Values.GetSize() >= m_MaxCacheSize) {
				// remove rarely used element
				CXCacheHelper<tValue> *pTmp = NULL;
				CXCacheHelper<tValue> *pDel = NULL;
				CXMapSort<tKey, CXCacheHelper<tValue> *>::POS Pos = m_Values.GetStart();
				int MaxCount = -1;
				tKey MaxKey;
				while(m_Values.GetNext(Pos, pTmp) != m_Values.NPOS) {
					if(pTmp->GetCounter() > MaxCount) {
						// found new maximum
						MaxKey = Pos.GetKey();
						MaxCount = pTmp->GetCounter();
						pDel = pTmp;
					}
				}
				// now remove maximum
				char buf[100];
				snprintf(buf, sizeof(buf), "Removing cache entry with key %d having age %d\n", MaxKey, MaxCount);
				DoOutputDebugString(buf);
				m_Values.RemoveAt(MaxKey);
				delete pDel;
			}
			char buf[100];
			snprintf(buf, sizeof(buf), "Adding cache entry with key %d\n", Key);
			DoOutputDebugString(buf);
			// value does not exist. create new tValue
			tValue *pNewValue = new tValue;
			// save in map
			m_Values.SetAt(Key, new CXCacheHelper<tValue>(pNewValue));
			// lookup again
			m_Values.Lookup(Key, pResult);
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
		CXCacheHelper<tValue> *pTmp = NULL;
		CXMapSort<tKey, CXCacheHelper<tValue> *>::POS Pos = m_Values.GetStart();
		while(m_Values.GetNext(Pos, pTmp) != m_Values.NPOS) {
			pTmp->IncrementCounter();
		}
	}
};

#endif //__CXCACHE_HPP__
