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

	for(size_t i=0; i<e_Way_EnumCount; i++) {
		m_Pens.Append(new CXPens());
	}
		
	CXPens *pPens = NULL;

	// now create pens
	// Mapnik
	pPens = m_Pens[e_Way_Fading];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xB0, 0xB0, 0xB0));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Way_Unknown];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Way_Motorway];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));

	pPens = m_Pens[e_Way_MotorwayLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));

	pPens = m_Pens[e_Way_Trunk];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));

	pPens = m_Pens[e_Way_TrunkLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));

	pPens = m_Pens[e_Way_Primary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x60, 0x70));

	pPens = m_Pens[e_Way_PrimaryLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x6C, 0x70));

	pPens = m_Pens[e_Way_Secondary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xA5, 0x7D, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFC, 0xBE, 0x6E));

	pPens = m_Pens[e_Way_Tertiary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xCB));

	pPens = m_Pens[e_Way_Unclassified];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xDD));

	pPens = m_Pens[e_Way_Track];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 2, CXRGB(0xD7, 0x93, 0x31));

	pPens = m_Pens[e_Way_Residential];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xFE));

	pPens = m_Pens[e_Way_Service];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xE0, 0xE0, 0xE0));

	pPens = m_Pens[e_Way_Bridleway];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Way_Cycleway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x80, 0x00));

	pPens = m_Pens[e_Way_Footway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xD7, 0x93, 0x31));

	pPens = m_Pens[e_Way_Pedestrian];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Way_Steps];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[e_Way_LivingStreet];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xD0, 0xD0, 0xD0));
	
	pPens = m_Pens[e_Way_NationalBorder];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 9, CXRGB(0xDD, 0x00, 0x00));
	
	for(size_t j=0; j<e_Way_EnumCount; j++) {
		m_ScaledPens.Append(new CXPens(*m_Pens[j]));
	}
}

//-------------------------------------
void CXPenHolder::DestroyPens() {
	for(size_t i=0; i<e_Way_EnumCount; i++) {
		CXPens *pPens = m_Pens[i];
		delete pPens;
		pPens = m_ScaledPens[i];
		delete pPens;
	}
	m_Pens.Clear();
	m_ScaledPens.Clear();
}

//-------------------------------------
CXPen *CXPenHolder::GetPenBg(E_WAY_TYPE eWayType) {
	CXPen *Result = m_Pens[eWayType]->m_pBg;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetPenFg(E_WAY_TYPE eWayType) {
	CXPen *Result = m_Pens[eWayType]->m_pSegm;
	return Result;
}

//-------------------------------------
void CXPenHolder::ScalePens(double ScaleFactor) {
	for(size_t i=0; i<e_Way_EnumCount; i++) {
		CXPens *pPens = m_Pens[i];
		CXPens *pScaledPens = m_ScaledPens[i];
		if(ScaleFactor > 1) {
			// scale
			if(pPens->m_pBg != NULL) {
				// try to make background only 2 pixel wider than segment,
				// so that border is only 1 pixel
				int BgWidth = static_cast<int>(ScaleFactor*pPens->m_pBg->GetWidth());
				int SegmWidth = Max(0, BgWidth -2);
				pScaledPens->m_pBg->SetWidth(BgWidth);
				if(pPens->m_pSegm != NULL)
					pScaledPens->m_pSegm->SetWidth(SegmWidth);
			} else {
				// no background width, scale segment width accordingly
				if(pPens->m_pSegm != NULL)
					pScaledPens->m_pSegm->SetWidth(static_cast<int>(ScaleFactor*m_Pens[i]->m_pSegm->GetWidth()));
			}
		} else {
			// do not scale. take default widths
			if(pPens->m_pBg != NULL)
				pScaledPens->m_pBg->SetWidth(pPens->m_pBg->GetWidth());
			if(pPens->m_pSegm != NULL)
				pScaledPens->m_pSegm->SetWidth(pPens->m_pSegm->GetWidth());
		}
	}
}

//-------------------------------------
CXPen *CXPenHolder::GetScaledPenBg(E_WAY_TYPE eWayType) {
	CXPen *Result = m_ScaledPens[eWayType]->m_pBg;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetScaledPenFg(E_WAY_TYPE eWayType) {
	CXPen *Result = m_ScaledPens[eWayType]->m_pSegm;
	return Result;
}
