/***************************************************************************
 *   Copyright (C) 2005 by Doru-Julian Bugariu                             *
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

#ifndef __CXNMEA_HPP__
#define __CXNMEA_HPP__

#include "CXStringASCII.hpp"

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXGGAPacket {
private:
	CXStringASCII	m_UTC;		///< oiu
	bool			m_oFix;		///< oiu
	int				m_NSat;		///< oiu
	double			m_dLon;		///< oiu
	double			m_dLat;		///< oiu
	double			m_dHeight;	///< oiu
	//-------------------------------------
	CXGGAPacket(const CXGGAPacket &);						///< Not used.
	const CXGGAPacket & operator = (const CXGGAPacket &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXGGAPacket();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXGGAPacket();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetUTC(const CXStringASCII &NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool HasFix() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int	GetNSat() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetNSat(int NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetLon() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLon(double NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetLat() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLat(double NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetHeight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetHeight(double NewValue);
};

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXRMCPacket {
private:
	CXStringASCII	m_UTC;		///< oiu
	bool			m_oFix;		///< oiu
	double			m_dLon;		///< oiu
	double			m_dLat;		///< oiu
	double			m_dSpeed;	///< oiu
	double			m_dCourse;	///< oiu
	//-------------------------------------
	CXRMCPacket(const CXRMCPacket &);						///< Not used.
	const CXRMCPacket & operator = (const CXRMCPacket &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXRMCPacket();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXRMCPacket();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetUTC(const CXStringASCII &NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool HasFix() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetLon() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLon(double NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetLat() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLat(double NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetSpeed() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSpeed(double NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	double GetCourse() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetCourse(double NewValue);
};

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXGSAPacket {
private:
	//-------------------------------------
	CXGSAPacket(const CXGSAPacket &);						///< Not used.
	const CXGSAPacket & operator = (const CXGSAPacket &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXGSAPacket();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXGSAPacket();
};

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXGSVSatelliteInfo {
private:
private:
	int		m_PRN;			///< oiu
	int		m_Elevation;	///< oiu
	int		m_Azimuth;		///< oiu
	int		m_SNR;			///< oiu
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void CopyFrom(const CXGSVSatelliteInfo &rOther);
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXGSVSatelliteInfo();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXGSVSatelliteInfo(const CXGSVSatelliteInfo &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXGSVSatelliteInfo();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	const CXGSVSatelliteInfo & operator = (const CXGSVSatelliteInfo &rOther);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetPRN() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetPRN(int NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetElevation() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetElevation(int NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetAzimuth() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetAzimuth(int NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetSNR() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSNR(int NewValue);
};

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXGSVPacket {
private:
	//-------------------------------------
	CXGSVPacket(const CXGSVPacket &);						///< Not used.
	const CXGSVPacket & operator = (const CXGSVPacket &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXGSVPacket();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXGSVPacket();
};


#endif //__CXNMEA_HPP__
