#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
//INCLUDES======================================================================
#include "api.h"
//#include "okapi/api.hpp"
#include "pros/api_legacy.h"
//==============================================================================

//CONFIG========================================================================
//Motors------------------------------------------------------------------------
#define LEFT_DRIVE_1 4
#define LEFT_DRIVE_2 10
#define RIGHT_DRIVE_1 5
#define RIGHT_DRIVE_2 3
#define LEFT_CATAPULT 6
#define RIGHT_CATAPULT 8
#define INTAKE 9
#define ARM 2
//Sensors-----------------------------------------------------------------------
#define POTENTIOMETER 'D'
extern adi_gyro_t gyro;
#define GYRO 'B'
#define GYRO_MULTIPLIER 1
//==============================================================================

//GLOBAL VARIABLES AND MACROS===================================================
#define CATAPULT_STAGE_1 2100//Released stage
#define CATAPULT_STAGE_2 1640//Loading stage
#define ARM_HEIGHT 355
extern int catapultStage;
extern bool readyToShoot;
extern bool suspendCap;
extern int auton;
//==============================================================================

//AUTON SELECT==================================================================
#define SKILLS 1
#define RED_FLAGS_1 2
#define BLUE_FLAGS_1 3
#define RED_FLAGS_2 4
#define BLUE_FLAGS_2 5
#define RED_CAPS 6
#define BLUE_CAPS 7
#define RED_CAPS_PARK 8
#define BLUE_CAPS_PARK 9
#define NONE 10
//==============================================================================
/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
void autonomous(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
