%module Recon

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
 #include "../include/ixpeHit.h"
 #include "../include/ixpeTrack.h"
 #include "../include/ixpeClustering.h"
 #include "../include/ixpeMomentsAnalysis.h"
%}

%include "../include/ixpeHit.h"

%include "../include/ixpeTrack.h"
%extend ixpeTrack {__STR__()};

%include "../include/ixpeClustering.h"

%include "../include/ixpeMomentsAnalysis.h"
%extend ixpeMomentsAnalysis {__STR__()};
