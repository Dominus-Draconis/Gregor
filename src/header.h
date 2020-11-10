#include "main.h"
void score();
void right();
void left();
void onepointright();
void onepointleft();
void skills();
void score();
extern Controller master;
extern Motor rightintake;
extern Motor leftintake;
extern Motor tower;
extern Motor towerlower;
extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern int mv;
extern int stop;
