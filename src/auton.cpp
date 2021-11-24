#include "auton.h"
#include "driver.h"
#include "debug.h"

void auto_lift_up () {
  while (rotation_value(liftl) < lift_max) {
    spin(liftl, 100);
    spin(liftr, 100);
  }
  liftl.stop();
  liftr.stop();
  liftl.setBrake(brakeType::hold);
  liftr.setBrake(brakeType::hold);
}

void auto_lift_down () {
  while (rotation_value(liftl) > 0) {
    spin(liftl, -100);
    spin(liftr, -100);
  }
  liftl.stop();
  liftr.stop();
  liftl.setBrake(brakeType::hold);
  liftr.setBrake(brakeType::hold);
}

void auto_clamp_up () {
  while (rotation_value(clamp) < clamp_max) {
    spin(clamp, 100);
  }
  clamp.stop();
  clamp.setBrake(brakeType::hold);
}

void auto_clamp_down () {
  while (rotation_value(clamp) > 0) {
    spin(clamp, -100);
  } 
  clamp.stop();
  clamp.setBrake(brakeType::hold);
}

void auto_back_up () {
  while (rotation_value(back) < back_max) {
    spin(back, 100);
  }
  back.stop();
  back.setBrake(brakeType::hold);
}

void auto_back_down () {
  while (rotation_value(back) > 0) {
    spin(back, -100);
  }
  back.stop();
}

thread t1;
thread t2;
thread t3;

void chassis_fwd (int target, int power, bool LIFT = false, bool CLAMP = false, bool BACK = false) {
  if (LIFT) {
    t1 = auto_lift_up;
  }
  else {
    t1 = auto_lift_down;
  }
  if (CLAMP) {
    t2 = auto_clamp_up; 
  } else {
    t2 = auto_clamp_down;
  }
  if (BACK) {
    t3 = auto_back_up;
  }
  else {
    t3 = auto_back_down;
  }
  t1.join(); 
  t2.join(); 
  t3.join();
  while(std::abs(rotation_value(lf)) < std::abs(target)){
    spin(lf, power);
    spin(lb, power);
    spin(rf, power);
    spin(rb, power);
  }
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
  lf.resetRotation();
  lb.resetRotation();
  rf.resetRotation();
  rb.resetRotation();
}

void chassis_turn (int target, int power, bool LIFT = false, bool CLAMP = false, bool BACK = false) {
  if (LIFT)  {
    t1 = auto_lift_up; 
  }
  else {
    t1 = auto_lift_down;
  }
  if (CLAMP) {
    t2 = auto_clamp_up;
  }
  else {
    t2 = auto_clamp_down;
  }
  if (BACK)  {
    t3 = auto_back_up; 
  }
  else {
    t3 = auto_back_down;
  }
  t1.join(); 
  t2.join(); 
  t3.join();
  while(std::abs(rotation_value(lf)) < std::abs(target)){
    spin(lf, power);
    spin(lb, power);
    spin(rf, -power);
    spin(rb, -power);
  }
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
  lf.resetRotation();
  lb.resetRotation();
  rf.resetRotation();
  rb.resetRotation();
}

void Left () {

}

void Right () {

}

void SKILL () {
  chassis_fwd(1000, 100);
  chassis_fwd(1000, 100, true);
  chassis_fwd(1000, 100, false, true);
  chassis_fwd(1000, 100, false, false, true);
}

int auton_option = 2;

void auton_ctrl () {
  switch (auton_option) {
    case 0:
      Left();
      break;
    case 1:
      Right();
      break;
    case 2:
      SKILL();
      break;
  }
}