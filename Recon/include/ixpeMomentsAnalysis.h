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


#ifndef IXPMOMENTSANALYSIS_H
#define IXPMOMENTSANALYSIS_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "ixpeHit.h"


class ixpeMomentsAnalysis
{
 public:
  
  /// Constructor, unweighted version.
  ixpeMomentsAnalysis(const std::vector<ixpeHit> &hits, double threshold,
		      double x0, double y0);
  
  // Constructor, weighted version.
  ixpeMomentsAnalysis(const std::vector<ixpeHit> &hits, double threshold,
		      double x0, double y0, const std::vector<double> &weights);

  /// Return the x coordinate of the pivot.
  double x0() const {return m_x0;}

  /// Return the y coordinate of the pivot.
  double y0() const {return m_y0;}

  /// Return the direction of the principal axis.
  double phi() const {return m_phi;}

  /// Return the longitudinal second moment.
  double mom2long() const {return m_mom2long;}        

  /// Return the transverse second moment.
  double mom2trans() const {return m_mom2trans;}

  /// Return the longitudinal third moments.
  double mom3long() const {return m_mom3long;}

  /// Return the internal status code.
  int statusCode() const {return m_statusCode;}

  /// Return the square root of the longitudinal second moment.
  double rmsLong() const;

  /// Return the square root of the transverse second moment.
  double rmsTrans() const;

  /// Return the skewness, i.e., m_mom3long/pow(m_mom2long, 1.5).
  double skewness() const;

  /// Return the elongation, i.e., m_mom2long/m_mom2trans.
  double elongation() const;

  /// Terminal formatting.
  std::ostream& fillStream(std::ostream& os) const;
  friend std::ostream& operator<<(std::ostream& os,
				  const ixpeMomentsAnalysis& m)
  {return m.fillStream(os);}
  

 private:
  
  /// The x coordinate of the pivot point.
  double m_x0;

  /// The y coordinate of the pivot point.
  double m_y0;
    
  /// The azimuthal angle of the major axis of the charge distribution.
  double m_phi;

  /// The longitudinal second moment.
  double m_mom2long;

  /// The transverse second moment.
  double m_mom2trans;
    
  /// The longitudinal third moment.
  double m_mom3long;

  enum StatusCode
  {
    UNDEFINED,
    SUCCESS,
    NOT_ENOUGH_HITS
  };
  
  /// Internal status code to store the outcome of the moments analysis.
  int m_statusCode;

  /// Run the actual moments analysis.
  void run(const std::vector<ixpeHit> &hits, double threshold, double x0,
	   double y0, const std::vector<double> &weights);
};


#endif //IXPEMOMENTSANALYSIS_H
