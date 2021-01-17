#include "main.h"
#include "functions.h"

adi_gyro_t gyro;

int auton;
void initialize() {
	//Motors====================================================================
	//Left Drive 1--------------------------------------------------------------
	motor_set_encoder_units(LEFT_DRIVE_1, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(LEFT_DRIVE_1, MOTOR_GEARSET_18);
	motor_set_reversed(LEFT_DRIVE_1, false);
	//Left Drive 2--------------------------------------------------------------
	motor_set_encoder_units(LEFT_DRIVE_2, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(LEFT_DRIVE_2, MOTOR_GEARSET_18);
	motor_set_reversed(LEFT_DRIVE_2, false);
	//Right Drive 1-------------------------------------------------------------
	motor_set_encoder_units(RIGHT_DRIVE_1, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(RIGHT_DRIVE_1, MOTOR_GEARSET_18);
	motor_set_reversed(RIGHT_DRIVE_1, true);
	//Right Drive 2-------------------------------------------------------------
	motor_set_encoder_units(RIGHT_DRIVE_2, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(RIGHT_DRIVE_2, MOTOR_GEARSET_18);
	motor_set_reversed(RIGHT_DRIVE_2, true);
	//Left Catapult-------------------------------------------------------------
	motor_set_encoder_units(LEFT_CATAPULT, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(LEFT_CATAPULT, MOTOR_GEARSET_18);
	motor_set_reversed(LEFT_CATAPULT, true);
	//Right Catapult------------------------------------------------------------
	motor_set_encoder_units(RIGHT_CATAPULT, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(RIGHT_CATAPULT, MOTOR_GEARSET_18);
	motor_set_reversed(RIGHT_CATAPULT, false);
	//Intake--------------------------------------------------------------------
	motor_set_encoder_units(INTAKE, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(INTAKE, MOTOR_GEARSET_06);
	motor_set_reversed(INTAKE, false);
	//Arm-----------------------------------------------------------------------
	motor_set_encoder_units(ARM, MOTOR_ENCODER_DEGREES);
	motor_set_gearing(ARM, MOTOR_GEARSET_18);
	motor_set_reversed(ARM, true);
	motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
	//==========================================================================

	//Sensors===================================================================
	gyro = adi_gyro_init(GYRO, GYRO_MULTIPLIER);
	delay(200);
	adi_port_set_config(POTENTIOMETER, E_ADI_ANALOG_IN);
	lcd_initialize();
	//==========================================================================
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
void competition_initialize() {
	auton = SKILLS;
	lcd_register_btn0_cb(LeftButtonPressed);
	lcd_register_btn2_cb(RightButtonPressed);
	while(1){
		//This is what the brain displays in set up:
		//--------------------------------------------------
		//AUTON SSELECT: _
		//[(1)skill]  (2)r-f   (3)b-f   (4)r-fp   (5)b-fp
		// (6)r-c     (7)b-c   (8)r-cp  (9)b-cp   (10)n/a
		//------------------------------------------------------------
		lcd_print(0,"AUTON SELECT: %d",auton);
		if(auton == SKILLS){
			lcd_print(1,"[(1)skill]  (2)r-f1  (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp  (9)b-cp   (10)n/a ");
		}
		else if(auton == RED_FLAGS_1){
			lcd_print(1," (1)skill  [(2)R-F1] (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp  (9)b-cp   (10)n/a ");
		}
		else if(auton == BLUE_FLAGS_1){
			lcd_print(1," (1)skill   (2)r-f1 [(3)B-F1] (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp  (9)b-cp   (10)n/a ");
		}
		else if(auton == RED_FLAGS_2){
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1 [(4)R-F2]  (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp  (9)b-cp   (10)n/a ");
		}
		else if(auton == BLUE_FLAGS_2){
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1  (4)r-f2  [(5)B-F2]");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp  (9)b-cp   (10)n/a ");
		}
		else if(auton == RED_CAPS){
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2,"[(6)R-C]    (7)b-c   (8)r-cp  (9)b-cp   (10)n/a ");
		}
		else if(auton == BLUE_CAPS){
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c    [(7)B-C]  (8)r-cp  (9)b-c2   (10)n/a ");
		}
		else if(auton == RED_CAPS_PARK){
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c  [(8)R-CP] (9)b-cp   (10)n/a ");
		}
		else if(auton == BLUE_CAPS_PARK){
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp [(9)B-CP]  (10)n/a ");
		}
		else{
			lcd_print(1," (1)skill   (2)r-f1  (3)b-f1  (4)r-f2   (5)b-f2 ");
			lcd_print(2," (6)r-c     (7)b-c   (8)r-cp  (9)b-cp  [(10)N/A]");
		}
		delay(20);
	}
}
