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

#ifndef __CXNMEA_HPP__
#define __CXNMEA_HPP__

#include "CXStringASCII.hpp"

//---------------------------------------------------------------------
/**
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
	double			m_dHDOP;	///< oiu
	//-------------------------------------
	CXGGAPacket(const CXGGAPacket &);						///< Not used.
	const CXGGAPacket & operator = (const CXGGAPacket &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGGAPacket();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGGAPacket();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetUTC(const CXStringASCII &NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool HasFix() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int	GetNSat() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetNSat(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLon() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLon(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLat() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLat(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetHeight(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetHDOP() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetHDOP(double NewValue);
};

//---------------------------------------------------------------------
/**
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
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXRMCPacket();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXRMCPacket();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetUTC() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetUTC(const CXStringASCII &NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool HasFix() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFix(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLon() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLon(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetLat() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLat(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSpeed() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSpeed(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetCourse() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCourse(double NewValue);
};

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXGSAPacket {
private:
	CXBuffer<int>		m_Satellites;	///< oiu
	double				m_HDOP;			///< oiu
	double				m_VDOP;			///< oiu
	//-------------------------------------
	CXGSAPacket(const CXGSAPacket &);						///< Not used.
	const CXGSAPacket & operator = (const CXGSAPacket &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGSAPacket();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGSAPacket();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void ClearSatellites();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void AddSatellite(int SatNr);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	const CXBuffer<int> & GetSatellites() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetHDOP() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetHDOP(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetVDOP() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetVDOP(double NewValue);
};

//---------------------------------------------------------------------
/**
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
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXGSVPacket();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXGSVPacket();
};


#endif //__CXNMEA_HPP__
