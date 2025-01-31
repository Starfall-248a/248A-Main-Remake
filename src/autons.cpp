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

void redHighNeg(){
    chassis.setPose(-49.235, 36.683, 297);
    chassis.moveToPoint(-23.5, 23.5, 1050, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    pros::delay(150);
    pros::Task intake(RintakeTask, "Intake function");
    chassis.turnToPoint(-23.5, 47.5, 1000);
    chassis.moveToPoint(-23.5, 51, 1000);
    chassis.turnToPoint(-10, 56, 1000);
    chassis.moveToPoint(-10, 56, 1250, {.maxSpeed = 75});
    chassis.moveToPoint(-17.25, 44.5, 1100, {.forwards = false, .maxSpeed = 75, .minSpeed = 60, .earlyExitRange = 2});
    chassis.turnToPoint(-10, 43.5, 1000, {.minSpeed = 60, .earlyExitRange = 3});
    chassis.moveToPoint(-17, 43.5, 1000, {.maxSpeed = 75});
    pros::delay(100);
    chassis.moveToPoint(-9, 43.5, 1500, {.maxSpeed = 75});
    chassis.moveToPoint(-45, 43.5, 3500, {.forwards = false, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 5});
    chassis.turnToPoint(-47, 0, 1200);
    chassis.moveToPoint(-47, 0, 1500, {.maxSpeed = 60});
    chassis.waitUntil(15);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    moveRelative(15, 70, 2000); // Negate the x-coordinate for relative movement
    chassis.moveToPose(-23.5, 5, 180, 3500);
}

void blueHighNeg(){
    chassis.setPose(49.235, 36.683, 63);
    chassis.moveToPoint(23.5, 23.5, 1050, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    pros::delay(150);
    pros::Task intake(BintakeTask, "Intake function");
    chassis.turnToPoint(23.5, 47.5, 1000);
    chassis.moveToPoint(23.5, 51, 1000);
    chassis.turnToPoint(10, 56, 1000);
    chassis.moveToPoint(10, 56, 1250, {.maxSpeed = 75});
    chassis.moveToPoint(17.25, 44.5, 1100, {.forwards = false, .maxSpeed = 75, .minSpeed = 60, .earlyExitRange = 2});
    chassis.turnToPoint(10, 43.5, 1000, {.minSpeed = 60, .earlyExitRange = 3});
    chassis.moveToPoint(17, 43.5, 1000, {.maxSpeed = 75});
    pros::delay(100);
    chassis.moveToPoint(9, 43.5, 1500, {.maxSpeed = 75});
    chassis.moveToPoint(45, 43.5, 3500, {.forwards = false, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 5});
    chassis.turnToPoint(47, 0, 1200);
    chassis.moveToPoint(47, 0, 1500, {.maxSpeed = 60});
    chassis.waitUntil(15);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    moveRelative(-15, 70, 2000);
    chassis.moveToPose(23.5, 5, 180, 3500);
}

void twoTopRed(){
    chassis.setPose(-58.5, 10, 0);
    chassis.moveToPoint(-58.5, -3, 750, {.maxSpeed = 45});
    chassis.moveToPoint(-58.5, 0, 750, {.maxSpeed = 45});
    chassis.turnToHeading(270, 750, {}, false);
    pros::delay(100);
    currState = 4;
    target = states[currState];
    pros::delay(50);
    chassis.moveToPoint(-61, 0, 850, {.maxSpeed = 50}, false);
    currState = 0;
    target = states[currState];
    moveRelative(3, 50, 750);
    chassis.turnToPoint(-23.5, 23.5, 1000, {.forwards = false, .maxSpeed = 75});
    chassis.moveToPoint(-23.5, 23.5, 1275, {.forwards = false, .maxSpeed = 70}, false);
    Clamp.set_value(HIGH);
    pros::delay(200);
    chassis.turnToPoint(-23.5, 47.5, 1250);
    preroller.move(0);
    pros::Task intake(RintakeTask, "Intake function");
    chassis.moveToPoint(-23.5, 51, 1000);
    chassis.turnToPoint(-10, 54, 1000);
    chassis.moveToPoint(-10, 54, 1250, {.maxSpeed = 75});
    chassis.moveToPoint(-17.25, 44.5, 1100, {.forwards = false, .maxSpeed = 75, .minSpeed = 60, .earlyExitRange = 2});
    chassis.turnToPoint(-10, 43.5, 1000, {.minSpeed = 60, .earlyExitRange = 3});
    chassis.moveToPoint(-17, 43.5, 1000, {.maxSpeed = 75});
    pros::delay(100);
    chassis.moveToPoint(-7, 43.5, 1500, {.maxSpeed = 75});
    chassis.moveToPoint(-30, 43.5, 1000, {.forwards = false, .maxSpeed = 75, .minSpeed = 70, .earlyExitRange = 2});
    chassis.moveToPoint(-23.5, 0, 1200);
}

void twoTopBlue(){
    chassis.setPose(58.5, 10,180);
    chassis.moveToPoint(58.5, -3, 750, {.maxSpeed = 45});
    chassis.moveToPoint(58.5, 0, 750, {.maxSpeed = 45});
    chassis.turnToHeading(90, 750, {}, false);
    pros::delay(100);
    currState = 4;
    target = states[currState];
    pros::delay(50);
    chassis.moveToPoint(61, 0, 850, {.maxSpeed = 50}, false);
    currState = 0;
    target = states[currState];
    moveRelative(-3, 50, 750);
    chassis.turnToPoint(23.5, 23.5, 1000, {.forwards = false, .maxSpeed = 75});
    chassis.moveToPoint(23.5, 23.5, 1275, {.forwards = false, .maxSpeed = 70}, false);
    Clamp.set_value(HIGH);
    pros::delay(200);
    chassis.turnToPoint(23.5, 47.5, 1250);
    preroller.move(0);
    pros::Task intake(BintakeTask, "Intake function");
    chassis.moveToPoint(23.5, 51, 1000);
    chassis.turnToPoint(10, 54, 1000);
    chassis.moveToPoint(10, 54, 1250, {.maxSpeed = 75});
    chassis.moveToPoint(17.25, 44.5, 1100, {.forwards = false, .maxSpeed = 75, .minSpeed = 60, .earlyExitRange = 2});
    chassis.turnToPoint(10, 43.5, 1000, {.minSpeed = 60, .earlyExitRange = 3});
    chassis.moveToPoint(17, 43.5, 1000, {.maxSpeed = 75});
    pros::delay(100);
    chassis.moveToPoint(7, 43.5, 1500, {.maxSpeed = 75});
    chassis.moveToPoint(30, 43.5, 1000, {.forwards = false, .maxSpeed = 75, .minSpeed = 70, .earlyExitRange = 2});
    chassis.moveToPoint(23.5, 0, 1200);
}

void fourRingRed(){
    //grab first goal
    chassis.setPose(-48.912,-36.043,245);
    chassis.moveToPoint(-23.5, -23.5, 2000, { .forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    intake.move(127);
    pros::delay(100);
    //grab 1st ring
    chassis.turnToPoint(-24, -49, 1500);
    chassis.moveToPoint(-24, -49, 2000, {}, false);
    pros::delay(1750);
    //go to alliance stake 2 stack
    chassis.turnToPoint(-50, 4, 1250, {}, false);
    chassis.moveToPoint(-50, 4, 3000, {.maxSpeed = 60});
    chassis.waitUntil(5);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    chassis.moveToPoint(-14.737, -58.573, 1250, {.forwards = false, .maxSpeed = 70});
    // chassis.moveToPoint(-23.5, 0,1500);
    intake.brake();
    
    // chassis.turnToPoint(-66.101, -66.745, 1000, {.forwards = false},false);
    // Clamp.set_value(LOW);
    chassis.turnToHeading(270, 1000);
}

void fourRingBlue(){
    blueSide = true;
    //grab first goal
    chassis.setPose(48.912,-36.043,115);
    chassis.moveToPoint(23.5, -23.5, 2000, { .forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    intake.move(127);
    pros::delay(100);
    //grab 1st ring
    chassis.turnToPoint(24, -49, 1500);
    chassis.moveToPoint(24, -49, 2000, {}, false);
    pros::delay(1750);
    //go to alliance stake 2 stack
    chassis.turnToPoint(50, 4, 1250, {}, false);
    chassis.moveToPoint(50, 4, 3000, {.maxSpeed = 60});
    chassis.waitUntil(5);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    chassis.moveToPoint(34.526, -18.939, 1250, {.forwards = false, .maxSpeed = 50});
    chassis.moveToPoint(23.5, 0,1500);
    intake.brake();

}

void gRushRed(){
    chassis.setPose(-51, -58.5, 270);
    chassis.moveToPoint(-20, -58.5, 1300, {.forwards = false, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 2});
    chassis.turnToPoint(-0, -46, 700, {.forwards = false});
    pros::Task autoClamp(autoClampTask);
    chassis.moveToPoint(-6.5, -50, 1450, {.forwards = false, .maxSpeed = 85});
    pros::delay(750); //delay for clamp
    moveRelative(5, 100, 750);
    chassis.waitUntil(5);
    autoClamp.suspend();
    pros::Task intake(RintakeTask);
    chassis.turnToPoint(-23.5, -47.5, 750, {}, false);
    Clamp.set_value(LOW);
    intake.suspend();
    hooks.move(0);
    preroller.move(127);
    chassis.moveToPoint(-23.5, -47.5, 750, {.maxSpeed = 100, .minSpeed = 70, .earlyExitRange = 2});
    chassis.turnToPoint(-21, -23.5, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 1});
    autoClamp.resume();
    chassis.moveToPoint(-21.5, -23.5, 1250, {.forwards = false, .maxSpeed = 65}, false);
    preroller.move(0);
    intake.resume();
    chassis.swingToPoint(-45, 0, lemlib::DriveSide::RIGHT, 1000);
    chassis.moveToPoint(-45, 0, 1500, {.maxSpeed = 60});
    chassis.waitUntil(3);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    moveRelative(-20, 100, 1250);
    intake.suspend();
    preroller.move(0);
    // chassis.moveToPoint(-23.5, -5, 1500, {.maxSpeed = 70});
    autoClamp.suspend();
}

void gRushBlue(){
    chassis.setPose(51, -58.5, 90);
    chassis.moveToPoint(20, -58.5, 1300, {.forwards = false, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 2});
    chassis.turnToPoint(0, -46, 700, {.forwards = false});
    pros::Task autoClamp(autoClampTask);
    chassis.moveToPoint(6.5, -50, 1450, {.forwards = false, .maxSpeed = 85});
    pros::delay(750); //delay for clamp
    moveRelative(5, 100, 750);
    chassis.waitUntil(5);
    autoClamp.suspend();
    pros::Task intake(BintakeTask);
    chassis.turnToPoint(23.5, -47.5, 750, {}, false);
    Clamp.set_value(LOW);
    intake.suspend();
    hooks.move(0);
    preroller.move(127);
    chassis.moveToPoint(23.5, -47.5, 750, {.maxSpeed = 100, .minSpeed = 70, .earlyExitRange = 2});
    chassis.turnToPoint(21, -23.5, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 1});
    autoClamp.resume();
    chassis.moveToPoint(21.5, -23.5, 1250, {.forwards = false, .maxSpeed = 65}, false);
    preroller.move(0);
    intake.resume();
    chassis.swingToPoint(45, 0, lemlib::DriveSide::LEFT, 1000);
    chassis.moveToPoint(45, 0, 1500, {.maxSpeed = 60});
    chassis.waitUntil(3);
    inLift.set_value(HIGH);
    chassis.waitUntilDone();
    inLift.set_value(LOW);
    pros::delay(250);
    moveRelative(-20, 100, 1250);
    intake.suspend();
    preroller.move(0);
    // chassis.moveToPoint(23.5, -5, 1500, {.maxSpeed = 70});
    autoClamp.suspend();
}

void dRushRed(){
    chassis.setPose(-50.75, -35.5,90);
    doink.set_value(HIGH);
    preroller.move(127);
    chassis.moveToPose(-10.5, -47.5, 95, 1600, {.lead = .4, .minSpeed = 85}, false);
    doink.set_value(LOW);
    pros::delay(100);
    moveRelative(-20, 75, 1000);
    chassis.waitUntil(12);
    doink.set_value(HIGH);
    chassis.waitUntilDone();
    doink.set_value(LOW);
    chassis.turnToHeading(chassis.getPose().theta - 190, 1250, {}, false);
    pros::Task autoClamp(autoClampTask);
    moveRelative(-30, 70, 1200);
    chassis.waitUntilDone();
    hooks.move_relative(1000, 600);
    pros::delay(1000);
    autoClamp.suspend();
    chassis.turnToHeading(270, 250);
    moveRelative(30, 75, 1500);
    chassis.waitUntil(5);
    Clamp.set_value(LOW);
    chassis.waitUntilDone();
    chassis.turnToPoint(-15, -22.5, 750, {.forwards = false});
    autoClamp.resume();
    chassis.moveToPoint(-16, -22.5, 1500, {.forwards = false, .maxSpeed = 75}, false);
    hooks.move_relative(3000, 600);
    // chassis.moveToPoint(float x, float y, int timeout);
    moveRelative(10, 75, 1000);
    chassis.waitUntilDone();
    inLift.set_value(HIGH);
    chassis.turnToPoint(-45, -2, 1000);
    pros::Task intake(BintakeTask);
    currState = 1;
    target = states[currState];
    chassis.moveToPoint(-45, -2, 1000, {.maxSpeed = 70}, false);
    inLift.set_value(LOW);
    pros::delay(250);
    chassis.turnToHeading(chassis.getPose().theta + 180, 1000, {}, false);
    moveRelative(65, 100, 1250);
    intake.suspend();
    preroller.move(0);
}

void dRushBlue(){
    chassis.setPose(50.75, -35.5,270);
    doink.set_value(HIGH);
    preroller.move(127);
    chassis.moveToPose(10.5, -47.5, 265, 1600, {.lead = .4, .minSpeed = 85}, false);
    doink.set_value(LOW);
    pros::delay(100);
    moveRelative(-20, 75, 1000);
    chassis.waitUntil(12);
    doink.set_value(HIGH);
    chassis.waitUntilDone();
    doink.set_value(LOW);
    chassis.turnToHeading(chassis.getPose().theta + 190, 1250, {}, false);
    pros::Task autoClamp(autoClampTask);
    moveRelative(-30, 70, 1200);
    chassis.waitUntilDone();
    hooks.move_relative(1000, 600);
    pros::delay(1000);
    autoClamp.suspend();
    chassis.turnToHeading(90, 250);
    moveRelative(30, 75, 1500);
    chassis.waitUntil(5);
    Clamp.set_value(LOW);
    chassis.waitUntilDone();
    chassis.turnToPoint(15, -22.5, 750, {.forwards = false});
    autoClamp.resume();
    chassis.moveToPoint(16, -22.5, 1500, {.forwards = false, .maxSpeed = 75}, false);
    hooks.move_relative(3000, 600);
    // chassis.moveToPoint(float x, float y, int timeout);
    moveRelative(10, 75, 1000);
    chassis.waitUntilDone();
    inLift.set_value(HIGH);
    chassis.turnToPoint(45, -2, 1000);
    pros::Task intake(BintakeTask);
    currState = 1;
    target = states[currState];
    chassis.moveToPoint(45, -2, 1000, {.maxSpeed = 70}, false);
    inLift.set_value(LOW);
    pros::delay(250);
    chassis.turnToHeading(chassis.getPose().theta + 180, 1000, {}, false);
    moveRelative(65, 100, 1250);
    intake.suspend();
    preroller.move(0);
}

void skills(){
    chassis.setPose(-60.5, 0, 90);
    hooks.move_relative(1500, 600);
    pros::delay(500);
    chassis.moveToPoint(-46.7, 0, 1250, {.maxSpeed = 60});
    chassis.turnToPoint(-46.7, 23.5, 1000, {.forwards = false});
    chassis.moveToPoint(-46.7, 23.5, 1250, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    intake.move(127);
    chassis.turnToPoint(-23.5, 23.5, 1000, {}, false);
    currState = 1;
    target = states[currState];
    chassis.moveToPoint(-23.5, 23.5, 1000, {.maxSpeed = 75, .minSpeed = 60, .earlyExitRange = 2});


    chassis.moveToPose(0, 65, 0, 2500, {.lead = 0.25, .maxSpeed = 60});
    chassis.waitUntil(23);
    intake.move(0);
    currState = 2;
    target = states[currState];
    chassis.waitUntilDone();
    intake.move(127);
    currState = 3;
    target = states[currState];
    pros::delay(1150);
    
    intake.move(0);
    intake.move_relative(-600, 127);
    
    
    moveRelative(-10, 70, 1000);
    chassis.waitUntilDone();
    currState = 0;
    target = states[currState];
    chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPose(-59, 48.5, 270, 3000, {.maxSpeed = 60});
    chassis.turnToPoint(-47, 59, 1000);
    chassis.moveToPoint(-47, 59, 1500, {.maxSpeed = 60}, false);
    chassis.turnToPoint(-38.317, 55, 1250, {}, false);
    Clamp.set_value(LOW);
    moveRelative(-15, 65, 1250);
    chassis.turnToPoint(-23.5, -23.5, 1000, {.forwards = false, .maxSpeed = 60});

    //2nd half

    chassis.moveToPose(-53, -23.5, 0, 3500, {.forwards = false, .maxSpeed = 75}, false);
    chassis.setPose(-1 * localizerL.get_distance() / 25.4 - 26.25, chassis.getPose().y, 0);
    Clamp.set_value(HIGH);
    intake.move(127);
    chassis.turnToPoint(-23.5, -20, 1000);
    currState = 1;
    target = states[currState];
    chassis.moveToPoint(-30, -18, 1150, {.maxSpeed = 75, .minSpeed = 60, .earlyExitRange = 2});


    chassis.moveToPose(-1, -65, 195, 3000, {.lead = 0.2, .maxSpeed = 55});
    chassis.waitUntil(36);
    intake.move(0);
    currState = 2;
    target = states[currState];
    chassis.waitUntilDone();
    intake.move(127);
    currState = 3;
    target = states[currState];
    pros::delay(1150);
    
    intake.move(0);
    intake.move_relative(-600, 127);


    moveRelative(-10, 70, 1000);
    chassis.waitUntilDone();
    currState = 0;
    target = states[currState];
    chassis.waitUntilDone();
    intake.move(127);
    chassis.moveToPose(-65, -48.5, 270, 3000, {.maxSpeed = 60});
    chassis.turnToPoint(-52, -59, 1000);
    chassis.moveToPoint(-52, -59, 1500, {.maxSpeed = 60}, false);
    chassis.turnToPoint(-43.317, -55, 1250, {}, false);
    Clamp.set_value(LOW);
    moveRelative(-15, 65, 1250);
    intake.move(0);
    hooks.move_relative(-700, 127);
    preroller.move(127);
    chassis.moveToPoint(0, -45, 2500, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(23.5, -23.5, 2500, {.maxSpeed = 60});
    chassis.turnToPoint(43, 0, 1000, {.forwards = false, .maxSpeed = 60});
    chassis.moveToPoint(43, 0, 1500, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(HIGH);
    hooks.move(127);
    chassis.moveToPoint(23.5, -47.5, 1500);
    chassis.moveToPoint(47.5, -59, 1500);
    moveRelative(-10, 70, 1000);
    chassis.moveToPoint(47.5, -47.5, 1500);
    moveRelative(-15, 70, 1000);
    chassis.turnToPoint(62, -67, 1500, {.forwards = false, .maxSpeed = 60}, false);
    Clamp.set_value(LOW);
    chassis.moveToPoint(62, -67, 1500, {.forwards = false, .maxSpeed = 60}, false);
}