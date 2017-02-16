/***********************************************************************
Copyright (C) 2017 the Imaging X-ray Polarimetry Explorer (IXPE) team.

For the license terms see the file LICENSE, distributed along with this
software.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***********************************************************************/


#include "ixpeDataFormat.h"


///
extern const int IXPE_FILE_HEADER = 0xEFFF;

///
extern const int IXPE_BUFFER_HEADER = 0xFFFF;

///
extern const int IXPE_EVENT_HEADER = 0xDFFF;


int byteswap16(idf_byte_t lsb, idf_byte_t msb)
{
  return ( ((msb & 0xFF) << 8) | (lsb & 0xFF) );
}

