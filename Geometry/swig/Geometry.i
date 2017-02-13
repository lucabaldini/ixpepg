%module Geometry

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

// Actual modules.
%{
#include "../include/ixpeGeometryConstant.h"
#include "../include/ixpeGeometrySvc.h"
#include "../include/ixpeHexagonalCoordinates.h"
%}

%include "std_sstream.i"

%include "../include/ixpeGeometryConstant.h"
%extend ixpeGeometryConstant {__STR__()};

%include "../include/ixpeGeometrySvc.h"
%extend ixpeGeometrySvc {__STR__()};

%include "../include/ixpeHexagonalCoordinates.h"
%extend ixpeOffsetCoordinate {__STR__()};
%extend ixpeCubeCoordinate {__STR__()};
%extend ixpeAxialCoordinate {__STR__()};
