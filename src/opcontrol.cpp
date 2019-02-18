#include "main.h"

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

//using namespace pros;

void opcontrol() {
	Controller master(E_CONTROLLER_MASTER);

 
    // Driving variables
    Motor left_mtr1(10);
    Motor left_mtr2(9);
    Motor right_mtr1(1, true);
    Motor right_mtr2(2, true);

    // cap flipper
    Motor cap_flipper(20);

	while (true) {
	
        // drive
        
        int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);



        // flip caps

           if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
             cap_flipper = 127;

           } else if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
             cap_flipper = -127;
           }
           else {
               cap_flipper = 0;
           }

        if (master.get_digital(E_CONTROLLER_DIGITAL_A)) {
            autonomous();
        }

        //set variables

        left_mtr1 = left;
        left_mtr2 = left;
        right_mtr1 = right;
        right_mtr2 = right;

        pros::delay(20);
	}
}
