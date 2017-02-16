%module Event

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

%{
#include "../include/ixpeEventWindow.h"
#include "../include/ixpeEvent.h"
%}

%include "../include/ixpeEventWindow.h"
%extend ixpeEventWindow {__STR__()};

%include "../include/ixpeEvent.h"
