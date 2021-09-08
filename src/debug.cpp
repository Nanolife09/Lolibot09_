#include "debug.h"
#include "driver.h"
#include <iostream>
#include <cmath>

float rotation_value (encoder name) {
  return name.rotation(rotationUnits::raw);
}

void debug() {
  while (true) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Encoder Right: %f", rotation_value(encoderR));
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Encoder Left: %f", rotation_value(encoderL));
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("Error: %f", std::abs(rotation_value(encoderR)) - std::abs(rotation_value(encoderL)));
  }
}