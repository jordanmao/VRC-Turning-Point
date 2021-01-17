#include "main.h"
#include "functions.h"
int catapultStage;
bool readyToShoot;
bool suspendCap;
void opcontrol() {
	adi_gyro_reset(gyro);
	delay(200);
	ResetEncoders();
	task_t SetCatapult = task_create(SetCatapultFn, NULL,TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "SetCatapult");
	task_t SuspendCap = task_create(SuspendCapFn, NULL,TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "SuspendCap");
	SetDriveBrake(MOTOR_BRAKE_BRAKE);
	motor_set_brake_mode(ARM, MOTOR_BRAKE_HOLD);
	readyToShoot = false;
	catapultStage = 2;
	while (true) {
		//Display===============================================================
		lcd_print(0, "Left Encoder: %f", motor_get_position(LEFT_DRIVE_2));
		lcd_print(1, "Right Encoder: %f", motor_get_position(RIGHT_DRIVE_2));
		lcd_print(4, "Gyro: %f", adi_gyro_get(gyro));
		lcd_print(5, "Catapult Stage: %d", catapultStage);
		lcd_print(6, "ARM: %f", motor_get_position(ARM));
		if (lcd_read_buttons() == LCD_BTN_CENTER){
			while (lcd_read_buttons() == LCD_BTN_CENTER){delay(10);}
	 		ResetEncoders();
		}
		if (lcd_read_buttons() == LCD_BTN_LEFT){
			while (lcd_read_buttons() == LCD_BTN_LEFT){delay(10);}
			adi_gyro_reset(gyro);
		}
		//======================================================================

		//Drive Train===========================================================
		LeftDriveVoltage(controller_get_analog(CONTROLLER_MASTER,ANALOG_LEFT_Y));
		RightDriveVoltage(controller_get_analog(CONTROLLER_MASTER,ANALOG_RIGHT_Y));
		//======================================================================

		//Catapult==============================================================
		if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_A) &&
		adi_analog_read(POTENTIOMETER) < CATAPULT_STAGE_2 + 200){
		 	catapultStage = 1;
		}
		//getting ball from outer spot to inside spot
		else if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_B) &&
		motor_get_actual_velocity(LEFT_CATAPULT) == 0){
			readyToShoot = false;
		}
		else if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_Y)){ // If the catapult is stuck when trying to reset
			catapultStage = 2;
		}
		//======================================================================

		//Intake================================================================
		if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_R1)){
			IntakeVelocity(350);
		}
		else if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_R2)){
			IntakeVelocity(-300);
		}
		else{
			IntakeVelocity(0);
		}
		//======================================================================

		//Arm===================================================================
		if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_L1)){
			if (motor_get_brake_mode(ARM) == MOTOR_BRAKE_HOLD){
				motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
			}
			ArmVelocity(180);
			if (suspendCap){
				suspendCap = false;
			}
		}
		else if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_L2)){
			if (motor_get_brake_mode(ARM) == MOTOR_BRAKE_HOLD){
				motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
			}
			ArmVelocity(-200);
			if (suspendCap){
				suspendCap = false;
			}
		}
		else if (controller_get_digital(CONTROLLER_MASTER,DIGITAL_UP) && !suspendCap){
			suspendCap = true;
		}
		else if (!suspendCap){
			ArmVelocity(0);
		}
		//======================================================================

		//Setting Brake Mode====================================================
		if (controller_get_digital(CONTROLLER_MASTER, DIGITAL_DOWN)){
			while (controller_get_digital(CONTROLLER_MASTER, DIGITAL_DOWN)){
				delay(20);
			}
			if (motor_get_brake_mode(LEFT_DRIVE_1) == MOTOR_BRAKE_COAST){
				SetDriveBrake(MOTOR_BRAKE_HOLD);
			}
			else {
				SetDriveBrake(MOTOR_BRAKE_COAST);
			}
		}
		delay(20);
	}
}
