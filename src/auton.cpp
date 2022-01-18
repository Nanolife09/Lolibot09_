#include "auton.h"
#include "driver.h"
#include "debug.h"
#include <chrono>
#include <vector>

const float left_KP = 0.048;
const float left_KI = 0.000009;
const float left_KD = 0.0026;
const float right_KP = 0.048;
const float right_KI = 0.0000085;
const float right_KD = 0.0012;
int right_prev_error = 0, left_prev_error = 0, right_position_error = 0, left_position_error = 0, time_error = 0;
float right_proportional = 0, right_integeral = 0, right_derivative = 0, left_proportional = 0, left_integeral = 0, left_derivative = 0;

auto start = std::chrono::high_resolution_clock::now();
auto end = std::chrono::high_resolution_clock::now();

void PID_forward(int target) {
  lf.resetRotation();
  lb.resetRotation();
  rf.resetRotation();
  rb.resetRotation();
  start = std::chrono::high_resolution_clock::now();
  while (std::abs(rotation_value(lf)) <= std::abs(target)) {
    end = std::chrono::high_resolution_clock::now();
    time_error = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    right_prev_error = rotation_value(rf);
    left_prev_error = rotation_value(lf);
    right_position_error = std::abs(target) - std::abs(rotation_value(rf));
    left_position_error = std::abs(target) - std::abs(rotation_value(lf));
    right_proportional = right_KP * right_position_error;
    left_proportional = left_KP * left_position_error;
    right_integeral = right_KI * right_position_error * time_error;
    left_integeral = left_KI * left_position_error * time_error;
    right_derivative = right_KD * right_position_error / time_error;
    left_derivative = left_KD * left_position_error / time_error;
    right_power = right_proportional + right_integeral + right_derivative;
    left_power = left_proportional + left_integeral + left_derivative;
    if (left_power < 1) left_power = 1;
    if (right_power < 1) right_power = 1;
    if (target < 0) {
      left_power *= -1;
      right_power *= -1;
    }
    spin(lf, left_power);
    spin(lb, left_power);
    spin(rf, right_power);
    spin(rb, right_power);
  } 
  lf.resetRotation();
  lb.resetRotation();
  rf.resetRotation();
  rb.resetRotation();
  lf.stop();
  lb.stop();
  rf.stop();
  rb.stop();
}

void clamp_up () {
  clamp.spinTo(1000, rotationUnits::raw, 80, velocityUnits::pct);
  clamp.stop();
}

void auton_ctrl() {
  PID_forward(2000);
  PID_forward(-2000);
  clamp_up();
}