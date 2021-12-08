#include "debug.h"

float rotation_value (motor name) {
  return name.rotation(rotationUnits::raw);
}

void display_acceleration_mode() {
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

void display_rotation_value() {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Left front: %f", rotation_value(lf));
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Left back: %f", rotation_value(lb));
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("Right front: %f", rotation_value(rf));
  Brain.Screen.setCursor(7, 1);
  Brain.Screen.print("Right back: %f", rotation_value(rb));
}