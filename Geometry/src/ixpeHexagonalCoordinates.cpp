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
#include <iomanip>

#include "ixpeHexagonalCoordinates.h"


/* ixpeCartesianCoordinate */

ixpeCartesianCoordinate::ixpeCartesianCoordinate(double x, double y) :
  m_x(x),
  m_y(y)
{}


ixpeCartesianCoordinate& ixpeCartesianCoordinate::operator+= 
  (const ixpeCartesianCoordinate &rhs)
{
  /// Check for self assignment
  if (this == &rhs){
    return *this;
  } 
  m_x += rhs.m_x;
  m_y += rhs.m_y;
  return *this;
}  


ixpeCartesianCoordinate& ixpeCartesianCoordinate::operator-=
  (const ixpeCartesianCoordinate &rhs)
{
  /// Check for self assignment
  if (this == &rhs){
    return *this;
  }
  m_x -= rhs.m_x;
  m_y -= rhs.m_y;
  return *this;
}


ixpeCartesianCoordinate& ixpeCartesianCoordinate::operator*= (double scalar)
{
  m_x *= scalar;
  m_y *= scalar;
  return *this;
}


std::ostream& ixpeCartesianCoordinate::fillStream(std::ostream& os) const
{
  os << "Cartesian(" << std::showpos << std::fixed << std::setprecision(6)
     << m_x << ", " << m_y << ")" << std::defaultfloat << std::noshowpos;
  return os;
}


const ixpeCartesianCoordinate ixpeCartesianCoordinate::operator+(
  const ixpeCartesianCoordinate& rhs) const
{
	return ixpeCartesianCoordinate(m_x + rhs.x(),
	                               m_y + rhs.y());
}


const ixpeCartesianCoordinate ixpeCartesianCoordinate::operator-(
  const ixpeCartesianCoordinate& rhs) const
{
	return ixpeCartesianCoordinate(m_x - rhs.x(),
	                               m_y - rhs.y());
}


/* ixpeOffsetCoordinate */

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
  os << "Offset(" << std::setw(3) << m_column << ", " << std::setw(3)
     << m_row << ")";
  return os;
}


const ixpeOffsetCoordinate ixpeOffsetCoordinate::operator+(
  const ixpeOffsetCoordinate& rhs) const
{
	return ixpeOffsetCoordinate(m_column + rhs.column(), m_row + rhs.row());
}


const ixpeOffsetCoordinate ixpeOffsetCoordinate::operator-(
  const ixpeOffsetCoordinate& rhs) const
{
	return ixpeOffsetCoordinate(m_column - rhs.column(), m_row - rhs.row());
}


/* ixpeCubeCoordinate */

ixpeCubeCoordinate::ixpeCubeCoordinate(int q, int r, int s) :
  m_q(q),
  m_r(r),
  m_s(s)
{}


bool ixpeCubeCoordinate::operator==(const ixpeCubeCoordinate& rhs)
{
  return (q() == rhs.q()) && (r() == rhs.r()) && (s() == rhs.s());
}


std::ostream& ixpeCubeCoordinate::fillStream(std::ostream& os) const
{
  os << "Cube(" << std::setw(3) << m_q << ", " << std::setw(3) << m_r << ", "
     << std::setw(3) << m_s << ")";
  return os;
}


const ixpeCubeCoordinate ixpeCubeCoordinate::operator+(
  const ixpeCubeCoordinate& rhs) const
{
	return ixpeCubeCoordinate(m_q + rhs.q(), m_r + rhs.r(), m_s + rhs.s());
}


const ixpeCubeCoordinate ixpeCubeCoordinate::operator-(
  const ixpeCubeCoordinate& rhs) const
{
	return ixpeCubeCoordinate(m_q - rhs.q(), m_r - rhs.r(), m_s - rhs.s());
}


/* Coordinates transformation */

ixpeOffsetCoordinate cubeToEroffset(const ixpeCubeCoordinate& c) {
  int col = c.q() + int((c.r() + (c.r() & 1)) / 2);
  int row = c.r();
  return ixpeOffsetCoordinate(col, row);
}


ixpeCubeCoordinate eroffsetToCube(const ixpeOffsetCoordinate& c) {
  int q = c.column() - int((c.row() + (c.row() & 1)) / 2);
  int r = c.row();
  int s = -q -r; 
  return ixpeCubeCoordinate(q, r, s);
}


/* Other utility functions */

ixpeCubeCoordinate cubeRound(double fq, double fr, double fs)
{
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
  } else{
    if (dr > ds)
      {
	r = -q - s;
      }
    else
      {
	s = -q - r;
      }
  }
  // And, finally, convert to the actual cube coordinate.
return ixpeCubeCoordinate(q, r, s);
}


std::vector<ixpeCubeCoordinate> neighborCoords(
                                             const ixpeCubeCoordinate& coords)
{
  // It's faster to reserve the memory in advance (a pixel has 6 neighbors)
  std::vector<ixpeCubeCoordinate> neighborsVec(6);
  neighborsVec[0] = coords + ixpeCubeCoordinate(+1, -1,  0);
  neighborsVec[1] = coords + ixpeCubeCoordinate(+1,  0, -1);
  neighborsVec[2] = coords + ixpeCubeCoordinate( 0, +1, -1);
  neighborsVec[3] = coords + ixpeCubeCoordinate(-1, +1,  0);
  neighborsVec[4] = coords + ixpeCubeCoordinate(-1,  0, +1);
  neighborsVec[5] = coords + ixpeCubeCoordinate( 0, -1, +1);
  return neighborsVec;
}
