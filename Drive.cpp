#include "Drive.h"
#include "Config.h"


Drive::Drive(void){
	oFrontLeft = new Talon(PORT_TALON_DRIVE_FRONTLEFT);
	oFrontRight = new Talon(PORT_TALON_DRIVE_FRONTRIGHT);
	oBackLeft = new Talon(PORT_TALON_DRIVE_BACKLEFT);
	oBackRight = new Talon(PORT_TALON_DRIVE_BACKRIGHT);
}


Drive::~Drive(void){
	delete oFrontLeft;
	delete oFrontRight;
	delete oBackLeft;
	delete oBackRight;
}


void Drive::SetMotors(float left, float right){
	DRIVE_MOTOR_FRONTLEFT_REVERSED ? oFrontLeft->Set(-left * LEFT_MOTOR_MULTIPLIER) : oFrontLeft->Set(left * LEFT_MOTOR_MULTIPLIER);
	DRIVE_MOTOR_FRONTRIGHT_REVERSED ? oFrontRight->Set(-right * RIGHT_MOTOR_MULTIPLIER) : oFrontRight->Set(right * RIGHT_MOTOR_MULTIPLIER);
	DRIVE_MOTOR_BACKLEFT_REVERSED ? oBackLeft->Set(-left * LEFT_MOTOR_MULTIPLIER) : oBackLeft->Set(left * LEFT_MOTOR_MULTIPLIER);
	DRIVE_MOTOR_BACKRIGHT_REVERSED ? oBackRight->Set(-right * RIGHT_MOTOR_MULTIPLIER) : oBackRight->Set(right * RIGHT_MOTOR_MULTIPLIER);
}


void Drive::StopMotors(void){
	oFrontLeft->Set(0);
	oFrontRight->Set(0);
	oBackLeft->Set(0);
	oBackRight->Set(0);
}
