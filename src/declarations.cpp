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
//function to score 2 points on the right side
void right(){
	//flips out the hood (asynchronously)
	towerControl->setTarget(-1000);
	//adjusts the robot
	chassis->moveDistance(3_in);
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->setMaxVelocity(100);
	//chassis->turnAngle(26_deg);
	chassis->moveDistance(1_in);
	//scores the ball
	chassis->moveDistance(-1_in);
	score(1500);
	//backs up
	chassis->moveDistance(-5_in);
	//turns around to sorta face the side goal
	chassis->turnAngle(-184_deg);
	chassis->setMaxVelocity(200); //speeds up the robot
	//starts the intakes and lower tower to prepare to pick up a ball
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//moves forward
	chassis->moveDistance(28_in);
	//turns to face second goal
	chassis->setMaxVelocity(100);
	chassis->turnAngle(-82_deg);
	chassis->setMaxVelocity(200);
	//moves to the second goal
	chassis->moveDistance(22_in);
	//stops sucking in balls
	//moves the right side a bit then the left side a bit to compensate for any variation
	chassis->setMaxVelocity(150);
	chassis->getModel()->left(1);
	delay(250);
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(250);
	chassis->getModel()->right(0);
	chassis->moveDistance(2_in);
	chassis->moveDistance(-3_in);
	//socres for 2 seconds
	score(2500);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-8_in);
}

void left(){
	towerControl->setTarget(-1000);
	//adjusts the robot
	chassis->moveDistance(4_in);
	//scores the ball
	score(1500);
	chassis->moveDistance(-3_in);
	//turns around to sorta face the side goal
	chassis->turnAngle(170_deg);
	chassis->setMaxVelocity(200); //less magic
	//starts the intakes and lower tower to prepare to pick up a ball
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//moves forward by 31.5 inches
	chassis->moveDistance(29_in);
	//turns to face second goal
	chassis->setMaxVelocity(100);
	chassis->turnAngle(75_deg);
	chassis->setMaxVelocity(200); //more magic
	//moves to the second goal
	chassis->moveDistance(15_in);
	//stops sucking in balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//moves the right side a bit then the left side a bit to compensate for any variation
	chassis->setMaxVelocity(100);
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(500);
	chassis->getModel()->right(0);
	chassis->moveDistance(-2.25_in);
	//socres for 2 seconds
	score(2000);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-8_in);
}
//defines a function to score from the right of the goal
void onepointright(){
	//flips out the hood
	towerControl->setTarget(-1000);
	//adjusts the robot
	chassis->moveDistance(8_in);
	chassis->setMaxVelocity(50);
	chassis->turnAngle(-15_deg);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-.75_in);
	//scores the ball
	score(1500);
	//backs up the robot so it isnt touching a ball
	chassis->moveDistance(-8_in);
}
//function to score on the left of the goal
void onepointleft(){
	//flips out hood
	//towerControl->setTarget(-1000);
	//adjusts the robot
	chassis->moveDistance(8_in);
	chassis->setMaxVelocity(50);
	chassis->turnAngle(15_deg);
	chassis->setMaxVelocity(200); //and here it is in a different function
	chassis->moveDistance(-.75_in);
	//scores the ball
	score(1500);
	//backs up the robot so it isnt touching a ball
	chassis->moveDistance(-8_in);
}
void test(){
	towerControl->setTarget(-1000);
	chassis->moveDistance(4_in);
	//scores the ball
	score(1500);
	chassis->moveDistance(-3_in);
	//turns around to sorta face the side goal
	chassis->turnAngle(184_deg);
	chassis->setMaxVelocity(200); //less magic
	//starts the intakes and lower tower to prepare to pick up a ball
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//moves forward by 31.5 inches
	chassis->moveDistance(30_in);
	//turns to face second goal
	chassis->setMaxVelocity(100);
	chassis->turnAngle(80_deg);
	chassis->setMaxVelocity(200); //more magic
	//moves to the second goal
	chassis->moveDistance(20_in);
	//stops sucking in balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//moves the right side a bit then the left side a bit to compensate for any variation
	chassis->setMaxVelocity(100);
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(500);
	chassis->getModel()->right(0);
	chassis->moveDistance(-3_in);
	//socres for 2 seconds
	score(2000);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-8_in);
	chassis->turnAngle(-100_deg);
	chassis->moveDistance(50_in);
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	chassis->setMaxVelocity(100);
	chassis->turnAngle(-80_deg);
	chassis->setMaxVelocity(200); //more magic
	//moves to the second goal
	chassis->moveDistance(20_in);
	//stops sucking in balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//moves the right side a bit then the left side a bit to compensate for any variation
	chassis->setMaxVelocity(100);
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(500);
	chassis->getModel()->right(0);
	chassis->moveDistance(-3_in);
	//socres for 2 seconds
	score(2000);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-8_in);
}
//function for the skills autonomous
void skills(){
	towerControl->setTarget(-300);
	//start intaking balls
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.75*mv);
	//move the chassis forward to the first ball
	chassis->setMaxVelocity(75);
	chassis->moveDistance(30_in);
	//stop the intakes and tower
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//turn to face the first goal
	//														chassis->setMaxVelocity(50);
	chassis->turnAngle(135_deg);
	//														chassis->setMaxVelocity(200);
	//move to the first goal
	towerlower.move_velocity(-.1*mv);
	//towerControl->setTarget(50);
	chassis->moveDistance(36_in);
	towerlower.move_velocity(stop);
	//adjusts robot so its at the right angle
	chassis->getModel()->left(1);
	delay(1100);
	chassis->getModel()->left(0);
	chassis->moveDistance(-3_in);
	//scores 2 balls in the first goal
	score(1600);
	//														chassis->setMaxVelocity(50);
	//slows down chassis to back up the robot so it doesnt tip a lot
	chassis->getModel()->left(-1);
	delay(2200);
	chassis->getModel()->left(0);
	chassis->moveDistance(-15_in);
	chassis->moveDistance(5_in);
	//turn around to face 3rd ball
	chassis->turnAngle(-50_deg);
	//														chassis->setMaxVelocity(200);
	//start intaking balls
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//move to the third ball
	chassis->moveDistance(63_in);
	//turns to second goal
	//														chassis->setMaxVelocity(50);
	chassis->turnAngle(-80_deg);
	//														chassis->setMaxVelocity(200); //same thing
	//stop intaking balls
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//move to second goal
	chassis->moveDistance(8_in);
	//scores one ball in second goal
	score(1200);
	//slows robot down to back up
	//														chassis->setMaxVelocity(50);
	chassis->moveDistance(-9_in);
	//														chassis->setMaxVelocity(100);
	//turns the robot to the starting wall
	//														chassis->setMaxVelocity(50);
	chassis->turnAngle(-70_deg);
	//														chassis->setMaxVelocity(200); //here again
	//moves to the wall
	chassis->moveDistance(40_in);
	//starts the intakes
	leftintake.move_velocity(mv);
	rightintake.move_velocity(mv);
	towerlower.move_velocity(.5*mv);
	//turns to the fourth ball
	//														chassis->setMaxVelocity(50);
	chassis->turnAngle(92_deg);
	//														chassis->setMaxVelocity(200); //I'm sure you get the idea
	//moves to the fourth ball
	chassis->moveDistance(13.5_in);
	//backs up
	chassis->moveDistance(-8_in);
	//stops the intakes
	leftintake.move_velocity(stop);
	rightintake.move_velocity(stop);
	towerlower.move_velocity(stop);
	//turns to the third goal
	//														chassis->setMaxVelocity(50);
	chassis->turnAngle(-54_deg);
	//														chassis->setMaxVelocity(200); // oh look another one
	//moves to the third goal
	chassis->moveDistance(22_in);
	chassis->moveDistance(-3_in);
	//scores one ball in the third gaol
	score(1200);
}
