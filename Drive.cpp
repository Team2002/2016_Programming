#include "WPILib.h"
#include "Config.h"
#include "Drive.h"


Drive::Drive(){
	FrontLeft = new Talon(TALON_PORT_FRONTLEFT);
	FrontRight = new Talon(TALON_PORT_FRONTRIGHT);
	BackLeft = new Talon(TALON_PORT_BACKLEFT);
	BackRight = new Talon(TALON_PORT_BACKRIGHT);

	o_Encoder = new Encoder(ENCODER_PORT_1, ENCODER_PORT_2, false, Encoder::k4X);

	o_Encoder->Reset();
}

Drive::~Drive(){
	delete FrontLeft;
	delete FrontRight;
	delete BackLeft;
	delete BackRight;

	delete o_Encoder;
}


void Drive::SetMotors(float a, float b, float c, float d, bool reverse){
	if(!reverse){
		FrontLeft->Set(-a);
		FrontRight->Set(-b);
		BackLeft->Set(-c);
		BackRight->Set(-d);
	}
	else{
		FrontLeft->Set(a);
		FrontRight->Set(b);
		BackLeft->Set(c);
		BackRight->Set(d);
	}

	SmartDashboard::PutNumber("Encoder Get: ", o_Encoder->Get());
	SmartDashboard::PutNumber("Encoder GetRaw: ", o_Encoder->GetRaw());
	SmartDashboard::PutNumber("Encoder GetDistance: ", o_Encoder->GetDistance());
}
