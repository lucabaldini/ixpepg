
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


#ifdef DEBUG_BUILD
#define DEBUG(x) do { \
  if (debugging_enabled) { std::cerr << x; } \
} while (0)
#else
#  define DEBUG(x) do {} while (0)
#endif

#include <functional>
#include <algorithm>

#include "ixpeClustering.h"
#include "ixpeHit.h"
#include "ixpeGeometrySvc.h"
#include "ixpeHexagonalCoordinates.h"


ixpeCartesianCoordinate indexToCartesian(const ixpeEvent& event,
                                         const int pixelIndex)
{
  // First convert the pixel index to offset (logical) coordinates
  ixpeOffsetCoordinate offsetCoords = indexToOffset(event, pixelIndex);
  // Create a grid object to get real word coordinate transformations
  // NOTE: the grid object is static and is istantiated only once, at the time
  // of the first call. Subsequent calls will only get a reference to the
  // same object
  ixpeXpolAsicGrid grid = ixpeGeometrySvc::xpolAsicGrid();
  // Finally convert logical to physical coordinates and return them
  return grid.pixelToWorld(offsetCoords);
  
}


void regionQuery(std::vector<int>& neighbors, const int pixelId,
                 const ixpeEvent& event, const int threshold)
{
  // Get all the neighbors pixel
  std::vector<ixpeCubeCoordinate> neighborsVec =
                                 neighborCoords(indexToCubic(event, pixelId));
  for (const auto& neighbor : neighborsVec){
    if (isInWindow(event, neighbor)){
      int neighborId = cubicToIndex(event, neighbor);
      if (event(neighborId) > threshold){
        DEBUG (neighborId << " ");
        neighbors.push_back(neighborId);
      }
    }
  }
  DEBUG(std::endl);
  return;
}


void assignPixelToTrack(const int pixelId, const ixpeEvent& event,
                        std::vector<int>& areAssigned, ixpeTrack& track)
{
  // Get catesian (physical) coordinates
  ixpeCartesianCoordinate cartesCoords = indexToCartesian(event, pixelId);
  // Add the pixel to the track
  track.addHit(ixpeHit{cartesCoords.x(), cartesCoords.y(), event(pixelId)});
  // Mark the pixel as assigned
  areAssigned.at(pixelId) = 1;
}

template <typename T>
void printVec(const std::vector<T>& vec)
{
  for (const T& v : vec){
    DEBUG(v << " ");
  }
}


ixpeTrack expandCluster(const int pixelId, const size_t minClusterPoints,
                        const int threshold, const ixpeEvent& event,
                        std::vector<int>& neighbors, 
                        std::vector<int>& areVisited,
                        std::vector<int>& areAssigned)
{
  // Create the track object to be filled
  ixpeTrack track;
  // Add the first pixel to the track
  assignPixelToTrack(pixelId, event, areAssigned, track);
  DEBUG("\t" << pixelId << ": " << "added to track" << std::endl);
  // Loop over the adiacent pixel (we can't use iterator becuase the vector is
  // changed inside the loop)
  for (int i =0; i < static_cast<int>(neighbors.size()); ++i){
    int neighborId = neighbors.at(i);
    DEBUG("\t" << "Neighbors vector is now: ");
    printVec(neighbors);
    DEBUG(std::endl);
    DEBUG("\t" << neighborId << ": " << "visiting..." << std::endl);
    if (areVisited.at(neighborId) == 0){
      areVisited.at(neighborId) = 1;
      DEBUG("\t" << neighborId << ": " << "creating list of nearby pixels: ");
      std::vector<int> currentPixelNeighbors;
      regionQuery(currentPixelNeighbors, neighborId, event, threshold);
      if (currentPixelNeighbors.size() > minClusterPoints){
        neighbors.reserve(neighbors.size() + currentPixelNeighbors.size());
        /// Expand the track with the neighbors of the current pixel
        neighbors.insert(neighbors.end(), currentPixelNeighbors.begin(),
                         currentPixelNeighbors.end());
      }
    } else {
      DEBUG("\t" << neighborId << ": " << "already visited." << std::endl);
    }
    if (areAssigned.at(neighborId) == 0){
      assignPixelToTrack(neighborId, event, areAssigned, track);
      DEBUG("\t" << neighborId << ": " << "added to track" << std::endl);
    }
  }
  return track;
}


std::vector<ixpeTrack> dbScan(const ixpeEvent& event, const int threshold,
                              const size_t minClusterPoints)
{
  std::vector<ixpeTrack> tracks; /// Will hold all the tracks found
  std::vector<int> areVisited(event.size()); /// Visited flag
  for (auto& isVisited : areVisited) // Vecotr init
    {isVisited = 0;}
  std::vector<int> areAssigned(event.size()); /// Assigned to a track flag
  for (auto& isAssigned : areAssigned) // Vector init
    {isAssigned = 0;}

  /// Main loop
  for (int pixelId = 0; pixelId < event.size(); ++pixelId){
    DEBUG(pixelId << ": " << "visiting..." << std::endl);
    if (areVisited.at(pixelId)){ // Skip already visted pixels
      DEBUG(pixelId << ": " << "already visited." << std::endl);
      continue;
    }
    areVisited.at(pixelId) = 1; // Set the pixel as visited
    if (event(pixelId) <= threshold){ // Skip under threshold events
      DEBUG(pixelId << ": " << "under threshold." << std::endl);
      continue;
    }
    DEBUG(pixelId << ": " << "creating list of nearby pixels: ");
    std::vector<int> neighbors; // Growing list of nearby pixels
    regionQuery(neighbors, pixelId, event, threshold); // Fill 'neighbors'
    if (neighbors.size() >= minClusterPoints){
      DEBUG(pixelId << ": " << "start building a cluster..." << std::endl);
      // If the condition is satisfied, build the track around this pixel
      ixpeTrack newTrack = expandCluster(pixelId, minClusterPoints, threshold,
                               event, neighbors, areVisited, areAssigned);
      // Add the track to the list of found tracks
      tracks.push_back(newTrack);
    }
  }
  std::sort(tracks.begin(), tracks.end(), std::greater<ixpeTrack>());
  return tracks;
}
