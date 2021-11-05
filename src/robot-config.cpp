#include "vex.h"
#include "driver.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller ctrl;

motor lf    (PORT5, true);
motor lb    (PORT4, true);
motor rf    (PORT9);
motor rb    (PORT12);
motor liftr (PORT3);
motor liftl (PORT10, true);
motor back  (PORT4);
motor clamp (PORT6, true);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}