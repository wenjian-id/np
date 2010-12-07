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

#ifndef __CXSTRINGUTF8_HPP__
#define __CXSTRINGUTF8_HPP__

#include <TargetIncludes.hpp>
#include "CXBuffer.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class  CXStringUTF8 : public tUCBuffer {
private:
    mutable wchar_t         *m_wbuf;    ///< oiu
    mutable unsigned char   *m_ucbuf;   ///< oiu
    //-------------------------------------
    /**
     * \brief oiu.
     *
     * oiu.
     */
    void ClearSTRBuffers();
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXStringUTF8();
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXStringUTF8(const CXStringUTF8 &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8(const char *pcChar);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8(const char *pcChar, size_t Len);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXStringUTF8();
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXStringUTF8 & operator = (const CXStringUTF8 &rOther);
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXStringUTF8 & operator = (const tUCBuffer &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if equal.
     */
    bool operator == (const CXStringUTF8 &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if not equal.
     */
    bool operator != (const CXStringUTF8 &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void operator += (const CXStringUTF8 &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8 operator + (const CXStringUTF8 &rOther) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8 operator + (const char *pcString) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void Empty();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    wchar_t *w_str() const ;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    unsigned char *uc_str() const;
};

#endif // __CXSTRINGUTF8_HPP__
