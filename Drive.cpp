#include "WPILib.h"
#include "Config.h"
#include "Drive.h"


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


void Drive::SetMotors(float a, float b, float c, float d){
	FrontLeft->Set(-a / RATIO);
	FrontRight->Set(b / RATIO);
	BackLeft->Set(-c);
	BackRight->Set(d);
}
