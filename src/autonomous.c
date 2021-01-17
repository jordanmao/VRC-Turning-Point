#include "main.h"
#include "functions.h"

void autonomous() {
	task_t SetCatapult = task_create(SetCatapultFn, NULL,TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "SetCatapult");
	task_t SuspendCap = task_create(SuspendCapFn, NULL,TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "SuspendCap");
	SetDriveBrake(MOTOR_BRAKE_HOLD);
	motor_set_brake_mode(ARM, MOTOR_BRAKE_BRAKE);
	catapultStage = 0;
	adi_gyro_reset(gyro);
	if (auton == SKILLS){//SKILLS AUTONOMOUS////////////////////////////////////
		//FIRST SET OF FLAGS====================================================
		PMove(1150);
		//Flipping Cap
		IntakeVelocity(-100);
		ArmVelocity(110);
		Move(110,50,false);
		IntakeVelocity(0);
		ArmVoltage(-50);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		delay(100);
		//Getting Ball Under Cap
		IntakeVelocity(400);
		Move(70,50,false);
		delay(300);
		PMove(-1200);//-1200
		ArmVoltage(0);
		//Aiming For Flags
		PIDGyroTurn(-970);
		Move(610,150,false);
		delay(400);
		//Shooting Flags
		catapultStage = 1;
		WaitForShot();
		IntakeVelocity(-100);
		//Going For Two Balls On CAP
		PIDGyroTurn(-1990);//-2000
		delay(100);
		ArmVoltage(-30);
		Move(-450,-50,false);
		delay(300);
		//Picking Up Cap
		ArmVoltage(0);
		suspendCap = true;
		delay(1500);
		suspendCap = false;
		motor_set_brake_mode(ARM,MOTOR_BRAKE_COAST);
		ArmVoltage(-50);
		delay(300);
		ArmVoltage(0);
		IntakeVelocity(0);
		//Toggling low Flag
		Move(490,130,false);
		delay(150);
		PIDGyroTurn(-1000);
		delay(150);
		Move(780,150,false);
		//Squaring
		Square(65);
		adi_gyro_reset(gyro);
		delay(100);
		//Flipping Cap
		PMove(-370);
		PIDGyroTurn(1285);
		IntakeVelocity(-300);
		motor_set_brake_mode(INTAKE, MOTOR_BRAKE_HOLD);
		Move(830,80,false);
		delay(800);
		IntakeVelocity(0);
		Move(600,70,false);
		motor_set_brake_mode(INTAKE, MOTOR_BRAKE_COAST);
		//MIDDLE SET OF FLAGS===================================================
		//Aiming For Flags
		Move(-90,-70,false);
		PIDGyroTurn(120);
		Move(160,70,false);
		//Shooting Flags
		catapultStage = 1;
		WaitForShot();
		//Toggling low flag
		RightMove(70,50);
		delay(150);
		Move(400,170,false);
		Square(50);
		adi_gyro_reset(gyro);
		//LAST SET OF FLAGS=====================================================
		//Getting Two Balls On Cap
		PMove(-360);
		PIDGyroTurn(-785);
		PMove(-990);
		ArmVoltage(-30);
		Move(-370,-50,false);
		delay(200);
		//Picking Up Cap
		ArmVoltage(0);
		suspendCap = true;
		IntakeVelocity(400);
		delay(1500);
		//Shooting Flags
		PIDGyroTurn(110);
		Move(-50,-70,false);
		catapultStage = 1;
		WaitForShot();
		IntakeVelocity(0);
		//Toggling Low Flag
		RightMove(50,50);
		delay(150);
		Move(350,170,false);
		Square(50);
		adi_gyro_reset(gyro);
		//Flipping Cap on Ball
		PMove(-900);//-1400
		PIDGyroTurn(-1340);
		delay(100);
		IntakeVelocity(-200);
		PMove(820);
		delay(300);
		LeftMove(180,70);
		delay(300);
		//BACK HALF OF THE FIELD================================================
		//Resetting
		Move(-1250,-180,false);
		Square(-40);
		adi_gyro_reset(gyro);
		//Going To Pole On Back Wall
		PMove(500);//470
		PIDGyroTurn(-910);//-920
		delay(150);
		PMove(2100);
		Square(60);
		adi_gyro_reset(gyro);
		//Putting Cap On Pole
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		ArmVoltage(100);
		delay(500);
		ArmVoltage(0);
		//Moving Out
		Move(-300,-130,false);
		ArmVoltage(-100);
		Move(-450,-130,false);
		ArmVoltage(0);
		IntakeVelocity(0);
		//Flipping Cap On Ball
		PIDGyroTurn(850);
		PMove(820);
		//PARKING ON YELLOW PLATFORM============================================
		Move(-280,-100,false);
		PIDGyroTurn(1940);
		IntakeVoltage(70);
		//Blue Platform
		Square(40);
		adi_gyro_reset(gyro);
		Move(540,160,false);
		PIDGyroTurn(-970);
		//Yellow Platform
		Square(40);
		Move(560,160,false);
		IntakeVoltage(0);
	}
	else if (auton == RED_FLAGS_1 || auton == RED_FLAGS_2){/////////////////////
		//First Set Of Flags====================================================
		//Getting Ball Under Cap
		PMove(1180);
		IntakeVelocity(300);
		ArmVelocity(110);
		Move(110,40,false);
		ArmVoltage(-50);
		delay(200);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		PMove(-1100);
		ArmVoltage(0);
		//Aiming for First set of flags
		PIDGyroTurn(-970);
		Move(600,150,false);
		delay(200);
		//Shooting First set of flags
		catapultStage = 1;
		WaitForShot();
		if (auton == RED_FLAGS_1){
			IntakeVelocity(500);
			//Toggling low flag
			RightMove(60,60);
			delay(200);
			Move(740,180,false);
			//Squaring
			Square(65);
			adi_gyro_reset(gyro);
			//Flipping CAP
			Move(-370,-150,false);
			IntakeVelocity(80);
			PIDGyroTurn(1310);
			IntakeVelocity(-400);
			PMove(750);
			IntakeVelocity(0);
			//Aiming for Middle Set of Flags
			PIDGyroTurn(490);
			Move(370,100,false);
			delay(100);
			//Shooting Middle set of flags
			catapultStage = 1;
			WaitForShot();
			//Toggling low flag of middle SET
			Move(360,180,false);
			RightMove(330,190);
		}
		else{
			PIDGyroTurn(-2000);
			IntakeVelocity(300);
			delay(150);
			ArmVoltage(-30);
			Move(-480,-50,false);
			delay(300);
			ArmVoltage(0);
			suspendCap = true;
			delay(1000);
			PIDGyroTurn(-470);
			Move(320,70,false);
			delay(100);
			catapultStage = 1;
			WaitForShot();
			IntakeVelocity(0);
			Move(500,150,false);
			RightMove(330,190);
		}

	}
	else if (auton == BLUE_FLAGS_1 || auton == BLUE_FLAGS_2){
		//Getting ball under cap
		PMove(1150);
		IntakeVelocity(300);
		ArmVelocity(110);
		Move(110,40,false);
		ArmVoltage(-50);
		delay(200);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		PMove(-1120);
		ArmVoltage(0);
		//Aiming for First set of flags
		PIDGyroTurn(970);
		Move(560,150,false);
		delay(200);
		//Shooting First set of flags
		catapultStage = 1;
		WaitForShot();
		if (auton == BLUE_FLAGS_1){
			IntakeVelocity(500);
			//Toggling low flag
			LeftMove(20,50);
			delay(200);
			Move(740,130,false);
			//Squaring
			Square(50);
			adi_gyro_reset(gyro);
			//Flipping CAP
			IntakeVelocity(400);
			PMove(-370);
			IntakeVelocity(80);
			PIDGyroTurn(-1310);
			IntakeVelocity(-400);
			PMove(750);
			IntakeVelocity(0);
			//Aiming for Middle Set of Flags
			PIDGyroTurn(-500);
			Move(330,100,false);
			delay(100);
			//Shooting Middle set of flags
			catapultStage = 1;
			WaitForShot();
			//Toggling low flag of middle SET
			Move(370,180,false);
			LeftMove(300,190);
		}
		else{
			PIDGyroTurn(1950);
			IntakeVelocity(300);
			delay(150);
			ArmVoltage(-30);
			Move(-480,-50,false);
			delay(300);
			ArmVoltage(0);
			suspendCap = true;
			delay(1200);
			PIDGyroTurn(380);
			Move(320,70,false);
			delay(100);
			catapultStage = 1;
			WaitForShot();
			IntakeVelocity(0);
			Move(350,150,false);
			LeftMove(330,190);
		}
	}
	else if (auton == RED_CAPS){
		ArmVelocity(200);
		delay(400);
		ArmVelocity(0);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		ArmVoltage(-90);
		delay(300);
		//Picking up for cap
		PMove(-1400);
		ArmVoltage(0);
		suspendCap = true;
		RightMove(70,50);
		IntakeVelocity(-300);
		delay(200);
		//Going to pole
		Move(1260,200,false);
		IntakeVelocity(0);
		DriveVoltage(60);
		delay(200);
		DriveVoltage(0);
		LeftDriveVoltage(70);
		delay(200);
		LeftDriveVoltage(0);
		delay(100);
		//Putting Cap on Pole
		adi_gyro_reset(gyro);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		ArmVoltage(90);
		delay(500);
		ArmVoltage(0);
		delay(100);
		IntakeVelocity(-300);
		Move(-300,-80,false);
		ArmVoltage(-80);
		delay(200);
		//Going for ball under cap
		PIDGyroTurn(1730);
		ArmVoltage(0);
		IntakeVelocity(300);
		Move(1000,100,false);
		delay(200);
		IntakeVelocity(0);
		PIDGyroTurn(1230);
		Move(50,40,false);
		catapultStage = 1;
		WaitForShot();
		IntakeVelocity(500);
		LeftMove(-150,-50);
		delay(200);
		Move(-220,-100,false);
		delay(200);
		readyToShoot = false;
		delay(300);
		Move(-40,-35,false);
		delay(300);
		catapultStage = 1;
		WaitForShot();
	}
	else if (auton == BLUE_CAPS){
		ArmVoltage(110);
		delay(350);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		ArmVoltage(-90);
		delay(300);
		//Picking up for cap
		PMove(-1400);
		ArmVoltage(0);
		suspendCap = true;
		LeftMove(70,50);
		IntakeVelocity(-300);
		delay(200);
		//Going to pole
		Move(1260,200,false);
		IntakeVelocity(0);
		DriveVoltage(80);
		delay(300);
		DriveVoltage(0);
		LeftDriveVoltage(80);
		delay(300);
		LeftDriveVoltage(0);
		//Putting Cap on Pole
		adi_gyro_reset(gyro);
		motor_set_brake_mode(ARM, MOTOR_BRAKE_COAST);
		ArmVoltage(100);
		delay(500);
		ArmVoltage(0);
		delay(100);
		IntakeVelocity(-300);
		Move(-300,-80,false);
		ArmVoltage(-80);
		delay(100);
		//Going for ball under cap
		PIDGyroTurn(-1850);
		ArmVoltage(0);
		delay(100);
		IntakeVelocity(300);
		Move(960,100,false);
		delay(300);
		IntakeVelocity(0);
		PIDGyroTurn(-1340);
		Move(70,40,false);
		catapultStage = 1;
		WaitForShot();
		IntakeVelocity(500);
		RightMove(-150,-50);
		delay(200);
		Move(-140,-50,false);
		delay(200);
		readyToShoot = false;
		delay(300);
		Move(-40,-40,false);
		delay(300);
		catapultStage = 1;
		WaitForShot();
	}
}
