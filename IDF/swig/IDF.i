%module IDF

%include "std_sstream.i"
%include "stdint.i"

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
#include "../../Event/include/ixpeEventWindow.h"
#include "../../Event/include/ixpeEvent.h"
#include "../include/ixpeDataFormat.h"
#include "../include/ixpeBinaryFile.h"
%}


%include "../../Event/include/ixpeEventWindow.h"
%extend ixpeEventWindow {__STR__()};

%include "../../Event/include/ixpeEvent.h"

%include "../include/ixpeDataFormat.h"

%include "../include/ixpeBinaryFile.h"
