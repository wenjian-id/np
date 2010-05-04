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

#ifndef __CXSMARTPTR_HPP__
#define __CXSMARTPTR_HPP__

#include "CXMutexLocker.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 * oiu
 */
template<class t> class CXSmartPtr {
private:
	//-------------------------------------
	/**
	 * \brief oiu.
	 * 
	 * oiu.
	 */
	template<class tt> class CXDescriptor {
	private:
		bool				m_oIsArray;	///< oiu
		size_t				m_Counter;	///< oiu
		mutable CXMutex		m_Mutex;	///< Synchronization object.
		//-------------------------------------
		CXDescriptor();												///< Not used.
		CXDescriptor(const CXDescriptor &);							///< Not used.
		const CXDescriptor & operator = (const CXDescriptor &);		///< Not used.
	protected:
	public:
		tt					*m_pPtr;	///< oiu
		//-------------------------------------
		/**
		 * \brief Default constructor.
		 * 
		 * Default constructor.
		 */
		CXDescriptor(tt *pPtr, bool oIsArray) {
			m_pPtr = pPtr;
			m_oIsArray = oIsArray;
			m_Counter = 0;
		}
		//-------------------------------------
		/**
		 * \brief Destructor.
		 * 
		 * Destructor.
		 */
		virtual ~CXDescriptor() {
		}
		//-------------------------------------
		/**
		 * \brief oiu
		 * 
		 * oiu.
		 */
		size_t AddRef() {
			CXMutexLocker ML(&m_Mutex);
			m_Counter++;
			return m_Counter;
		}
		//-------------------------------------
		/**
		 * \brief oiu.
		 *
		 * oiu.
		 */
		size_t Release() {
			CXMutexLocker ML(&m_Mutex);
			m_Counter--;
			if(m_Counter == 0) {
				// delete m_pPtr
				if(m_oIsArray)
					delete [] m_pPtr;
				else
					delete m_pPtr;
				// set to NULL;
				m_pPtr = NULL;
			}
			return m_Counter;
		}
	};
private:
	CXDescriptor<t>		*m_pDescriptor;		///< oiu
	mutable CXMutex		m_Mutex;			///< Synchronization object.
	//-------------------------------------
	/**
	 * \brief oiu.
	 *
	 * oiu.
	 */
	void Release() {
		if((m_pDescriptor != NULL) && (m_pDescriptor->Release() == 0)) {
			delete m_pDescriptor;
			m_pDescriptor = NULL;
		}
	}
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 * 
	 * Default constructor.
	 */
	CXSmartPtr() {
		m_pDescriptor = NULL;
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 * 
	 * oiu
	 */
	CXSmartPtr(t *pPtr, bool oIsArray) {
		m_pDescriptor = new CXDescriptor<t>(pPtr, oIsArray);
		m_pDescriptor->AddRef();
	}
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXSmartPtr(const CXSmartPtr &rOther) {
		// lock other instance
		CXMutexLocker ML(&rOther.m_Mutex);
		// new reference
		m_pDescriptor = rOther.m_pDescriptor;
		if(m_pDescriptor != NULL)
			m_pDescriptor->AddRef();

	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXSmartPtr() {
		// lock instance
		CXMutexLocker ML(&m_Mutex);
		// release reference
		Release();
	}
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXSmartPtr & operator = (const CXSmartPtr &rOther) {
		// lock instance
		CXMutexLocker ML1(&m_Mutex);
		// lock other instance
		CXMutexLocker ML2(&rOther.m_Mutex);
		// release reference
		Release();
		// set new reference
		m_pDescriptor = rOther.m_pDescriptor;
		if(m_pDescriptor != NULL)
			m_pDescriptor->AddRef();
		return *this;
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	t *GetPtr() {
		if(m_pDescriptor != NULL)
			return m_pDescriptor->m_pPtr;
		return NULL;
	}
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	const t *GetPtr() const {
		if(m_pDescriptor != NULL)
			return m_pDescriptor->m_pPtr;
		return NULL;
	}
};

#endif // __CXSMARTPTR_HPP__


