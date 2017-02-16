%module Geometry

%include "std_sstream.i"

// And this is necessary to use std::pairs, see
// http://www.swig.org/Doc1.3/Library.html#Library_stl_cpp_library
// (under std_vector.i, as the std_pair.i magic is apparently not covered).
%include "std_pair.i"
namespace std {
  %template(pairii) std::pair<int, int>;
  %template(pairdd) std::pair<double, double>;
};

// Suppress SWIG warnings about the << operators.
%ignore operator<<;

// Macro to map the c++ << operators into Python __str__()
%define __STR__()
std::string __str__() {
  std::ostringstream out;
  out << (*$self);
  return out.str();
}
%enddef

// Actual modules. Why do we have to list everything twice?
%{
 #include "../include/ixpeGeometryConstant.h"
 #include "../include/ixpeGeometrySvc.h"
 #include "../include/ixpeHexagonalCoordinates.h"
 #include "../include/ixpeHexagonalGrid.h"
%}


%include "../include/ixpeGeometryConstant.h"
%extend ixpeGeometryConstant {__STR__()};

%include "../include/ixpeGeometrySvc.h"
%extend ixpeGeometrySvc {__STR__()};

%include "../include/ixpeHexagonalCoordinates.h"
%extend ixpeOffsetCoordinate {__STR__()};
%extend ixpeCubeCoordinate {__STR__()};
%extend ixpeAxialCoordinate {__STR__()};

%include "../include/ixpeHexagonalGrid.h"
