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

#ifndef __CXOPTIONS_HPP__
#define __CXOPTIONS_HPP__

#include "CXStringASCII.hpp"
#include "CXMutex.hpp"
#include "ISerial.hpp"

//---------------------------------------------------------------------
/*
 * \brief oiu
 *
 */
class CXOptions {
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	enum E_OSM_VALI {
		e_OSMValiName		= 0x0001,		///< oiu
		e_OSMValiRef		= 0x0002,		///< oiu
		e_OSMValiMaxSpeed	= 0x0004,		///< oiu
	};
private:
	static CXOptions	*m_pInstance;			///< oiu
	CXStringASCII		m_StartPath;			///< oiu
	CXSerialPortConfig	m_SerialPortConfig;		///< oiu
	bool				m_oNorthing;			///< oiu
	bool				m_oFullScreen;			///< oiu
	bool				m_oShowLogo;			///< show logo
	bool				m_oSaving;				///< oiu
	bool				m_oShowZoomButtons;		///< oiu
	bool				m_oShowMaxSpeed;		///< oiu
	bool				m_oShowCompass;			///< oiu
	bool				m_oShowTrackLog;		///< oiu
	t_uint64			m_OSMVali;				///< oiu
	int					m_InfoBarBottomHeight;	///< oiu
	int					m_InfoBarTopHeight;		///< oiu
	int					m_MaxSpeedSize;			///< oiu
	int					m_CompassSize;			///< oiu
	CXStringASCII		m_DirectoryMaps;		///< oiu
	CXStringASCII		m_DirectorySave;		///< oiu
	CXStringASCII		m_DirectoryIcons;		///< oiu
	unsigned long		m_LogoTime;				///< oiu
	CXStringASCII		m_LogoFileName;			///< oiu
	CXStringASCII		m_InfoFileName;			///< oiu
	CXStringASCII		m_QuitFileName;			///< oiu
	CXStringASCII		m_SavingOnFileName;		///< oiu
	CXStringASCII		m_SavingOffFileName;	///< oiu
	CXStringASCII		m_ZoomInFileName;		///< oiu
	CXStringASCII		m_ZoomOutFileName;		///< oiu
	mutable CXMutex		m_Mutex;				///< oiu
	//-------------------------------------
	CXOptions(const CXOptions &);						///< Not used.
	const CXOptions & operator = (const CXOptions &);	///< Not used.
protected:
public:
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXOptions();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	virtual ~CXOptions();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	static CXOptions *Instance();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool ReadFromFile(const char *pcFileName);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetStartPath() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetStartPath(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXSerialPortConfig GetSerialPortConfig() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSerialPortConfig(const CXSerialPortConfig & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsNorthing() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetNorthing(bool Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsFullScreen() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetFullScreen(bool Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetInfoBarBottomHeight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetInfoBarTopHeight() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetInfoBarBottomHeight(int Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetInfoBarTopHeight(int Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetMaxSpeedSize() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetMaxSpeedSize(int Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	int GetCompassSize() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetCompassSize(int Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetDirectoryMaps() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetDirectoryMaps(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetDirectorySave() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetDirectorySave(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetDirectoryIcons() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetDirectoryIcons(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	unsigned long GetLogoTime() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLogoTime(unsigned long LogoTime);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetLogoFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetLogoFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetInfoFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetInfoFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetQuitFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetQuitFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetSaveOnFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSaveOnFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetSaveOffFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetSaveOffFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetZoomInFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetZoomInFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	CXStringASCII GetZoomOutFileName() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetZoomOutFileName(const CXStringASCII & Value);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsSaving() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ToggleSaving();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ClearShowLogoFlag();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetShowLogoFlag();
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool MustShowLogo() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool MustShowZoomButtons() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetShowZoomButtonsFlag(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool MustShowMaxSpeed() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetShowMaxSpeedFlag(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool MustShowCompass() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetShowCompassFlag(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool MustShowTrackLog() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetShowTrackLogFlag(bool NewValue);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	t_uint64 GetOSMValiFlags() const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	bool IsOSMValiFlagSet(E_OSM_VALI eFlag) const;
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void SetOSMValiFlag(E_OSM_VALI eFlag);
	//-------------------------------------
	/*
	 * \brief oiu
	 *
	 */
	void ClearOSMValiFlag(E_OSM_VALI eFlag);
};

#endif // __CXOPTIONS_HPP__
