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


#include "ixpeGeometry.h"


ixpeGeometry::ixpeGeometry()
{
  add("XPOL_ASIC_PITCH", 0.050, "mm");
  add("Z_READOUT_PLANE", 0., "mm");
  add("Z_GEM_BOTTOM", 1., "mm");
  add("Z_GEM_TOP", 1.05, "mm");
  add("GEM_PITCH", 0.050, "mm");
  add("Z_DRIFT", 11.05, "mm");
}


//ixpeGeometry::ixpeGeometry(std::string filePath)
//{}


void ixpeGeometry::add(std::string name, double value, std::string units)
{
  m_map.insert(std::make_pair(name, ixpeGeometryConstant(value, units)));
}


double ixpeGeometry::value(std::string name)
{
  try {
    return m_map.at(name).value();
  } catch (const std::out_of_range& exc) {
    std::cerr << exc.what() << std::endl;
    exit(1);
  }
}


std::ostream& ixpeGeometry::fillStream(std::ostream& os) const
{
  for(auto const &element : m_map) {
    os << element.first << ": " << element.second << std::endl;
  }
  return os;
}
