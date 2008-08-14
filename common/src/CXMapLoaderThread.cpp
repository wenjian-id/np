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

#include "CXMapLoaderThread.hpp"
#include "CXMutexLocker.hpp"

//-------------------------------------
CXMapLoaderThread::CXMapLoaderThread() {
}

//-------------------------------------
CXMapLoaderThread::~CXMapLoaderThread() {
	for(size_t i=0; i<m_TOCDescrBuffer.GetSize(); i++)
		delete m_TOCDescrBuffer[i];
}

//-------------------------------------
void CXMapLoaderThread::OnThreadStarted() {
	// nothing to do
}

//-------------------------------------
void CXMapLoaderThread::OnThreadStopped() {
	// nothing to do
}

//-------------------------------------
void CXMapLoaderThread::OnWorkFunc() {
	bool oFurtherWork = false;
	bool oLoadTOC = false;
	CXTOCDescr *pTOCDescr = NULL;
	TTOCMapContainerPtr TOC;
	{
		CXMutexLocker L(&m_Mutex);
		if(m_TOCMapContainerArray.GetSize() != 0) {
			oLoadTOC = true;
			TOC = m_TOCMapContainerArray[0];
			pTOCDescr = m_TOCDescrBuffer[0];
			m_TOCMapContainerArray.RemoveAt(0);
			m_TOCDescrBuffer.RemoveAt(0);
		}
	}
	if(oLoadTOC) {
		TOC.GetPtr()->Load(pTOCDescr->m_FileName, pTOCDescr->m_ZoomLevel, pTOCDescr->m_Key);
		delete pTOCDescr;
	}
	bool oLoadSection = false;
	TMapSectionPtr MS;
	{
		CXMutexLocker L(&m_Mutex);
		if(m_MapSectionArray.GetSize() != 0) {
			oLoadSection = true;
			MS = m_MapSectionArray[0];
			m_MapSectionArray.RemoveAt(0);
		}
	}
	if(oLoadSection) {
		MS.GetPtr()->LoadMap();
	}
	{
		CXMutexLocker L(&m_Mutex);
		if(m_TOCMapContainerArray.GetSize() != 0)
			oFurtherWork = true;
		if(m_MapSectionArray.GetSize() != 0)
			oFurtherWork = true;
	}
	if(oFurtherWork)
		RequestWork();
}

//-------------------------------------
void CXMapLoaderThread::LoadTOCMapContainer(TTOCMapContainerPtr &TOCMapContainer, const CXStringASCII & FileName, unsigned char ZoomLevel, t_uint32 Key) {
	CXMutexLocker L(&m_Mutex);
	if(TOCMapContainer.GetPtr()->GetLoadStatus() != e_LSNotLoaded)
		return;
	TOCMapContainer.GetPtr()->SetLoadStatus(e_LSInList);
	m_TOCMapContainerArray.Append(TOCMapContainer);
	m_TOCDescrBuffer.Append(new CXTOCDescr(FileName, ZoomLevel, Key));
	RequestWork();
}

//-------------------------------------
void CXMapLoaderThread::LoadMapSection(TMapSectionPtr &MapSection) {
	CXMutexLocker L(&m_Mutex);
	if(MapSection.GetPtr()->GetLoadStatus() != e_LSNotLoaded)
		return;
	MapSection.GetPtr()->SetLoadStatus(e_LSInList);
	m_MapSectionArray.Append(MapSection);
	CXTOCMapSection *pTOC = MapSection.GetPtr()->GetTOC().GetPtr();
	RequestWork();
}
