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

#ifndef __CXMAPLOADERTHREAD_HPP__
#define __CXMAPLOADERTHREAD_HPP__

#include "CXWorkRequestThread.hpp"
#include "CXMapContainer.hpp"
#include "CXMutex.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXMapLoaderThread : public CXWorkRequestThread {
private:
	class CXTOCDescr {
		private:
			//-------------------------------------
			CXTOCDescr();										///< Not used.
			CXTOCDescr(const CXTOCDescr &);						///< Not used.
			const CXTOCDescr & operator = (const CXTOCDescr &);	///< Not used.
		protected:
		public:
			CXStringASCII	m_FileName;		///< oiu
			unsigned char	m_ZoomLevel;	///< oiu
			t_uint32		m_Key;			///< oiu
			//-------------------------------------
			/**
			 * \brief oiu.
			 *
			 * oiu.
			 */
			CXTOCDescr(const CXStringASCII & FileName, unsigned char ZoomLevel, t_uint32 Key) :
				m_FileName(FileName),
				m_ZoomLevel(ZoomLevel),
				m_Key(Key)
			{
			}
			//-------------------------------------
			/**
			 * \brief Destructor.
			 *
			 * Destructor.
			 */
			virtual ~CXTOCDescr() {
			}
	};
private:
	TTOCMapContainerPtrArray		m_TOCMapContainerArray;		///< oiu
	CXBuffer<CXTOCDescr *>			m_TOCDescrBuffer;			///< oiu
	TMapSectionPtrArray				m_MapSectionArray;			///< oiu
	mutable CXMutex					m_Mutex;					///< Synchronization object.
	//-------------------------------------
	CXMapLoaderThread(const CXMapLoaderThread &);						///< Not used.
	const CXMapLoaderThread & operator = (const CXMapLoaderThread &);	///< Not used.
	//-------------------------------------
	virtual void OnWorkFunc();
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXMapLoaderThread();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXMapLoaderThread();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStarted();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	virtual void OnThreadStopped();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void LoadTOCMapContainer(TTOCMapContainerPtr &TOCMapContainer, const CXStringASCII & FileName, unsigned char ZoomLevel, t_uint32 Key);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void LoadMapSection(TMapSectionPtr &MapSection);
};

#endif // __CXMAPLOADERTHREAD_HPP__
