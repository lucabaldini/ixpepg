#include "ixpeTrack.h"

ixpeTrack::addHit(ixpeHit hit)
{
  m_hits.push_back(hit);
}


const ixpeTrack::ixpeHit& operator() (int index) const
{
  if (index < 0 || index >= nOfHits())
    throw -1; // FIXME we need a proper exception
  return m_hits.at(index);
}
