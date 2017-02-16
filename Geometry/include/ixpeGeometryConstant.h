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


#ifndef IXPEGEOMETRYCONSTANT_H
#define IXPEGEOMETRYCONSTANT_H


#include <string>
#include <iostream>
#include <sstream>


class ixpeGeometryConstant
{
  
 public:

  /// Constructor with no units.
  ixpeGeometryConstant(double value);

  /// Constructor with value and units.
  ixpeGeometryConstant(double value, std::string units);

  /// Return the value of the geometry constant.
  double value() const {return m_value;}

  /// Return the units of the geometry constant.
  std::string units() const {return m_units;}
  
  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os,
				  const ixpeGeometryConstant& c)
  {
    return c.fillStream(os);
  }

  
 private:

  /// The numerical value of the geometry constant.
  double m_value;

  /// The units of the geometry constant.
  std::string m_units;
  
};


#endif //IXPEGEOMETRYCONSTANT_H
