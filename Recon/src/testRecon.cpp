#include <iostream>

#include "ixpeEvent.h"
#include "ixpeHit.h"
#include "ixpeTrack.h"
#include "ixpeClustering.h"
#include "ixpeBinaryFile.h"
#include "ixpeLogger.h"


std::vector<ixpeTrack> testCluster(const ixpeEvent& event,
                                   const int threshold,
                                   const size_t minClusterPoints)
{
  std::vector<ixpeTrack> tracks = dbScan(event, threshold, minClusterPoints);
  return tracks;
}


int main()
{
  loggerInit("testLogger.log", DEBUG);
  LOG_DEBUG << "debug message";
  ixpeBinaryFile f("/home/alberto/xpe/xpedaq/data/test_fe_500evts.mdat");
  const int threshold = 5;
  const int minClusterSize = 3;
  const int nEventsToAnalyze = 10;
  for (int i = 0; i < nEventsToAnalyze; ++i){
    ixpeEvent evt = f.next();
    //LOG_DEBUG << "Test event: " << evt << std::endl;
    std::vector<ixpeTrack> tracks = testCluster(evt, threshold,
                                                minClusterSize);
    LOG_DEBUG << "Found " << tracks.size() << " tracks." << std::endl;
    for (const auto& track : tracks){
      LOG_DEBUG << track << "\n";
      LOG_DEBUG << track.barycenter() << std::endl;
    }
  }
  return 0;
}
