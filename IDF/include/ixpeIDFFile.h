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


#ifndef IXPEIDFFILE_H
#define IXPEIDFFILE_H


#include <fstream>


/// The basic data type in the stream from the FPGA.
typedef unsigned char idf_byte_t;

/// The data type for the ACD counts in the binary stream.
typedef uint16_t adc_count_t;

/// The data type for th microsecond field.
typedef uint64_t microsecond_t;

/// Byte-swap function to convert big-endian to little-endian.
int byteswap_16(idf_byte_t lsb, idf_byte_t msb);

///
extern const int IXPE_FILE_HEADER;

///
extern const int IXPE_BUFFER_HEADER;

///
extern const int IXPE_EVENT_HEADER;



class ixpeIDFFile
{
  
 public:

  /// Basic constructor given a file path.
  ixpeIDFFile(std::string filePath);

  /// Read the next 16-bit data word from the input file.
  int readWord();

  /// Peek the next 16-bit data word from the input file.
  int peekWord();
  

 private:

  /// The underlying istream object.
  std::ifstream m_inputStream;
  
};


#endif //IXPEIDFFILE_H
