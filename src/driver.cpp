#include "vex.h"
#include "debug.h"
#include <cmath>

//------------------------------------------settings----------------------------------------//

int change_sens = 50; // set a axis value where the power of the chassis changes from fast to slow or viceversa (0 to 127)
int dead_zone = 50; // sets a maximum power of the chassis value for the span of slow mode (0 to 100)
int lift_power_limit = 50; // sets a minimum power value of the chassis when the lift is fully lifted (0 to 100)
int lift_rotation_error = 0; // sets a value so that the rotation error do not mess up the whole system (do not touch it unless it is necessary)

int lift_max = 4000; // sets a maximum rotation of the lift
int lift_power = 100; // sets a lift power (0 to 100)

int clamp_max = 700; // sets a max limit for the clamp
int clamp_power = 80; // sets a motor power for the clamp (0 to 100)

int back_max = 1450; // sets a max limit for the back
int back_power = 50; // sets a power for the back

//-----------------------------DO NOT TOUCH ANYTHING FROM HERE----------------------//

void spin(motor name, int power) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

int left_power;
int right_power;

void manual_lift_ctrl() {
  while (true) {
    if (ctrl.ButtonR1.pressing() && rotation_value(liftl) < lift_max) {
      spin(liftl, lift_power);
      spin(liftr, lift_power);
    }
    else if (ctrl.ButtonR2.pressing() && rotation_value(liftl) > lift_rotation_error) {
      spin(liftl, -lift_power);
      spin(liftr, -lift_power);
      if (rotation_value(liftl) > lift_rotation_error) {
        clamp.spinTo(clamp_max, rotationUnits::raw, clamp_power, velocityUnits::pct);
      }
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

void back_ctrl() {
  //A for up
  while (true) {
    if (ctrl.ButtonX.pressing() && rotation_value(back) < back_max) {
      spin(back, back_power);
    }
    //x for down
    else if (ctrl.ButtonA.pressing() && rotation_value(back) > 0) {
      spin(back, -back_power);
    }
    else {
      back.stop();
      back.setBrake(brakeType::hold);
    }
  }
}

void mogo_lift_ctrl() {
  thread Lift = manual_lift_ctrl;
  thread Clamp_ctrl = mogo_clamp_ctrl;
  while (true) {
    Lift.join();
    Clamp_ctrl.join();
    task::sleep(20);
  }
}

void tank_ctrl() {
  while (true) {
    if (Brain.Battery.capacity() > 50) {
      //Left motors power calculations //DO NOT TOUCH THIS!
      // sets a motor power based on the axis value
      if (-change_sens <= ctrl.Axis3.value() && ctrl.Axis3.value() <= change_sens) {
        left_power = (dead_zone/std::pow(change_sens,3)) * std::pow(ctrl.Axis3.value(),3);
      }
      else {
        left_power = ctrl.Axis3.value();
      }

      //Right motors power calculations // DO NOT TOUCH THIS!
      // sets a motor power based on the axis value
      if (-change_sens < ctrl.Axis2.value() && ctrl.Axis2.value() < change_sens) {
        right_power = dead_zone/std::pow(change_sens,3) * std::pow(ctrl.Axis2.value(),3);
      }
      else {
        right_power = ctrl.Axis2.value();
      }
    }
    else {
      lift_power_limit = 50;
      left_power = ctrl.Axis3.value();
      right_power = ctrl.Axis2.value();
    }

    // sets a motor power based on the rotation of the lift 
    left_power *= -(1 - (lift_power_limit * 0.01)) * liftl.rotation(rotationUnits::raw)/(lift_max + lift_rotation_error) + 1;

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

void driver_ctrl() {
  thread tank = tank_ctrl;
  thread lift = mogo_lift_ctrl;
  thread Back = back_ctrl;
  while (true) {
    tank.join();
    lift.join();
    Back.join();
  }
}