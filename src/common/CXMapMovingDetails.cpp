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

#include "CXMapMovingDetails.hpp"
#include "CXReadLocker.hpp"
#include "CXWriteLocker.hpp"

CXMapMovingDetails *CXMapMovingDetails::m_pInstance = NULL;     ///< oiu

//-------------------------------------
CXMapMovingDetails::CXMapMovingDetails() {
}

//-------------------------------------
CXMapMovingDetails::~CXMapMovingDetails() {
}

//-------------------------------------
CXMapMovingDetails *CXMapMovingDetails::Instance() {
    if(m_pInstance == NULL)
        m_pInstance = new CXMapMovingDetails();
    return m_pInstance;
}

//-------------------------------------
CXCoor CXMapMovingDetails::GetPosition() const {
    CXReadLocker RL(&m_RWLock);
    return m_Position;
}

//-------------------------------------
void CXMapMovingDetails::SetPosition(const CXCoor &NewValue) {
    CXWriteLocker WL(&m_RWLock);
    m_Position = NewValue;
}

//-------------------------------------
void CXMapMovingDetails::SetMatrix(const CXTransformationMatrix2D &Matrix) {
    CXWriteLocker WL(&m_RWLock);
    m_Matrix = Matrix;
}

//-------------------------------------
void CXMapMovingDetails::OffsetPosition(int OffsetPixelX, int OffsetPixelY) {
    CXWriteLocker WL(&m_RWLock);
    // compute inverse to TMMap
    CXTransformationMatrix2D Inv = m_Matrix.Inverse();

    CXCoorVector CurPos = m_Matrix*CXCoorVector(m_Position.GetUTMEasting(), m_Position.GetUTMNorthing());
    CXCoorVector NewPos(CurPos.GetX() + OffsetPixelX, CurPos.GetY() + OffsetPixelY);
    CXCoorVector NewCoor = Inv*NewPos;
    m_Position.OffsetCoor(NewCoor.GetX()-m_Position.GetUTMEasting(), NewCoor.GetY()-m_Position.GetUTMNorthing());
}
