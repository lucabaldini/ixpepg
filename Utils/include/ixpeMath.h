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


class ixpeMath {
  
 public:
  
  /// PI.
  static double pi() {return 3.141592653589793;}

  /// Convert radians to degrees.
  static double radToDeg(double rad) {return rad * 57.29577951308232;}

  /// Convert degrees to radians.
  static double degToRad(double deg) {return deg * 0.017453292519943295;}

  /// Fold an angle (in radians) from [-pi, pi] to [-pi/2., pi/2.].
  static double foldAngle(double rad)
  {
    if (rad < -pi() / 2.) {
      return rad + pi();
    }
    if (rad > pi() / 2.) {
      return rad - pi();
    }
    return rad;
  }

  /// Flip an angle making sure that the result is in [-pi, pi]
  static double flipAngle(double rad) {return rad - std::copysign(pi(), rad);}

  /// "Exact" sqrt(3).
  static double sqrt3() {return 1.7320508075688772;}
  
  // Truncated sqrt(3) to match the XPOL 50/43.3 um horizontal/vertical pitch.
  static double xpolSqrt3() {return 1.7320;}
};


#endif //IXPEMATH_H
