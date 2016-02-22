#include "Drive.h"
#include "Config.h"


Drive::Drive(void){
	oFrontLeft = new Talon(PORT_DRIVE_TALON_FRONTLEFT);
	oFrontRight = new Talon(PORT_DRIVE_TALON_FRONTRIGHT);
	oBackLeft = new Talon(PORT_DRIVE_TALON_BACKLEFT);
	oBackRight = new Talon(PORT_DRIVE_TALON_BACKRIGHT);
}


Drive::~Drive(void){
	delete oFrontLeft;
	delete oFrontRight;
	delete oBackLeft;
	delete oBackRight;
}


void Drive::SetMotors(float left, float right){
	DRIVE_MOTOR_FRONTLEFT_REVERSED ? oFrontLeft->Set(-left) : oFrontLeft->Set(left);
	DRIVE_MOTOR_FRONTRIGHT_REVERSED ? oFrontRight->Set(-right) : oFrontRight->Set(right);
	DRIVE_MOTOR_BACKLEFT_REVERSED ? oBackLeft->Set(-left) : oBackLeft->Set(left);
	DRIVE_MOTOR_BACKRIGHT_REVERSED ? oBackRight->Set(-right) : oBackRight->Set(right);
}


void Drive::StopMotors(void){
	oFrontLeft->Set(0);
	oFrontRight->Set(0);
	oBackLeft->Set(0);
	oBackRight->Set(0);
}
