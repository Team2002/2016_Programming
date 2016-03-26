#ifndef CATAPULT_H__INCLUDED
#define CATAPULT_H__INCLUDED


#include "WPILib.h"

// In this class, the entire boulder launching mechanism (both the "launch" and the "intake") is referred to as the "catapult"
class Catapult{
public:
	Catapult(void);
	~Catapult(void);

	void SetCharging(void); // Puts the intake DOWN and starts CHARGING the launch
	void SetReady(void); // Brings the intake UP ands sets the launch to READY. Use when starting the robot with the launch already charged to prevent unwanted firing.

	void CheckCatapult(void); // Checks the states of the launch and intake, and their respective limit switches, to see if anything needs to be done

	// Launch
	enum LaunchState {CHARGING, READY, FIRE};
	void SetLaunchState(LaunchState);

	//Intake
	enum IntakeState {UP, DOWN};
	void SetIntakeState(IntakeState);
	enum IntakeWheels {FORWARD, BACK, OFF};
	void ForceIntakeWheels(IntakeWheels);

private:
	// Launch
	Talon* oLaunchMotor;
	DigitalInput* oLaunchLimitSwitch;
	LaunchState launchCurrentState;

	// Intake
	Talon* oIntakeMotor;
	DoubleSolenoid* oIntakeSolenoid;
	DigitalInput* oIntakeLimitSwitch;
	IntakeState intakeCurrentState;
	IntakeWheels intakeWheelsState;
	bool intakeStateChanged; // Used to be sure the intake solenoid only changes states if it needs to
};


#endif /* CATAPULT_H__INCLUDED */
