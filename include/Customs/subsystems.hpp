#include "pros/rtos.hpp"

void setClamp();
void setIntakes();

void setLifter();
void ledTime();
void setLB();
void setDoink();
void setAutoClamp();

// Declare the task function prototype
void primeClampTask(void* param);

// Declare the flag to indicate when the task should run
extern bool clampTaskRunning;

// Function to start the autoClampTask
void startAutoClampTask();

// Function to stop the autoClampTask
void stopAutoClampTask();



static bool blueSide = false;

extern pros::Task guh;