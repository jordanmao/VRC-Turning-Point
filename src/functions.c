#include "main.h"

//MISCELLANEOUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int GetSign(int number){
	if (number == abs(number)){ //number is positive
		return 1;
	}
	else{
		return -1;             //number is negative
	}
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//DRIVE FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Drive Brake Functions=========================================================
void SetDriveBrake(int brakeMode){
	motor_set_brake_mode(LEFT_DRIVE_1, brakeMode);
	motor_set_brake_mode(LEFT_DRIVE_2, brakeMode);
	motor_set_brake_mode(RIGHT_DRIVE_1, brakeMode);
	motor_set_brake_mode(RIGHT_DRIVE_2, brakeMode);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//Drive Voltage Functions=======================================================
void LeftDriveVoltage(int voltage){
	motor_move(LEFT_DRIVE_1,voltage);
	motor_move(LEFT_DRIVE_2,voltage);
}
void RightDriveVoltage(int voltage){
	motor_move(RIGHT_DRIVE_1,voltage);
	motor_move(RIGHT_DRIVE_2,voltage);
}
void DriveVoltage(int voltage){
	LeftDriveVoltage(voltage);
	RightDriveVoltage(voltage);
}
//Drive Velocity Functions======================================================
void LeftDriveVelocity(float velocity){
	motor_move_velocity(LEFT_DRIVE_1,velocity);
	motor_move_velocity(LEFT_DRIVE_2,velocity);
}
void RightDriveVelocity(float velocity){
	motor_move_velocity(RIGHT_DRIVE_1,velocity);
	motor_move_velocity(RIGHT_DRIVE_2,velocity);
}
void DriveVelocity(float velocity){
	RightDriveVelocity(velocity);
	LeftDriveVelocity(velocity);
}
//Squaring Functions============================================================
void Square(int voltage){
	SetDriveBrake(MOTOR_BRAKE_COAST);
	DriveVoltage(voltage);
	delay(200);
	int counter = 0;
	while ((motor_get_actual_velocity(LEFT_DRIVE_2) || motor_get_actual_velocity(RIGHT_DRIVE_2))
			&& counter < 200){
		delay(50);
		counter++;
	}
	DriveVoltage(0);
	SetDriveBrake(MOTOR_BRAKE_HOLD);
}
//Drive Encoder Functions=======================================================
void ResetEncoders(){
	motor_tare_position(LEFT_DRIVE_1);
	motor_tare_position(RIGHT_DRIVE_1);
	motor_tare_position(LEFT_DRIVE_2);
	motor_tare_position(RIGHT_DRIVE_2);
}
void Move(float degrees, int velocity, _Bool rampUp){
	bool leftDone = false;
	bool rightDone = false;
	ResetEncoders();
	SetDriveBrake(MOTOR_BRAKE_BRAKE);
	//Ramp up------------------------------------------------------
	if (rampUp && fabs(degrees) > 400){
		while (fabs(motor_get_position(LEFT_DRIVE_2)) < 200){
			DriveVelocity((abs(velocity)-20)*GetSign(velocity));
		}
	}
	while(!leftDone || !rightDone){
		if(fabs(motor_get_position(RIGHT_DRIVE_2)) < fabs(degrees) && !rightDone){
			RightDriveVelocity(velocity);
		}
		else{
			rightDone = true;
			RightDriveVelocity(0);
		}
		if(fabs(motor_get_position(LEFT_DRIVE_2)) < fabs(degrees) && !leftDone){
			LeftDriveVelocity(velocity);
		}
		else{
			leftDone = true;
			LeftDriveVelocity(0);
		}
		delay(10);
	}
}
void LeftMove(float degrees, int velocity){
	ResetEncoders();
	while(fabs(motor_get_position(LEFT_DRIVE_2)) < fabs(degrees)){
		LeftDriveVelocity(velocity);
		delay(10);
	}
	LeftDriveVelocity(0);
}
void RightMove(float degrees, int velocity){
	ResetEncoders();
	while(fabs(motor_get_position(RIGHT_DRIVE_2)) < fabs(degrees)){
		RightDriveVelocity(velocity);
		delay(10);
	}
	RightDriveVelocity(0);
}
void PMove(float target){
	const float kP = 0.50;//0.51
	float error;
	float prevError = 0;
	float output;
	float test = target;
	int counter = 0;
	float iterationTime = 25;
	float maxSpeed = 0.06*fabs(target) + 120;
	ResetEncoders();
	while (counter < 4){
		error = target - motor_get_position(RIGHT_DRIVE_1);
		test = kP*error;
		if (fabs(test) > maxSpeed){ // max speed
			test = maxSpeed*GetSign(test);
		}
		output = test;
		DriveVelocity(output);
		if (error-2 < prevError && prevError < error+2 && error){
			counter++;
		}
		else{
			counter = 0;
		}
		prevError = error;
		delay(iterationTime);
	}
	DriveVelocity(0);
}
void Turn(float degrees, int velocity, bool turnLeft){
	ResetEncoders();
	int sign = 1;
	if (turnLeft){
		sign = -1;
	}
	while(motor_get_position(LEFT_DRIVE_2) < fabs(degrees)){
		LeftDriveVelocity(velocity*sign);
		RightDriveVelocity(-velocity*sign);
		delay(10);
	}
	DriveVelocity(0);
}

//GYRO FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void PIDGyroTurn(float target){
	//kU = 0.32,tU = 1.7
	//PD = 0.22,0.8 //PID0.22,0.0001,0.3
	float error = adi_gyro_get(gyro) - target;
	const float kP = 0.00006*fabs(error)+0.098;//0.0000597*fabs(error)+0.098;
	const float kI = 0.0003;//0.0005
	const float kD = 0.0041;//0.0041
	float prevError = 0;
	float integral;
	float derivative;
	int output;
	int test;
	int counter = 0;
	int iterationTime = 10;
	bool turnClockWise = false;
	if (adi_gyro_get(gyro) < target){
		turnClockWise = true;
	}
	while (counter < 10 || fabs(error) > 100){
		lcd_print(0, "gyro: %f", adi_gyro_get(gyro));
		lcd_print(1, "Target: %f", target);
		error = adi_gyro_get(gyro) - target;
		derivative = error - prevError;
		test = kP*error + kD*derivative;
		if (abs(test) > 120){//120
			test = 120*GetSign(test);
		}
		else{
			integral += error;
		}
		output = test + kI*integral;
		LeftDriveVelocity(-output);
		RightDriveVelocity(output);
		if (fabs(error - prevError) < 3){
			counter++;
		}
		else{
			counter = 0;
		}
		prevError = error;
		delay(iterationTime);
	}
	DriveVelocity(0);
}
//INTAKE FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void IntakeVoltage(int voltage){
	motor_move(INTAKE,voltage);
}
void IntakeVelocity(int velocity){
	motor_move_velocity(INTAKE,velocity);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//CATAPULT FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void CatapultVelocity(int velocity){
	if (motor_get_temperature(LEFT_CATAPULT) > 50.0 || motor_get_temperature(RIGHT_CATAPULT) > 50.0){
		lcd_print(6,"CATAPULT MOTORS ARE TOO HOT!");
		motor_move_velocity(LEFT_CATAPULT,0);
		motor_move_velocity(RIGHT_CATAPULT,0);
	}
	else{
		motor_move_velocity(LEFT_CATAPULT,velocity);
		motor_move_velocity(RIGHT_CATAPULT,velocity);
	}
}
void CatapultVoltage(int voltage){
	if (motor_get_temperature(LEFT_CATAPULT) > 50.0 || motor_get_temperature(RIGHT_CATAPULT) > 50.0){
		lcd_print(6,"CATAPULT MOTORS ARE TOO HOT!");
		motor_move(LEFT_CATAPULT,0);
		motor_move(RIGHT_CATAPULT,0);
	}
	else{
		motor_move(LEFT_CATAPULT,voltage);
		motor_move(RIGHT_CATAPULT,voltage);
	}
}
void CatapultMove(float degrees, int velocity){
	motor_tare_position(LEFT_CATAPULT);
	motor_tare_position(RIGHT_CATAPULT);
	while(motor_get_position(LEFT_CATAPULT) < fabs(degrees)){
		CatapultVelocity(velocity);
		delay(10);
	}
	CatapultVelocity(0);
}
void SetCatapultFn(){
	//catapultStage = 0;
	readyToShoot = false;
	while(1){
		if (adi_analog_read(POTENTIOMETER) != 0){ //Start task after potentiometer is initialized
			while (catapultStage == 1 && adi_analog_read(POTENTIOMETER) < CATAPULT_STAGE_1){
				CatapultVelocity(70);
				if (readyToShoot){
					readyToShoot = false;
				}
				delay(20);
			}
			if (catapultStage != 0){
				catapultStage = 2;
			}
			while (catapultStage == 2 && adi_analog_read(POTENTIOMETER) > CATAPULT_STAGE_2 && !readyToShoot){ //Loading
				CatapultVelocity(70);
				delay(20);
			}
			readyToShoot = true;
			if (motor_get_target_position(LEFT_CATAPULT) == 0){
				CatapultVelocity(0);
			}
			delay(20);
		}
	}
}
void WaitForShot(){
	while (adi_analog_read(POTENTIOMETER) < CATAPULT_STAGE_1){
		delay(20);
	}
	delay(100);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//CAP SCORER FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void ArmVelocity(int velocity){
	motor_move_velocity(ARM,velocity);
}
void ArmVoltage(int voltage){
	if (motor_get_temperature(ARM) > 50.0){
		lcd_print(6,"ARM MOTOR IS TOO HOT! %lf",motor_get_temperature(ARM));
	}
	else{
		motor_move(ARM,voltage);
	}
}
void SuspendCapFn(){
	suspendCap = false;
	while(1){
		if (suspendCap){
			motor_set_brake_mode(ARM,MOTOR_BRAKE_HOLD);
			while (motor_get_position(ARM) < ARM_HEIGHT){
				motor_move_velocity(ARM, 60);//70
			}
			motor_move_velocity(ARM, 0);
			suspendCap = false;
		}
		delay(20);
	}
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//LCD BUTTONS FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void LeftButtonPressed(){
	if (auton != 1){
		auton--;
	}
}
void RightButtonPressed(){
	if (auton != 10){
		auton++;
	}
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
