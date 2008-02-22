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

#include "CXOptions.hpp"
#include "CXFileIni.hpp"
#include "CXMutexLocker.hpp"
#include "Utils.hpp"
#include <OSSpecific.hpp>

#include  <stdlib.h>

CXOptions * CXOptions::m_pInstance = NULL;

static const int TO = 2000;

//-------------------------------------
CXOptions::CXOptions() :
	m_oNorthing(false),
	m_oFullScreen(false),
	m_oShowLogo(true),
	m_oSaving(false),
	m_oShowZoomButtons(false),
	m_oShowMaxSpeed(true),
	m_oShowCompass(false),
	m_oShowTrackLog(false),
	m_oShowScale(false),
	m_OSMVali(0),
	m_DebugInfo(0),
	m_InfoBarBottomHeight(20),
	m_InfoBarTopHeight(20),
	m_MaxSpeedSize(61),
	m_CompassSize(50),
	m_TrackLogSize(0),
	m_TrackLogMinDist(10),
	m_ScaleWidth(100),
	m_ScaleHeight(5),
	m_LogoTime(5000)
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
CXStringASCII CXOptions::CreateAbsolutePath(const CXStringASCII & StartPath, const CXStringASCII &Path) {
	CXStringASCII Result;
	if((Path.GetSize() >= 1) && (Path[0] == PATHDELIMITER)) {
		// Path is an absolute path already. use it
		Result = Path;
	} else {
		// Path is a relative path. Append to StartPath.
		Result = StartPath;
		Result += Path;
	}
	// append PATHDELIMITER if neccessary
	if((Result.GetSize() > 0) && (Result[Result.GetSize()-1] != PATHDELIMITER)) {
		Result+=PATHDELIMITER;
	}
	return Result;
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
	// InfoBar Bottom Height
	SetInfoBarBottomHeight(atoi(F.Get("InfoBarBottomHeight", "20").c_str()));
	// InfoBar Top Height
	SetInfoBarTopHeight(atoi(F.Get("InfoBarTopHeight", "20").c_str()));
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
	// amenity
	CXStringASCII Amenity1=DirIcons;
	Amenity1+=F.Get("Amenity1Name", "amenity1.bmp");
	SetAmenity1FileName(Amenity1);
	return true;
}

//-------------------------------------
CXStringASCII CXOptions::GetStartPath() const {
	CXMutexLocker L(&m_Mutex);
	return m_StartPath;
}

//-------------------------------------
void CXOptions::SetStartPath(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_StartPath = Value;
}

//-------------------------------------
CXSerialPortConfig CXOptions::GetSerialPortConfig() const {
	CXMutexLocker L(&m_Mutex);
	return m_SerialPortConfig;
}

//-------------------------------------
void CXOptions::SetSerialPortConfig(const CXSerialPortConfig & Value) {
	CXMutexLocker L(&m_Mutex);
	m_SerialPortConfig = Value;
}

//-------------------------------------
bool CXOptions::IsNorthing() const {
	CXMutexLocker L(&m_Mutex);
	return m_oNorthing;
}

//-------------------------------------
void CXOptions::SetNorthing(bool Value) {
	CXMutexLocker L(&m_Mutex);
	m_oNorthing = Value;
}

//-------------------------------------
bool CXOptions::IsFullScreen() const {
	CXMutexLocker L(&m_Mutex);
	return m_oFullScreen;
}

//-------------------------------------
void CXOptions::SetFullScreen(bool Value) {
	CXMutexLocker L(&m_Mutex);
	m_oFullScreen = Value;
}

//-------------------------------------
int CXOptions::GetInfoBarBottomHeight() const {
	CXMutexLocker L(&m_Mutex);
	return m_InfoBarBottomHeight;
}

//-------------------------------------
int CXOptions::GetInfoBarTopHeight() const {
	CXMutexLocker L(&m_Mutex);
	return m_InfoBarTopHeight;
}

//-------------------------------------
void CXOptions::SetInfoBarBottomHeight(int Value) {
	CXMutexLocker L(&m_Mutex);
	m_InfoBarBottomHeight = Value;
}

//-------------------------------------
void CXOptions::SetInfoBarTopHeight(int Value) {
	CXMutexLocker L(&m_Mutex);
	m_InfoBarTopHeight = Value;
}

//-------------------------------------
int CXOptions::GetMaxSpeedSize() const {
	CXMutexLocker L(&m_Mutex);
	return m_MaxSpeedSize;
}

//-------------------------------------
void CXOptions::SetMaxSpeedSize(int Value) {
	CXMutexLocker L(&m_Mutex);
	m_MaxSpeedSize = Value;
}

//-------------------------------------
int CXOptions::GetCompassSize() const {
	CXMutexLocker L(&m_Mutex);
	return m_CompassSize;
}

//-------------------------------------
void CXOptions::SetCompassSize(int Value) {
	CXMutexLocker L(&m_Mutex);
	m_CompassSize = Value;
}

//-------------------------------------
int CXOptions::GetScaleWidth() const {
	CXMutexLocker L(&m_Mutex);
	return m_ScaleWidth;
}

//-------------------------------------
void CXOptions::SetScaleWidth(int Value) {
	CXMutexLocker L(&m_Mutex);
	m_ScaleWidth = Value;
}

//-------------------------------------
int CXOptions::GetScaleHeight() const {
	CXMutexLocker L(&m_Mutex);
	return m_ScaleHeight;
}

//-------------------------------------
void CXOptions::SetScaleHeight(int Value) {
	CXMutexLocker L(&m_Mutex);
	m_ScaleHeight = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetDirectoryMaps() const {
	CXMutexLocker L(&m_Mutex);
	return m_DirectoryMaps;
}

//-------------------------------------
void CXOptions::SetDirectoryMaps(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_DirectoryMaps = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetDirectorySave() const {
	CXMutexLocker L(&m_Mutex);
	return m_DirectorySave;
}

//-------------------------------------
void CXOptions::SetDirectorySave(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_DirectorySave = Value;
}

//-------------------------------------
void CXOptions::SetDirectoryIcons(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_DirectoryIcons = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetDirectoryIcons() const {
	CXMutexLocker L(&m_Mutex);
	return m_DirectoryIcons;
}

//-------------------------------------
unsigned long CXOptions::GetLogoTime() const {
	CXMutexLocker L(&m_Mutex);
	return m_LogoTime;
}

//-------------------------------------
void CXOptions::SetLogoTime(unsigned long LogoTime) {
	CXMutexLocker L(&m_Mutex);
	m_LogoTime = LogoTime;
}

//-------------------------------------
CXStringASCII CXOptions::GetLogoFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_LogoFileName;
}

//-------------------------------------
void CXOptions::SetLogoFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_LogoFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetInfoFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_InfoFileName;
}

//-------------------------------------
void CXOptions::SetInfoFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_InfoFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetQuitFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_QuitFileName;
}

//-------------------------------------
void CXOptions::SetQuitFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_QuitFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetSaveOnFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_SavingOnFileName;
}

//-------------------------------------
void CXOptions::SetSaveOnFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_SavingOnFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetSaveOffFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_SavingOffFileName;
}

//-------------------------------------
void CXOptions::SetSaveOffFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_SavingOffFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetZoomInFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_ZoomInFileName;
}

//-------------------------------------
void CXOptions::SetZoomInFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_ZoomInFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetZoomOutFileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_ZoomOutFileName;
}

//-------------------------------------
void CXOptions::SetZoomOutFileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_ZoomOutFileName = Value;
}

//-------------------------------------
CXStringASCII CXOptions::GetAmenity1FileName() const {
	CXMutexLocker L(&m_Mutex);
	return m_Amenity1FileName;
}

//-------------------------------------
void CXOptions::SetAmenity1FileName(const CXStringASCII & Value) {
	CXMutexLocker L(&m_Mutex);
	m_Amenity1FileName = Value;
}

//-------------------------------------
bool CXOptions::IsSaving() const {
	CXMutexLocker L(&m_Mutex);
	return m_oSaving;
}

//-------------------------------------
void CXOptions::ToggleSaving() {
	CXMutexLocker L(&m_Mutex);
	m_oSaving = ! m_oSaving;
}

//-------------------------------------
void CXOptions::SetShowLogoFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowLogo = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowLogo() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowLogo;
}

//-------------------------------------
bool CXOptions::MustShowZoomButtons() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowZoomButtons;
}

//-------------------------------------
void CXOptions::SetShowZoomButtonsFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowZoomButtons = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowMaxSpeed() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowMaxSpeed;
}

//-------------------------------------
void CXOptions::SetShowMaxSpeedFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowMaxSpeed = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowCompass() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowCompass;
}

//-------------------------------------
void CXOptions::SetShowCompassFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowCompass = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowScale() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowScale;
}

//-------------------------------------
void CXOptions::SetShowScaleFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowScale = NewValue;
}

//-------------------------------------
bool CXOptions::MustShowTrackLog() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowTrackLog;
}

//-------------------------------------
void CXOptions::SetShowTrackLogFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowTrackLog = NewValue;
}

//-------------------------------------
size_t CXOptions::GetTrackLogSize() const {
	CXMutexLocker L(&m_Mutex);
	return m_TrackLogSize;
}

//-------------------------------------
void CXOptions::SetTrackLogSize(size_t NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_TrackLogSize = NewValue;
}

//-------------------------------------
unsigned int CXOptions::GetTrackLogMinDist() const {
	CXMutexLocker L(&m_Mutex);
	return m_TrackLogMinDist;
}

//-------------------------------------
void CXOptions::SetTrackLogMinDist(unsigned int NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_TrackLogMinDist = NewValue;
}

//-------------------------------------
t_uint64 CXOptions::GetOSMValiFlags() const {
	CXMutexLocker L(&m_Mutex);
	return m_OSMVali;
}

//-------------------------------------
bool CXOptions::IsOSMValiFlagSet(E_OSM_VALI eFlag) const {
	CXMutexLocker L(&m_Mutex);
	return (m_OSMVali & eFlag) != 0;
}

//-------------------------------------
void CXOptions::SetOSMValiFlag(E_OSM_VALI eFlag) {
	CXMutexLocker L(&m_Mutex);
	m_OSMVali |= eFlag;
}

//-------------------------------------
void CXOptions::ClearOSMValiFlag(E_OSM_VALI eFlag) {
	CXMutexLocker L(&m_Mutex);
	m_OSMVali &= ~eFlag;
}

//-------------------------------------
bool CXOptions::IsDebugInfoFlagSet(E_DEBUGINFO eFlag) const {
	CXMutexLocker L(&m_Mutex);
	return (m_DebugInfo & eFlag) != 0;
}

//-------------------------------------
void CXOptions::SetDebugInfoFlag(E_DEBUGINFO eFlag) {
	CXMutexLocker L(&m_Mutex);
	m_DebugInfo |= eFlag;
}

//-------------------------------------
void CXOptions::ClearDebugInfoFlag(E_DEBUGINFO eFlag) {
	CXMutexLocker L(&m_Mutex);
	m_DebugInfo &= ~eFlag;
}
