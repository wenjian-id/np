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

#ifndef __CXTRANSFORMATIONMATRIX_HPP__
#define __CXTRANSFORMATIONMATRIX_HPP__

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXCoorVector {
private:
	double m_x;		///< oiu
	double m_y;		///< oiu
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXCoorVector &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXCoorVector();
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXCoorVector(double x, double y);
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXCoorVector(const CXCoorVector &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXCoorVector();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXCoorVector & operator = (const CXCoorVector &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetX() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	double GetY() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetIntX() const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	int GetIntY() const;
};

//---------------------------------------------------------------------
/**
 * \brief oiu
 *
 */
class CXTransformationMatrix2D {
private:
	double	m_a11;	///< oiu
	double	m_a12;	///< oiu
	double	m_a13;	///< oiu
	double	m_a21;	///< oiu
	double	m_a22;	///< oiu
	double	m_a23;	///< oiu
	double	m_a31;	///< oiu
	double	m_a32;	///< oiu
	double	m_a33;	///< oiu
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXTransformationMatrix2D(	double a11, double a12, double a13, 
								double a21, double a22, double a23, 
								double a31, double a32, double a33);
	//-------------------------------------
	/**
	 * \brief Copy from other instance to self.
	 *
	 * Copy from other instance to self.
	 * \param	rOther	Instance to copy from.
	 */
	void CopyFrom(const CXTransformationMatrix2D &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Multiply(const CXTransformationMatrix2D &rOther);
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * Default constructor.
	 */
	CXTransformationMatrix2D();
	//-------------------------------------
	/**
	 * \brief Copy constructor.
	 *
	 * Copy constructor.
	 * \param	rOther	Instance to copy from.
	 */
	CXTransformationMatrix2D(const CXTransformationMatrix2D &rOther);
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * Destructor.
	 */
	virtual ~CXTransformationMatrix2D();
	//-------------------------------------
	/**
	 * \brief Assignment operator.
	 *
	 * Assignment operator.
	 * \param	rOther	Instance to copy from.
	 * \return			Const reference to self.
	 */
	const CXTransformationMatrix2D & operator = (const CXTransformationMatrix2D &rOther);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	CXCoorVector operator * (const CXCoorVector &Value) const;
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Rotate(double dRad);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Rotate(double dCos, double dSin);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Translate(double dX, double dY);
	//-------------------------------------
	/**
	 * \brief oiu
	 *
	 */
	void Scale(double dX, double dY);
};

#endif // __CXTRANSFORMATIONMATRIX_HPP__
