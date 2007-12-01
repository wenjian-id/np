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
	m_InfoBarBottomHeight(20),
	m_InfoBarTopHeight(20),
	m_MaxSpeedSize(61),
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
	// MaxSpeed
	SetShowMaxSpeedFlag(F.Get("ShowMaxSpeed", "on").ToUpper() == "ON");
	// InfoBar Bottom Height
	SetInfoBarBottomHeight(atoi(F.Get("InfoBarBottomHeight", "20").c_str()));
	// InfoBar Top Height
	SetInfoBarTopHeight(atoi(F.Get("InfoBarTopHeight", "20").c_str()));
	// MaxSpeed size
	SetMaxSpeedSize(atoi(F.Get("MaxSpeedSize", "61").c_str()));
	// maps directory
	CXStringASCII DirMaps=m_StartPath;
	DirMaps+=F.Get("DirectoryMaps", "Maps");
	if((DirMaps.GetSize() > 0) && (DirMaps[DirMaps.GetSize()-1] != PATHDELIMITER)) {
		DirMaps+=PATHDELIMITER;
	}
	SetDirectoryMaps(DirMaps);
	// Save directory
	CXStringASCII DirSave=m_StartPath;
	DirSave+=F.Get("DirectorySave", "Save");
	if((DirSave.GetSize() > 0) && (DirSave[DirSave.GetSize()-1] != PATHDELIMITER)) {
		DirSave+=PATHDELIMITER;
	}
	SetDirectorySave(DirSave);
	// Icons directory
	CXStringASCII DirIcons=m_StartPath;
	DirIcons+=F.Get("DirectoryIcons", "Icons");
	if((DirIcons.GetSize() > 0) && (DirIcons[DirIcons.GetSize()-1] != PATHDELIMITER)) {
		DirIcons+=PATHDELIMITER;
	}
	SetDirectoryIcons(DirIcons);
	// logo
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
bool CXOptions::Northing() const {
	CXMutexLocker L(&m_Mutex);
	return m_oNorthing;
}

//-------------------------------------
void CXOptions::SetNorthing(bool Value) {
	CXMutexLocker L(&m_Mutex);
	m_oNorthing = Value;
}

//-------------------------------------
bool CXOptions::FullScreen() const {
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
void CXOptions::ClearShowLogoFlag() {
	CXMutexLocker L(&m_Mutex);
	m_oShowLogo = false;
}

//-------------------------------------
void CXOptions::SetShowLogoFlag() {
	CXMutexLocker L(&m_Mutex);
	m_oShowLogo = true;
}

//-------------------------------------
bool CXOptions::ShowLogo() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowLogo;
}

//-------------------------------------
bool CXOptions::ShowZoomButtons() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowZoomButtons;
}

//-------------------------------------
void CXOptions::SetShowZoomButtonsFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowZoomButtons = NewValue;
}

//-------------------------------------
bool CXOptions::ShowMaxSpeed() const {
	CXMutexLocker L(&m_Mutex);
	return m_oShowMaxSpeed;
}

//-------------------------------------
void CXOptions::SetShowMaxSpeedFlag(bool NewValue) {
	CXMutexLocker L(&m_Mutex);
	m_oShowMaxSpeed = NewValue;
}
