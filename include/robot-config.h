using namespace vex;

extern brain Brain;
extern controller ctrl;

extern motor lb;
extern motor rf;
extern motor rb;
extern motor lf;
extern digital_out piston;
extern encoder encoderR;
extern encoder encoderL;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
