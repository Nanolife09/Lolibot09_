#include "debug.h"

float rotation_value (motor name) {
  return name.rotation(rotationUnits::raw);
}

void debug() {
  while(true){
    Brain.Screen.setCursor(1, 1);
    if (Brain.Battery.capacity() > 50) {
      Brain.Screen.print("ACCELERATION: ON");
    }
    else {
      Brain.Screen.print("ACCELERATION: OFF");
    }
  }
}

