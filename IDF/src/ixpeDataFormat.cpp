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


extern const idf_word_t IXPE_FILE_HEADER = 0xdfff;


extern const idf_word_t IXPE_BUFFER_HEADER = 0xefff;


extern const idf_word_t IXPE_EVENT_HEADER = 0xffff;


extern const idf_word_t MAX_ADC_COUNTS = 0x0fff;


idf_word_t byteswap16(idf_byte_t lsb, idf_byte_t msb)
{
  return ( ((msb & 0xff) << 8) | (lsb & 0xff) );
}


idf_tick_t ticks(idf_word_t w1, idf_word_t w2)
{
  return w1 + 65534*w2;
}


idf_second_t seconds(idf_word_t w1, idf_word_t w2)
{
  return w2 + w1*65536;
}
