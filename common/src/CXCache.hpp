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
	template <class tValue> class oiu {
	private:
		int					m_Counter;	///< oiu
		CXSmartPtr<tValue>	m_Value;	///< oiu
	protected:
	public:
		//-------------------------------------
		/**
		 * \brief oiu.
		 * 
		 * oiu.
		 */
		oiu(tValue *pValue) :
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
		virtual ~oiu() {
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
	CXMapSort<tKey, oiu<tValue> >	m_Values;		///< oiu
	//-------------------------------------
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
	CXCache() {
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXCache() {
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXSmartPtr<tValue> GetAt(const tKey & Key) {
		oiu<tValue> oiuResult(NULL);
		// check if value exists
		if(!m_Values.Lookup(Key, oiuResult)) {
			// value does not exist. create new tValue
			tValue *pNewValue = new tValue;
			// save in map
			m_Values.SetAt(Key, oiu<tValue>(pNewValue));
			// lookup again
			m_Values.Lookup(Key, oiuResult);
		}
		// reset counter
		oiuResult.ResetCounter();
		// and return value
		return oiuResult.GetValue();
	}
};

#endif //__CXCACHE_HPP__
