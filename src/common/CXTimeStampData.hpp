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

#ifndef __CXTIMESTAMPDATA_HPP__
#define __CXTIMESTAMPDATA_HPP__

#include "CXExactTime.hpp"
#include "CXUTCTime.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
template<class tData> class CXTimeStampData {
private:
    tData           m_Data;
    CXExactTime     m_TimeStamp;
    CXUTCTime       m_UTCTime;
    //-------------------------------------
    /**
     * \brief Copy from other instance to self.
     *
     * Copy from other instance to self.
     * \param   rOther  Instance to copy from.
     */
    void CopyFrom(const CXTimeStampData &rOther);
protected:
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXTimeStampData();
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    CXTimeStampData(const tData & Data);
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    CXTimeStampData(const tData & Data, const CXExactTime &TimeStamp);
    //-------------------------------------
    /**
     * \brief Copy constructor.
     *
     * Copy constructor.
     * \param   rOther  Instance to copy from.
     */
    CXTimeStampData(const CXTimeStampData &rOther);
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXTimeStampData();
    //-------------------------------------
    /**
     * \brief Assignment operator.
     *
     * Assignment operator.
     * \param   rOther  Instance to copy from.
     * \return          Const reference to self.
     */
    const CXTimeStampData & operator = (const CXTimeStampData &rOther);
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    void SetData(const tData & Data);
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    tData & Data();
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    const tData & Data() const;
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    const CXExactTime & TimeStamp() const;
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    const CXUTCTime & UTCTime() const;
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    void SetNow();
    //-------------------------------------
    /**
     * \brief   oiu
     *
     * oiu
     */
    void SetUTCTime(const CXUTCTime &UTCTime);
};


//-------------------------------------
template<class tData> CXTimeStampData<tData>::CXTimeStampData() {
    m_TimeStamp.SetNow();
}

//-------------------------------------
template<class tData> CXTimeStampData<tData>::CXTimeStampData(const tData & Data, const CXExactTime &TimeStamp) :
    m_Data(Data),
    m_TimeStamp(TimeStamp)
{
}

//-------------------------------------
template<class tData> CXTimeStampData<tData>::CXTimeStampData(const tData & Data) :
    m_Data(Data)
{
    m_TimeStamp.SetNow();
}

//-------------------------------------
template<class tData> CXTimeStampData<tData>::CXTimeStampData(const CXTimeStampData & rOther) {
    CopyFrom(rOther);
}

//-------------------------------------
template<class tData> CXTimeStampData<tData>::~CXTimeStampData() {
}

//-------------------------------------
template<class tData> void CXTimeStampData<tData>::CopyFrom(const CXTimeStampData &rOther) {
    m_Data = rOther.m_Data;
    m_TimeStamp = rOther.m_TimeStamp;
    m_UTCTime = rOther.m_UTCTime;
}

//-------------------------------------
template<class tData> const CXTimeStampData<tData> & CXTimeStampData<tData>::operator = (const CXTimeStampData &rOther) {
    if(this != &rOther)
        CopyFrom(rOther);
    return *this;
}

//-------------------------------------
template<class tData> void CXTimeStampData<tData>::SetData(const tData & Data) {
    m_Data = Data;
}

//-------------------------------------
template<class tData> tData & CXTimeStampData<tData>::Data() {
    return m_Data;
}

//-------------------------------------
template<class tData> const tData & CXTimeStampData<tData>::Data() const {
    return m_Data;
}

//-------------------------------------
template<class tData> const CXExactTime & CXTimeStampData<tData>::TimeStamp() const {
    return m_TimeStamp;
}

//-------------------------------------
template<class tData> const CXUTCTime & CXTimeStampData<tData>::UTCTime() const {
    return m_UTCTime;
}

//-------------------------------------
template<class tData> void CXTimeStampData<tData>::SetNow() {
    m_TimeStamp.SetNow();
}

//-------------------------------------
template<class tData> void CXTimeStampData<tData>::SetUTCTime(const CXUTCTime &UTCTime) {
    m_UTCTime = UTCTime;
}

#endif // __CXTIMESTAMPDATA_HPP__
