#include <iostream>

#include "ixpeGeometrySvc.h"
#include "ixpeGeometry.h"

int main(){
  ixpeGeometry geometry = ixpeGeometrySvc::geometry();
  std::cout<< geometry <<std::endl;
  return 0; 
}
