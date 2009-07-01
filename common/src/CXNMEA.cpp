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

#include "CXNMEA.hpp"


//----------------------------------------------------------------------------
//-------------------------------------
CXGGAPacket::CXGGAPacket() :
	m_oFix(false),
	m_NSat(0),
	m_dLon(0),
	m_dLat(0),
	m_dHeight(0)
{
}

//-------------------------------------
CXGGAPacket::~CXGGAPacket() {
}

//-------------------------------------
CXStringASCII CXGGAPacket::GetUTC() const {
	return m_UTC;
}

//-------------------------------------
void CXGGAPacket::SetUTC(const CXStringASCII &NewValue) {
	m_UTC = NewValue;
}

//-------------------------------------
bool CXGGAPacket::HasFix() const {
	return m_oFix;
}

//-------------------------------------
void CXGGAPacket::SetFix(bool NewValue) {
	m_oFix = NewValue;
}

//-------------------------------------
int	CXGGAPacket::GetNSat() const {
	return m_NSat;
}

//-------------------------------------
void CXGGAPacket::SetNSat(int NewValue) {
	m_NSat = NewValue;
}

//-------------------------------------
double CXGGAPacket::GetHeight() const {
	return m_dHeight;
}

//-------------------------------------
void CXGGAPacket::SetHeight(double NewValue) {
	m_dHeight = NewValue;
}

//-------------------------------------
double CXGGAPacket::GetHDOP() const {
	return m_dHDOP;
}

//-------------------------------------
void CXGGAPacket::SetHDOP(double NewValue) {
	m_dHDOP = NewValue;
}

//-------------------------------------
double CXGGAPacket::GetLon() const {
	return m_dLon;
}

//-------------------------------------
void CXGGAPacket::SetLon(double NewValue) {
	m_dLon = NewValue;
}

//-------------------------------------
double CXGGAPacket::GetLat() const {
	return m_dLat;
}

//-------------------------------------
void CXGGAPacket::SetLat(double NewValue) {
	m_dLat = NewValue;
}


//----------------------------------------------------------------------------
//-------------------------------------
CXRMCPacket::CXRMCPacket() :
	m_oFix(false),
	m_dLon(0),
	m_dLat(0),
	m_dSpeed(0),
	m_dCourse(0)
{
}

//-------------------------------------
CXRMCPacket::~CXRMCPacket() {
}

//-------------------------------------
CXStringASCII CXRMCPacket::GetUTC() const {
	return m_UTC;
}

//-------------------------------------
void CXRMCPacket::SetUTC(const CXStringASCII &NewValue) {
	m_UTC = NewValue;
}

//-------------------------------------
bool CXRMCPacket::HasFix() const {
	return m_oFix;
}

//-------------------------------------
void CXRMCPacket::SetFix(bool NewValue) {
	m_oFix = NewValue;
}

//-------------------------------------
double CXRMCPacket::GetLon() const {
	return m_dLon;
}

//-------------------------------------
void CXRMCPacket::SetLon(double NewValue) {
	m_dLon = NewValue;
}

//-------------------------------------
double CXRMCPacket::GetLat() const {
	return m_dLat;
}

//-------------------------------------
void CXRMCPacket::SetLat(double NewValue) {
	m_dLat = NewValue;
}

//-------------------------------------
double CXRMCPacket::GetSpeed() const {
	return m_dSpeed;
}

//-------------------------------------
void CXRMCPacket::SetSpeed(double NewValue) {
	m_dSpeed = NewValue;
}

//-------------------------------------
double CXRMCPacket::GetCourse() const {
	return m_dCourse;
}

//-------------------------------------
void CXRMCPacket::SetCourse(double NewValue) {
	m_dCourse = NewValue;
}


//----------------------------------------------------------------------------
//-------------------------------------
CXGSAPacket::CXGSAPacket() :
	m_HDOP(0),
	m_VDOP(0)
{
}

//-------------------------------------
CXGSAPacket::~CXGSAPacket() {
}

//-------------------------------------
void CXGSAPacket::ClearSatellites() {
	m_Satellites.Clear();
}

//-------------------------------------
void CXGSAPacket::AddSatellite(int SatNr) {
	m_Satellites.Append(SatNr);
}

//-------------------------------------
const CXBuffer<int> & CXGSAPacket::GetSatellites() const {
	return m_Satellites;
}

//-------------------------------------
double CXGSAPacket::GetHDOP() const {
	return m_HDOP;
}

//-------------------------------------
void CXGSAPacket::SetHDOP(double NewValue) {
	m_HDOP = NewValue;
}

//-------------------------------------
double CXGSAPacket::GetVDOP() const {
	return m_VDOP;
}

//-------------------------------------
void CXGSAPacket::SetVDOP(double NewValue) {
	m_VDOP = NewValue;
}

//----------------------------------------------------------------------------
//-------------------------------------
CXGSVSatelliteInfo::CXGSVSatelliteInfo() :
	m_PRN(0),
	m_Elevation(0),
	m_Azimuth(0),
	m_SNR(0)
{
}

//-------------------------------------
CXGSVSatelliteInfo::CXGSVSatelliteInfo(const CXGSVSatelliteInfo &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXGSVSatelliteInfo::~CXGSVSatelliteInfo() {
}

//-------------------------------------
const CXGSVSatelliteInfo & CXGSVSatelliteInfo::operator = (const CXGSVSatelliteInfo &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXGSVSatelliteInfo::CopyFrom(const CXGSVSatelliteInfo &rOther) {
	m_PRN		= rOther.m_PRN;
	m_Elevation	= rOther.m_Elevation;
	m_Azimuth	= rOther.m_Azimuth;
	m_SNR		= rOther.m_SNR;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetPRN() const {
	return m_PRN;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetPRN(int NewValue) {
	m_PRN = NewValue;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetElevation() const {
	return m_Elevation;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetElevation(int NewValue) {
	m_Elevation = NewValue;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetAzimuth() const {
	return m_Azimuth;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetAzimuth(int NewValue) {
	m_Azimuth = NewValue;
}

//-------------------------------------
int CXGSVSatelliteInfo::GetSNR() const {
	return m_SNR;
}

//-------------------------------------
void CXGSVSatelliteInfo::SetSNR(int NewValue) {
	m_SNR = NewValue;
}


