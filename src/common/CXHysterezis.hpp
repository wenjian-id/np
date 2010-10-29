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

#ifndef __CXHYSTEREZIS_HPP__
#define __CXHYSTEREZIS_HPP__

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tX, class tY> class CXHystInterval {
private:
    tX      m_XDown;
    tX      m_XUp;
    tY      m_Y;
    //-------------------------------------
    CXHystInterval();                                               ///< Not used.
    CXHystInterval(const CXHystInterval &);                         ///< Not used.
    const CXHystInterval & operator = (const CXHystInterval &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXHystInterval(const tX & XDown, const tX & XUp, const tY & Y):
        m_XDown(XDown),
        m_XUp(XUp),
        m_Y(Y)
    {
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual ~CXHystInterval() {
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tX GetXDown() const {
        return m_XDown;
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tX GetXUp() const {
        return m_XUp;
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tY GetY() const {
        return m_Y;
    }
};

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
template<class tX, class tY> class CXHysterezis {
private:
    tX                                      m_LastX;        ///< oiu
    tY                                      m_LastY;        ///< oiu
    int                                     m_LastInterval; ///< oiu
    bool                                    m_oFirstRun;    ///< oiu
    CXBuffer< CXHystInterval<tX, tY> *>     m_Values;       ///< oiu
    //-------------------------------------
    CXHysterezis(const CXHysterezis &);                         ///< Not used.
    const CXHysterezis & operator = (const CXHysterezis &);     ///< Not used.
protected:
public:
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    CXHysterezis() :
        m_LastX(0),
        m_LastY(0),
        m_LastInterval(0),
        m_oFirstRun(true)
    {
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    virtual ~CXHysterezis() {
        for(size_t i=0; i<m_Values.GetSize(); i++) {
            delete m_Values[i];
        }
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void AddInterval(const tX & XDown, const tX & XUp, const tY & Y) {
        /// \todo insert sorted!!!
        m_Values.Append(new CXHystInterval<tX, tY>(XDown, XUp, Y));
    }
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    tY GetHysterezisValue(const tX & X) {
        tY Result = 0;
        int NewIntervalIndex = -1; 
        if(m_Values.GetSize() == 0)
            return Result;
        // check if X increased or decreased
        if(m_oFirstRun || (X > m_LastX)) {
            // X increased or first run
            // check in which interval we are
            bool found = false;
            for(int i=0; i<(int)(m_Values.GetSize())-1; i++) {
                if((m_Values[i]->GetXUp() <= X) && (X < m_Values[i+1]->GetXUp())) {
                    // found
                    NewIntervalIndex = i;
                    found = true;
                    break;
                }
            }
            if(!found) {
                // is in last interval.
                NewIntervalIndex = (int)(m_Values.GetSize())-1;
            }
            int IntervalIndex = Max(m_LastInterval, NewIntervalIndex);
            Result = m_Values[IntervalIndex]->GetY();
            NewIntervalIndex = IntervalIndex;
        } else if (X < m_LastX) {
            // X decreased
            // check in which interval we are
            bool found = false;
            for(int i=0; i<(int)(m_Values.GetSize())-1; i++) {
                if((m_Values[i]->GetXDown() <= X) && (X < m_Values[i+1]->GetXDown())) {
                    // found
                    NewIntervalIndex = i;
                    found = true;
                    break;
                }
            }
            if(!found) {
                // is in last interval.
                NewIntervalIndex = (int)(m_Values.GetSize())-1;
            }
            int IntervalIndex = Min(m_LastInterval, NewIntervalIndex);
            Result = m_Values[IntervalIndex]->GetY();
            NewIntervalIndex = IntervalIndex;
        } else {
            // X constant
            // do nothing
            Result = m_LastY;
            NewIntervalIndex = m_LastInterval;
        }
        // now remember new values
        m_LastX = X;
        m_LastY = Result;
        m_LastInterval = NewIntervalIndex;
        m_oFirstRun = false;
        return Result;
    }
};

#endif // __CXHYSTEREZIS_HPP__
