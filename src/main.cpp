#include "main.h"
#include "header.h"
//#include "globals.cpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
//uses a slower maimum velocity than in driver control to be more precise
chassis->setMaxVelocity(100);
chassis->setState({0_in, 0_in, 0_deg});
//options:
//1)runs the 2 point match auton on the right side
//left();

//2) runs the 2 point match auton on the left side
//right();

//3) scores the preload in the goal in front from the right
//onepointright();

//4) scores the preload in the goal in front from the left
//onepointleft();

//5) runs the autonomous for skills
skills();
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {
		lcd::print(0, "%d %d %d", (lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		//creates tank control for the chassis
		chassis->getModel()->tank(master.get_analog(ANALOG_RIGHT_Y),
												master.get_analog(ANALOG_LEFT_Y));
		//moves the intakes in
		if (master.get_digital(DIGITAL_R1)){
			rightintake.move_velocity(mv);
			leftintake.move_velocity(mv);
		}
		//moves the intakes out
		else if (master.get_digital(DIGITAL_R2)){
			rightintake.move_velocity(-mv);
			leftintake.move_velocity(-mv);
		}
		//if R1 or R2 isnt pressed stop moving the intakes
		else{
			rightintake.move_velocity(0);
			leftintake.move_velocity(0);
		}
		//moves the lower two tower rollers up
		if (master.get_digital(DIGITAL_L1)){
			towerlower.move_velocity(mv);
		}
		// moves lower tower rollers down
		else if (master.get_digital(DIGITAL_L2)){
			towerlower.move_velocity(-mv);
		}
		//stops moving the lower tower roller
		else {
			towerlower.move_velocity(0);
		}
		//moves the upper and lower towers in order to shoot the ball out
		if (master.get_digital(DIGITAL_UP)){
			tower.move_velocity(2.5*mv);
			towerlower.move_velocity(mv);
		}
		//moves the whole tower down, not that important
		else if (master.get_digital(DIGITAL_DOWN)){
			tower.move_velocity(-2.5*mv);
			towerlower.move_velocity(-mv);
		}
		//stops the upper tower, the lower tower doesnt need to be stopped because it already is
		else {
			tower.move_velocity(0);
		}
		//starts the autonomous from the A button, helpful for testing
		if (master.get_digital(DIGITAL_A)){
			autonomous();
		}
		//updates ever 10 milliseconds
		delay(10);
	}
}
