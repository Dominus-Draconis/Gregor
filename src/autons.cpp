#include "main.h"
//#include "globals.cpp"
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor rightintake(3,E_MOTOR_GEARSET_18,true);
pros::Motor leftintake(10);
pros::Motor tower(9,E_MOTOR_GEARSET_06,true);
pros::Motor towerlower(11);
std::shared_ptr<okapi::OdomChassisController> chassis =
	okapi::ChassisControllerBuilder()
		.withMotors(-6, 7) // Left: 14, 16 | Right: 15, 17
		.withDimensions(okapi::AbstractMotor::gearset::green, {{4.125_in, 12.75_in}, okapi::imev5GreenTPR}) // Drop Center Wheels: 4.32in
		.withMaxVelocity(125)
//		.withSensors(ADIEncoder{'A', 'B', true}, ADIEncoder{'C', 'D'}) // Left Tracking Pod: 'A', 'B' | Right Tracking Pod: 'C', 'D'
		.withOdometry()
		.buildOdometry();
std::shared_ptr<okapi::AsyncMotionProfileController> profileController =
	okapi::AsyncMotionProfileControllerBuilder()
		.withLimits({
			1, // Maximum linear velocity of the Chassis in m/s
			5, // Maximum linear acceleration of the Chassis in m/s/s
			10 // Maximum linear jerk of the Chassis in m/s/s/s
		})
		.withOutput(chassis)
		.buildMotionProfileController();
int mv=200;
int stop=0;
void score(int time){
	towerlower.move_velocity(200);
	tower.move_velocity(600);
	delay(time);
	towerlower.move_velocity(0);
	tower.move_velocity(0);
}
void right(){
	chassis->moveDistance(1.5_in);
	chassis->turnAngle(15_deg);
	score(1500);
	chassis->turnAngle(-200_deg);
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	chassis->moveDistance(31.5_in);
	chassis->turnAngle(-60_deg);
	chassis->moveDistance(12_in);
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(500);
	chassis->getModel()->right(0);
	chassis->moveDistance(-4_in);
	score(2000);
}

void left(){
	chassis->moveDistance(1.5_in);
	chassis->turnAngle(-15_deg);
	score(1500);
	chassis->turnAngle(200_deg);
	leftintake.move_velocity(-mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	chassis->moveDistance(30.2_in);
	chassis->turnAngle(70_deg);
	chassis->moveDistance(12_in);
	delay(500);
	chassis->moveDistance(5_in);
	leftintake.move_velocity(mv);
	rightintake.move_velocity(-mv);
	chassis->moveDistance(-4_in);
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	score(2000);
}
void onepointright(){
	chassis->moveDistance(1.5_in);
	chassis->turnAngle(-15_deg);
	score(1500);
}
void onepointleft(){
	chassis->moveDistance(1.5_in);
	chassis->turnAngle(15_deg);
	score(1500);
}
void skills(){
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//move the chassis forward to the first ball
	chassis->moveDistance(28_in);
	//stop the intakes and tower
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//turn to face the first goal
	chassis->turnAngle(145_deg);
	//move to the first goal
	chassis->moveDistance(32_in);
	//put the balls in the goal
	score(2000);
	//turn around
	chassis->turnAngle(175_deg);
	//start intaking balls
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//move to the third ball
	chassis->moveDistance(50_in);
	//stop intaking balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	chassis->moveDistance(-1_in);
	//turn to face the second goal
	chassis->turnAngle(285_deg);
	//move twords the second goal
	chassis->moveDistance(20_in);
	//put the balls in the goal
	score(2000);
}
