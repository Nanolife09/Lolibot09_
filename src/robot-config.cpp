#include "vex.h"
#include "driver.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller ctrl;

motor lf (PORT5, true);
motor lb (PORT4, true);
motor rf (PORT9);
motor rb (PORT10);
motor liftr (PORT20);
motor liftl (PORT11, true);
motor clamp (PORT16);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}