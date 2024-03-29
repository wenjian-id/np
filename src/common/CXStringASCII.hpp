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

#ifndef __CXSTRINGASCII_HPP__
#define __CXSTRINGASCII_HPP__

#include <TargetIncludes.hpp>
#include "CXBuffer.hpp"

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class  CXStringASCII : public tCBuffer {
private:
    mutable char    *m_pcstr;
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
    CXStringASCII();
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXStringASCII(const CXStringASCII &rOther);
    //-------------------------------------
    /**
     * \brief Constructor.
     *
     * Constructor.
     * \param   rOther  Buffer to copy from.
     */
    CXStringASCII(const tCBuffer &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII(const char *pcChar);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII(const char *pcChar, size_t Len);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXStringASCII();
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXStringASCII & operator = (const CXStringASCII &rOther);
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXStringASCII & operator = (const tCBuffer &rOther);
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if equal.
     */
    bool operator == (const CXStringASCII &rOther) const;
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if not equal.
     */
    bool operator != (const CXStringASCII &rOther) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void operator += (char c);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void operator += (const CXStringASCII &rOther);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII operator + (const char *pcString) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII operator + (const CXStringASCII &rOther) const;
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if this instance < other instance.
     */
    bool operator < (const CXStringASCII &rOther) const;
    //-------------------------------------
    /**
     * \brief Comparison operator.
     *
     * Compares this instance with other instance.
     * \param   rOther  Instance to compare with.
     * \return          True if this instance > other instance.
     */
    bool operator > (const CXStringASCII &rOther) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t Find(const char *pcFind) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t Find(const CXStringASCII &FindString) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t ReverseFind(char cFind) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t Find(char cFind) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    size_t Count(char cFind) const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void TrimLeft();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void TrimRight();
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
    CXStringASCII ToUpper() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringASCII ToLower() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    double ToDouble() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int ToInt() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    int ToIntFromHex() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    const char *c_str() const;
};

#endif // __CXSTRINGASCII_HPP__
