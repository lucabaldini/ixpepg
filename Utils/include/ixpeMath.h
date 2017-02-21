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


#ifndef IXPEMATH_H
#define IXPEMATH_H


namespace ixpeMath {
  extern const double PI;

  double rad2deg(double rad);
  double deg2rad(double deg);

  extern const double SQRT3;
  // truncated sqrt(3) to match horizontal pitch 50 um with vertical 43.3 um
  static const double XPOLSQRT3() {return 1.7320;}
}


#endif //IXPEMATH_H
