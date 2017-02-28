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


#include "ixpeEvent.h"


ixpeEvent::ixpeEvent() :
  ixpeEventWindow(),
  m_bufferId(0),
  m_ticks(0),
  m_seconds(0)
{}


ixpeEvent::ixpeEvent(int minColumn, int maxColumn, int minRow, int maxRow,
		     int bufferId, idf_tick_t ticks, idf_second_t seconds) :
  ixpeEventWindow(minColumn, maxColumn, minRow, maxRow),
  m_bufferId(bufferId),
  m_ticks(ticks),
  m_seconds(seconds)
{}


void ixpeEvent::addPixel(idf_adc_count_t adc_count)
{
  /// Check that the size of the vector won't excede the one declared
  /// in the header of the event after the addition
  if (static_cast<int>(m_adc_counts.size()) >= this->size())
    throw -1;
  m_adc_counts.push_back(adc_count);
}


double ixpeEvent::timestamp() const
{
  return m_seconds + m_ticks * tickToMicroseconds * 1.e-6;
}


idf_adc_count_t ixpeEvent::operator() (
                                    const ixpeOffsetCoordinate& coords) const
{
  return m_adc_counts.at(offsetToIndex(*this, coords));
}


idf_adc_count_t ixpeEvent::operator() (const ixpeCubeCoordinate& coords) const
{
  return m_adc_counts.at(cubicToIndex(*this, coords));
}


std::ostream& ixpeEvent::fillStream(std::ostream& os) const
{
  ixpeEventWindow::fillStream(os);
  os << " buf " << m_bufferId << " @ " << timestamp() << " s";
  return os;
}
