#include "vex.h"
#include "robot-config.h"
#include <cmath>

void spin(motor name, int power) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

int power_limit (int value, int limits) {
  if (abs(value) < limits) {
    return value * 0.3;
  }
  else {
    return value;
  }
}

void tank_ctrl() {
  while (true) {
    spin(rf, power_limit(ctrl.Axis2.value(), 70));
    spin(rb, power_limit(ctrl.Axis2.value(), 70));
    spin(lf, power_limit(ctrl.Axis3.value(), 70));
    spin(lb, power_limit(ctrl.Axis3.value(), 70));
    task::sleep(20);
  }
}

void piston_ctrl() {
  while (true) {
    if (ctrl.ButtonL1.pressing()) {
      piston.set(true);
    }
    else {
      piston.set(false);
    }
    task::sleep(20);
  }
}

void driver_ctrl() {
  thread chassis = tank_ctrl;
  thread piston = piston_ctrl;
  chassis.join();
  piston.join();
}
