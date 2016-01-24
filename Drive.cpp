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


void Drive::SetMotors(float left_speed, float right_speed){
	TALON_REVERSED_FRONTLEFT ? FrontLeft->Set(-left_speed) : FrontLeft->Set(left_speed);
	TALON_REVERSED_FRONTRIGHT ? FrontRight->Set(-right_speed) : FrontRight->Set(right_speed);
	TALON_REVERSED_BACKLEFT ? BackLeft->Set(-left_speed) : BackLeft->Set(left_speed);
	TALON_REVERSED_BACKRIGHT ? BackRight->Set(-right_speed) : BackRight->Set(right_speed);
}

void Drive::StopMotors(){
	FrontLeft->Set(0);
	FrontRight->Set(0);
	BackLeft->Set(0);
	BackRight->Set(0);
}
