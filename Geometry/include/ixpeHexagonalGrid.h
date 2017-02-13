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

  std::pair<double, double> pixel2world(int col, int row) const;
  std::pair<int, int> world2pixel(double x, double y) const;
    
   
 private:

  int m_numColumns;
  int m_numRows;
  double m_columnPitch;
  double m_rowPitch;
};



///
//ixpeOffsetCoordinate cube2eroffset(ixpeCubeCoordinate c);



#endif //IXPEHEXAGONALGRID_H
