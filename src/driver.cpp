#include "vex.h"
#include "robot-config.h"
#include <cmath>

//------------------------------------------settings----------------------------------------//

int change_sens = 80; // set a axis value where the power of the chassis changes from fast to slow or viceversa

int liftl_max = 650; // sets a maximum rotation of the liftl
int manual_power = 70; // sets a liftl power when liftl is manually control

int clamp_max = 0; // sets a max limit for the clamp
int clamp_power = 0; // sets a motor power for the clamp

//-----------------------------DO NOT TOUCH ANYTHING FROM HERE----------------------//

void spin(motor name, int power) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

int lift_power = 0;

void toggle_lift_up() {
  while (liftl.rotation(rotationUnits::raw) < liftl_max) {
    lift_power = (100/std::pow(liftl_max/2,2)) * liftl.rotation(rotationUnits::raw) * (liftl.rotation(rotationUnits::raw) - liftl_max);
    spin(liftl, lift_power);
    spin(liftr, lift_power);
  }
  liftl.stop();
  liftr.stop();
}

void toggle_lift_down() {
  while (liftl.rotation(rotationUnits::raw) > 0) {
    lift_power = (100/std::pow(liftl_max/2,2)) * liftl.rotation(rotationUnits::raw) * (liftl.rotation(rotationUnits::raw) - liftl_max);
    spin(liftl, -lift_power);
    spin(liftr, -lift_power);
    task::sleep(20);
  }
  liftl.stop();
  liftr.stop();
  clamp.rotateTo(0, rotationUnits::raw, clamp_power, velocityUnits::pct);
}

void toggle_lift_ctrl() {
  ctrl.ButtonL1.pressed(toggle_lift_up);
  ctrl.ButtonL2.pressed(toggle_lift_down);
}

void manual_lift_ctrl() {
  if (ctrl.ButtonR1.pressing() && liftl.rotation(rotationUnits::raw) < liftl_max) {
    spin(liftl, manual_power);
    spin(liftr, manual_power);
  }
  else if (ctrl.ButtonR2.pressing() && liftl.rotation(rotationUnits::raw) > 0) {
    spin(liftl, -manual_power);
    spin(liftr, -manual_power);
  }
}

void mogo_lift_ctrl() {
  thread toggle = toggle_lift_ctrl;
  thread manual = manual_lift_ctrl;
  while (true) {
    toggle.join();
    manual.join();
    task::sleep(20);
  }
}

void tank_ctrl() {
  int left_power = 0;
  int right_power = 0;
  while (true) {
    //Left motors power calculations //DO NOT TOUCH THIS!
    // sets a motor power based on the axis value
    if (-change_sens < ctrl.Axis2.value() && ctrl.Axis2.value() < change_sens) {left_power = (50/std::pow(change_sens,3));}
    else if (ctrl.Axis2.value() < -change_sens) {left_power = 5/2 * (ctrl.Axis2.value() + 50) - 50;}
    else if (change_sens < ctrl.Axis2.value()) {left_power = 5/2 * (ctrl.Axis2.value() - 50) + 50;}
    // sets a motor power based on the rotation of the lift
    if (ctrl.Axis2.value() < 0) {left_power *= -(std::sqrt((2500/-liftl_max)*(liftl.rotation(rotationUnits::raw) -liftl_max)) + 50);}
    else if (0 < ctrl.Axis2.value()) {left_power *= (std::sqrt((2500/-liftl_max)*(liftl.rotation(rotationUnits::raw) -liftl_max)) + 50);}
    //Right motors power calculations // DO NOT TOUCH THIS!
    // sets a motor power based on the axis value
    if (-change_sens < ctrl.Axis3.value() && ctrl.Axis3.value() < change_sens){right_power = (50/std::pow(change_sens,3));}
    else if (ctrl.Axis3.value() < -change_sens) {right_power = 5/2 * (ctrl.Axis3.value() + 50) - 50;}
    else if (change_sens < ctrl.Axis3.value()) {right_power = 5/2 * (ctrl.Axis3.value() - 50) + 50;}
    // sets a motor power based on the rotation of the liftl
    if (ctrl.Axis3.value() < 0) {right_power *= -(std::sqrt((2500/-liftl_max)*(liftl.rotation(rotationUnits::raw) -liftl_max)) + 50);}
    else if (0 < ctrl.Axis3.value()) {right_power *= (std::sqrt((2500/-liftl_max)*(liftl.rotation(rotationUnits::raw) -liftl_max)) + 50);}

    //motor spins
    spin(rf, right_power);
    spin(rb, right_power);
    spin(lf, left_power);
    spin(lb, left_power);

    //hardware friendly pause :)
    task::sleep(20);
  }
}

void driver_ctrl() {
  thread tank = tank_ctrl;
  thread mogo = mogo_lift_ctrl;
  while (true) {
    tank.join();
    mogo.join();
    task::sleep(20);
  }
}