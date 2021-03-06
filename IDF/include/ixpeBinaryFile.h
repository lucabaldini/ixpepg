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


#ifndef IXPEBINARYFILE_H
#define IXPEBINARYFILE_H


#include <fstream>

#include "ixpeDataFormat.h"
#include "ixpeEvent.h"


class ixpeBinaryFile
{
  
 public:

  /// Basic constructor given a file path.
  ixpeBinaryFile(const std::string& filePath);

  /// Read the next 16-bit data word from the input file.
  idf_word_t read();

  /// Peek the next 16-bit data word from the input file.
  idf_word_t peek();

  /// Read the next event.
  ixpeEvent next();
  

 private:

  /// The underlying istream object.
  std::ifstream m_inputStream;
  
};


#endif //IXPEBINARYFILE_H
