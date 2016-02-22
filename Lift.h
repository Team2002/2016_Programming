#ifndef LIFT_H__INCLUDED
#define LIFT_H__INCLUDED


#include "WPILib.h"


class Lift{
public:
	Lift(void);
	~Lift(void);
	
private:
	Talon* oTalonUp;
	Talon* oTalonDown;
	DoubleSolenoid* oSolenoid;
};


#endif /* LIFT_H__INCLUDED */
