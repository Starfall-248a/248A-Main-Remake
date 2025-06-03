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
    
}

void redStandard(){
    
}

void blueInt(){
    
}

void skills(){
    chassis.setPose(-51.5, 30.75, 270);
    pros::Task autoClamp(autoClampTask);
    chassis.moveToPoint(-23.5, 47.5, 1000, {.forwards = false});
    if(Clamp.get_value() == HIGH){
        chassis.cancelMotion();
    }
    chassis.turnToPoint(-23.5, 23.5, 750);
    pros::Task intake(RintakeTask);
    chassis.moveToPoint(-23.5, 23.5, 1000);
    chassis.turnToPoint(-3.5, 43.5, 1000);
    chassis.moveToPoint(-3.5, 43.5, 1500, {.earlyExitRange = 2});
    chassis.swingToHeading(0, lemlib::DriveSide::LEFT, 750, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .minSpeed = 50, .earlyExitRange = 2});
    chassis.moveToPoint(0, 53.5, 500);
    chassis.moveToPoint(0, 47.5, 500, {.forwards = false});
    chassis.turnToPoint(23.5, 47.5, 750);
    chassis.moveToPoint(23.5, 47.5, 1250);
    chassis.turnToPoint(-47.5, 47.5, 1000);
    chassis.moveToPoint(-47.5, 47.5, 2000);
    chassis.turnToPoint(-100, 100, 750);
    chassis.moveToPoint(-60, 60, 1000, {.maxSpeed = 75});
    chassis.moveToPoint(-50, 50, 750, {.maxSpeed = 75});
    chassis.turnToPoint(-50, 50, 750, {.forwards = false});
    chassis.moveToPoint(-60, 60, 750, {.forwards = false});
}