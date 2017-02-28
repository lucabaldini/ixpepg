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


#include "ixpeMomentsAnalysis.h"


ixpeMomentsAnalysis::ixpeMomentsAnalysis(const std::vector<ixpeHit> &hits,
					 double threshold, double x0,
					 double y0) :
  m_x0(x0),
  m_y0(y0),
  m_phi(-1000.),
  m_mom2long(-1000.),
  m_mom2trans(-1000.),
  m_mom3long(-1000.),
  m_statusCode(UNDEFINED)
{
  std::vector<double> weights(hits.size(), 1.0);
  run(hits, threshold, x0, y0, weights);
}


ixpeMomentsAnalysis::ixpeMomentsAnalysis(const std::vector<ixpeHit> &hits,
					 double threshold, double x0, double y0,
					 const std::vector<double> &weights) :
  m_x0(x0),
  m_y0(y0),
  m_phi(-1000.),
  m_mom2long(-1000.),
  m_mom2trans(-1000.),
  m_mom3long(-1000.),
  m_statusCode(UNDEFINED)
{
  run(hits, threshold, x0, y0, weights);
}


void ixpeMomentsAnalysis::run(const std::vector<ixpeHit> &hits,
			      double threshold, double x0, double y0,
			      const std::vector<double> &weights)
{
  // If there are not enough hits, return right away.
  if (hits.size() < 3) {
    m_statusCode = NOT_ENOUGH_HITS;
    return;
  }

  // Calculate the offsets with respect to the pivot.
  std::vector<double> dx;
  std::vector<double> dy;
  std::vector<double> w;
  double wsum = 0.;
  for (unsigned int i = 0; i < hits.size(); i++) {
    ixpeHit hit = hits.at(i);
    if (hit.count > threshold) {
      dx.push_back(hit.x - x0);
      dy.push_back(hit.y - y0);
      w.push_back(hit.count * weights.at(i));
      wsum += hit.count * weights.at(i);
    }
  }

  // Solve for the angle of the principa axis (note that at this point
  // phi is comprised between -pi/2 and pi/2 and might indicate either
  // the major or the minor axis of the tensor of inertia).
  double A = 0;
  double B = 0;
  for (unsigned int i = 0; i < dx.size(); i++) {
    A += (dx.at(i) * dy.at(i) * w.at(i));
    B += ((pow(dy.at(i), 2.) - pow(dx.at(i), 2.)) * w.at(i));
  }
  m_phi = -0.5 * atan2(2*A, B);

  // Rotate by an angle phi and calculate the eigenvalues of the tensor
  // of inertia.
  std::vector<double> xp;
  std::vector<double> yp;
  double cphi = cos(m_phi);
  double sphi = sin(m_phi);
  for (unsigned int i = 0; i < dx.size(); i++){
    xp.push_back(cphi * dx.at(i) + sphi * dy.at(i));
    yp.push_back(-sphi * dx.at(i) + cphi * dy.at(i));
  }
  m_mom2long = 0.;
  m_mom2trans = 0.;
  for (unsigned int i = 0; i < xp.size(); i++) {
    m_mom2long += (pow(xp.at(i), 2.) * w.at(i));
    m_mom2trans += (pow(yp.at(i), 2.) * w.at(i));
  }
  m_mom2long /= wsum;
  m_mom2trans /= wsum;
  // We want mom2long to be the highest eigenvalue, so we need to
  // check wheteher we have to swap the eigenvalues, here. Note that
  // at this point phi is still comprised between -pi/2 and pi/2.
  if (m_mom2long < m_mom2trans){
    std::swap(m_mom2long, m_mom2trans);
    m_phi -= std::copysign(0.5 * M_PI, m_phi);
  }

  // Calculate the third moment along the principal axis.
  cphi = cos(m_phi);
  sphi = sin(m_phi);
  for (unsigned int i = 0; i < dx.size(); i++){
    xp[i] = cphi * dx.at(i) + sphi * dy.at(i);
  }
  m_mom3long = 0.;
  for (unsigned int i = 0; i < xp.size(); ++i){
    m_mom3long += (pow(xp.at(i), 3.) * w.at(i));
  }
  m_mom3long /= wsum;

  m_statusCode = SUCCESS;
}


double ixpeMomentsAnalysis::rmsLong() const
{
  if (m_mom2long >= 0) {
    return sqrt(m_mom2long);
  }
  return -1.;
}


double ixpeMomentsAnalysis::rmsTrans() const
{
  if (m_mom2trans >= 0) {
    return sqrt(m_mom2trans);
  }
  return -1.;
}


double ixpeMomentsAnalysis::skewness() const
{
  if (m_mom2long > 0) {
    return m_mom3long/pow(m_mom2long, 1.5);
  }
  return -1.;
}


double ixpeMomentsAnalysis::elongation() const
{
  if (m_mom2trans > 0) {
    return m_mom2long/m_mom2trans;
  }
  return -1.;
}


void ixpeMomentsAnalysis::flip()
{
  m_phi -= std::copysign(M_PI, m_phi);
}


void ixpeMomentsAnalysis::flip3()
{
  if (m_mom3long > 0.) {
    flip();
  }
}


std::ostream& ixpeMomentsAnalysis::fillStream(std::ostream& os) const
{
  os << "Pivot = (" << m_x0 << ", " << m_y0 << "), phi = " <<
    m_phi << ", moments = (2l: " << m_mom2long << ", 2t: " << m_mom2trans <<
    "3l: " << m_mom3long << ")";
  return os;
}
