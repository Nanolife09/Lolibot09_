#include "vex.h"
#include "robot-config.h"
#include <cmath>
#include <chrono>

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

/*
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
*/

int count = 0;

void mogo_lift_ctrl() {
  bool is_lifted = false;
  while (true) {
    if (ctrl.ButtonL1.pressing()) {
      is_lifted = true;
    }
    else if (ctrl.ButtonL2.pressing()) {
      is_lifted = false;
    }
    if (is_lifted) {
      while (lift.rotation(rotationUnits::raw) < 1000) {
        spin(lift, 70);
      }
      lift.setBrake(brakeType::hold);
    }
    else if (!is_lifted) {
      while (lift.rotation(rotationUnits::raw) > 250) {
        spin(lift, -70);
      }
      lift.setBrake(brakeType::hold);
    }
  }
}

void driver_ctrl() {
  thread chassis = tank_ctrl;
  thread mogo = mogo_lift_ctrl;
  chassis.join();
  mogo.join();
}
