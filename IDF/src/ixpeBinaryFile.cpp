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


#include <iostream>
#include <assert.h>

#include "ixpeBinaryFile.h"
#include "ixpeDataFormat.h"


ixpeBinaryFile::ixpeBinaryFile(const std::string& filePath)
{
  std::cout << "Opening input file " << filePath << "..." << std::endl;
  m_inputStream.open(filePath, std::ios::binary);
  if (not m_inputStream.good()) {
    std::cout << "Could not open file." << std::endl;
    exit(1);
  }
  std::cout << "Autodetecting file type... ";
  int word = peek();
  std::cout << "0x" << std::hex << word << std::dec << " found";
  if (word == IXPE_FILE_HEADER) {
    std::cout << " (new-style)" << std::endl;
  } else if (word == IXPE_EVENT_HEADER) {
    std::cout << " (old-style, window mode)" << std::endl;
  } else if (word <= MAX_ADC_COUNTS) {
    std::cout << " (old-style, full-frame mode)" << std::endl;
  } else {
    std::cout << "Ooops, failing miserably." << std::endl;
    exit(1);
  }
}


idf_word_t ixpeBinaryFile::read()
{
  idf_byte_t lsb = m_inputStream.get();
  idf_byte_t msb = m_inputStream.get();
  return byteswap16(lsb, msb);
}


idf_word_t ixpeBinaryFile::peek()
{
  int word = read();
  m_inputStream.seekg(-2, std::ios::cur);
  return word;
}


/*! @todo Here we might want to read the equivalent of a pDataBuffer, so that
  the field alignment is specified once and forever in a single place.
 */
ixpeEvent ixpeBinaryFile::next()
{
  int header = read();
  if (header != IXPE_EVENT_HEADER) {
    std::cout << "Event header mismatch (" << std::hex << header << " != "
	      << IXPE_EVENT_HEADER << ")" << std::endl;
    exit(1);
  }
  int minColumn = read();
  int maxColumn = read();
  int minRow = read();
  int maxRow = read();
  int bufferId = read();
  int t1 = read();
  int t2 = read();
  int s1 = read();
  int s2 = read();
  ixpeEvent event(minColumn, maxColumn, minRow, maxRow, bufferId,
		  ticks(t1, t2), seconds(s1, s2));
  /// Here we assume that the input files has the pixels listed in the right
  /// order, i.e. the one implicilty defined by the transformations between
  /// index and coordinates in ixpeEventWindow.h
  for (int i = 0; i < event.size(); i ++) {
      idf_adc_count_t adc = read();
      event.addPixel(adc);
  }
  return event;
}
