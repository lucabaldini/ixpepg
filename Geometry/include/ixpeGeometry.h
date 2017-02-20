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


#ifndef IXPEGEOMETRY_H
#define IXPEGEOMETRY_H

#include "ixpeGeometryConstant.h"
#include <map>


class ixpeGeometry
{
  
 public:

  /// Empty constructor.
  ixpeGeometry();

  /// Actual constructor from a FITS file.
  //ixpeGeometry(std::string filePath);

  /// Register a geometry constant into the geometry service.
  void add(std::string name, double value, std::string units);

  /// Return the value of a specific geometry constant givent its name.
  double value(std::string name);

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os, const ixpeGeometry& geo)
  {
    return geo.fillStream(os);
  }

  
 private:

  /// The basic underlying map of geometry constants.
  std::map<std::string, ixpeGeometryConstant> m_map;

};


#endif //IXPEGEOMETRY_H
