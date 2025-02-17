#include "main.h"
#include "pros/rtos.hpp"
#include "robodash/api.h"

rd::Selector Match_autos({
	{"Skills", &skills},
	{"Red Solo Winpoint", &redSoloWP},
	{"Blue Solo Winpoint", &blueSoloWP},
	{"Red five ring", &fourRingRed},
	{"Blue five ring", &fourRingBlue},
	{"Red rush", &rushRed},
	{"Blue rush", &rushBlue},
	{"Red disrupt", &disruptRed},
	{"Blue disrupt", &disruptBlue},
	
});

rd::Image planet("Planet.bin", "Planet");
rd::Image goof("goof.bin", "goof");

void initialize() {
	Match_autos.focus();
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

void disabled() {
	
}

void competition_initialize() {
  
}

void autonomous() {
	goof.focus();
	Match_autos.run_auton();
}

void opcontrol() {
	console.clear();
	planet.focus(); 
	pros::Task Flasher(ledTime, "LED time");
	pros::Task ledBind(ledBinds, "LED binds");
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
		
		pros::delay(10);          // Run for 10 ms then update
	}
}