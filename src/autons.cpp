#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.hpp"

void moveRelative(float distance, float maxSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed});
    }
};

void blueStandard(){
    chassis.setPose(58.75, -16.25, 90);
    chassis.swingToHeading(180, lemlib::DriveSide::LEFT, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 90, .earlyExitRange = 2});
    chassis.moveToPoint(47.5, 0, 750, {.forwards = false, .minSpeed = 50});
    chassis.waitUntil(7);
    Clamp.set_value(HIGH);
    chassis.waitUntilDone();
    pros::Task intake(BintakeTask, "Intake function");

}