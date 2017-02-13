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


#include "ixpeGeometrySvc.h"


ixpeGeometrySvc::ixpeGeometrySvc()
{}


ixpeGeometrySvc::ixpeGeometrySvc(std::string filePath)
{}


void ixpeGeometrySvc::add(std::string name, double value, std::string units)
{
  m_map.insert(std::make_pair(name, ixpeGeometryConstant(value, units)));
}


double ixpeGeometrySvc::value(std::string name)
{
  try {
    return m_map.at(name).value();
  } catch (const std::out_of_range& exc) {
    std::cerr << exc.what() << std::endl;
    exit(1);
  }
}


std::ostream& ixpeGeometrySvc::fillStream(std::ostream& os) const
{
  for(auto const &element : m_map) {
    os << element.first << ": " << element.second << std::endl;
  }
  return os;
}
