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

#include "ixpeTrack.h"

void ixpeTrack::addHit(ixpeHit hit)
{
  m_hits.push_back(hit);
}


const ixpeHit& ixpeTrack::operator() (int index) const
{
  if (index < 0 || index >= nOfHits())
    throw -1; // FIXME we need a proper exception
  return m_hits.at(index);
}


std::ostream& ixpeTrack::fillStream(std::ostream& os) const
{
  os << "Track of " << nOfHits() << " hits: ";
  for (const auto& hit : m_hits){
    os << "(" << hit.x << ", " << hit.y << ", " << hit.count << "), ";
  }
  return os;
}
