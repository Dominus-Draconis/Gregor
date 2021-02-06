#include "main.h"
#include "header.h"
void right(){
	towerControl->setTarget(-2000);
	chassis->moveDistance(3_in);
	chassis->getModel()->left(1);
	delay(500);
	chassis->getModel()->left(0);
	chassis->setMaxVelocity(100);
	chassis->moveDistance(1_in);
	chassis->moveDistance(-1_in);
	score(1500);
	chassis->moveDistance(-5_in);
	chassis->turnAngle(-190_deg);
	chassis->setMaxVelocity(200);
	intake(1);
	chassis->moveDistance(28_in);
	chassis->setMaxVelocity(100);
	chassis->turnAngle(-82_deg);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(22_in);
	chassis->setMaxVelocity(150);
	chassis->getModel()->left(1);
	delay(250);
	intake(0);
	chassis->getModel()->left(0);
	chassis->getModel()->right(1);
	delay(250);
	chassis->getModel()->right(0);
	chassis->moveDistance(2_in);
	chassis->moveDistance(-3_in);
	score(2500);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-8_in);
}
void left(){
  towerControl->setTarget(-2000);
	chassis->moveDistance(3_in);
	chassis->getModel()->right(1);
	delay(500);
	chassis->getModel()->right(0);
	chassis->setMaxVelocity(100);
	chassis->moveDistance(1_in);
	chassis->moveDistance(-1_in);
	score(1500);
	chassis->moveDistance(-5_in);
	chassis->turnAngle(184_deg);
	chassis->setMaxVelocity(200);
	intake(1);
	chassis->moveDistance(28_in);
	chassis->setMaxVelocity(100);
	chassis->turnAngle(82_deg);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(22_in);
	chassis->setMaxVelocity(150);
	chassis->getModel()->right(1);
	delay(250);
	intake(0);
	chassis->getModel()->right(0);
	chassis->getModel()->left(1);
	delay(250);
	chassis->getModel()->left(0);
	chassis->moveDistance(2_in);
	chassis->moveDistance(-3_in);
	score(2500);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-8_in);
}
void onepointright(){
	towerControl->setTarget(-2000);
	chassis->moveDistance(8_in);
	chassis->setMaxVelocity(50);
	chassis->turnAngle(-15_deg);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(2_in);
	score(1500);
	chassis->moveDistance(-8_in);
}
void onepointleft(){
  towerControl->setTarget(-2000);
	chassis->moveDistance(8_in);
	chassis->setMaxVelocity(50);
	chassis->turnAngle(15_deg);
	chassis->setMaxVelocity(200);
	chassis->moveDistance(-.5_in);
	score(1500);
	chassis->moveDistance(-8_in);
}
//function for the skills autonomous
void skills(){
	chassis->setState({0_in, 0_in, 0_deg});	//set inital conditions
	chassis->setMaxVelocity(100);						//make it slow
	towerControl->setTarget(-300);					//flip out hood
	intake(1);															//start intakes
	chassis->moveDistance(20_in);						//move to first ball
	chassis->turnToAngle(90_deg);				  	//turns to vertical center line
	intake(0);															//stop intakes
	chassis->moveDistance(36_in);				  	//moves to vertical center line
	chassis->turnToAngle(180_deg);				  	//turns to goal
	chassis->setMaxVelocity(50);
	chassis->moveDistance(11_in);				  	//moves to first goal
	score1(2);															//scores 2 balls in first goal
	chassis->moveDistance(-6.8_in);					//backs up
	chassis->setMaxVelocity(100);
	chassis->turnToAngle(0_deg);					//turn around
	intake(1);															//start intakes
	chassis->moveDistance(24_in);						//moves to second ball
	chassis->turnToAngle(-45_deg);					//turns to third ball
	chassis->moveDistance(32_in);				  	//moves to third ball
	chassis->turnToAngle(-15_deg);						//turns to fourth ball
	chassis->moveDistance(42_in);						//moves to fourth ball
	chassis->turnToAngle(-57_deg);					//turns to second goal
	intake(0);															//starts intaking balls
	chassis->moveDistance(24.8_in);					//moves to second goal
	score1(3);															//scores one ball
	chassis->moveDistance(-10.8_in);				//backs up
	chassis->turnToAngle(-120_deg);					//turns to fifth ball
	intake(1);															//starts intakes
	chassis->moveDistance(56_in);						//moves to fifth ball
	chassis->turnToAngle(90_deg);					  //turns to third goal
	intake(0);															//stops intakes
	chassis->moveDistance(7.2_in);					//moves to third goal
	score(2); 															//scores two balls
	chassis->moveDistance(-7.2_in);					//backs up
	chassis->turnToAngle(90_deg);				  //turns to face starting wall
	chassis->moveDistance(36_in);						//moves to starting wall
	chassis->turnToAngle(90_deg);					//turns to sixth ball
	intake(1);															//starts intakes
	chassis->moveDistance(15.2_in);					//moves to sixth ball
	chassis->moveDistance(-15.2_in);				//backs up
	intake(0);															//stop intakes
	chassis->turnToAngle(120_deg);			//turn to fourth goal
	chassis->moveDistance(24.4_in);					//move to fourth goal	score1(1);
	chassis->moveDistance(-10_in);					//backs up
}
