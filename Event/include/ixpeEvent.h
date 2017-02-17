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


#include "ixpeEventWindow.h"
#include "ixpeDataFormat.h"


class ixpeEvent : public ixpeEventWindow
{
  
 public:

  /// Default constructor.
  ixpeEvent();

  /// Basic constructor.
  ixpeEvent(int minColumn, int maxColumn, int minRow, int maxRow,
	    int bufferId, idf_tick_t ticks, idf_second_t seconds);

  double timestamp() const;

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

  ///
  idf_tick_t m_ticks;

  ///
  idf_second_t m_seconds;
};


#endif //IXPEEVENT_H
