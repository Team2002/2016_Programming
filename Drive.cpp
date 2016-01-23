#include "Drive.h"
#include "WPILib.h"
#include "Config.h"


Drive::Drive(){
	FrontLeft = new Talon(TALON_PORT_FRONTLEFT);
	FrontRight = new Talon(TALON_PORT_FRONTRIGHT);
	BackLeft = new Talon(TALON_PORT_BACKLEFT);
	BackRight = new Talon(TALON_PORT_BACKRIGHT);
}

Drive::~Drive(){
	delete FrontLeft;
	delete FrontRight;
	delete BackLeft;
	delete BackRight;
}


void Drive::SetMotors(float a, float b, float c, float d, bool reverse){
	if(!reverse){
		FrontLeft->Set(-a * DRIVE_MOTOR_MULTIPLIER / DRIVE_MOTOR_RATIO);
		FrontRight->Set(-b * DRIVE_MOTOR_MULTIPLIER / DRIVE_MOTOR_RATIO);
		BackLeft->Set(-c * DRIVE_MOTOR_MULTIPLIER);
		BackRight->Set(-d * DRIVE_MOTOR_MULTIPLIER);
	}
	else{
		FrontLeft->Set(a * DRIVE_MOTOR_MULTIPLIER / DRIVE_MOTOR_RATIO);
		FrontRight->Set(b * DRIVE_MOTOR_MULTIPLIER / DRIVE_MOTOR_RATIO);
		BackLeft->Set(c * DRIVE_MOTOR_MULTIPLIER);
		BackRight->Set(d * DRIVE_MOTOR_MULTIPLIER);
	}
}
