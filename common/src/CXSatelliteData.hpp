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

#ifndef __CXSATELLITEDATA_HPP__
#define __CXSATELLITEDATA_HPP__

#include "CXBuffer.hpp"
#include "CXNMEA.hpp"
#include "CXRWLock.hpp"

class CXDeviceContext;

//----------------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXSatelliteData {
private:
	static CXSatelliteData			*m_pInstance;			///< oiu
	int								m_NrSat;				///< oiu
	CXBuffer<int>					m_ActiveSatellites;		///< oiu
	CXBuffer<CXGSVSatelliteInfo *>	m_SatInfo;				///< oiu
	CXBuffer<CXGSVSatelliteInfo *>	m_TmpSatInfo;			///< oiu
	int								m_LastReceivedGSVTel;	///< oiu
	int								m_TmpNrSat;				///< oiu
	bool							m_oRMCDataReceived;		///< oiu
	bool							m_oGGADataReceived;		///< oiu
	bool							m_oGSADataReceived;		///< oiu
	bool							m_oGSVDataReceived;		///< oiu
	mutable CXRWLock				m_RWLock;				///< oiu
	//-------------------------------------
	CXSatelliteData(const CXSatelliteData &);						///< Not used.
	const CXSatelliteData & operator = (const CXSatelliteData &);	///< Not used.
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ClearBuffer(CXBuffer<CXGSVSatelliteInfo *> & rBuffer);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXSatelliteData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXSatelliteData();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	static CXSatelliteData *Instance();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetRMCReceived();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetNrSatGGA(int NrSatGGA);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetNrSat() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetActiveSatellites(const CXBuffer<int> &ActiveSatellites);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetGSVData(int NTelegrams, int NCurrentTelegram, int NSat, int NInfos, 
					const CXGSVSatelliteInfo &Info1, const CXGSVSatelliteInfo &Info2,
					const CXGSVSatelliteInfo &Info3, const CXGSVSatelliteInfo &Info4);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void Paint(CXDeviceContext *pDC, int OffsetX, int OffsetY, int Width, int Height);
};

#endif // __CXSATELLITEDATA_HPP__
