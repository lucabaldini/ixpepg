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
#include <vector>

/* 
define coordinades types 
Inspired (copied) by 
http://www.redblobgames.com/grids/hexagons/codegen/output/lib.cc
Documented in 
http://www.redblobgames.com/grids/hexagons/implementation.htm
*/

class ixpeCartesianCoordinate
{
  
 public:

  /// Constructor.
  ixpeCartesianCoordinate(double x, double y);

  /// Empty constructor.
  ixpeCartesianCoordinate() : ixpeCartesianCoordinate(0, 0) {;}

  /// Return the x coordinate.
  double x() const {return m_x;}

  /// Return the y coordinate.
  double y() const {return m_y;}

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os,
				  const ixpeCartesianCoordinate& c)
  {
    return c.fillStream(os);
  }
  
  /// +=, -= operators
  ixpeCartesianCoordinate& operator+= (const ixpeCartesianCoordinate &rhs);
  ixpeCartesianCoordinate& operator-= (const ixpeCartesianCoordinate &rhs);
  
  /// *= operator (product by a scalar)
  ixpeCartesianCoordinate& operator*= (double scalar);

  /// Sum and difference
  const ixpeCartesianCoordinate operator+(const ixpeCartesianCoordinate& rhs)
    const;
  const ixpeCartesianCoordinate operator-(const ixpeCartesianCoordinate& rhs)
    const;
  
 private:

  /// The x coordinate
  double m_x;

  /// The y coordinate.
  double m_y;

};



class ixpeOffsetCoordinate
{
  
 public:

  /// Constructor.
  ixpeOffsetCoordinate(int column, int row);

  /// Empty constructor.
  ixpeOffsetCoordinate() : ixpeOffsetCoordinate(0, 0) {;}

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

  /// Sum and difference
  const ixpeOffsetCoordinate operator+(const ixpeOffsetCoordinate& rhs) const;
  const ixpeOffsetCoordinate operator-(const ixpeOffsetCoordinate& rhs) const;
  
 private:

  /// The column identifier.
  int m_column;

  /// The row identifier.
  int m_row;

};


// Cube coordinate
// Since cube is just and extension of hex (axial) we use only this one
class ixpeCubeCoordinate
{
  
 public:

  /// Constructor.
  ixpeCubeCoordinate(int q, int r, int s);

  /// Empty constructor.
 ixpeCubeCoordinate() : ixpeCubeCoordinate(0, 0, 0) {;}

  /// Return the q coordinate.
  int q() const {return m_q;}

  /// Return the r coordinate.
  int r() const {return m_r;}

  /// Return the z coordinate.
  int s() const {return m_s;}

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

  /// Sum and difference
  const ixpeCubeCoordinate operator+(const ixpeCubeCoordinate &rhs) const;
  const ixpeCubeCoordinate operator-(const ixpeCubeCoordinate &rhs) const;

 private:

  /// The q coordinate.
  int m_q;

  /// The r coordinate.
  int m_r;

  /// The s coordinate/
  int m_s;

};

///
ixpeOffsetCoordinate cubeToEroffset(const ixpeCubeCoordinate& c);

///
ixpeCubeCoordinate eroffsetToCube(const ixpeOffsetCoordinate& c);

///
ixpeCubeCoordinate cubeRound(double fq, double fr, double fs);

/// Neighbors of a given pixels in cubic coordinates
std::vector<ixpeCubeCoordinate> neighborCoords(
                                            const ixpeCubeCoordinate& coords);

#endif //IXPEHEXAGONALCOORDINATES_H
