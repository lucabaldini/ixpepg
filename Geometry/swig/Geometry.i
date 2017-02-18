%module Geometry

%include "std_string.i"

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
%extend ixpeCartesianCoordinate {__STR__()};
%extend ixpeOffsetCoordinate {__STR__()};
%extend ixpeCubeCoordinate {__STR__()};
%extend ixpeAxialCoordinate {__STR__()};

%include "../include/ixpeHexagonalGrid.h"
