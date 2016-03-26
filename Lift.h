#ifndef LIFT_H__INCLUDED
#define LIFT_H__INCLUDED


#include "WPILib.h"


class Lift{
public:
	Lift(void);
	~Lift(void);

	void LiftUp(void);
	void LiftDown(void);
	void LiftStop(void);

	enum LiftPiston {IN, OUT};
	void LiftToggleInOut(void);

private:
	void Move(float, float, float, float);

	LiftPiston LiftPistonCurrentState;

	Talon *oTalonLeftUp, *oTalonRightUp, *oTalonLeftDown, *oTalonRightDown;
	DoubleSolenoid* oSolenoid;

	const float LIFT_SPEED_UP = 1;
	const float LIFT_SPEED_DOWN = 1;
};


#endif /* LIFT_H__INCLUDED */
