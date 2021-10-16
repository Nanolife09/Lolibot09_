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
    Brain.Screen.print("Left rotation: %f", rotation_value(lf));
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("right rotation: %f", rotation_value(rf));
  }
}