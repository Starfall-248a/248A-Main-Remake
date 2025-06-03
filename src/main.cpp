#include "main.h"
#include "robodash/api.h"

rd::Selector Match_autos({
	{"blue standard", &blueStandard},
	{"red standard", &redStandard},
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

bool iso = true;

void autonomous() {
    static int autonRunCount = 0; // Tracks how many times auton has run

    if (autonRunCount == 0) {
        Match_autos.run_auton(); // Run the default autonomous function
    } else if (autonRunCount == 1) {
        blueInt();
    } else {
        return; // Do nothing after the second execution
    }

    autonRunCount++; // Increment the counter
}

void opcontrol() {
	console.clear();
	planet.focus(); 

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
		setDoink();
		setAutoClamp();
		
		pros::delay(10);          // Run for 10 ms then update
	}
}