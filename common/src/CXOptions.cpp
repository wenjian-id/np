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

#include "CXOptions.hpp"
#include "Utils.hpp"
#include "CXFileIni.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"
#include <OSSpecific.hpp>


#include "CXPOWMMap.hpp"

#include  <stdlib.h>

CXOptions * CXOptions::m_pInstance = NULL;

static const int TO = 2000;

//---------------------------------------------------------------------
//-------------------------------------
CXOptions::CXOptions() :
	m_oNorthing(false),
	m_oFullScreen(false),
	m_oShowLogo(true),
	m_oSaving(false),
	m_oShowZoomButtons(false),
	m_oAutomaticZoom(false),
	m_oShowMaxSpeed(true),
	m_oShowCompass(false),
	m_oShowTrackLog(false),
	m_oShowScale(false),
	m_oShowMinimizeButton(false),
	m_oShowPOIs(false),
	m_oSnapToWay(false),
	m_oStartWithLastPosition(false),
	m_oMapMovingManually(false),
	m_WatchdogTimeout(0),
	m_OSMVali(0),
	m_DebugInfo(0),
	m_InfoBarBottomHeight(20),
	m_InfoBarTopHeight(20),
	m_InfoBarCommonWidth(65),
	m_InfoBarCommonHeight(60),
	m_MaxSpeedSize(61),
	m_CompassSize(50),
	m_TrackLogSize(0),
	m_TrackLogMinDist(10),
	m_ScaleWidth(100),
	m_ScaleHeight(5),
	m_eMode(e_ModeCar),
	m_LogoTime(5000),
	m_SpeedThresholdCar(1),
	m_SpeedThresholdBike(1),
	m_SpeedThresholdPedestrian(1),
	m_SpeedThresholdCaching(1),
	m_SpeedThresholdMapping(1),
	m_GPSReceiverLag(0),
	m_ZoomLevel(e_ZoomLevel_0),
	m_POIFontSize(16),
	m_ScaleFontSize(16),
	m_DebugFontSize(16)
{
}

//-------------------------------------
CXOptions::~CXOptions() {
}

//-------------------------------------
CXOptions *CXOptions::Instance() {
	if(m_pInstance == NULL)
		m_pInstance = new CXOptions();
	return m_pInstance;
}

//-------------------------------------
bool CXOptions::ReadFromFile(const char *pcFileName) {
	// read options
	CXFileIni F;
	if(!F.Read(pcFileName))
		return false;
	// now extract options
	// serial port
	CXSerialPortConfig SPC;
	CXStringASCII SPCStr = F.Get("SerialPort", "COM5:;8;N;1");
	// check if DEMO
	if(SPCStr.Find("DEMO") == 0) {
		// DEMO, don't change anything
		SPC.SetPort(SPCStr);
	} else {
		// Port
		SPC.SetPort(ExtractFirstToken(SPCStr, ';'));
		// Baudrate
		SPC.SetBaudrate(atoi(ExtractFirstToken(SPCStr, ';').c_str()));
		// data bits
		SPC.SetDataBits(atoi(ExtractFirstToken(SPCStr, ';').c_str()));
		// parity
		SPC.SetParity(ExtractFirstToken(SPCStr, ';'));
		// stop bits
		SPC.SetStopBits(SPCStr);
	}
	SetSerialPortConfig(SPC);
	// northing
	SetNorthing(F.Get("Northing", "off").ToUpper() == "ON");
	// fullscreen
	SetFullScreen(F.Get("FullScreen", "off").ToUpper() == "ON");
	// showzoom
	SetShowZoomButtonsFlag(F.Get("ShowZoomButtons", "off").ToUpper() == "ON");
	SetAutomaticZoomString(F.Get("AutoZoom", "off").ToUpper());
	// InfoBar Bottom Height
	SetInfoBarBottomHeight(atoi(F.Get("InfoBarBottomHeight", "20").c_str()));
	// InfoBar Top Height
	SetInfoBarTopHeight(atoi(F.Get("InfoBarTopHeight", "20").c_str()));
	// InfoBar Common Width
	SetInfoBarCommonWidth(atoi(F.Get("InfoBarCommonWidth", "65").c_str()));
	// InfoBar Common Height
	SetInfoBarCommonHeight(atoi(F.Get("InfoBarCommonHeight", "60").c_str()));
	// MaxSpeed
	SetShowMaxSpeedFlag(F.Get("ShowMaxSpeed", "on").ToUpper() == "ON");
	// MaxSpeed size
	SetMaxSpeedSize(atoi(F.Get("MaxSpeedSize", "61").c_str()));
	// Compass
	SetShowCompassFlag(F.Get("ShowCompass", "on").ToUpper() == "ON");
	// Compass size
	SetCompassSize(atoi(F.Get("CompassSize", "50").c_str()));
	// Scale
	SetShowScaleFlag(F.Get("ShowScale", "on").ToUpper() == "ON");
	// Scale width
	SetScaleWidth(atoi(F.Get("ScaleWidth", "100").c_str()));
	// Scale height
	SetScaleHeight(atoi(F.Get("ScaleHeight", "5").c_str()));
	// TrackLog
	SetShowTrackLogFlag(F.Get("ShowTrackLog", "off").ToUpper() == "ON");
	// TrackLogSize
	SetTrackLogSize(static_cast<size_t>(Max(0, atoi(F.Get("TrackLogSize", "0").c_str()))));
	// TrackLogMinDist
	SetTrackLogMinDist(static_cast<unsigned int>(Max(0, atoi(F.Get("TrackLogMinDist", "10").c_str()))));
	// OSMVali name
	if(F.Get("OSMValiName", "off").ToUpper() == "ON")
		SetOSMValiFlag(e_OSMValiName);
	// OSMVali ref
	if(F.Get("OSMValiRef", "off").ToUpper() == "ON")
		SetOSMValiFlag(e_OSMValiRef);
	// OSMVali maxspeed
	if(F.Get("OSMValiMaxSpeed", "off").ToUpper() == "ON")
		SetOSMValiFlag(e_OSMValiMaxSpeed);
	// DebugInfo
	// DBGDrawTimes
	if(F.Get("DBGDrawTimes", "off").ToUpper() == "ON")
		SetDebugInfoFlag(e_DBGDrawTimes);
	// DBGDrawMapSectionBorders
	if(F.Get("DBGDrawMapSectionBorders", "off").ToUpper() == "ON")
		SetDebugInfoFlag(e_DBGDrawMapSectionBorders);
	// DBGDrawPositions
	if(F.Get("DBGDrawPositions", "off").ToUpper() == "ON")
		SetDebugInfoFlag(e_DBGDrawPositions);
	// mode
	CXStringASCII Mode = F.Get("Mode", "off").ToUpper();
	if(Mode == "CAR")
		SetMode(e_ModeCar);
	else if (Mode == "BIKE")
		SetMode(e_ModeBike);
	else if (Mode == "PED")
		SetMode(e_ModePedestrian);
	else if (Mode == "CACHE")
		SetMode(e_ModeCaching);
	else if (Mode == "MAP")
		SetMode(e_ModeCaching);
	else
		SetMode(e_ModeCar);
	// maps directory
	SetDirectoryMaps(CreateAbsolutePath(m_StartPath, F.Get("DirectoryMaps", "Maps")));
	// Save directory
	SetDirectorySave(CreateAbsolutePath(m_StartPath, F.Get("DirectorySave", "Save")));
	// Icons directory
	SetDirectoryIcons(CreateAbsolutePath(m_StartPath, F.Get("DirectoryIcons", "Icons")));
	// logo
	CXStringASCII DirIcons=GetDirectoryIcons();
	CXStringASCII Logo=DirIcons;
	Logo+=F.Get("LogoName", "logo.bmp");
	SetLogoFileName(Logo);
	SetLogoTime(atoi(F.Get("LogoTime", "5000").c_str()));
	// info bmp
	CXStringASCII Info=DirIcons;
	Info+=F.Get("InfoName", "info.bmp");
	SetInfoFileName(Info);
	// quit bmp
	CXStringASCII Quit=DirIcons;
	Quit+=F.Get("QuitName", "quit.bmp");
	SetQuitFileName(Quit);
	// Minimize bmp
	SetShowMinimizeButtonFlag(F.Get("ShowMinimizeButton", "off").ToUpper() == "ON");
	CXStringASCII Minimize=DirIcons;
	Minimize+=F.Get("MinimizeName", "minimize.bmp");
	SetMinimizeFileName(Minimize);
	// save bmps
	CXStringASCII SaveOn=DirIcons;
	SaveOn+=F.Get("SaveOnName", "saveon.bmp");
	SetSaveOnFileName(SaveOn);
	CXStringASCII SaveOff=DirIcons;
	SaveOff+=F.Get("SaveOffName", "saveoff.bmp");
	SetSaveOffFileName(SaveOff);
	// zoom bmps
	CXStringASCII ZoomIn=DirIcons;
	ZoomIn+=F.Get("ZoomInName", "zoomin.bmp");
	SetZoomInFileName(ZoomIn);
	CXStringASCII ZoomOut=DirIcons;
	ZoomOut+=F.Get("ZoomOutName", "zoomout.bmp");
	SetZoomOutFileName(ZoomOut);
	// POIs
	SetShowPOIsFlag(F.Get("ShowPOIs", "off").ToUpper() == "ON");
	// SnapToWay
	SetSnapToWayFlag(F.Get("SnapToWay", "off").ToUpper() == "ON");
	// StartWithLastPosition
	SetStartWithLastPositionFlag(F.Get("StartWithLastPosition", "off").ToUpper() == "ON");
	// Speed thresholds
	SetSpeedThresholdCar(atof(F.Get("SpeedThresholdCar", "2").c_str()));
	SetSpeedThresholdBike(atof(F.Get("SpeedThresholdBike", "1.5").c_str()));
	SetSpeedThresholdPedestrian(atof(F.Get("SpeedThresholdPedestrian", "1").c_str()));
	SetSpeedThresholdCaching(atof(F.Get("SpeedThresholdCaching", "1").c_str()));
	SetSpeedThresholdMapping(atof(F.Get("SpeedThresholdMapping", "1").c_str()));
	// GPS receiver lag
	SetGPSReceiverLag(atoi(F.Get("GPSReceiverLag", "0").c_str()));
	// Watchdog
	SetWatchdogTimeout(Max(0, 1000*atoi(F.Get("WatchdogTimeout", "0").c_str())));
	// Font Sizes
	SetPOIFontSize(atoi(F.Get("POIFontSize", "16").c_str()));
	SetScaleFontSize(atoi(F.Get("ScaleFontSize", "16").c_str()));
	SetDebugFontSize(atoi(F.Get("DebugFontSize", "16").c_str()));
	return true;
}

//-------------------------------------
CXStringASCII CXOptions::GetStartPath() const {
	CXReadLocker RL(&m_RWLock);
	return m_StartPath;
}

//-------------------------------------
void CXOptions::SetStartPath(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_StartPath = Value;
}

//-------------------------------------
CXSerialPortConfig CXOptions::GetSerialPortConfig() const {
	CXReadLocker RL(&m_RWLock);
	return m_SerialPortConfig;
}

//-------------------------------------
void CXOptions::SetSerialPortConfig(const CXSerialPortConfig & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_SerialPortConfig = Value;
}

//-------------------------------------
bool CXOptions::IsNorthing() const {
	CXReadLocker RL(&m_RWLock);
	return m_oNorthing;
}

//-------------------------------------
void CXOptions::SetNorthing(bool Value) {
	CXWriteLocker WL(&m_RWLock);
	m_oNorthing = Value;
}

//-------------------------------------
bool CXOptions::IsFullScreen() const {
	CXReadLocker RL(&m_RWLock);
	return m_oFullScreen;
}

//-------------------------------------
void CXOptions::SetFullScreen(bool Value) {
	CXWriteLocker WL(&m_RWLock);
	m_oFullScreen = Value;
}

//-------------------------------------
int CXOptions::GetInfoBarBottomHeight() const {
	CXReadLocker RL(&m_RWLock);
	return m_InfoBarBottomHeight;
}

//-------------------------------------
int CXOptions::GetInfoBarTopHeight() const {
	CXReadLocker RL(&m_RWLock);
	return m_InfoBarTopHeight;
}

//-------------------------------------
void CXOptions::SetInfoBarBottomHeight(int Value) {
	CXWriteLocker WL(&m_RWLock);
	m_InfoBarBottomHeight = Value;
}

//-------------------------------------
void CXOptions::SetInfoBarTopHeight(int Value) {
	CXWriteLocker WL(&m_RWLock);
	m_InfoBarTopHeight = Value;
}

//-------------------------------------
int CXOptions::GetInfoBarCommonWidth() const {
	CXReadLocker RL(&m_RWLock);
	return m_InfoBarCommonWidth;
}

//-------------------------------------
void CXOptions::SetInfoBarCommonWidth(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_InfoBarCommonWidth = NewValue;
}

//-------------------------------------
int CXOptions::GetInfoBarCommonHeight() const {
	CXReadLocker RL(&m_RWLock);
	return m_InfoBarCommonHeight;
}

//-------------------------------------
void CXOptions::SetInfoBarCommonHeight(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_InfoBarCommonHeight = NewValue;
}

//-------------------------------------
int CXOptions::GetMaxSpeedSize() const {
	CXReadLocker RL(&m_RWLock);
	return m_MaxSpeedSize;
}

//-------------------------------------
void CXOptions::SetMaxSpeedSize(int Value) {
	CXWriteLocker WL(&m_RWLock);
	m_MaxSpeedSize = Value;
}

//-------------------------------------
int CXOptions::GetCompassSize() const {
	CXReadLocker RL(&m_RWLock);
	return m_CompassSize;
}

//-------------------------------------
void CXOptions::SetCompassSize(int Value) {
	CXWriteLocker WL(&m_RWLock);
	m_CompassSize = Value;
}

//-------------------------------------
int CXOptions::GetScaleWidth() const {
	CXReadLocker RL(&m_RWLock);
	return m_ScaleWidth;
}

//-------------------------------------
void CXOptions::SetScaleWidth(int Value) {
	CXWriteLocker WL(&m_RWLock);
	m_ScaleWidth = Value;
}

//-------------------------------------
int CXOptions::GetScaleHeight() const {
	CXReadLocker RL(&m_RWLock);
	return m_ScaleHeight;
}

//-------------------------------------
void CXOptions::SetScaleHeight(int Value) {
	CXWriteLocker WL(&m_RWLock);
	m_ScaleHeight = Value;
}

//-------------------------------------
CXOptions::E_MODE CXOptions::GetMode() const {
	CXReadLocker RL(&m_RWLock);
	return m_eMode;
}

//-------------------------------------
void CXOptions::SetMode(E_MODE NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_eMode = NewValue;
}

//-------------------------------------
CXStringASCII CXOptions::GetDirectoryMaps() const {
	CXReadLocker RL(&m_RWLock);
	return m_DirectoryMaps;
}

//-------------------------------------
void CXOptions::SetDirectoryMaps(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_DirectoryMaps = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetDirectorySave() const {
	CXReadLocker RL(&m_RWLock);
	return m_DirectorySave;
}

//-------------------------------------
void CXOptions::SetDirectorySave(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_DirectorySave = Value;
}

//-------------------------------------
void CXOptions::SetDirectoryIcons(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_DirectoryIcons = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetDirectoryIcons() const {
	CXReadLocker RL(&m_RWLock);
	return m_DirectoryIcons;
}

//-------------------------------------
unsigned long CXOptions::GetLogoTime() const {
	CXReadLocker RL(&m_RWLock);
	return m_LogoTime;
}

//-------------------------------------
void CXOptions::SetLogoTime(unsigned long LogoTime) {
	CXWriteLocker WL(&m_RWLock);
	m_LogoTime = LogoTime;
}

//-------------------------------------
CXStringASCII CXOptions::GetLogoFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_LogoFileName;
}

//-------------------------------------
void CXOptions::SetLogoFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_LogoFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetInfoFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_InfoFileName;
}

//-------------------------------------
void CXOptions::SetInfoFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_InfoFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetQuitFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_QuitFileName;
}

//-------------------------------------
void CXOptions::SetQuitFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_QuitFileName = Value;
}

//-------------------------------------
bool CXOptions::MustShowMinimizeButton() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowMinimizeButton;
}

//-------------------------------------
void CXOptions::SetShowMinimizeButtonFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowMinimizeButton = NewValue;
}

//-------------------------------------
CXStringASCII CXOptions::GetMinimizeFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_MinimizeFileName;
}

//-------------------------------------
void CXOptions::SetMinimizeFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_MinimizeFileName = Value;
}

//-------------------------------------
bool CXOptions::MustShowPOIs() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowPOIs;
}

//-------------------------------------
void CXOptions::SetShowPOIsFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowPOIs = NewValue;
}

//-------------------------------------
bool CXOptions::MustSnapToWay() const {
	CXReadLocker RL(&m_RWLock);
	return m_oSnapToWay;
}

//-------------------------------------
void CXOptions::SetSnapToWayFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oSnapToWay = NewValue;
}

//-------------------------------------
bool CXOptions::MustStartWithLastPosition() const {
	CXReadLocker RL(&m_RWLock);
	return m_oStartWithLastPosition;
}

//-------------------------------------
void CXOptions::SetStartWithLastPositionFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oStartWithLastPosition = NewValue;
}

//-------------------------------------
bool CXOptions::IsMapMovingManually() const {
	CXReadLocker RL(&m_RWLock);
	return m_oMapMovingManually;
}

//-------------------------------------
void CXOptions::SetMapMovingManually(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oMapMovingManually = NewValue;
}

//-------------------------------------
int CXOptions::GetWatchdogTimeout() const {
	CXReadLocker RL(&m_RWLock);
	return m_WatchdogTimeout;
}

//-------------------------------------
void CXOptions::SetWatchdogTimeout(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_WatchdogTimeout = NewValue;
}

//-------------------------------------
CXStringASCII CXOptions::GetSaveOnFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_SavingOnFileName;
}

//-------------------------------------
void CXOptions::SetSaveOnFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_SavingOnFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetSaveOffFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_SavingOffFileName;
}

//-------------------------------------
void CXOptions::SetSaveOffFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_SavingOffFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetZoomInFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_ZoomInFileName;
}

//-------------------------------------
void CXOptions::SetZoomInFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_ZoomInFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetZoomOutFileName() const {
	CXReadLocker RL(&m_RWLock);
	return m_ZoomOutFileName;
}

//-------------------------------------
void CXOptions::SetZoomOutFileName(const CXStringASCII & Value) {
	CXWriteLocker WL(&m_RWLock);
	m_ZoomOutFileName = Value;
}

//-------------------------------------
bool CXOptions::IsSaving() const {
	CXReadLocker RL(&m_RWLock);
	return m_oSaving;
}

//-------------------------------------
void CXOptions::ToggleSaving() {
	CXWriteLocker WL(&m_RWLock);
	m_oSaving = ! m_oSaving;
}

//-------------------------------------
void CXOptions::SetShowLogoFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowLogo = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowLogo() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowLogo;
}

//-------------------------------------
bool CXOptions::MustShowZoomButtons() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowZoomButtons;
}

//-------------------------------------
void CXOptions::SetShowZoomButtonsFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowZoomButtons = NewValue;
}

//-------------------------------------
bool CXOptions::AutomaticZoom() const {
	CXReadLocker RL(&m_RWLock);
	return m_oAutomaticZoom;
}

//-------------------------------------
void CXOptions::SetAutomaticZoomFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oAutomaticZoom = NewValue;
}

//-------------------------------------
CXStringASCII CXOptions::GetAutomaticZoomString() const {
	CXReadLocker RL(&m_RWLock);
	return m_AutomaticZoomString;
}

//-------------------------------------
void CXOptions::SetAutomaticZoomString(const CXStringASCII & NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_AutomaticZoomString = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowMaxSpeed() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowMaxSpeed;
}

//-------------------------------------
void CXOptions::SetShowMaxSpeedFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowMaxSpeed = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowCompass() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowCompass;
}

//-------------------------------------
void CXOptions::SetShowCompassFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowCompass = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowScale() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowScale;
}

//-------------------------------------
void CXOptions::SetShowScaleFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowScale = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowTrackLog() const {
	CXReadLocker RL(&m_RWLock);
	return m_oShowTrackLog;
}

//-------------------------------------
void CXOptions::SetShowTrackLogFlag(bool NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_oShowTrackLog = NewValue;
}

//-------------------------------------
size_t CXOptions::GetTrackLogSize() const {
	CXReadLocker RL(&m_RWLock);
	return m_TrackLogSize;
}

//-------------------------------------
void CXOptions::SetTrackLogSize(size_t NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_TrackLogSize = NewValue;
}

//-------------------------------------
unsigned int CXOptions::GetTrackLogMinDist() const {
	CXReadLocker RL(&m_RWLock);
	return m_TrackLogMinDist;
}

//-------------------------------------
void CXOptions::SetTrackLogMinDist(unsigned int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_TrackLogMinDist = NewValue;
}

//-------------------------------------
t_uint64 CXOptions::GetOSMValiFlags() const {
	CXReadLocker RL(&m_RWLock);
	return m_OSMVali;
}

//-------------------------------------
bool CXOptions::IsOSMValiFlagSet(E_OSM_VALI eFlag) const {
	CXReadLocker RL(&m_RWLock);
	return (m_OSMVali & eFlag) != 0;
}

//-------------------------------------
void CXOptions::SetOSMValiFlag(E_OSM_VALI eFlag) {
	CXWriteLocker WL(&m_RWLock);
	m_OSMVali |= eFlag;
}

//-------------------------------------
void CXOptions::ClearOSMValiFlag(E_OSM_VALI eFlag) {
	CXWriteLocker WL(&m_RWLock);
	m_OSMVali &= ~eFlag;
}

//-------------------------------------
bool CXOptions::IsDebugInfoFlagSet(E_DEBUGINFO eFlag) const {
	CXReadLocker RL(&m_RWLock);
	return (m_DebugInfo & eFlag) != 0;
}

//-------------------------------------
void CXOptions::SetDebugInfoFlag(E_DEBUGINFO eFlag) {
	CXWriteLocker WL(&m_RWLock);
	m_DebugInfo |= eFlag;
}

//-------------------------------------
void CXOptions::ClearDebugInfoFlag(E_DEBUGINFO eFlag) {
	CXWriteLocker WL(&m_RWLock);
	m_DebugInfo &= ~eFlag;
}

//-------------------------------------
double CXOptions::GetSpeedThresholdCar() const {
	CXReadLocker RL(&m_RWLock);
	return m_SpeedThresholdCar;
}

//-------------------------------------
void CXOptions::SetSpeedThresholdCar(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_SpeedThresholdCar = NewValue;
}

//-------------------------------------
double CXOptions::GetSpeedThresholdBike() const {
	CXReadLocker RL(&m_RWLock);
	return m_SpeedThresholdBike;
}

//-------------------------------------
void CXOptions::SetSpeedThresholdBike(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_SpeedThresholdBike = NewValue;
}

//-------------------------------------
double CXOptions::GetSpeedThresholdPedestrian() const {
	CXReadLocker RL(&m_RWLock);
	return m_SpeedThresholdPedestrian;
}

//-------------------------------------
void CXOptions::SetSpeedThresholdPedestrian(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_SpeedThresholdPedestrian = NewValue;
}

//-------------------------------------
double CXOptions::GetSpeedThresholdCaching() const {
	CXReadLocker RL(&m_RWLock);
	return m_SpeedThresholdCaching;
}

//-------------------------------------
void CXOptions::SetSpeedThresholdCaching(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_SpeedThresholdCaching = NewValue;
}

//-------------------------------------
double CXOptions::GetSpeedThresholdMapping() const {
	CXReadLocker RL(&m_RWLock);
	return m_SpeedThresholdMapping;
}

//-------------------------------------
void CXOptions::SetSpeedThresholdMapping(double NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_SpeedThresholdMapping = NewValue;
}

//-------------------------------------
int CXOptions::GetGPSReceiverLag() const {
	CXReadLocker RL(&m_RWLock);
	return m_GPSReceiverLag;
}

//-------------------------------------
void CXOptions::SetGPSReceiverLag(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_GPSReceiverLag = NewValue;
}

//-------------------------------------
E_ZOOM_LEVEL CXOptions::GetZoomLevel() const {
	CXReadLocker RL(&m_RWLock);
	return m_ZoomLevel;
}

//-------------------------------------
void CXOptions::SetZoomLevel(E_ZOOM_LEVEL NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_ZoomLevel = NewValue;
}

//-------------------------------------
int CXOptions::GetPOIFontSize() const {
	CXReadLocker RL(&m_RWLock);
	return m_POIFontSize;
}

//-------------------------------------
void CXOptions::SetPOIFontSize(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_POIFontSize = NewValue;
}

//-------------------------------------
int CXOptions::GetScaleFontSize() const {
	CXReadLocker RL(&m_RWLock);
	return m_ScaleFontSize;
}

//-------------------------------------
void CXOptions::SetScaleFontSize(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_ScaleFontSize = NewValue;
}

//-------------------------------------
int CXOptions::GetDebugFontSize() const {
	CXReadLocker RL(&m_RWLock);
	return m_DebugFontSize;
}

//-------------------------------------
void CXOptions::SetDebugFontSize(int NewValue) {
	CXWriteLocker WL(&m_RWLock);
	m_DebugFontSize = NewValue;
}
