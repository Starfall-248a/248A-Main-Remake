#include "main.h"
#include "pros/rtos.hpp"

std::string detectedColor = "None";
bool objectProcessed = false;

void odomTask() {
  console.printf("The robot's heading is %f\n", imu.get_heading());
  console.printf("The robot's x position is %f\n", chassis.getPose().x);
  console.printf("The robot's y position is %f\n", chassis.getPose().y);
  pros::delay(50);
}

void LBTask() {
  while (true) {
    liftControl();
    pros::delay(10);
  }
}

void autoClampTask() {
  while (true) {
    // Check if the distance sensor detects a small distance (e.g., less than 25
    // mm)
    if (clamper.get_distance() < 25) {
      Clamp.set_value(true); // Set the clamp to HIGH
    }
    pros::delay(25); // Small delay to prevent excessive CPU usage
  }
}

void BintakeTask() {
  uint32_t lastCheckTime = pros::millis();
  sorter.set_led_pwm(100);
  while (true) {
    if (!objectProcessed) {
      int hue = sorter.get_hue();
      if (hue >= 0 && hue <= 20) {
        detectedColor = "Red";
      } else if (hue >= 160 && hue <= 240) {
        detectedColor = "Blue";
      } else {
        detectedColor = "None";
      }
    }

    if (Ejector.get_distance() < 25) {
      if (detectedColor == "Red") {
        hooks.move_velocity(-600);
        pros::delay(150);
        hooks.move_velocity(600);
        objectProcessed = true;
      }
    } else {
      objectProcessed = false;
    }

    if (pros::millis() - lastCheckTime >= 300) {
      if (hooks.get_actual_velocity() < 150 && currState != 1) {
        hooks.move_velocity(-600);
        pros::delay(150);
        hooks.move_velocity(600);
        lastCheckTime = pros::millis();
      } else {
        lastCheckTime = pros::millis();
      }
    }

    pros::delay(50);
  }
}

void RintakeTask() {
  uint32_t lastCheckTime = pros::millis();
  sorter.set_led_pwm(100);
  while (true) {
    if (!objectProcessed) {
      int hue = sorter.get_hue();
      if (hue >= 0 && hue <= 20) {
        detectedColor = "Red";
      } else if (hue >= 160 && hue <= 240) {
        detectedColor = "Blue";
      } else {
        detectedColor = "None";
      }
    }

    if (Ejector.get_distance() < 25) {
      if (detectedColor == "Blue") {
        hooks.move_velocity(-600);
        pros::delay(150);
        hooks.move_velocity(600);
        objectProcessed = true;
      }
    } else {
      objectProcessed = false;
    }

    if (pros::millis() - lastCheckTime >= 300) {
      if (hooks.get_actual_velocity() < 150 && currState != 1) {

        hooks.move_velocity(-600);
        pros::delay(150);
        hooks.move_velocity(600);

        lastCheckTime = pros::millis();
      } else {

        lastCheckTime = pros::millis();
      }
    }

    pros::delay(50);
  }
}

// Define the threshold value for the Tracker sensor
const int threshold = 1000; // Adjust this value based on your specific requirements

void cancelDrivetrainTask() {
    while (true) {
        // Check the Tracker sensor value
        int trackerValue = Tracker.get_value();

        // If the Tracker sensor value exceeds the threshold, stop the drivetrain
        if (trackerValue > threshold) {
            chassis.cancelMotion();
            break; // Exit the loop to cancel the task
        }

        pros::delay(10); // Small delay to prevent excessive CPU usage
    }
    pros::Task::current().remove(); // Exit the task
}

pros::Task lineTrackerTask(cancelDrivetrainTask);