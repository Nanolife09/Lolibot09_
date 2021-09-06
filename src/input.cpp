#include "vex.h"

controller ctrl;

int axis1, axis2, axis3, axis4;

bool buttonA, buttonB, buttonX, buttonY;

void input_update () {
  while (true) {
    axis1 = ctrl.Axis1.value();
    axis2 = ctrl.Axis2.value();
    axis3 = ctrl.Axis3.value();
    axis4 = ctrl.Axis4.value();
  
    buttonA = (ctrl.ButtonA.pressing()) ? true : false;
    buttonB = (ctrl.ButtonB.pressing()) ? true : false;
    buttonX = (ctrl.ButtonX.pressing()) ? true : false;
    buttonY = (ctrl.ButtonY.pressing()) ? true : false;
  }
}