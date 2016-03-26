#include "Lift.h"
#include "Config.h"


Lift::Lift(void){
	oTalonLeftUp = new Talon(PORT_TALON_LIFT_LEFT_UP);
	oTalonRightUp = new Talon(PORT_TALON_LIFT_RIGHT_UP);
	oTalonLeftDown = new Talon(PORT_TALON_LIFT_LEFT_DOWN);
	oTalonRightDown = new Talon(PORT_TALON_LIFT_RIGHT_DOWN);
	oSolenoid = new DoubleSolenoid(PORT_SOLENOID_LIFT_1, PORT_SOLENOID_LIFT_2);

	LiftPistonCurrentState = IN;
	oSolenoid->Set(DoubleSolenoid::kReverse);
}


Lift::~Lift(void){
	delete oTalonLeftUp;
	delete oTalonRightUp;
	delete oTalonLeftDown;
	delete oTalonRightDown;
	delete oSolenoid;
}


void Lift::Move(float leftUp, float rightUp, float leftDown, float rightDown){
	LIFT_MOTOR_LEFT_UP_REVERSED ? oTalonLeftUp->Set(-leftUp) : oTalonLeftUp->Set(leftUp);
	LIFT_MOTOR_RIGHT_UP_REVERSED ? oTalonRightUp->Set(-rightUp) : oTalonRightUp->Set(rightUp);
	LIFT_MOTOR_LEFT_DOWN_REVERSED ? oTalonLeftDown->Set(-leftDown) : oTalonLeftDown->Set(leftDown);
	LIFT_MOTOR_RIGHT_DOWN_REVERSED ? oTalonRightDown->Set(-rightDown) : oTalonRightDown->Set(rightDown);
}


void Lift::LiftUp(void){
	Move(LIFT_SPEED_UP, LIFT_SPEED_UP, -LIFT_SPEED_DOWN, -LIFT_SPEED_DOWN);
}


void Lift::LiftDown(void){
	Move(-LIFT_SPEED_UP, -LIFT_SPEED_UP, LIFT_SPEED_DOWN, LIFT_SPEED_DOWN);
}


void Lift::LiftStop(void){
	Move(0, 0, 0, 0);
}


void Lift::LiftToggleInOut(void){
	if(LiftPistonCurrentState == IN){
		LiftPistonCurrentState == OUT;
		oSolenoid->Set(DoubleSolenoid::kForward);
	}else{
		LiftPistonCurrentState == IN;
		oSolenoid->Set(DoubleSolenoid::kReverse);
	}
}
