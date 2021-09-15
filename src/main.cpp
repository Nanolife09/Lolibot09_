/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\User                                             */
/*    Created:      Mon Sep 06 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "debug.h"
#include "driver.h"

using namespace vex;

competition Competition;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Competition.drivercontrol(driver_ctrl);
  Competition.drivercontrol(mogo_lift_ctrl);
}
