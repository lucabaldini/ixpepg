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

from ixpeswpy.Recon import dbScan, ixpeMomentsAnalysis
from ixpeswpy.IDF import ixpeBinaryFile
from ixpeswpy.Utils import ixpeEnviron

import os
import numpy

import matplotlib.pyplot as plt


def testCluster(event, threshold, minClusterHits):
    """
    """
    tracks = dbScan(event, threshold, minClusterHits)
    return tracks


if __name__ == "__main__":
    """
    """
    filePath = os.path.join(ixpeEnviron.envVar('IXPESWROOT'), 'Recon', 'data',
                            'test_fe_500evts.mdat')
    f = ixpeBinaryFile(filePath)
    threshold = 5;
    minClusterHits = 1;
    nEventsToAnalyze = 1;
    for i in range (0, nEventsToAnalyze):
        evt = f.next()
        print(evt)
        tracks = testCluster(evt, threshold, minClusterHits)
        print ("Found %d tracks" % (tracks.size()))
        print ("")        
        for track in tracks:
            if (track.nOfHits() > 5):
                print (track)
                _hits = track.hits()
                _barycenter = track.barycenter()
                print ("Barycenter = %s" % (_barycenter))
                print (track.pulseHeight())
                mom = ixpeMomentsAnalysis(_hits, threshold, _barycenter.x(),
                                          _barycenter.y())
                print(mom)
                print ("")
        print ("")
