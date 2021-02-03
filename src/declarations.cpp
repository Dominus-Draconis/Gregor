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
void score(int reps){
	/*//starts the lower tower and upper tower moving at their respective maximum velocities
	towerlower.move_velocity(.5*mv);
	tower.move_velocity(3*mv);
	//waits for the time given when the function is called
	delay(time);
	//stops the tower motors
	towerlower.move_velocity(stop);
	tower.move_velocity(stop);
*/
	towerlowerControl->setTarget(-90);
	for (int i=0; i<reps; i++){
		tower.move_velocity(3*mv);
		delay(1500);
		towerlowerControl->setTarget(360*2);
	}
}
void intake(int mult){
	leftintake.move_velocity(mv*mult);
	rightintake.move_velocity(mv*mult);
	towerlower.move_velocity(.75*mv*mult);
}
void go(okapi::QLength x, okapi::QLength y, bool reversed){
	if(reversed==false){
		chassis->turnToPoint({x,y});
	}
	chassis->driveToPoint({x,y}, reversed);
}

//function for the skills autonomous
void skills1(){
	chassis->setState({0_in, 0_in, 0_deg});	//set inital conditions
	chassis->setMaxVelocity(75);						//make it slow
	towerControl->setTarget(-300);					//flip out hood
	intake(1);															//start intakes
	chassis->moveDistance(25_in);						//move to first ball
	chassis->turnToAngle(-90_deg);					//turns to vertical center line
	intake(0);															//stop intakes
	chassis->moveDistance(36.8_in);					//moves to vertical center line
	chassis->turnToAngle(-180_deg);					//turns to goal
	chassis->moveDistance(14.4_in);					//moves to first goal
	score(2);																//scores 2 balls in first goal
	chassis->moveDistance(-6.8_in);					//backs up
	chassis->turnToAngle(0_deg);						//turn around
	intake(1);															//start intakes
	chassis->moveDistance(28_in);						//moves to second ball
	chassis->turnToAngle(45_deg);						//turns to third ball
	chassis->moveDistance(34.4_in);					//moves to third ball
	chassis->turnToAngle(15_deg);						//turns to fourth ball
	chassis->moveDistance(50_in);						//moves to fourth ball
	chassis->turnToAngle(57_deg);						//turns to second goal
	intake(0);															//starts intaking balls
	chassis->moveDistance(24.8_in);					//moves to second goal
	score(1);																//scores one ball
	chassis->moveDistance(-10.8_in);				//backs up
	chassis->turnToAngle(180_deg);					//turns to fifth ball
	intake(1);															//starts intakes
	chassis->moveDistance(56_in);						//moves to fifth ball
	chassis->turnToAngle(90_deg);						//turns to third goal
	intake(0);															//stops intakes
	chassis->moveDistance(7.2_in);					//moves to third goal
	score(2); 															//scores two balls
	chassis->moveDistance(-7.2_in);					//backs up
	chassis->turnToAngle(180_deg);					//turns to face starting wall
	chassis->moveDistance(36_in);						//moves to starting wall
	chassis->turnToAngle(90_deg);						//turns to sixth ball
	intake(1);															//starts intakes
	chassis->moveDistance(15.2_in);					//moves to sixth ball
	chassis->moveDistance(-15.2_in);				//backs up
	intake(0);															//stop intakes
	chassis->turnToAngle(149.5_deg);				//turn to fourth goal
	chassis->moveDistance(24.4_in);					//move to fourth goal
	score(1); 															//scores one ball
	chassis->moveDistance(-10_in);					//backs up
}



void skills2(){
	chassis->setState({0_in, 0_in, 0_deg});
	chassis->setMaxVelocity(75);
	towerControl->setTarget(-300);
	intake(1);
	chassis->moveDistance(25_in);
	chassis->turnToAngle(-90_deg);
	intake(0);
	chassis->moveDistance(36.8_in);
	chassis->turnToAngle(-180_deg);
	chassis->moveDistance(14.4_in);
	score(2); //two balls
	chassis->moveDistance(-6.8_in);
	chassis->turnToAngle(0_deg);
	intake(1);
	chassis->moveDistance(28_in);
	chassis->turnToAngle(63.5_deg);
	chassis->moveDistance(54.4_in);
	chassis->turnToAngle(90_deg);
	intake(0);
	chassis->moveDistance(7.2_in);
	score(2); //two balls
	chassis->moveDistance(-7.2_in);
	chassis->turnToAngle(180_deg);
	chassis->moveDistance(36_in);
	chassis->turnToAngle(90_deg);
	intake(1);
	chassis->moveDistance(15.2_in);
	chassis->moveDistance(-15.2_in);
	intake(0);
	chassis->turnToAngle(149.5_deg);
	chassis->moveDistance(24.4_in);
	score(1); //one ball
	chassis->moveDistance(-10_in);
}



void skills3(){
	chassis->setState({0_in, 0_in, 0_deg});
	chassis->setMaxVelocity(75);
	towerControl->setTarget(-300);
	intake(1);
	go(0_in, 25_in, false);
	intake(0);
	go(-36.8_in, 25_in, false);
	go(-36.8_in, 10.6_in, false);
	score(2);
	go(-36.8_in, 17.4_in, true);
	intake(1);
	go(-36.8_in, 40.8_in, false);
	go(-12_in, 65.2_in, false);
	go(0_in, 113.6_in, false);
	intake(0);
	go(-20.8_in, 127.12_in, false);
	score(1);
	go(12_in, 120.8_in, true);
	intake(1);
	go(12_in, 65.2_in, false);
	intake(0);
	go(19.2_in, 65.2_in, false);
	score(2);
	go(12_in, 65.2_in, true);
	go(12_in, 29.2_in, false);
	intake(1);
	go(27.2_in, 29.2_in, false);
	intake(0);
	go(12_in, 29.2_in, true);
	go(24.8_in, 8.18_in, false);
	score(1);
	go(12_in, 29.2_in, true);
}




void skills4(){
	chassis->setState({0_in, 0_in, 0_deg});
	chassis->setMaxVelocity(75);
	towerControl->setTarget(-300);
	intake(1);
	go(0_in, 25_in, false);
	intake(0);
	go(-36.8_in, 25_in, false);
	go(-36.8_in, 10.6_in, false);
	score(2);
	go(-36.8_in, 17.4_in, true);
	intake(1);
	go(-36.8_in, 40.8_in, false);
	go(12_in, 65.2_in, false);
	intake(0);
	go(19.2_in, 65.2_in, false);
	score(2);
	go(12_in, 65.2_in, true);
	go(12_in, 29.2_in, false);
	intake(1);
	go(27.2_in, 29.2_in, false);
	intake(0);
	go(12_in, 29.2_in, true);
	go(24.8_in, 8.18_in, false);
	score(1);
	go(12_in, 29.2_in, true);
}
