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

#ifndef __CXSAVER_HPP__
#define __CXSAVER_HPP__

#include "CXFile.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXSaver {
private:
	bool			m_oSaving;	///< oiu
	CXStringASCII	m_Suffix;	///< oiu
	//-------------------------------------
	CXSaver();										///< Not used.
	CXSaver(const CXSaver &);						///< Not used.
	const CXSaver & operator = (const CXSaver &);	///< Not used.
protected:
	CXFile			m_File;		///< oiu
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool PrepareSaving();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual void AfterOpen() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual void BeforeClose() = 0;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	bool Close();
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	CXSaver(const char *pcSuffix);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 * oiu
	 */
	virtual ~CXSaver();
};

#endif //__CXSAVER_HPP__
