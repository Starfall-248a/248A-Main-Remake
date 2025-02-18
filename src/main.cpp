#include "main.h"
#include "pros/rtos.hpp"
#include "robodash/api.h"

rd::Selector Match_autos({
	{"Elims Blue", &elimBlue},
	{"Red Solo WP", &redSoloWP},
	{"Blue Solo WP", &blueSoloWP},
	{"Red Rush Clear", &rushClearRed},
	{"Blue Rush Clear", &rushClearBlue},
	{"Red doinker rush", &dRushRed},
	{"Blue doinker rush", &dRushBlue},
	{"Red clamp rush", &gRushRed},
	{"Blue clamp rush", &gRushBlue},
	{"Red 1+3", &twoTopRed},
	{"Blue 1+3", &twoTopBlue},
	{"Red Neg 5 ring", &redHighNeg},
	{"Blue Neg 5 ring", &blueHighNeg},
	{"Skills", &skills},
});

void initialize() {
	Match_autos.focus();
	sorter.set_integration_time(10);
	console.println("Initializing robot...");
	chassis.calibrate(); // calibrate sensors
	ledManager.initialize(); // initialize the LED manager
	ledManager.flow(0x421C52, 0x732C7B);
	pros::Task liftControlTask(LBTask, "LB Task");
	pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            console.printf("X: %f", chassis.getPose().x); // x
            console.printf("Y: %f", chassis.getPose().y); // y
            console.printf("Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(50);
			console.clear();
        }
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	goof.focus();
	Match_autos.run_auton();
}

void opcontrol() {
	console.clear();
	planet.focus(); 
	pros::Task Flasher(ledTime, "LED time");
	
	while (true) {
		// get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX, false, 0.5);
		
		// set subsystems
		setLifter();
		setIntakes();
		setClamp();
		setLB();
		setDoink();
		setAutoClamp();
		
		pros::delay(10);          // Run for 10 ms then update
	}
}