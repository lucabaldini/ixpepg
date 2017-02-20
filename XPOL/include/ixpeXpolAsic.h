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


#ifndef IXPEXPOLASIC_H
#define IXPEXPOLASIC_H



class ixpeXpolAsic
{
  
 public:

  /// Return the number of columns in the XPOL readout ASIC.
  static const int numColumns() {return 300;}
  
  /// Return the number of rows in the XPOL readout ASIC.
  static const int numRows() {return 352;}


 private:


};




#endif //IXPEXPOLASIC_H
