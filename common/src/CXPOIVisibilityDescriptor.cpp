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

#include "CXPOIVisibilityDescriptor.hpp"

//-------------------------------------
CXPOIVisibilityDescriptor::CXPOIVisibilityDescriptor() :
	m_oShowAll(false),
	m_oShowParking(false),
	m_oShowFuel(false),
	m_oShowTrafficSignals(false),
	m_oShowAmenities(false),
	m_oShowPublicTransport(false),
	m_oShowFoodDrink(false),
	m_oShowAccomodation(false),
	m_oShowChurches(false),
	m_oShowOther(false)
{
}

//-------------------------------------
CXPOIVisibilityDescriptor::CXPOIVisibilityDescriptor(const CXPOIVisibilityDescriptor &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXPOIVisibilityDescriptor::~CXPOIVisibilityDescriptor() {
}

//-------------------------------------
const CXPOIVisibilityDescriptor & CXPOIVisibilityDescriptor::operator = (const CXPOIVisibilityDescriptor &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::CopyFrom(const CXPOIVisibilityDescriptor &rOther) {
	m_oShowAll = rOther.m_oShowAll;
	m_oShowParking = rOther.m_oShowParking;
	m_oShowFuel = rOther.m_oShowFuel;
	m_oShowTrafficSignals = rOther.m_oShowTrafficSignals;
	m_oShowAmenities = rOther.m_oShowAmenities;
	m_oShowPublicTransport = rOther.m_oShowPublicTransport;
	m_oShowFoodDrink = rOther.m_oShowFoodDrink;
	m_oShowAccomodation = rOther.m_oShowAccomodation;
	m_oShowChurches = rOther.m_oShowChurches;
	m_oShowOther = rOther.m_oShowOther;
}

//-------------------------------------
bool CXPOIVisibilityDescriptor::MustShowAll() const {
	return m_oShowAll;
}

//-------------------------------------
bool CXPOIVisibilityDescriptor::MustShowPOIType(E_POI_TYPE ePOIType) const {
	if((ePOIType == e_POI_None) || (ePOIType == e_POI_All))
		return false;
	bool oVisible = false;
	switch(ePOIType) {
		// parking
		case e_POI_Parking:					oVisible = m_oShowParking; break;
		// fuel
		case e_POI_Fuel:					oVisible = m_oShowFuel; break;
		// traffic signals
		case e_POI_TrafficSignals:
		case e_POI_MotorwayJunction:
		case e_POI_Stop:
		case e_POI_Crossing:
		case e_POI_LevelCrossing:			oVisible = m_oShowTrafficSignals; break;

		// amenities
		case e_POI_Pharmacy:
		case e_POI_Hospital:
		case e_POI_Supermarket:
		case e_POI_FireStation:
		case e_POI_Police:
		case e_POI_School:
		case e_POI_PostOffice:
		case e_POI_Telephone:
		case e_POI_PostBox:
		case e_POI_Toilets:					oVisible = m_oShowAmenities; break;

		// public transport
		case e_POI_BusStop:
		case e_POI_BusStation:
		case e_POI_RailwayStation:
		case e_POI_RailwayHalt:
		case e_POI_TramStop:
		case e_POI_SubwayEntrance:
		case e_POI_Taxi:
		case e_POI_Aerodrome:
		case e_POI_Helipad:					oVisible = m_oShowPublicTransport; break;

		// food / drink
		case e_POI_Restaurant:
		case e_POI_Pub:						oVisible = m_oShowFoodDrink; break;

		// accomodation
		case e_POI_Hotel:
		case e_POI_Hostel:
		case e_POI_CampSite:				oVisible = m_oShowAccomodation; break;

		// church
		case e_POI_PlcOfWrshp_Christian:
		case e_POI_PlcOfWrshp_Jewish:
		case e_POI_PlcOfWrshp_Muslim:
		case e_POI_PlcOfWrshp_Hindu:
		case e_POI_PlcOfWrshp_Buddhist:
		case e_POI_PlcOfWrshp_Shinto:
		case e_POI_PlcOfWrshp_Taoist:
		case e_POI_PlcOfWrshp_Unknown:		oVisible = m_oShowChurches; break;

		// other
		case e_POI_PowerTower:
		case e_POI_PowerSubStation:			oVisible = m_oShowOther; break;

		case e_POI_EnumCount:
		case e_POI_None:
		case e_POI_All:						break;
	}
	return oVisible;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowAll(bool NewValue) {
	m_oShowAll = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowParking(bool NewValue) {
	m_oShowParking = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowFuel(bool NewValue) {
	m_oShowFuel = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowTrafficSignals(bool NewValue) {
	m_oShowTrafficSignals = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowAmenities(bool NewValue) {
	m_oShowAmenities = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowPublicTransport(bool NewValue) {
	m_oShowPublicTransport = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowFoodDrink(bool NewValue) {
	m_oShowFoodDrink = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowAccomodation(bool NewValue) {
	m_oShowAccomodation = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowChurches(bool NewValue){
	m_oShowChurches = NewValue;
}

//-------------------------------------
void CXPOIVisibilityDescriptor::SetShowOther(bool NewValue) {
	m_oShowOther = NewValue;
}
