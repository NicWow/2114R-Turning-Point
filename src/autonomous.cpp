#include "main.h"

using namespace okapi;

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

float distance_number = 48; // inches
float distance_per_rotation = 12.5663706144;
float rotation_number = (distance_number / distance_per_rotation) * 360;

auto drive = ChassisControllerFactory::create(
		{9, 10},
		{-1, -2},
		AbstractMotor::gearset::green,
		{4_in, 15_in});

AsyncMotionProfileController driveProfile = AsyncControllerFactory::motionProfile(
		1.0,
		1.5,
		100.0,
		drive
		);
void autonomous() {
	driveProfile.generatePath({
		Point{0_in, 0_in, 0_deg},
		Point{54_in, 0_in, 0_deg},
	},
			"ForwardFlag");

	pros::Motor roller(20);

	pros::lcd::set_text(4, "Autonomous is Running!");
	/*
	int amount = 6;
	int space = 48 - amount;
	int negative = 48 - amount;

	*/

	// Hit Flags
	pros::lcd::set_text(4, "Getting that flag!");
	//drive.moveDistance(54_in);
	driveProfile.setTarget("ForwardFlag");
	driveProfile.generatePath({
		Point{0_in, 0_in, 0_deg},
		Point{66_in, 0_in, 0_deg},
		},
				"BackwardFlag");
	driveProfile.waitUntilSettled();
	driveProfile.removePath("ForwardFlag");

	// Move Back
	pros::lcd::set_text(4, "Moving Back!");
	//drive.moveDistance(-66_in);


	driveProfile.setTarget("BackwardFlag", true);
	//new path here

	driveProfile.generatePath({
		Point{0_in, 0_in, 0_deg},
		Point{54_in, 0_in, 0_deg},
		},
				"OntoPlatform");

	driveProfile.waitUntilSettled();
	driveProfile.removePath("BackwardFlag");


	// Turn
	pros::lcd::set_text(4, "Turning!");
	drive.turnAngle(90_deg);
	// Get onto Platform
	pros::lcd::set_text(4, "Getting onto platforms!");
	//drive.moveDistance(54_in);
	driveProfile.setTarget("OntoPlatform");
	driveProfile.waitUntilSettled();
	driveProfile.removePath("OntoPlatform");



	// Motor definitions
	/*Motor left_mtr1(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor left_mtr2(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor right_mtr1(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor right_mtr2(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

	// cap flipper
	Motor cap_flipper(20);

	// flippin caps
	cap_flipper = -127;*/

	/*cap_flipper = 127;
    delay(1000);
    cap_flipper = 0;*/

	/*left_mtr1.move_absolute(rotation_number, 100); // Moves 100 units forward
	pros::lcd::set_text(4, "Autonomous is Runing!!");
	left_mtr2.move_absolute(rotation_number, 100); // Moves 100 units forward
	pros::lcd::set_text(4, "Autonomous is Runing!!!!");
	right_mtr1.move_absolute(rotation_number, 100); // Moves 100 units forward
	pros::lcd::set_text(4, "Autonomous is Runing!!!!!");
	right_mtr2.move_absolute(rotation_number, 100); // Moves 100 units forward
	pros::lcd::set_text(4, "Autonomous is Runing!!!!!!");

	while (!((left_mtr1.get_position() < rotation_number + 5) && (left_mtr1.get_position() > rotation_number - 5))) {
		// Continue running this loop as long as the motor is not within +-5 units of its goal
		pros::delay(2);
		pros::lcd::set_text(4, "Autonomous is Runing!!!!!!!");
	}

	while (!((right_mtr1.get_position() < rotation_number + 5) && (right_mtr1.get_position() > rotation_number - 5))) {
		// Continue running this loop as long as the motor is not within +-5 units of its goal
		pros::delay(2);
		pros::lcd::set_text(4, "Autonomous is Runing!!!!!!!!!");
	}
    pros::lcd::set_text(4, "Autonomous is Run!!!");*/
}
