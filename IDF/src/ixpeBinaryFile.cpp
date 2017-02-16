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


#include "ixpeBinaryFile.h"


ixpeBinaryFile::ixpeBinaryFile(std::string filePath)
{
  m_inputStream.open(filePath, std::ios::binary);
}


int ixpeBinaryFile::readWord()
{
  idf_byte_t msb = m_inputStream.get();
  idf_byte_t lsb = m_inputStream.get();
  return byteswap16(lsb, msb);
}


int ixpeBinaryFile::peekWord()
{
  int word = readWord();
  m_inputStream.seekg(-2, std::ios::cur);
  return word;
}
