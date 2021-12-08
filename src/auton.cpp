#include "auton.h"
#include "driver.h"
#include "debug.h"
#include <chrono>

const float KP = 0.003;
const float KI = 0.0002;
const float KD = 0.001;
int right_prev_error = 0, left_prev_error = 0, right_position_error = 0, left_position_error = 0, time_error = 0;
float right_proportional = 0, right_integeral = 0, right_derivative = 0, left_proportional = 0, left_integeral = 0, left_derivative = 0;

auto start = std::chrono::high_resolution_clock::now();
auto end = std::chrono::high_resolution_clock::now();

void PID_forward(float target) {
  start = std::chrono::high_resolution_clock::now();
  while (std::abs(rotation_value(lf)) < std::abs(target)) {
    end = std::chrono::high_resolution_clock::now();
    time_error = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    right_prev_error = right_position_error;
    left_prev_error = left_position_error;
    right_position_error = std::abs(target) - std::abs(rotation_value(rf));
    left_position_error = std::abs(target) - std::abs(rotation_value(lf));
    right_proportional = KP * right_position_error;
    left_proportional = KP * left_position_error;
    right_integeral = KI * right_position_error * time_error;
    left_integeral = KI * left_position_error * time_error;
    right_derivative = KD * right_position_error / time_error;
    left_derivative = KD * left_position_error / time_error;
    right_power = right_proportional + right_integeral + right_derivative;
    left_power = left_proportional + left_integeral + left_derivative;
    if (target < 0) {
      left_power *= -1;
      right_power *= -1;
    }
    spin(lf, left_power);
    spin(lb, left_power);
    spin(rf, right_power);
    spin(rb, right_power);
    vex::task::sleep(20);
  } 
  vex::task::sleep(50);
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
  lf.setBrake(brakeType::hold);
  lb.setBrake(brakeType::hold);
  rf.setBrake(brakeType::hold);
  rb.setBrake(brakeType::hold);
  display_rotation_value();
}

void auton_ctrl() {
  lf.resetRotation();
  lb.resetRotation();
  rf.resetRotation();
  rb.resetRotation();
  PID_forward(1000);
  PID_forward(1000);
}