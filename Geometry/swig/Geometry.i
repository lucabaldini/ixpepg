%module Geometry

%include "std_string.i"
%include "exception.i"

%exception {
try {
$action
} catch (const std::exception& e) {
SWIG_exception(SWIG_RuntimeError, e.what());
} catch (const std::string& e) {
SWIG_exception(SWIG_RuntimeError, e.c_str());
}
}

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
 #include "../include/ixpeGeometry.h"
 #include "../include/ixpeHexagonalCoordinates.h"
 #include "../include/ixpeHexagonalGrid.h"
%}

%include "../include/ixpeGeometryConstant.h"
%extend ixpeGeometryConstant {__STR__()};

%include "../include/ixpeGeometry.h"
%extend ixpeGeometry {__STR__()};

%include "../include/ixpeHexagonalCoordinates.h"
%extend ixpeCartesianCoordinate {__STR__()};
%extend ixpeOffsetCoordinate {__STR__()};
%extend ixpeCubeCoordinate {__STR__()};
%extend ixpeAxialCoordinate {__STR__()};

%include "../include/ixpeHexagonalGrid.h"
