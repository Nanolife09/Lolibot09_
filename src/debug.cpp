#include "debug.h"
#include "driver.h"
#include <iostream>
#include <cmath>

float rotation_value (motor name) {
  return name.rotation(rotationUnits::raw);
}

void debug() {
  while (true){
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(rotation_value(clamp));
  }
}