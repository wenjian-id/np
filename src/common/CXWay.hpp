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

#ifndef __CXWAY_HPP__
#define __CXWAY_HPP__

#include "CXNode.hpp"
#include "CXStringUTF8.hpp"

class CXWay;

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXWay {
private:
    E_WAY_TYPE          m_eWayType;         ///< oiu
    CXStringUTF8        m_Name;             ///< oiu
    CXStringUTF8        m_Ref;              ///< oiu
    CXStringUTF8        m_IntRef;           ///< oiu
    unsigned char       m_MaxSpeedForward;  ///< oiu 0 means no max speed
    unsigned char       m_MaxSpeedBackward; ///< oiu 0 means no max speed
    char                m_Layer;            ///< oiu
    E_ONEWAY_TYPE       m_eOneway;          ///< oiu
    bool                m_oOSMValiOK;       ///< oiu
    CXOrderedNodeList   *m_pNodeList;           ///< oiu
    //-------------------------------------
    CXWay();                                    ///< Not used.
    CXWay(const CXWay &);                       ///< Not used.
    const CXWay & operator = (const CXWay &);   ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXWay(E_WAY_TYPE eWayType, const CXStringUTF8 & Name, const CXStringUTF8 & Ref, const CXStringUTF8 & IntRef);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXWay();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXOrderedNodeList *GetNodeList() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetNodeList(CXOrderedNodeList *pNodeList);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_WAY_TYPE GetWayType() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8 GetName() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8 GetRef() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXStringUTF8 GetIntRef() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetMaxSpeedForward(unsigned char NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    unsigned char GetMaxSpeedForward() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetMaxSpeedBackward(unsigned char NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    unsigned char GetMaxSpeedBackward() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetLayer(char NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    unsigned char GetLayer() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetOneway(E_ONEWAY_TYPE NewValue);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    E_ONEWAY_TYPE GetOneway() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    bool IsOSMValiOK() const;
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetOSMValiOK(bool NewValue);
};

typedef CXBuffer<CXWay *>                       TWayBuffer;     ///< oiu

#endif // __CXWAY_HPP__
