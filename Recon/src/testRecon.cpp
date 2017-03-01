#include <iostream>

#include "ixpeEvent.h"
#include "ixpeHit.h"
#include "ixpeTrack.h"
#include "ixpeClustering.h"
#include "ixpeBinaryFile.h"


std::vector<ixpeTrack> testCluster(const ixpeEvent& event,
                                   const int threshold,
                                   const size_t minClusterPoints)
{
  std::vector<ixpeTrack> tracks = dbScan(event, threshold, minClusterPoints);
  return tracks;
}


int main()
{
  ixpeBinaryFile f("/home/alberto/xpe/xpedaq/data/test_fe_500evts.mdat");
  const int threshold = 5;
  const int minClusterSize = 3;
  const int nEventsToAnalyze = 10;
  for (int i = 0; i < nEventsToAnalyze; ++i){
    ixpeEvent evt = f.next();
    std::cout << "Test event: " << evt << std::endl;
    std::vector<ixpeTrack> tracks = testCluster(evt, threshold,
                                                minClusterSize);
    std::cout << "Found " << tracks.size() << " tracks." << std::endl;
    for (const auto& track : tracks){
      std::cout << track << "\n";
      std::cout << track.barycenter() << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
