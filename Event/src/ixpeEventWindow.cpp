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
