//autons.cpp
#include "main.h"
//declares motors and controlers
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor rightintake(3,E_MOTOR_GEARSET_18,true);
pros::Motor leftintake(10);
pros::Motor tower(9,E_MOTOR_GEARSET_06,true);
pros::Motor towerlower(11);
//sets up okapi chassis control
std::shared_ptr<okapi::OdomChassisController> chassis =
	okapi::ChassisControllerBuilder()
		.withMotors(-6, 7)
		.withDimensions(okapi::AbstractMotor::gearset::green, {{4.125_in, 12.75_in}, okapi::imev5GreenTPR})
		.withOdometry()
		.buildOdometry();
std::shared_ptr<okapi::AsyncMotionProfileController> profileController =
	okapi::AsyncMotionProfileControllerBuilder()
		.withLimits({
			1.1, // Maximum linear velocity of the Chassis in m/s
			2, // Maximum linear acceleration of the Chassis in m/s/s
			10 // Maximum linear jerk of the Chassis in m/s/s/s
		})
		.withOutput(chassis)
		.buildMotionProfileController();
std::shared_ptr<okapi::AsyncPositionController<double, double>> towerlowerControl =
  okapi::AsyncPosControllerBuilder()
    .withMotor(11) // lift motor port 11
    .build();
std::shared_ptr<okapi::AsyncPositionController<double, double>> intakeControl =
  okapi::AsyncPosControllerBuilder()
    .withMotor({-3, 10}) // intake motors ports 3 reversed and 10
    .build();
std::shared_ptr<okapi::AsyncPositionController<double, double>> towerControl =
  okapi::AsyncPosControllerBuilder()
    .withMotor(-9) // intake motors ports 3 reversed and 10
    .build();
//defines variables for maximum velocity and stop velocity
int mv=200;
int stop=0;
//defines a function to score the balls with the paramerter of how long the shooty thingy should run
void score(int time){
	//starts the lower tower and upper tower moving at their respective maximum velocities
	towerlower.move_velocity(.5*mv);
	tower.move_velocity(3*mv);
	//waits for the time given when the function is called
	delay(time);
	//stops the tower motors
	towerlower.move_velocity(stop);
	tower.move_velocity(stop);
}
void score1(int reps){
	towerlowerControl->setTarget(-150);
	tower.move_velocity(3*mv);
	delay(1000);
	tower.move_velocity(stop);
	for (int i=0; i<=reps; i++){
		//lcd::print("i = %i", i);
		towerlowerControl->setTarget(360*10);
		towerlowerControl->waitUntilSettled();
		tower.move_velocity(3*mv);
		delay(1000);
		tower.move_velocity(stop);
	}
}
void intake(int mult){
	leftintake.move_velocity(mv*mult);
	rightintake.move_velocity(mv*mult);
	towerlower.move_velocity(.75*mv*mult);
}
