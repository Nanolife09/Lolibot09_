#include "vex.h"
#include "driver.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

motor lf (PORT1);
motor lb (PORT2);
motor rf (PORT3);
motor rb (PORT4);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}