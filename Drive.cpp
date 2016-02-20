#include "Drive.h"
#include "WPILib.h"
#include "Config.h"


Drive::Drive(void){
	frontLeft = new Talon(PORT_DRIVE_TALON_FRONTLEFT);
	frontRight = new Talon(PORT_DRIVE_TALON_FRONTRIGHT);
	backLeft = new Talon(PORT_DRIVE_TALON_BACKLEFT);
	backRight = new Talon(PORT_DRIVE_TALON_BACKRIGHT);
}


Drive::~Drive(void){
	delete frontLeft;
	delete frontRight;
	delete backLeft;
	delete backRight;
}


void Drive::SetMotors(float left, float right){
	DRIVE_MOTOR_FRONTLEFT_REVERSED ? frontLeft->Set(-left) : frontLeft->Set(left);
	DRIVE_MOTOR_FRONTRIGHT_REVERSED ? frontRight->Set(-right) : frontRight->Set(right);
	DRIVE_MOTOR_BACKLEFT_REVERSED ? backLeft->Set(-left) : backLeft->Set(left);
	DRIVE_MOTOR_BACKRIGHT_REVERSED ? backRight->Set(-right) : backRight->Set(right);
}

void Drive::SetMotors(float front_left, float front_right, float back_left, float back_right){
	DRIVE_MOTOR_FRONTLEFT_REVERSED ? frontLeft->Set(-front_left) : frontLeft->Set(front_left);
	DRIVE_MOTOR_FRONTRIGHT_REVERSED ? frontRight->Set(-front_right) : frontRight->Set(front_right);
	DRIVE_MOTOR_BACKLEFT_REVERSED ? backLeft->Set(-back_left) : backLeft->Set(back_left);
	DRIVE_MOTOR_BACKRIGHT_REVERSED ? backRight->Set(-back_right) : backRight->Set(back_right);
}


void Drive::StopMotors(void){
	frontLeft->Set(0);
	frontRight->Set(0);
	backLeft->Set(0);
	backRight->Set(0);
}
