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


#ifndef IXPEEVENT_H
#define IXPEEVENT_H


#include <vector>

#include "ixpeEventWindow.h"
#include "ixpeDataFormat.h"

class ixpeEvent : public ixpeEventWindow
{
  
 public:

  /// Default constructor.
  ixpeEvent();

  /// Basic constructor (event window only)
  ixpeEvent(int minColumn, int maxColumn, int minRow, int maxRow,
	          int bufferId, idf_tick_t ticks, idf_second_t seconds);

  /// Add the content of the next pixel to the event (used to fill the event
  /// in a loop). The caller is responsible for providing the values in the
  /// right order, i.e. the one implicitly defined by the transformations
  /// in ixpeEventWindow
  void addPixel(idf_adc_count_t adc_count);

  double timestamp() const;

  /// Randm access to pixel content in the event
  idf_adc_count_t operator() (int index) const
    {return m_adc_counts.at(index);}
  
  /// Retrieve pixel counts by offset coordinates
  idf_adc_count_t operator() (const ixpeOffsetCoordinate& coords) const;
  
  /// Retrieve pixel counts by cubic coordinates
  idf_adc_count_t operator() (const ixpeCubeCoordinate& coords) const;

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os, const ixpeEvent& e)
  {
    return e.fillStream(os);
  }


 private:

  ///
  int m_bufferId;

  /// Number of clock ticks from the start of the run (reported by the
  /// FPGA)
  idf_tick_t m_ticks;

  /// Current Unix Timestamp at the start of the run (given by the
  /// DAQ application)
  idf_second_t m_seconds;
  
  /// Ordered adc counts array
  std::vector<idf_adc_count_t> m_adc_counts;
};


#endif //IXPEEVENT_H
