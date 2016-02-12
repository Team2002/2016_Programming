#include "Drive.h"
#include "WPILib.h"
#include "Config.h"


Drive::Drive(void){
	FrontLeft = new Talon(TALON_PORT_FRONTLEFT);
	FrontRight = new Talon(TALON_PORT_FRONTRIGHT);
	BackLeft = new Talon(TALON_PORT_BACKLEFT);
	BackRight = new Talon(TALON_PORT_BACKRIGHT);
}


Drive::~Drive(void){
	delete FrontLeft;
	delete FrontRight;
	delete BackLeft;
	delete BackRight;
}


void Drive::SetMotors(float left, float right){
	TALON_REVERSED_FRONTLEFT ? FrontLeft->Set(-left) : FrontLeft->Set(left);
	TALON_REVERSED_FRONTRIGHT ? FrontRight->Set(-right) : FrontRight->Set(right);
	TALON_REVERSED_BACKLEFT ? BackLeft->Set(-left) : BackLeft->Set(left);
	TALON_REVERSED_BACKRIGHT ? BackRight->Set(-right) : BackRight->Set(right);
}

void Drive::SetMotors(float front_left, float front_right, float back_left, float back_right){
	TALON_REVERSED_FRONTLEFT ? FrontLeft->Set(-front_left) : FrontLeft->Set(front_left);
	TALON_REVERSED_FRONTRIGHT ? FrontRight->Set(-front_right) : FrontRight->Set(front_right);
	TALON_REVERSED_BACKLEFT ? BackLeft->Set(-back_left) : BackLeft->Set(back_left);
	TALON_REVERSED_BACKRIGHT ? BackRight->Set(-back_right) : BackRight->Set(back_right);
}


void Drive::StopMotors(void){
	FrontLeft->Set(0);
	FrontRight->Set(0);
	BackLeft->Set(0);
	BackRight->Set(0);
}
