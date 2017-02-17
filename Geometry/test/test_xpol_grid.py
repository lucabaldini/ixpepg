#***********************************************************************
# Copyright (C) 2017 the Imaging X-ray Polarimetry Explorer (IXPE) team.
#
# For the license terms see the file LICENSE, distributed along with this
# software.
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#***********************************************************************

from ixpeswpy.Geometry import *


TEST_COORDINATES = [(0, 0), (0, 1), (1, 0), (0, 351), (299, 0), (299, 351)]


def test_xpol_grid():
    """
    """
    grid = ixpeHexagonalGrid(300, 352, 0.05)
    for (col, row) in TEST_COORDINATES:
        x, y = grid.pixel2world(col, row)
        print('%s -> %s -> %s' % ((col, row), (x, y), grid.world2pixel(x, y)))


if __name__ == '__main__':
    test_xpol_grid()
