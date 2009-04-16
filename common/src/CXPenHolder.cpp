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

#include "CXPenHolder.hpp"
#include "CXPen.hpp"

//-------------------------------------
CXPenHolder::CXPenHolder() {
	CreatePens();
}

//-------------------------------------
CXPenHolder::~CXPenHolder() {
	DestroyPens();
}

//-------------------------------------
void CXPenHolder::CreatePens() {

	for(size_t i=0; i<e_Highway_EnumCount; i++) {
		m_Pens.Append(new CXPens());
	}
		
	CXPens *pPens = NULL;

	// now create pens
	// Mapnik
	pPens = m_Pens[e_Highway_Fading];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xB0, 0xB0, 0xB0));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Highway_Unknown];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Highway_Motorway];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));

	pPens = m_Pens[e_Highway_MotorwayLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));

	pPens = m_Pens[e_Highway_Trunk];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));

	pPens = m_Pens[e_Highway_TrunkLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));

	pPens = m_Pens[e_Highway_Primary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x60, 0x70));

	pPens = m_Pens[e_Highway_PrimaryLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x6C, 0x70));

	pPens = m_Pens[e_Highway_Secondary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xA5, 0x7D, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFC, 0xBE, 0x6E));

	pPens = m_Pens[e_Highway_Tertiary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xCB));

	pPens = m_Pens[e_Highway_Unclassified];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xDD));

	pPens = m_Pens[e_Highway_Track];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 2, CXRGB(0xD7, 0x93, 0x31));

	pPens = m_Pens[e_Highway_Residential];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xFE));

	pPens = m_Pens[e_Highway_Service];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE0, 0xE0, 0xE0));

	pPens = m_Pens[e_Highway_Bridleway];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Highway_Cycleway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x80, 0x00));

	pPens = m_Pens[e_Highway_Footway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xD7, 0x93, 0x31));

	pPens = m_Pens[e_Highway_Pedestrian];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Highway_Steps];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Highway_LivingStreet];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xFE));
	
	for(size_t i=0; i<e_Highway_EnumCount; i++) {
		m_ScaledPens.Append(new CXPens(*m_Pens[i]));
	}
}

//-------------------------------------
void CXPenHolder::DestroyPens() {
	for(size_t i=0; i<e_Highway_EnumCount; i++) {
		CXPens *pPens = m_Pens[i];
		delete pPens;
		pPens = m_ScaledPens[i];
		delete pPens;
	}
	m_Pens.Clear();
	m_ScaledPens.Clear();
}

//-------------------------------------
CXPen *CXPenHolder::GetPenBg(E_KEYHIGHWAY_TYPE HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pBg;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetPenFg(E_KEYHIGHWAY_TYPE HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pSegm;
	return Result;
}

//-------------------------------------
void CXPenHolder::ScalePens(double ScaleFactor) {
	for(size_t i=0; i<e_Highway_EnumCount; i++) {
		CXPens *pPens = m_Pens[i];
		CXPens *pScaledPens = m_ScaledPens[i];
		if(ScaleFactor > 1) {
			// scale
			if(pPens->m_pBg != NULL)
				pScaledPens->m_pBg->SetWidth(static_cast<int>(ScaleFactor*pPens->m_pBg->GetWidth()));
			if(pPens->m_pSegm != NULL)
				pScaledPens->m_pSegm->SetWidth(static_cast<int>(ScaleFactor*m_Pens[i]->m_pSegm->GetWidth()));
		} else {
			// do not scale
			if(pPens->m_pBg != NULL)
				pScaledPens->m_pBg->SetWidth(pPens->m_pBg->GetWidth());
			if(pPens->m_pSegm != NULL)
				pScaledPens->m_pSegm->SetWidth(pPens->m_pSegm->GetWidth());
		}
	}
}

//-------------------------------------
CXPen *CXPenHolder::GetScaledPenBg(E_KEYHIGHWAY_TYPE HighwayType) {
	CXPen *Result = m_ScaledPens[HighwayType]->m_pBg;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetScaledPenFg(E_KEYHIGHWAY_TYPE HighwayType) {
	CXPen *Result = m_ScaledPens[HighwayType]->m_pSegm;
	return Result;
}
