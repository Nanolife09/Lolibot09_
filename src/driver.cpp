#include "vex.h"
#include "robot-config.h"
#include "debug.h"
#include <cmath>

//------------------------------------------settings----------------------------------------//

int change_sens = 50; // set a axis value where the power of the chassis changes from fast to slow or viceversa (0 to 127)
int dead_zone = 50; // sets a maximum power of the chassis value for the span of slow mode (0 to 100)
int lift_power_limit = 50; // sets a minimum power value of the chassis when the lift is fully lifted (0 to 100)
int lift_rotation_error = 200;

int lift_max = 4000; // sets a maximum rotation of the liftl
int manual_power = 100; // sets a lift power when liftl is manually control (0 to 100)

int clamp_max = 400; // sets a max limit for the clamp
int clamp_power = 50; // sets a motor power for the clamp (0 to 100)

//-----------------------------DO NOT TOUCH ANYTHING FROM HERE----------------------//

void spin(motor name, int power) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

int lift_power = 0;

void manual_lift_ctrl() {
  while (true) {
    if (ctrl.ButtonR1.pressing() && liftl.rotation(rotationUnits::raw) < lift_max) {
      spin(liftl, manual_power);
      spin(liftr, manual_power);
    }
    else if (ctrl.ButtonR2.pressing() && liftl.rotation(rotationUnits::raw) > 100) {
      spin(liftl, -manual_power);
      spin(liftr, -manual_power);
    }
    else {
      spin(liftl,0);
      spin(liftr, 0);
      liftl.setBrake(brakeType::hold);
      liftr.setBrake(brakeType::hold);
    }
  }
}

void mogo_clamp_ctrl() {
  while (true) {
    if (ctrl.ButtonL1.pressing() && clamp.rotation(rotationUnits::raw) < clamp_max) {
      spin(clamp, clamp_power);
    }
    else if (ctrl.ButtonL2.pressing() && clamp.rotation(rotationUnits::raw) > 0) {
      spin(clamp, -clamp_power);
    }
    else {
      spin(clamp,0);
      clamp.setBrake(brakeType::hold);
    }
  }
}

void mogo_lift_ctrl() {
  thread manual = manual_lift_ctrl;
  thread clamp_ctrl = mogo_clamp_ctrl;
  while (true) {
    manual.join();
    clamp_ctrl.join();
    task::sleep(20);
  }
}

float left_power = 0;
float right_power = 0;

void tank_ctrl() {
  while (true) {
    //Left motors power calculations //DO NOT TOUCH THIS!
    // sets a motor power based on the axis value
    if (-change_sens <= ctrl.Axis3.value() && ctrl.Axis3.value() <= change_sens) {
      left_power = (dead_zone/std::pow(change_sens,3)) * std::pow(ctrl.Axis3.value(),3);
    }
    else {
      left_power = ctrl.Axis3.value();
    }
    
    // sets a motor power based on the rotation of the lift 
    left_power *= -(1 - (lift_power_limit * 0.01)) * liftl.rotation(rotationUnits::raw)/(lift_max + lift_rotation_error) + 1;

    //Right motors power calculations // DO NOT TOUCH THIS!
    // sets a motor power based on the axis value
    if (-change_sens < ctrl.Axis2.value() && ctrl.Axis2.value() < change_sens) {
      right_power = dead_zone/std::pow(change_sens,3) * std::pow(ctrl.Axis2.value(),3);
    }
    else if (ctrl.Axis2.value() < -change_sens) {
      right_power = ctrl.Axis2.value();
    }
    else if (change_sens < ctrl.Axis2.value()) {
      right_power = ctrl.Axis2.value();
    }

    // sets a motor power based on the rotation of the lift
    right_power *= -(1 - (lift_power_limit * 0.01)) * liftl.rotation(rotationUnits::raw)/(lift_max + lift_rotation_error) + 1;

    //motor spins
    spin(rf, right_power);
    spin(rb, right_power);
    spin(lf, left_power);
    spin(lb, left_power);

    //hardware friendly pause :)
    task::sleep(20);
  }
}

void test () {
  while (true) {
    spin(rf, ctrl.Axis2.value());
    spin(rb, ctrl.Axis2.value());
    spin(lf, ctrl.Axis3.value());
    spin(lb, ctrl.Axis3.value());
  }
}

void driver_ctrl() {
  thread tank = tank_ctrl;
  thread lift = mogo_lift_ctrl;
  while (true) {
    tank.join();
    lift.join();
  }
}