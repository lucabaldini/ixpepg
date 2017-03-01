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


TEST_OFFSET_COORDINATES = [(0,0), (0,1), (0,2), (0,3), (1,0), (2,0), (1,1),
                           (2,2), (299,0), (0, 351), (299,351)]


def test_offset_cube():
    """
    """
    for (col, row) in TEST_OFFSET_COORDINATES:
        oc = ixpeOffsetCoordinate(col, row)
        cc = eroffsetToCube(oc)
        tc = cubeToEroffset(cc)
        print('%s -> %s -> %s' % (oc, cc, tc)) 
        assert tc == oc


def test_cartesian():
    """
    """
    coord = ixpeCartesianCoordinate(3., 5.)
    print(coord)

if __name__ == '__main__':
    test_offset_cube()
    test_cartesian()
