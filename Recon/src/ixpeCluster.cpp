
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


#include "ixpeCluster.h"
#include "ixpeHit.h"


void regionQuery(std::vector<int>& neighbors, const int pixelId,
                 const ixpeEvent& event, const int threshold)
{
  /// TODO
  return;
}


ixpeTrack expandCluster(const int pixelId, const size_t minClusterPoints,
                        const int threshold, const ixpeEvent& event,
                        std::vector<int>& neighbors, 
                        std::vector<int>& areVisited,
                        std::vector<int>& areAssigned)
{
  ixpeTrack track;
  ixpeOffsetCoordinate pixelOffsetCoords = indexToOffset(event, pixelId);
  track.addHit(ixpeHit{pixelOffsetCoords.column(), pixelOffsetCoords.row(),
                       event(pixelId)});
  /// FIXME we should create hits with physical coordinates, not logical!!!!
  for (auto currentPixelId : neighbors){
    if (areVisited.at(currentPixelId) == 0){
      areVisited[currentPixelId] = 1;
      std::vector<int> currentPixelNeighbors;
      regionQuery(currentPixelNeighbors, currentPixelId, event, threshold);
      if (currentPixelNeighbors.size() > minClusterPoints){
        neighbors.reserve(neighbors.size() + currentPixelNeighbors.size());
        /// Expand the track with the neighbors of the current pixel
        neighbors.insert(neighbors.end(), currentPixelNeighbors.begin(),
                         currentPixelNeighbors.end());
      }
    }
    if (areAssigned.at(currentPixelId) == 0){
      areAssigned[currentPixelId] = 1;
    }
  }
  return track;
}


std::vector<ixpeTrack> dbScan(const ixpeEvent& event, const int threshold,
                              const size_t minClusterPoints)
{
  std::vector<ixpeTrack> tracks; /// Will hold all the tracks found
  std::vector<int> areVisited(event.size()); /// Visited flag
  for (auto& isVisited : areVisited)
    {isVisited = 0;}
  std::vector<int> areAssigned(event.size()); /// Assigned to a track flag
  for (auto& isAssigned : areAssigned)
    {isAssigned = 0;}

  /// Main loop
  for (int pixelId = 0; pixelId < event.size(); ++pixelId){
    if (areVisited.at(pixelId)){
      continue;
    }
    areVisited[pixelId] = 1;
    std::vector<int> neighbors;
    regionQuery(neighbors, pixelId, event, threshold);
    if (neighbors.size() >= minClusterPoints){
      tracks.push_back(expandCluster(pixelId, minClusterPoints, threshold,
                                  event, neighbors, areVisited, areAssigned));
    }
  }
  return tracks;
}
