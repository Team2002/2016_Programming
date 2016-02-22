#include "Lift.h"
#include "Config.h"


Lift::Lift(void){
	oTalonUp = new Talon(PORT_LIFT_TALON_UP);
	oTalonDown = new Talon(PORT_LIFT_TALON_DOWN);
	oSolenoid = new DoubleSolenoid(PORT_LIFT_SOLENOID_1, PORT_LIFT_SOLENOID_1);
}


Lift::~Lift(void){
	delete oTalonUp;
	delete oTalonDown;
	delete oSolenoid;
}
