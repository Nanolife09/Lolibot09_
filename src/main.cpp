#include "debug.h" 
#include "driver.h"
#include "auton.h"
#include "vex.h"

using namespace vex;

int main() {
  vexcodeInit();
  Competition.drivercontrol(driver_ctrl);
  Competition.autonomous(auton_ctrl);
  display_rotation_value(2);
}