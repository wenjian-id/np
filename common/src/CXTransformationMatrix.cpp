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

#include "CXTransformationMatrix.hpp"

#include <math.h>

//---------------------------------------------------------------------
//-------------------------------------
CXCoorVector::CXCoorVector() :
	m_x(0),	m_y(0)
{
}

//-------------------------------------
CXCoorVector::CXCoorVector(double x, double y) :
	m_x(x), m_y(y)
{
}

//-------------------------------------
CXCoorVector::CXCoorVector(const CXCoorVector & rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXCoorVector::~CXCoorVector() {
}

//-------------------------------------
const CXCoorVector & CXCoorVector::operator = (const CXCoorVector &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXCoorVector::CopyFrom(const CXCoorVector &rOther) {
	m_x = rOther.m_x;
	m_y = rOther.m_y;
}

//-------------------------------------
double CXCoorVector::GetX() const {
	return m_x;
}

//-------------------------------------
double CXCoorVector::GetY() const {
	return m_y;
}

//-------------------------------------
int CXCoorVector::GetIntX() const {
	return static_cast<int>(m_x);
}

//-------------------------------------
int CXCoorVector::GetIntY() const {
	return static_cast<int>(m_y);
}


//---------------------------------------------------------------------
//-------------------------------------
CXTransformationMatrix2D::CXTransformationMatrix2D() :
	m_a11(1), m_a12(0), m_a13(0),
	m_a21(0), m_a22(1), m_a23(0),
	m_a31(0), m_a32(0), m_a33(1)
{
}

//-------------------------------------
CXTransformationMatrix2D::CXTransformationMatrix2D(	double a11, double a12, double a13, 
													double a21, double a22, double a23, 
													double a31, double a32, double a33) :
	m_a11(a11), m_a12(a12), m_a13(a13),
	m_a21(a21), m_a22(a22), m_a23(a23),
	m_a31(a31), m_a32(a32), m_a33(a33)
{
}

//-------------------------------------
CXTransformationMatrix2D::CXTransformationMatrix2D(const CXTransformationMatrix2D &rOther) {
	CopyFrom(rOther);
}

//-------------------------------------
CXTransformationMatrix2D::~CXTransformationMatrix2D() {
}

//-------------------------------------
const CXTransformationMatrix2D & CXTransformationMatrix2D::operator = (const CXTransformationMatrix2D &rOther) {
	if(this != &rOther)
		CopyFrom(rOther);
	return *this;
}

//-------------------------------------
void CXTransformationMatrix2D::CopyFrom(const CXTransformationMatrix2D &rOther) {
	m_a11 = rOther.m_a11;
	m_a12 = rOther.m_a12;
	m_a13 = rOther.m_a13;
	m_a21 = rOther.m_a21;
	m_a22 = rOther.m_a22;
	m_a23 = rOther.m_a23;
	m_a31 = rOther.m_a31;
	m_a32 = rOther.m_a32;
	m_a33 = rOther.m_a33;
}

//-------------------------------------
CXCoorVector CXTransformationMatrix2D::operator * (const CXCoorVector &Value) const {
	double x = Value.GetX();
	double y = Value.GetY();
	return CXCoorVector(m_a11*x + m_a12*y + m_a13, m_a21*x + m_a22*y + m_a23);
}

//-------------------------------------
void CXTransformationMatrix2D::Multiply(const CXTransformationMatrix2D &rOther) {
	double a11 = m_a11*rOther.m_a11 + m_a12*rOther.m_a21 + m_a13*rOther.m_a31;
	double a12 = m_a11*rOther.m_a12 + m_a12*rOther.m_a22 + m_a13*rOther.m_a32;
	double a13 = m_a11*rOther.m_a13 + m_a12*rOther.m_a23 + m_a13*rOther.m_a33;
	double a21 = m_a21*rOther.m_a11 + m_a22*rOther.m_a21 + m_a23*rOther.m_a31;
	double a22 = m_a21*rOther.m_a12 + m_a22*rOther.m_a22 + m_a23*rOther.m_a32;
	double a23 = m_a21*rOther.m_a13 + m_a22*rOther.m_a23 + m_a23*rOther.m_a33;
	double a31 = m_a31*rOther.m_a11 + m_a32*rOther.m_a21 + m_a33*rOther.m_a31;
	double a32 = m_a31*rOther.m_a12 + m_a32*rOther.m_a22 + m_a33*rOther.m_a32;
	double a33 = m_a31*rOther.m_a13 + m_a32*rOther.m_a23 + m_a33*rOther.m_a33;
	m_a11 = a11;
	m_a12 = a12;
	m_a13 = a13;
	m_a21 = a21;
	m_a22 = a22;
	m_a23 = a23;
	m_a31 = a31;
	m_a32 = a32;
	m_a33 = a33;
}

//-------------------------------------
void CXTransformationMatrix2D::Rotate(double dRad) {
	double cs = cos(dRad);
	double sn = sin(dRad);
	CXTransformationMatrix2D RM(cs, -sn, 0, sn, cs, 0, 0, 0, 1);
	RM.Multiply(*this);
	*this = RM;
}

//-------------------------------------
void CXTransformationMatrix2D::Rotate(double dCos, double dSin) {
	CXTransformationMatrix2D RM(dCos, -dSin, 0, dSin, dCos, 0, 0, 0, 1);
	RM.Multiply(*this);
	*this = RM;
}

//-------------------------------------
void CXTransformationMatrix2D::Translate(double dX, double dY) {
	CXTransformationMatrix2D TM(1, 0, dX, 0, 1, dY, 0, 0, 1);
	TM.Multiply(*this);
	*this = TM;
}

//-------------------------------------
void CXTransformationMatrix2D::Scale(double dX, double dY) {
	CXTransformationMatrix2D SM(dX, 0, 0, 0, dY, 0, 0, 0, 1);
	SM.Multiply(*this);
	*this = SM;
}
