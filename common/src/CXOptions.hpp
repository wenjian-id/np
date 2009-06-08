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

#ifndef __CXOPTIONS_HPP__
#define __CXOPTIONS_HPP__

#include "CXStringASCII.hpp"
#include "CXRWLock.hpp"
#include "ISerial.hpp"
#include "Utils.hpp"

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXOptions {
public:
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	enum E_OSM_VALI {
		e_OSMValiName		= 0x0001,		///< oiu
		e_OSMValiRef		= 0x0002,		///< oiu
		e_OSMValiMaxSpeed	= 0x0004,		///< oiu
	};
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	enum E_MODE {
		e_ModeCar,			///< oiu
		e_ModeBike,			///< oiu
		e_ModePedestrian,	///< oiu
		e_ModeCaching,		///< oiu
		e_ModeMapping,		///< oiu
	};
	//-------------------------------------
	/**
	 * \brief Flags for displaying certain debug informations.
	 *
	 *	Flags for displaying certain debug informations.
	 */
	enum E_DEBUGINFO {
		e_DBGDrawTimes				= 0x0001,		///< Display drawing times.
		e_DBGDrawMapSectionBorders	= 0x0002,		///< Display map section borders.
		e_DBGDrawPositions			= 0x0004,		///< Display all computed positions
	};
private:
	static CXOptions		*m_pInstance;					///< oiu
	CXStringASCII			m_StartPath;					///< oiu
	CXSerialPortConfig		m_SerialPortConfig;				///< oiu
	bool					m_oNorthing;					///< oiu
	bool					m_oFullScreen;					///< oiu
	bool					m_oShowLogo;					///< Show logo.
	bool					m_oSaving;						///< oiu
	bool					m_oShowZoomButtons;				///< oiu
	bool					m_oAutomaticZoom;				///< oiu
	CXStringASCII			m_AutomaticZoomString;			///< oiu
	bool					m_oShowMaxSpeed;				///< oiu
	bool					m_oShowCompass;					///< oiu
	bool					m_oShowTrackLog;				///< oiu
	bool					m_oShowScale;					///< oiu
	bool					m_oShowMinimizeButton;			///< oiu
	bool					m_oShowPOIs;					///< Show some POIs.
	bool					m_oShowCities;					///< Show Cities.
	bool					m_oSnapToWay;					///< oiu
	bool					m_oStartWithLastPosition;		///< oiu
	bool					m_oMapMovingManually;			///< oiu
	int						m_WatchdogTimeout;				///< oiu
	t_uint64				m_OSMVali;						///< oiu
	t_uint64				m_DebugInfo;					///< Holder for debug info flags.
	int						m_InfoBarBottomHeight;			///< oiu
	int						m_InfoBarTopHeight;				///< oiu
	int						m_InfoBarCommonWidth;			///< oiu
	int						m_InfoBarCommonHeight;			///< oiu
	int						m_MaxSpeedSize;					///< oiu
	int						m_CompassSize;					///< oiu
	size_t					m_TrackLogSize;					///< oiu
	int						m_TrackLogMinDist;				///< oiu
	int						m_ScaleWidth;					///< oiu
	int						m_ScaleHeight;					///< oiu
	E_MODE					m_eMode;						///< oiu
	CXStringASCII			m_DirectoryMaps;				///< oiu
	CXStringASCII			m_DirectorySave;				///< oiu
	CXStringASCII			m_DirectoryIcons;				///< oiu
	unsigned long			m_LogoTime;						///< oiu
	CXStringASCII			m_LogoFileName;					///< oiu
	CXStringASCII			m_InfoFileName;					///< oiu
	CXStringASCII			m_QuitFileName;					///< oiu
	CXStringASCII			m_MinimizeFileName;				///< oiu
	CXStringASCII			m_SavingOnFileName;				///< oiu
	CXStringASCII			m_SavingOffFileName;			///< oiu
	CXStringASCII			m_ZoomInFileName;				///< oiu
	CXStringASCII			m_ZoomOutFileName;				///< oiu
	CXStringASCII			m_MoveFileName;					///< oiu
	CXStringASCII			m_CurrentPosFileName;			///< oiu
	double					m_SpeedThresholdCar;			///< oiu
	double					m_SpeedThresholdBike;			///< oiu
	double					m_SpeedThresholdPedestrian;		///< oiu
	double					m_SpeedThresholdCaching;		///< oiu
	double					m_SpeedThresholdMapping;		///< oiu
	int						m_GPSReceiverLag;				///< oiu
	E_ZOOM_LEVEL			m_ZoomLevel;					///< oiu
	int						m_POIFontSize;					///< oiu
	int						m_ScaleFontSize;				///< oiu
	int						m_DebugFontSize;				///< oiu
	int						m_CitySmallFontSize;			///< oiu
	int						m_CityMediumFontSize;			///< oiu
	int						m_CityLargeFontSize;			///< oiu
	mutable CXRWLock		m_RWLock;						///< Synchronization object.
	//-------------------------------------
	CXOptions(const CXOptions &);						///< Not used.
	const CXOptions & operator = (const CXOptions &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXOptions();
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXOptions();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	static CXOptions *Instance();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool ReadFromFile(const char *pcFileName);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetStartPath() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetStartPath(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXSerialPortConfig GetSerialPortConfig() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSerialPortConfig(const CXSerialPortConfig & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsNorthing() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetNorthing(bool Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsFullScreen() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetFullScreen(bool Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetInfoBarBottomHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetInfoBarTopHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetInfoBarBottomHeight(int Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetInfoBarTopHeight(int Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetInfoBarCommonWidth() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetInfoBarCommonWidth(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetInfoBarCommonHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetInfoBarCommonHeight(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetMaxSpeedSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMaxSpeedSize(int Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetCompassSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCompassSize(int Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetScaleWidth() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetScaleWidth(int Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetScaleHeight() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetScaleHeight(int Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	E_MODE GetMode() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMode(E_MODE NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetDirectoryMaps() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetDirectoryMaps(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetDirectorySave() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetDirectorySave(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetDirectoryIcons() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetDirectoryIcons(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	unsigned long GetLogoTime() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLogoTime(unsigned long LogoTime);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetLogoFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetLogoFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetInfoFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetInfoFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetQuitFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetQuitFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowMinimizeButton() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowMinimizeButtonFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetMinimizeFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMinimizeFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetSaveOnFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSaveOnFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetSaveOffFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSaveOffFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetMoveFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMoveFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetCurrentPosFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCurrentPosFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetZoomInFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetZoomInFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetZoomOutFileName() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetZoomOutFileName(const CXStringASCII & Value);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsSaving() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void ToggleSaving();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowLogoFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowLogo() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowZoomButtons() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowZoomButtonsFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool AutomaticZoom() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetAutomaticZoomFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXStringASCII GetAutomaticZoomString() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetAutomaticZoomString(const CXStringASCII & NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowMaxSpeed() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowMaxSpeedFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowCompass() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowCompassFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowScale() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowScaleFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowTrackLog() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowTrackLogFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowPOIs() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowPOIsFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustShowCities() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetShowCitiesFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustSnapToWay() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSnapToWayFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool MustStartWithLastPosition() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetStartWithLastPositionFlag(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsMapMovingManually() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetMapMovingManually(bool NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetWatchdogTimeout() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetWatchdogTimeout(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	size_t GetTrackLogSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetTrackLogSize(size_t NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	unsigned int GetTrackLogMinDist() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetTrackLogMinDist(unsigned int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	t_uint64 GetOSMValiFlags() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	bool IsOSMValiFlagSet(E_OSM_VALI eFlag) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetOSMValiFlag(E_OSM_VALI eFlag);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void ClearOSMValiFlag(E_OSM_VALI eFlag);
	//-------------------------------------
	/**
	 * \brief Check if debug info flag is set.
	 *
	 *	Check if debug info flag is set.
	 *	\param	eFlag	The flag.
	 *	\return			True if flag is set.
	 */
	bool IsDebugInfoFlagSet(E_DEBUGINFO eFlag) const;
	//-------------------------------------
	/**
	 * \brief Set a specific debug info flag.
	 *
	 *	Set a specific debug info flag
	 *	\param	eFlag	The flag.
	 */
	void SetDebugInfoFlag(E_DEBUGINFO eFlag);
	//-------------------------------------
	/**
	 * \brief Clear a specific debug info flag.
	 *
	 *	Clear a specific debug info flag
	 *	\param	eFlag	The flag.
	 */
	void ClearDebugInfoFlag(E_DEBUGINFO eFlag);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSpeedThresholdCar() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSpeedThresholdCar(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSpeedThresholdBike() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSpeedThresholdBike(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSpeedThresholdPedestrian() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSpeedThresholdPedestrian(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSpeedThresholdCaching() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSpeedThresholdCaching(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetSpeedThresholdMapping() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetSpeedThresholdMapping(double NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetGPSReceiverLag() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetGPSReceiverLag(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	E_ZOOM_LEVEL GetZoomLevel() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetZoomLevel(E_ZOOM_LEVEL NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetPOIFontSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetPOIFontSize(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetScaleFontSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetScaleFontSize(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetDebugFontSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetDebugFontSize(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetCitySmallFontSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCitySmallFontSize(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetCityMediumFontSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCityMediumFontSize(int NewValue);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetCityLargeFontSize() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void SetCityLargeFontSize(int NewValue);
};

#endif // __CXOPTIONS_HPP__
