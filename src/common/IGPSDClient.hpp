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


#ifndef __IGPSDCLIENT_HPP__
#define __IGPSDCLIENT_HPP__

//----------------------------------------------------------------------------
/**
 * \brief oiu.
 *
 * oiu.
 */
class IGPSDClient {
private:
	//-------------------------------------
	IGPSDClient(const IGPSDClient &);						///< Not used.
	const IGPSDClient & operator = (const IGPSDClient &);	///< Not used.
protected:
public:
	//-------------------------------------
	/**
	 * \brief Default constructor.
	 *
	 * The default constructor.
	 */
	IGPSDClient() {
	}
	//-------------------------------------
	/**
	 * \brief Destructor.
	 *
	 * The destructor.
	 */
	virtual ~IGPSDClient() {
	}
	//-------------------------------------
	/**
	 * \brief Open connection to gpsd.
	 *
	 * Open the connection to gpsd. Has to be implemented in derived classes.
	 * \return		true on success.
	 */
	virtual bool Open() = 0;
	//-------------------------------------
	/**
	 * \brief Close connection to gpsd.
	 *
	 * Close the connection to gpsd. Has to be implemented in derived classes.
	 * \return		true on success.
	 */
	virtual bool Close() = 0;
	//-------------------------------------
	/**
	 * \brief Check if connection is open.
	 *
	 * Check if the connection is open. Has to be implemented in derived classes.
	 * \return		true if open.
	 */
	virtual bool IsOpen() = 0;
};

#endif // __IGPSDCLIENT_HPP__
