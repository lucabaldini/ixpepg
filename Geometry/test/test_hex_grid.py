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

import numpy

import matplotlib.pyplot as plt


GRID = ixpeXpolAsicGrid()
TEST_COORDINATES = [(0, 0), (0, 1), (1, 0), (150, 175), (0, 351), (299, 0),
                    (299, 351)]


def test_coordinates():
    """
    """
    for (col, row) in TEST_COORDINATES:
        off1 = ixpeOffsetCoordinate(col, row)
        cart = GRID.pixelToWorld(off1)
        off2 = GRID.worldToPixel(cart)
        print('%s -> %s -> %s' % (off1, cart, off2))

def test_exception():
    """
    """
    try:
        GRID.worldToPixel(100., 100.)
    except Exception as e:
        print(e)

def test_random(n=100000, side=0.1):
    """
    """
    x = numpy.random.uniform(-side, side, n)
    y = numpy.random.uniform(-side, side, n)
    xred = []
    yred = []
    xblue = []
    yblue = []
    xgreen = []
    ygreen = []
    xgray = []
    ygray = []
    for _x, _y in zip(x, y):
        _cart = ixpeCartesianCoordinate(_x, _y)
        _off = GRID.worldToPixel(_x, _y)
        _col, _row = _off.column(), _off.row()
        if _col % 2 and _row % 2:
            xred.append(_x)
            yred.append(_y)
        elif _col % 2:
            xblue.append(_x)
            yblue.append(_y)
        elif _row % 2:
            xgreen.append(_x)
            ygreen.append(_y)
        else:
            xgray.append(_x)
            ygray.append(_y)
    plt.plot(xred, yred, '.', color='red')
    plt.plot(xblue, yblue, '.', color='blue')
    plt.plot(xgreen, ygreen, '.', color='green')
    plt.plot(xgray, ygray, '.', color='gray')
    plt.show()


if __name__ == '__main__':
    test_coordinates()
    test_exception()
    test_random()
