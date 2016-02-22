#ifndef CATAPULT_H__INCLUDED
#define CATAPULT_H__INCLUDED


#include "WPILib.h"

// In this class, the entire boulder launching mechanism (both the "launch" and the "intake") is referred to as the "catapult"
class Catapult{
public:
	Catapult(void);
	~Catapult(void);

	void CheckCatapult(void); // Checks the states of the launch and intake, and their respective limit switches, to see if anything needs to be done

	// Launch
	enum LaunchState {CHARGING, READY, FIRE};
	void SetLaunchState(LaunchState);

	//Intake
	enum IntakeState {UP, DOWN};
	void SetIntakeState(IntakeState);

private:
	// Launch
	Talon* oLaunchMotor;
	Encoder* oLaunchEncoder;
	DigitalInput* oLaunchLimitSwitch;
	LaunchState launchCurrentState;

	// Intake
	Talon* oIntakeMotor;
	DoubleSolenoid* oIntakeSolenoid;
	DigitalInput* oIntakeLimitSwitch;
	IntakeState intakeCurrentState;
};


#endif /* CATAPULT_H__INCLUDED */
