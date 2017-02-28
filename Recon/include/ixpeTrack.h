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


#ifndef IXPETRACK_H
#define IXPETRACK_H


#include <vector>
#include <iostream>
#include <iomanip>

#include "ixpeHit.h"


class ixpeTrack
{
  public:
    
    /// Default constructor.
    ixpeTrack(){;}
    
    /// Add a hit
    void addHit(ixpeHit hit);
    
    /// Define a custom iterator to facilitate loop over the hits
    /// (by delegating the native vector iterator)
    typedef std::vector<ixpeHit>::const_iterator const_iterator;
    typedef std::vector<ixpeHit>::iterator iterator;
    iterator begin()
      {return m_hits.begin();}
    iterator end()
      {return m_hits.end();}
    
    /// Random access to hit
    const ixpeHit& operator() (int index) const;
    
    /// Number of hits
    int nOfHits() const
      {return static_cast<int>(m_hits.size());}
    
    /// Streamer function for overloading the << operator.
    std::ostream& fillStream(std::ostream& os) const;

    /// Overloaded << operator.
    friend std::ostream& operator<<(std::ostream& os, const ixpeTrack& tr)
    {
      return tr.fillStream(os);
    }
    
    
  private:
  
    std::vector<ixpeHit> m_hits;
};

#endif //IXPETRACK_H
