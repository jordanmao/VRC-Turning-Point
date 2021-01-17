#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//MISCELLANEOUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int GetSign(int number);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//DRIVE FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Drive Brake Functions=========================================================
void SetDriveBrake(int brakeMode);
//Drive Voltage Functions=======================================================
void LeftDriveVoltage(int voltage);
void RightDriveVoltage(int voltage);
void DriveVoltage(int voltage);
//Drive Velocity Functions======================================================
void LeftDriveVelocity(float velocity);
void RightDriveVelocity(float velocity);
void DriveVelocity(float velocity);
//Squaring Functions============================================================
void Square(int voltage);
//Drive Encoder Functions=======================================================
void ResetEncoders();
void Move(float degrees, int velocity, _Bool rampUp);
void LeftMove(float degrees, int velocity);
void RightMove(float degrees, int velocity);
void PMove(float target);
void Turn(float degrees, int velocity, _Bool turnLeft);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//GYRO FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void PIDGyroTurn(float target);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//INTAKE FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void IntakeVoltage(int voltage);
void IntakeVelocity(int velocity);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//CATAPULT FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void CatapultVelocity(int velocity);
void CatapultVoltage(int voltage);
void CatapultMove(float degrees, int velocity);
void SetCatapultFn();
void WaitForShot();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//CAP SCORER FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void ArmVelocity(int velocity);
void ArmVoltage(int voltage);
void SuspendCapFn();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//LCD BUTTONS FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void LeftButtonPressed();
void RightButtonPressed();
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
