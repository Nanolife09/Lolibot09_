#include "debug.h"
#include "driver.h"
#include <iostream>
#include <cmath>

float rotation_value (encoder name) {
  return name.rotation(rotationUnits::raw);
}

void debug() {
  
}