#include "auton.h"
#include "driver.h"
#include "debug.h"

int sign;

void vertical (int target, int power = 100) {
  sign = (target < 0) ? -1 : 1;
  while (std::abs(rotation_value(lf)) < std::abs(target)) {
    spin(lf, power * sign);
    spin(rf, power * sign);
    spin(lb, power * sign);
    spin(rb, power * sign);
  }
  lf.stop();
  lb.stop();
  rb.stop();
  rf.stop();
  lf.resetRotation();
}

void turn (int target, int power = 100) {
  sign = (target < 0) ? -1 : 1;
  while (std::abs(rotation_value(lf)) < std::abs(target)) {
    spin(lf, power * sign);
    spin(rf, power * sign);
    spin(lb, -power * sign);
    spin(rb, -power * sign);
  }
  lf.stop();
  lb.stop();
  rb.stop();
  rf.stop();
  lf.resetRotation();
}

void red_right () {

}

void red_left () {

}

void blue_right () {

}

void blue_left () {

}

void skill () {

}

int auton_option = 4;

void auton_ctrl () {
  thread x;
  switch(auton_option) {
    case 0:
      x = red_left;
      x.join();
      break;
    case 1:
      x = red_right;
      x.join();
      break;
    case 2:
      x = blue_left;
      x.join();
      break;
    case 3:
      x = blue_right;
      x.join();
      break;
    case 4: 
      x = skill;
      x.join();
      break;
  }
  thread y = debug;
  y.join();
}