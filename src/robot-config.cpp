#include "vex.h"
#include "driver.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller ctrl;

motor lf (PORT14, true);
motor lb (PORT17, true);
motor rf (PORT11);
motor rb (PORT10);
motor liftr (PORT3, true);
motor liftl (PORT2, true);
motor clamp (PORT1);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}