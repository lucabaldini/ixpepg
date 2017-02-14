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


#ifndef IXPEHEXAGONALCOORDINATES_H
#define IXPEHEXAGONALCOORDINATES_H


#include <iostream>


class ixpeOffsetCoordinate
{
  
 public:

  /// Constructor.
  ixpeOffsetCoordinate(int col, int row);

  /// Return the column coordinate.
  int column() const {return m_column;}

  /// Return the row coordinate.
  int row() const {return m_row;}

  /// Overloaded comparison operator.
  bool operator==(const ixpeOffsetCoordinate& rhs);

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os,
				  const ixpeOffsetCoordinate& c)
  {
    return c.fillStream(os);
  }

  
 private:

  /// The column identifier.
  int m_column;

  /// The row identifier.
  int m_row;

};



class ixpeCubeCoordinate
{
  
 public:

  /// Constructor.
  ixpeCubeCoordinate(int x, int y, int z);

  /// Return the x coordinate.
  int x() const {return m_x;}

  /// Return the y coordinate.
  int y() const {return m_y;}

  /// Return the z coordinate.
  int z() const {return m_z;}

  /// Overloaded comparison operator.
  bool operator==(const ixpeCubeCoordinate& rhs);

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os,
				  const ixpeCubeCoordinate& c)
  {
    return c.fillStream(os);
  }

  
 private:

  /// The x coordinate.
  int m_x;

  /// The y coordinate.
  int m_y;

  /// The z coordinate/
  int m_z;

};


class ixpeAxialCoordinate
{
  
 public:

  /// Constructor.
  ixpeAxialCoordinate(int q, int r);

  /// Return the q coordinate.
  int q() const {return m_q;}

  /// Return the r coordinate.
  int r() const {return m_r;}

  /// Overloaded comparison operator.
  bool operator==(const ixpeAxialCoordinate& rhs);

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os,
				  const ixpeAxialCoordinate& c)
  {
    return c.fillStream(os);
  }

  
 private:

  /// The column identifier.
  int m_q;

  /// The row identifier.
  int m_r;

};


///
ixpeOffsetCoordinate cube2eroffset(ixpeCubeCoordinate c);

///
ixpeCubeCoordinate eroffset2cube(ixpeOffsetCoordinate c);

///
ixpeOffsetCoordinate axial2eroffset(ixpeAxialCoordinate c);

///
ixpeAxialCoordinate eroffset2axial(ixpeOffsetCoordinate c);

///
ixpeAxialCoordinate cube2axial(ixpeCubeCoordinate c);

///
ixpeCubeCoordinate axial2cube(ixpeAxialCoordinate c);



#endif //IXPEHEXAGONALCOORDINATES_H
