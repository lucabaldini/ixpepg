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


#ifndef IXPEHEXAGONALGRID_H
#define IXPEHEXAGONALGRID_H


#include <utility>


class ixpeHexagonalGrid
{
  
 public:

  /// Constructor.
  ixpeHexagonalGrid(int numColumns, int numRows, double columnPitch);

  /// Return the physical coordinates of a given pixel.
  std::pair<double, double> pixel2world(int col, int row) const;

  /// Return the address of the neirest pixel, given a physical position.
  std::pair<int, int> world2pixel(double x, double y) const;
    
   
 private:

  /// The number of columns in the grid.
  const int m_numColumns;

  /// The number of rows in the grid.
  const int m_numRows;

  /// The horizontal (columns) pitch.
  const double m_columnPitch;
  
  /// The vertical (row) pitch.
  const double m_rowPitch;

  ///
  const double m_columnOffset;

  ///
  const double m_rowOffset;

  ///
  const double m_hexagonSize;
};




#endif //IXPEHEXAGONALGRID_H
