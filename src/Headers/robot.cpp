#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include <sys/_intsup.h>
#include "stormlib/api.hpp"
#include "robodash/api.h"

using namespace pros;
using namespace lemlib;

stormlib::clock driverClock;

rd::Console console;

Controller controller(E_CONTROLLER_MASTER);

MotorGroup driveLeft({20, -19, 18}, pros::MotorGearset::blue); // left motors on ports 20, 19, 18
MotorGroup driveRight({-17, 16, -15}, pros::MotorGearset::blue); // right motors on ports 17, 16, 15

Motor LB(-2, pros::MotorGearset::green); // arm motor on port 6
Motor hooks(-7, pros::MotorGearset::blue); // right intake motor on port 10
Motor preroller(-13, pros::MotorGearset::green); // right intake motor on port 4
MotorGroup intake({-7, -13}, pros::MotorGearset::blue); // intake motors on ports 9, 4

Imu imu(12);

Distance clamper(5);
Distance localizerL(3);
Optical sorter(6);
Optical reader(4);

Rotation latRot(-8);
Rotation angRot(-13);

adi::Pneumatics Clamp('a', LOW);
adi::Pneumatics inLift('b', LOW);
adi::Pneumatics doink('e', LOW);
adi::Pneumatics tipper('f', LOW);

// drivetrain settings
Drivetrain drivetrain(&driveLeft, // left motor group
                              &driveRight, // right motor group
                              11.822028, // 10.6725 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
                              600, // drivetrain rpm is 450
                              2 // horizontal drift is 2
);

// horizontal tracking wheel
TrackingWheel horizontal_tracking_wheel(&angRot, 2.125, 2);
// vertical tracking wheel
TrackingWheel vertical_tracking_wheel(&latRot, 2.125, 1);

OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                        nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                        &horizontal_tracking_wheel, // horizontal tracking wheel 1
                        nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                        &imu // inertial sensor
);

// input curve for throttle input during driver control
ExpoDriveCurve throttle_curve(6.35, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain
);

// input curve for steer input during driver control
ExpoDriveCurve steer_curve(6.35, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.015 // expo curve gain
);

// create the chassis
Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);

stormlib::aRGB underglow(4, 30);
stormlib::aRGB TimeLED(3, 63);
stormlib::aRGB_manager ledManager(&underglow, &TimeLED, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

rd::Image planet("Planet.bin", "Planet");
rd::Image goof("goof.bin", "goof");