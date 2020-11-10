//header.h
#include "main.h"
//functions
void score();
void right();
void left();
void onepointright();
void onepointleft();
void skills();
void score();
//motors
extern Controller master;
extern Motor rightintake;
extern Motor leftintake;
extern Motor tower;
extern Motor towerlower;
//chassis
extern std::shared_ptr<okapi::OdomChassisController> chassis;
//variables
extern int mv;
extern int stop;
