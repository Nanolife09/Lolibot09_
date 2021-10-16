#include "auton.h"
#include "driver.h"
#include "debug.h"

std::vector <int> target;

void encoder_forward (int target) {
  const float a = 0.075;
  while (rf.rotation(rotationUnits::raw) <= abs(target)){
    int power = 0;
    if (target < 0) {
      power = (rf.rotation(rotationUnits::raw) - target) * a;
    }
    else if (target > 0) {
      power = (target - rf.rotation(rotationUnits::raw)) * a;
    }
    spin(rf, power);
    spin(lf, power);
    spin(lb, power);
    spin(rb, power);
  }
  rf.stop();
  lf.stop();
  lb.stop();
  rb.stop();
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
  encoder_forward(1000);
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