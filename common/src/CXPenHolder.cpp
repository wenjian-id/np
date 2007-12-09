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

	for(size_t i=0; i<CXWay::eEnumCount; i++) {
		m_Pens.Append(new SPens());
	}
		
	SPens *pPens = NULL;

	// now create pens
	// Mapnik
	pPens = m_Pens[CXWay::eUnknown];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[CXWay::eMotorway];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));

	pPens = m_Pens[CXWay::eMotorwayLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x50, 0x60, 0x76));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x80, 0x9B, 0xC0));

	pPens = m_Pens[CXWay::eTrunk];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));

	pPens = m_Pens[CXWay::eTrunkLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 7, CXRGB(0x47, 0x71, 0x47));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x7E, 0xC8, 0x7E));

	pPens = m_Pens[CXWay::ePrimary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x60, 0x70));

	pPens = m_Pens[CXWay::ePrimaryLink];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0x92, 0x46, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE3, 0x6C, 0x70));

	pPens = m_Pens[CXWay::eSecondary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xA5, 0x7D, 0x49));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFC, 0xBE, 0x6E));

	pPens = m_Pens[CXWay::eTertiary];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xCB));

	pPens = m_Pens[CXWay::eUnclassified];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xDD));

	pPens = m_Pens[CXWay::eTrack];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 2, CXRGB(0xF9, 0x80, 0x72));

	pPens = m_Pens[CXWay::eResidential];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xFE, 0xFE, 0xFE));

	pPens = m_Pens[CXWay::eService];
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 5, CXRGB(0xAA, 0xAA, 0xAA));
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 3, CXRGB(0xE0, 0xE0, 0xE0));

	pPens = m_Pens[CXWay::eBridleway];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[CXWay::eCycleway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x80, 0x00));

	pPens = m_Pens[CXWay::eFootway];
	pPens->m_pBg		= NULL;
	pPens->m_pSegm		= new CXPen(CXPen::e_Solid, 1, CXRGB(0xF9, 0x80, 0x72));

	pPens = m_Pens[CXWay::ePedestrian];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;

	pPens = m_Pens[CXWay::eSteps];
	/// \todo implement
	pPens->m_pBg		= new CXPen(CXPen::e_Solid, 1, CXRGB(0x00, 0x00, 0x00));
	pPens->m_pSegm		= NULL;
}

//-------------------------------------
void CXPenHolder::DestroyPens() {
	for(size_t i=0; i<CXWay::eEnumCount; i++) {
		SPens *pPens = m_Pens[i];
		delete pPens->m_pBg;
		delete pPens->m_pSegm;
		delete pPens;
	}
	m_Pens.Clear();
}

//-------------------------------------
CXPen *CXPenHolder::GetPenBg(CXWay::E_KEYHIGHWAY HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pBg;
	return Result;
}

//-------------------------------------
CXPen *CXPenHolder::GetPenFg(CXWay::E_KEYHIGHWAY HighwayType) {
	CXPen *Result = m_Pens[HighwayType]->m_pSegm;
	return Result;
}

