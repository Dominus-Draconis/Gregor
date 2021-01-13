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

//defines variables for maximum velocity and stop velocity
int mv=200;
int stop=0;
//defines a function to score the balls with the paramerter of how long the shooty thingy should run
void score(int time){
	//starts the lower tower and upper tower moving at their respective maximum velocities
	towerlower.move_velocity(.93*mv);
	tower.move_velocity(3*mv);
	//waits for the time given when the function is called
	delay(time);
	//stops the tower motors
	towerlower.move_velocity(stop);
	tower.move_velocity(stop);
}
//function to score 2 points on the right side
void right(){
	tower.move_velocity(mv);
	delay(500);
	tower.move_velocity(stop);
	//adjusts the robot
	chassis->moveDistance(2_in);
	chassis->turnAngle(15_deg);
	//scores the ball
	score(1500);
	//turns around to sorta face the side goal
	chassis->turnAngle(-180_deg);
	//starts the intakes and lower tower to prepare to pick up a ball
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//moves forward by 31.5 inches
	chassis->moveDistance(28_in);
	//turns to face second goal
	chassis->turnAngle(-60_deg);
	//moves to the second goal
	chassis->moveDistance(10_in);
	//stops sucking in balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//moves the right side a bit then the left side a bit to compensate for any variation
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(500);
	chassis->getModel()->right(0);
	chassis->moveDistance(-4_in);
	//socres for 2 seconds
	score(2000);
	chassis->moveDistance(-8_in);
}

void left(){
	chassis->moveDistance(1.5_in);
	chassis->turnAngle(-15_deg);
	score(1500);
	chassis->turnAngle(200_deg);
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	chassis->moveDistance(31.5_in);
	chassis->turnAngle(60_deg);
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
//defines a function to score from the right of the goal
void onepointright(){
	tower.move_velocity(mv);
	delay(500);
	tower.move_velocity(stop);
	//adjusts the robot
	chassis->moveDistance(8_in);
	chassis->turnAngle(-15_deg);
	//scores the ball
	score(1500);
	chassis->moveDistance(-8_in);
	chassis->turnAngle(180_deg);
}
//function to score on the left of the goal
void onepointleft(){
	tower.move_velocity(mv);
	delay(500);
	tower.move_velocity(stop);
	//adjusts the robot
	chassis->moveDistance(8_in);
	chassis->turnAngle(15_deg);
	//scores the ball
	score(1500);
	chassis->moveDistance(-8_in);
	chassis->turnAngle(-180_deg);
}
//function for the skills autonomous
void skills(){
	//start intaking balls
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//move the chassis forward to the first ball
	chassis->moveDistance(27.5_in);


	//stop the intakes and tower
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//turn to face the first goal
	chassis->turnAngle(130_deg);
	//move to the first goal
	chassis->moveDistance(4_in);
	//moves the rest of the distance to the first goal
	chassis->moveDistance(29.3_in);
	//adjusts robot so its at the right angle
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	//scores 2 balls in the first goal
	score(1400);
	//slows down chassis to back up the robot so it doesnt tip a lot
	chassis->setMaxVelocity(50);
	chassis->moveDistance(-5_in);

	//turn around to face 2nd ball
	chassis->turnAngle(190_deg);
	chassis->setMaxVelocity(100);
	//start intaking balls
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//move to the third ball
	chassis->moveDistance(70_in);
	//turns to second goal
	chassis->turnAngle(-69_deg);
	//stop intaking balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//move to second goal
	chassis->moveDistance(5_in);
	//scores one ball in second goal
	score(1200);
	//slows robot down to back up
	chassis->setMaxVelocity(50);
	chassis->moveDistance(-9_in);
	chassis->setMaxVelocity(100);
	//turns the robot to the starting wall
	chassis->turnAngle(-70_deg);
	//moves to the wall
	chassis->moveDistance(40_in);
	//starts the intakes
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	//turns to the fourth ball
	chassis->turnAngle(92_deg);
	//moves to the fourth ball
	chassis->moveDistance(13.5_in);
	//backs up
	chassis->moveDistance(-8_in);
	//stops the intakes
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	//turns to the third goal
	chassis->turnAngle(-54_deg);
	//moves to the third goal
	chassis->moveDistance(20_in);
	chassis->moveDistance(-5_in);
	//scores one ball in the third gaol
	score(1200);
}
