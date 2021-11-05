#include "debug.h"

float rotation_value (motor name) {
  return name.rotation(rotationUnits::raw);
}

void debug() {
  while (true){
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("%f",rotation_value(back));
  }
}