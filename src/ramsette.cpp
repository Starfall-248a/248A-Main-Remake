#include "main.h"
#include "okapi\squiggles\squiggles.hpp"

const double MAX_VEL = 2.0;     // in meters per second
const double MAX_ACCEL = 3.0;   // in meters per second per second
const double MAX_JERK = 6.0;    // in meters per second per second per second
const double ROBOT_WIDTH = 0.36; // in meters

const float b = 2.0;
const float zeta = 0.7;

const float wheelRadius = 2.75/2;

const float maxMotor = 600;
const float ratio = 1;

void follow_ramsette(double target_x, double target_y, double target_theta){
    //path creation
auto constraints = squiggles::Constraints(MAX_VEL, MAX_ACCEL, MAX_JERK);
auto generator = squiggles::SplineGenerator(
  constraints,
  std::make_shared<squiggles::TankModel>(ROBOT_WIDTH, constraints), 10);
    lemlib::Pose pose = chassis.getPose(true, true);
    lemlib::Pose target = lemlib::Pose(target_x, target_y, target_theta);
    auto path = generator.generate({squiggles::Pose(pose.x/39.37, pose.y/39.37, pose.theta), squiggles::Pose(target_x/39.37, target_y/39.37, target_theta)});
    target_x = target_x/39.37;
    target_y = target_y/39.37;
    float distTravelled = 0;
    lemlib::Pose lastPose = chassis.getPose();
    float time = 0;
    std::size_t pathSize = path.size();
    lemlib::Timer motion_check(10000);
    for(std::size_t i = 0; i < pathSize; i++){
        lemlib::Pose pose = chassis.getPose(true, true);
        const float distTarget = pose.distance(target)/39.37;

        // update distance traveled
        distTravelled += pose.distance(lastPose);
        lastPose = pose;

        //matrix multiply for e_x, e_y, e_theta
        const float converted_x = pose.x/39.37;
        const float converted_y = pose.y/39.37;
        
        const float goalX = path[time].vector.pose.x; //fix these later when u figure out syntax
        const float goalY = path[time].vector.pose.y; //fix these later
        const float goalTheta = path[time].vector.pose.yaw; //fix these later
        
        const auto segDT = time * 0.001;

        const float v_d = (path[time].wheel_velocities[0] + path[i].wheel_velocities[1])/2; //converting wheel velocities to linear
        const float w_d = -2*(path[time].wheel_velocities[0]-v_d)/ROBOT_WIDTH; // converting wheel velocities to angular
    
        const float x_diff = goalX - converted_x;
        const float y_diff = goalY - converted_y;
        const float theta_diff = (goalTheta) - (pose.theta*M_PI)/180; //goal theta in radians

        const float e_x = (x_diff * cos(pose.theta)) + (y_diff * sin(pose.theta)) + (theta_diff * 0);
        const float e_y = (x_diff * -sin(pose.theta)) + (y_diff * cos(pose.theta)) + (theta_diff * 0);
        const float e_theta = theta_diff;

        const float k = 2 * zeta * sqrt((w_d*w_d) + b * (v_d*v_d));
        const float output_v = v_d * cos(e_theta) + k * e_x;
        const float output_w = w_d + k * e_theta + (b*v_d*sin(e_theta)*e_y)/e_theta; //

        // const float wheelCircumference = 2*M_PI*wheelRadius;
        // const float linearMotorVelocity = output_v/wheelCircumference;
        const float leftMotorVelocities = output_v - (output_w*ROBOT_WIDTH)/2;
        const float rightMotorVelocities = output_v + (output_w*ROBOT_WIDTH)/2;

        const float ratio = std::max(leftMotorVelocities, rightMotorVelocities)/127;

        driveLeft.move_velocity((leftMotorVelocities / ratio) * (std::fabs(leftMotorVelocities) / leftMotorVelocities));
        driveRight.move_velocity((rightMotorVelocities / ratio) * (std::fabs(rightMotorVelocities) / rightMotorVelocities));
        // float ratio = std::max(std::fabs(leftMotorsRaw), std::fabs(rightMotorsRaw)) / 127;
        // if (ratio > 1) {
        //     leftMotorsRaw /= ratio;
        //     rightMotorsRaw /= ratio;
        // }
        time++;
        pros::delay(10 + (segDT - motion_check.getTimePassed()));
    }
}