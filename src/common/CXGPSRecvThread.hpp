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

#ifndef __CXGPSRECVTHREAD_HPP__
#define __CXGPSRECVTHREAD_HPP__

#include "CXLoopThread.hpp"
#include "CXExactTime.hpp"
#include "CXGPSProtocol.hpp"
#include "CXGPSInputChannel.hpp"
#include <CXMutex.hpp>
#include <CXSerial.hpp>

class CXLocatorThread;

//----------------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGPSRecvThread : public CXLoopThread {
private:
    CXGPSProtocol       *m_pGPSProtocol;            ///< oiu
    CXGPSInputChannel   *m_pGPSInputChannel;        ///< oiu
    size_t              m_LastGPSConnectTimeout;    ///< oiu
    CXExactTime         m_LastGPSConnect;           ///< oiu
    CXLocatorThread     *m_pLocator;                ///< oiu
    mutable CXMutex     m_Mutex;                    ///< Synchronization object.
    //-------------------------------------
    CXGPSRecvThread(const CXGPSRecvThread &);                       ///< Not used.
    const CXGPSRecvThread & operator = (const CXGPSRecvThread &);   ///< Not used.
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CreateGPSProtocol();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void OpenGPSProtocol();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void ReopenGPSProtocol();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void CloseGPSProtocol();
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
    virtual void OnThreadLoop();
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
    void Save(const tUCBuffer & Buffer);
public:
    //-------------------------------------
    /**
     * \brief Default constructor.
     *
     * Default constructor.
     */
    CXGPSRecvThread();
    //-------------------------------------
    /**
     * \brief Destructor.
     *
     * Destructor.
     */
    virtual ~CXGPSRecvThread();
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void SetLocator(CXLocatorThread *pLocator);
    //-------------------------------------
    /**
     * \brief oiu
     *
     */
    void FlushInput();
};


#endif // __CXGPSRECVTHREAD_HPP__
