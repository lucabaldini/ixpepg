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


#include "ixpeEventWindow.h"


ixpeEventWindow::ixpeEventWindow() :
  m_minColumn(0),
  m_maxColumn(0),
  m_minRow(0),
  m_maxRow(0)
{}


ixpeEventWindow::ixpeEventWindow(int minColumn, int maxColumn, int minRow,
				 int maxRow) :
  m_minColumn(minColumn),
  m_maxColumn(maxColumn),
  m_minRow(minRow),
  m_maxRow(maxRow)
{}


std::ostream& ixpeEventWindow::fillStream(std::ostream& os) const
{
  os << "w(" << std::setfill(' ')
     << std::setw(3) << m_minColumn << ", "
     << std::setw(3) << m_minRow << ")--("
     << std::setw(3) << m_maxColumn << ", "
     << std::setw(3) << m_maxRow << ") " << size() << " px";
  return os;
}



/// Return the index associate to given offset coordinates
int offsetToIndex(const ixpeEventWindow& window,
                  const ixpeOffsetCoordinate &coords)
{
  if (!isInWindow(window, coords))
    throw -1; /// FIXME: we need a proper exception
  else return coords.column() - window.minColumn() +\
              (coords.row() - window.minRow()) * window.numColumns();
}  

  
/// Return the offset coordinates associate to a given index
ixpeOffsetCoordinate indexToOffset(const ixpeEventWindow& window, int index)
{
  return ixpeOffsetCoordinate(index % window.numColumns() +window.minColumn(),
                              index / window.numColumns() + window.minRow());
}


/// Return the index associate to given cubic coordinate
int cubicToIndex(const ixpeEventWindow& window,
                 const ixpeCubeCoordinate &coords)  
{
  return offsetToIndex(window, cube2eroffset(coords));
}


/// Return the cubic coordinates associate to a given index
ixpeCubeCoordinate indexToCubic(const ixpeEventWindow& window, int index)
{
  return cube2eroffset(indexToOffset(window, index));
}

  
/// Check if the given offset coordinates belong to a given window
bool isInWindow(const ixpeEventWindow& window,
                const ixpeOffsetCoordinate& coords)
{
  return (coords.row() >= window.minRow() && \
          coords.row() <= window.maxRow() && \
          coords.column() >= window.minColumn() && \
          coords.column() <= window.maxColumn());
}

 
/// Check if the given cubic coordinates belong to a given window
bool isInWindow(const ixpeEventWindow& window,
                const ixpeCubeCoordinate& coords)
{
  return isInWindow(window, cube2eroffset(coords))
}
