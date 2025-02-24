#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

int wallMech = 0;
static bool toggle{false};
static bool inLifter{false};
bool toggleSorter{true};
int startTime;

void setIntakes() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        hooks.move(127);
        preroller.move(127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  
        hooks.move(-127);
        preroller.move(-127);
    } else {
        hooks.move(0);
        preroller.move(0);
    }
}

void setClamp() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
    if (Clamp.get_value() == LOW) {
      Clamp.set_value(HIGH);
    } else {
      Clamp.set_value(LOW);
    }
  }
}

// Define the flag to indicate when the task should run
bool clampTaskRunning = false;

// Define the task function
void primeClampTask(void* param) {
    while (clampTaskRunning) {
        // Check if the distance sensor detects a small distance (e.g., less than 25 mm)
        if (clamper.get_distance() < 25) {
            Clamp.set_value(true); // Set the clamp to HIGH
            clampTaskRunning = false; // Stop the task
        }
        pros::delay(50); // Small delay to prevent excessive CPU usage
    }
    ledManager.flow(0x421C52, 0x732C7B);
    pros::Task::current().remove(); // Exit the task
}

// Function to start the autoClampTask
void startAutoClampTask() {
    if (!clampTaskRunning) {
        clampTaskRunning = true;
        pros::Task primeClamp(primeClampTask, NULL, "Auto Clamp Task");
    }
}

void setAutoClamp(){
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
    startAutoClampTask();
    ledManager.rainbow(1);
  }
}

void setLifter() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
    if(!inLifter) {
      inLift.set_value(true);
      inLifter = !inLifter;
    } else {
      inLift.set_value(false);
      inLifter = !inLifter;
    }
  }
}

void setLB(){
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
    nextState();
  } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
    currState = 2;
    target = states[currState];
  } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    currState = 1;
    target = states[currState];
  } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_A) && currState == 1){
    currState = 0;
    target = states[currState];
  }
}

void setDoink() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
    if (doink.get_value() == LOW) {
      doink.set_value(HIGH);
    } else {
      doink.set_value(LOW);
    }
  }
}

void setTipper() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
    if (tipper.get_value() == LOW) {
      tipper.set_value(HIGH);
    } else {
      tipper.set_value(LOW);
    }
  }
}

void ledTime() {
  driverClock.start();
  driverClock.waitUntil(43 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(42 * 1000);
  TimeLED.off();
  driverClock.waitUntil(41 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(40 * 1000);
  TimeLED.off();
  driverClock.waitUntil(39 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(38 * 1000);
  TimeLED.off();
  driverClock.waitUntil(37 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(36 * 1000);
  TimeLED.off();
  driverClock.waitUntil(35 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(34 * 1000);
  TimeLED.off();
  driverClock.waitUntil(33 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(32 * 1000);
  TimeLED.off();
  driverClock.waitUntil(31 * 1000);
  TimeLED.setColor(0xE5195E);
  underglow.setColor(0xE5195E);
  driverClock.waitUntil(.2 * 1000);
  Clamp.set_value(LOW);
}