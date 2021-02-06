#include "main.h"
//functions
void score();
void intake(int mult);
void score1(int reps);
void right();
void left();
void onepointright();
void onepointleft();
void skills();
void test();
void score(int time);
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
