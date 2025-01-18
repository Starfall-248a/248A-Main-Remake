#include "main.h"
#include "pros/rtos.hpp"

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

void autoIntake() {
    uint32_t lastCheckTime = pros::millis();

    while (true) {
        hooks.move(127);
        preroller.move(127);

        if (sorter.get_hue() >= 215 && sorter.get_hue() <= 240 && blueSide || sorter.get_hue() >= 0 && sorter.get_hue() <= 20 && !blueSide) {
            hooks.move(-127);
            preroller.move(-127);
        }

        // Check if 200 ms have passed since the last check
        if (pros::millis() - lastCheckTime >= 200) {
            lastCheckTime = pros::millis(); // Reset the timer

            if (hooks.get_actual_velocity() < 200) {
                hooks.move(-50);
                pros::delay(200);
                hooks.move(127);
            }
        }

        pros::delay(20); // Small delay to prevent excessive CPU usage
    }
}

void autoClamp() {
    clampa = true;
    while (clampa) {
        if (clamper.get_distance() < 25) {
            Clamp.set_value(true);
            break;
        }
        pros::delay(50); 
    }
}

void detectSorter(){
    sorter.set_led_pwm(100);
    if (reader.get_hue() >= 0 && reader.get_hue() <= 20) {
        blueSide = false;
    } else if (reader.get_hue() >= 215 && reader.get_hue() <= 240) {
        blueSide = true;
    }
}