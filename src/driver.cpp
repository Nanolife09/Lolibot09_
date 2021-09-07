#include "vex.h"
#include "robot-config.h"
#include "input.h"

void spin(motor name, int power) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

void tank_ctrl() {
  spin(rf, ctrl.Axis1.value());
  spin(rb, ctrl.Axis1.value());
  spin(lf, ctrl.Axis3.value());
  spin(lb, ctrl.Axis3.value());
}

void driver_ctrl() {
  thread update = input_update; 
  update.join();
  while (true) {
    tank_ctrl();
    task::sleep(20);
  }
}