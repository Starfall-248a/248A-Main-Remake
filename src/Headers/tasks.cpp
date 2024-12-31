#include "main.h"

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