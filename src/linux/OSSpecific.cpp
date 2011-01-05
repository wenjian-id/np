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

#include "OSSpecific.hpp"

#include <sys/sysinfo.h>

//-------------------------------------
void TriggerWatchdog() {
    /// \todo implement
}

//-------------------------------------
t_uint64 GetFreeMem() {
    struct sysinfo SINFO;
    memset(&SINFO, 0, sizeof(SINFO));
    int res = sysinfo(&SINFO); 
    if(res < 0)
        return 0;
    t_uint64 FreeMem = static_cast<t_uint64>(SINFO.freeram) + static_cast<t_uint64>(SINFO.sharedram) + static_cast<t_uint64>(SINFO.bufferram);
    return FreeMem;
}
