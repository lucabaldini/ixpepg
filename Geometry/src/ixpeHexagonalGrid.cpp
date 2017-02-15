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


#include <cmath>

#include "ixpeHexagonalGrid.h"
#include "ixpeHexagonalCoordinates.h"
#include "ixpeMath.h"


ixpeHexagonalGrid::ixpeHexagonalGrid(int numColumns, int numRows,
				     double columnPitch) :
  m_numColumns(numColumns),
  m_numRows(numRows),
  m_columnPitch(columnPitch)
{
  m_rowPitch = m_columnPitch * ixpeMath::SQRT3 / 2.;
  m_hexagonSize = m_columnPitch * 2. / ixpeMath::SQRT3;
}


std::pair<double, double> ixpeHexagonalGrid::pixel2world(int col, int row) const
{
  double x = (col - 0.5*(m_numColumns - 1.5 + (row & 1)))*m_columnPitch;
  double y = (0.5*(m_numRows - 1) - row)*m_rowPitch;
  return std::make_pair(x, y);
}


std::pair<int, int> ixpeHexagonalGrid::world2pixel(double x, double y) const
{
  double fq = (x * ixpeMath::SQRT3 / 3.  - y / 3.) / m_hexagonSize;
  double fr = y * 2. / 3. / m_hexagonSize;
  ixpeAxialCoordinate axial = axialRound(fq, fr);
  ixpeOffsetCoordinate offset = axial2eroffset(axial);
  return std::make_pair(offset.column(), offset.row());
}
