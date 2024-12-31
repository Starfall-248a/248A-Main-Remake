#include "main.h"
#include "pros/motors.hpp"
#include <cmath>

const int numStates = 3;
int states[numStates] = {0, 50, 450};
int target = 0;

void nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}

void liftControl() {
    double kp = 1.4;
    double error = target - LB.get_position();
    double velocity = kp * error;
    LB.move(velocity);
}