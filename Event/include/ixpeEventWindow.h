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


#ifndef IXPEEVENTWINDOW_H
#define IXPEEVENTWINDOW_H


#include <iostream>
#include <iomanip>

#include "ixpeHexagonalCoordinates.h"


class ixpeEventWindow
{
  
 public:

  /// Default constructor.
  ixpeEventWindow();

  /// Basic constructor.
  ixpeEventWindow(int minColumn, int maxColumn, int minRow, int maxRow);

  /// Return the minimum column index (a.k.a. xmin).
  int minColumn() const {return m_minColumn;}

  /// Return the maximum column index (a.k.a. xmax).
  int maxColumn() const {return m_maxColumn;}

  /// Return the minimum row index (a.k.a. ymin).
  int minRow() const {return m_minRow;}

  /// Return the maximum row index (a.k.a. ymax).
  int maxRow() const {return m_maxRow;}

  /// Return the total number of columns in the window.
  int numColumns() const {return m_maxColumn - m_minColumn + 1;}

  /// Return the total number of rows in the window.
  int numRows() const {return m_maxRow - m_minRow + 1;}

  /// Return the total window size.
  int size() const {return numColumns() * numRows();}

  /// Streamer function for overloading the << operator.
  std::ostream& fillStream(std::ostream& os) const;

  /// Overloaded << operator.
  friend std::ostream& operator<<(std::ostream& os, const ixpeEventWindow& w)
  {
    return w.fillStream(os);
  }
  

 private:

  /// The minimum column index (a.k.a. xmin). 
  int m_minColumn;

  /// The maximum column index (a.k.a. xmax). 
  int m_maxColumn;

  /// The minimum row index (a.k.a. ymin). 
  int m_minRow;

  /// The maximum row index (a.k.a. ymax). 
  int m_maxRow;
  
};


///FIXME: do this transformations really belong here?

/// Return the index associate to given offset coordinates
int offsetToIndex(const ixpeEventWindow& window,
                  const ixpeOffsetCoordinate &coords);
  
/// Return the offset coordinates associate to a given index
ixpeOffsetCoordinate indexToOffset(const ixpeEventWindow& window, int index);

/// Return the index associate to given cubic coordinate
int cubicToIndex(const ixpeEventWindow& window,
                 const ixpeCubeCoordinate &coords);  
  
/// Return the cubic coordinates associate to a given index
ixpeCubeCoordinate indexToCubic(const ixpeEventWindow& window, int index);
    
/// Check if the given offset coordinates belong to a given window
bool isInWindow(const ixpeEventWindow& window,
                const ixpeOffsetCoordinate& coords);
  
/// Check if the given cubic coordinates belong to a given window
bool isInWindow(const ixpeEventWindow& window,
                const ixpeCubeCoordinate& coords);


#endif //IXPEEVENTWINDOW_H
