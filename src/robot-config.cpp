#include "vex.h"
#include "driver.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller ctrl;

motor lf (PORT3, true);
motor lb (PORT12, true);
motor rf (PORT10);
motor rb (PORT20);
digital_out piston = digital_out(Brain.ThreeWirePort.A);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}