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

#include "ixpeHexagonalCoordinates.h"


ixpeOffsetCoordinate::ixpeOffsetCoordinate(int column, int row) :
  m_column(column),
  m_row(row)
{}


bool ixpeOffsetCoordinate::operator==(const ixpeOffsetCoordinate& rhs)
{
  return (column() == rhs.column()) && (row() == rhs.row());
}


std::ostream& ixpeOffsetCoordinate::fillStream(std::ostream& os) const
{
  os << "Offset(" << m_column << ", " << m_row << ")";
  return os;
}


ixpeCubeCoordinate::ixpeCubeCoordinate(int x, int y, int z) :
  m_x(x),
  m_y(y),
  m_z(z)
{}


bool ixpeCubeCoordinate::operator==(const ixpeCubeCoordinate& rhs)
{
  return (x() == rhs.x()) && (y() == rhs.y()) && (z() == rhs.z());
}


std::ostream& ixpeCubeCoordinate::fillStream(std::ostream& os) const
{
  os << "Cube(" << m_x << ", " << m_y << ", " << m_z << ")";
  return os;
}


ixpeAxialCoordinate::ixpeAxialCoordinate(int q, int r) :
  m_q(q),
  m_r(r)
{}


bool ixpeAxialCoordinate::operator==(const ixpeAxialCoordinate& rhs)
{
  return (q() == rhs.q()) && (r() == rhs.r());
}


std::ostream& ixpeAxialCoordinate::fillStream(std::ostream& os) const
{
  os << "Axial(" << m_q << ", " << m_r << ")";
  return os;
}


ixpeOffsetCoordinate cube2eroffset(ixpeCubeCoordinate c) {
  int col = c.x() + (c.z() + (c.z() & 1)) / 2;
  int row = c.z();
  return ixpeOffsetCoordinate(col, row);
}


ixpeCubeCoordinate eroffset2cube(ixpeOffsetCoordinate c) {
  int x = c.column() - (c.row() + (c.row() & 1)) / 2;
  int z = c.row();
  int y = -(x + z); 
  return ixpeCubeCoordinate(x, y, z);
}


ixpeOffsetCoordinate axial2eroffset(ixpeAxialCoordinate c)
{
  int col = c.q() + (c.r() + (c.r() & 1)) / 2;
  int row = c.r();
  return ixpeOffsetCoordinate(col, row);
}


ixpeAxialCoordinate eroffset2axial(ixpeOffsetCoordinate c)
{
  int q = c.column() - (c.row() + (c.row() & 1)) / 2;
  int r = c.row();
  return ixpeAxialCoordinate(q, r);
}


ixpeAxialCoordinate cube2axial(ixpeCubeCoordinate c)
{
  int q = c.x();
  int r = c.z();
  return ixpeAxialCoordinate(q, r);
}


ixpeCubeCoordinate axial2cube(ixpeAxialCoordinate c)
{
  int x = c.q();
  int z = c.r();
  int y = - (x + z);
  return ixpeCubeCoordinate(x, y, z);
}


ixpeAxialCoordinate axialRound(double fq, double fr)
{
  // Calculate the third (redundant) fractional axial coordinate.
  double fs = -fq - fr;
  // Now round the numbers to the neirest integers...
  int q = int(std::round(fq));
  int r = int(std::round(fr));
  int s = int(std::round(fs));
  // ... and keep track of the differences.
  double dq = std::abs(q - fq);
  double dr = std::abs(r - fr);
  double ds = std::abs(s - fs);
  // Now do some magic.
  if (dq > dr and dq > ds) {
    q = -r - s;
  } else if (dr > ds) {
    r = -q - s;
  }
  // And, finally, convert to the actual axial coordinate.
  return ixpeAxialCoordinate(q, r);
}
