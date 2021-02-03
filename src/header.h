//header.h
#include "main.h"
//functions
//void right();
//void left();
//void onepointright();
//void onepointleft();
void skills1();
void skills2();
void skills3();
void skills4();
void score(int reps);
void intake(int mult);
//motors
extern Controller master;
extern Motor rightintake;
extern Motor leftintake;
extern Motor tower;
extern Motor towerlower;
//chassis
extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> towerlowerControl;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> towerControl;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> intakeControl;
//variables
extern int mv;
extern int stop;
