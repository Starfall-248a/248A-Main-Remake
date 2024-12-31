#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.hpp"

//Assets
ASSET(SkillsP1_txt)
ASSET(SkillsP2_txt)

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

void redSoloWP(){
    chassis.setPose(-60, -13.25, 323);
    currState = 2;
    pros::delay(1250);
    chassis.moveToPoint(-43.687, -36.394, 1750);
    chassis.turnToPoint(-23.5, -23.5, 750);
    chassis.moveToPoint(-23.5, -23.5, 1500, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
}

void blueSoloWP(){
    blueSide = true;
    //grab first goal
    chassis.setPose(48.912,-36.043,115);
    chassis.moveToPoint(29.665, -26.604, 2000, { .forwards = false, .maxSpeed = 75}, false);
    Clamp.set_value(HIGH);
    intake.move(127);
    pros::delay(100);
    //grab 1st ring
    chassis.turnToPoint(21, -49, 1500);
    chassis.moveToPoint(21, -49, 2000, {}, false);
    pros::delay(1750);
    //go to alliance stake 2 stack
    chassis.turnToPoint(48, 4, 1250, {}, false);
    Clamp.set_value(LOW);
    chassis.moveToPoint(48, 4, 2250);
    hooks.brake();
    chassis.waitUntil(10);
    preroller.move_velocity(200);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    //sort out blue ring
    chassis.turnToPoint(25.187, 21.741, 1000, {.forwards = false});
    chassis.waitUntil(15);
    chassis.moveToPoint(25.187, 21.741, 1500, {.forwards = false, .maxSpeed = 65}, false);
    chassis.waitUntil(5);
    Clamp.set_value(HIGH);
    pros::delay(100);
    hooks.move(127);
    chassis.turnToPoint(19, 5.5, 1000);
    chassis.moveToPoint(19, 5.5, 1500, {.maxSpeed = 50});
    chassis.waitUntil(5);
    intake.brake();
}

void fourRingRed(){
    //grab first goal
    chassis.setPose(-48.912,-36.043,245);
    chassis.moveToPoint(-29.665, -26.604, 2000, { .forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    intake.move(127);
    pros::delay(100);
    //grab 1st ring
    chassis.turnToPoint(-24, -49, 1500);
    chassis.moveToPoint(-24, -49, 2000, {}, false);
    pros::delay(1750);
    //go to alliance stake 2 stack
    chassis.turnToPoint(-50, 4, 1250, {}, false);
    chassis.moveToPoint(-50, 4, 2250);
    chassis.waitUntil(5);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    chassis.moveToPoint(-34.526, -18.939, 1250, {.forwards = false, .maxSpeed = 50});
    chassis.moveToPoint(-23.5, 0,1500);
    intake.brake();
}

void fourRingBlue(){
    blueSide = true;
    //grab first goal
    chassis.setPose(48.912,-36.043,115);
    chassis.moveToPoint(29.665, -26.604, 2000, { .forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    intake.move(127);
    pros::delay(100);
    //grab 1st ring
    chassis.turnToPoint(24, -49, 1500);
    chassis.moveToPoint(24, -49, 2000, {}, false);
    pros::delay(1750);
    //go to alliance stake 2 stack
    chassis.turnToPoint(50, 4, 1250, {}, false);
    chassis.moveToPoint(50, 4, 2250);
    chassis.waitUntil(5);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    chassis.moveToPoint(34.526, -18.939, 1250, {.forwards = false, .maxSpeed = 50});
    chassis.moveToPoint(23.5, 0,1500);
    intake.brake();

}

void disruptRed(){
    chassis.setPose(-46.489,31.313,70);
    inLift.set_value(HIGH);
    chassis.moveToPoint(-6, 46, 2000, {.maxSpeed = 100});
    chassis.moveToPoint(-23.5, 47, 1500, {.forwards = false, .maxSpeed = 60}, false);
    chassis.turnToPoint(-23.5, 23.5, 1000, {.forwards = false});
    chassis.moveToPoint(-23.5, 23.5, 1250, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    chassis.moveToPoint(-23.5, 23.5, 750, {.forwards = false, .maxSpeed = 70}, false);
    intake.move(127);
    inLift.set_value(LOW);
    pros::delay(200);
    chassis.moveToPoint(-19.341, 41.123, 1000);
    chassis.swingToHeading(180, lemlib::DriveSide::LEFT, 1250, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 60});
    chassis.turnToPoint(-48.191, 19.983, 1500);
    chassis.moveToPoint(-48.191, 19.983, 1500);
}

void disruptBlue(){
    chassis.setPose(46.489,31.313,290);
    inLift.set_value(HIGH);
    chassis.moveToPoint(6, 46, 2000, {.maxSpeed = 100});
    chassis.moveToPoint(23.5, 47, 1500, {.forwards = false, .maxSpeed = 60}, false);
    chassis.turnToPoint(23.5, 23.5, 1000, {.forwards = false});
    chassis.moveToPoint(23.5, 23.5, 1250, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    chassis.moveToPoint(23.5, 23.5, 750, {.forwards = false, .maxSpeed = 70}, false);
    intake.move(127);
    inLift.set_value(LOW);
    pros::delay(200);
    chassis.moveToPoint(19.341, 41.123, 1000);
    chassis.swingToHeading(180, lemlib::DriveSide::RIGHT, 1250, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 60});
    chassis.turnToPoint(48.191, 19.983, 1500);
    chassis.moveToPoint(48.191, 19.983, 1500);
}

void rushRed(){
    chassis.setPose(51, -60,90);
    chassis.moveToPoint(15, -60, 1250, {.forwards = false});
    chassis.turnToPoint(8.61, -53.904, 1000);
    chassis.moveToPoint(8.61, -53.904, 1000);
}

void rushBlue(){
    blueSide = true;
    chassis.setPose(51, -60,90);
    chassis.moveToPoint(15, -60, 1100, {.forwards = false});
    chassis.turnToPoint(8.61, -55, 650, {.forwards = false});
    chassis.moveToPoint(6, -53, 1000, {.forwards = false, .maxSpeed = 80}, false);
    // Clamp.set_value(HIGH);
    // intake.move(127);
    // pros::delay(100);
    // chassis.swingToPoint(25.42, -41.763, lemlib::DriveSide::LEFT, 1000);
}

void skills(){
    chassis.setPose(-60.5, 0, 90);
    hooks.move(127);
    pros::delay(750);
    preroller.move(127);
    chassis.moveToPoint(-49, 0, 1250);
    chassis.turnToPoint(-49, -50, 1250);
    chassis.moveToPoint(-49, 16, 1750, {.forwards = false, .maxSpeed = 70}, false);
    Clamp.set_value(HIGH);
    pros::delay(100);
    chassis.follow(SkillsP1_txt, 10, 20000);
    chassis.turnToPoint(-55.828, 61.431, 750, {.forwards = false}, false);
    Clamp.set_value(LOW);
    chassis.moveToPoint(-55.828, 61.431, 750, {.forwards = false, .maxSpeed = 70}, false);
    chassis.moveToPose(-49, -15, 0, 5000);
    chassis.follow(SkillsP2_txt, 10, 20000);
    chassis.turnToPoint(-55.828, -61.431, 750, {.forwards = false}, false);
    Clamp.set_value(LOW);
    chassis.moveToPoint(-55.828, -61.431, 750, {.forwards = false, .maxSpeed = 70}, false);
    hooks.brake();
    chassis.moveToPoint(0, -59, 2000, {.earlyExitRange = 5});
    chassis.moveToPose(47.133, -6.042, 180, 3000, {.lead = .55}, false);
    Clamp.set_value(HIGH);
}