#include "Catapult.h"
#include "WPILib.h"
#include "Config.h"


Catapult::Catapult(void){
	launchMotor = new Talon(PORT_LAUNCH_TALON);
	launchLimitSwitch = new DigitalInput(PORT_LAUNCH_LIMIT_SWITCH);

	intakeMotor = new Talon(PORT_INTAKE_TALON);
	intakeSolenoid = new DoubleSolenoid(PORT_INTAKE_SOLENOID_1,PORT_INTAKE_SOLENOID_2);
	intakeLimitSwitch = new DigitalInput(PORT_INTAKE_LIMIT_SWITCH);

	// Default states
	launchCurrentState = CHARGING; // Set the catapult to start charging ASAP

	intakeSolenoid->Set(DoubleSolenoid::kForward); // Set the intake to start down so the catapult can charge
	intakeCurrentState = DOWN;
}


Catapult::~Catapult(void){
	delete launchMotor;
	delete launchLimitSwitch;

	delete intakeMotor;
	delete intakeSolenoid;
	delete intakeLimitSwitch;
}


void Catapult::CheckCatapult(void){
	switch(launchCurrentState){
		case CHARGING:
			if(launchLimitSwitch->Get()){
				launchMotor->Set(0);
				launchCurrentState = READY;
			}else{
				launchMotor->Set(LAUNCH_MOTOR_SPEED);
			}
			break;

		case READY: break;

		case FIRE:
			if(launchLimitSwitch->Get()){
				launchMotor->Set(LAUNCH_MOTOR_SPEED);
			}else{
				launchCurrentState = CHARGING;
			}
			break;

		case RELEASE:
			if(launchLimitSwitch->Get()){
				launchMotor->Set(LAUNCH_MOTOR_SPEED);
			}else{
				Wait(RELEASE_TIME_DELAY);
				launchMotor->Set(0);
			}
			break;
	}

	switch(intakeCurrentState){
		case UP:
			intakeSolenoid->Set(DoubleSolenoid::kReverse);
			break;

		case DOWN:
			intakeSolenoid->Set(DoubleSolenoid::kForward);
			break;
	}

	if(intakeLimitSwitch->Get())
		intakeMotor->Set(INTAKE_MOTOR_SPEED);
	else
		intakeMotor->Set(0);
}


void Catapult::SetLaunchState(LaunchState state){
	if(state == CHARGING || state == READY) // Don't allow the launch state to be changed to these values (reserved for class use)
		return;

	if((state == FIRE || state == RELEASE) && launchCurrentState == READY) // Only allow launch state to be changed to FIRE or RELEASE if it is currently READY
		launchCurrentState = state;
}


void Catapult::SetIntakeState(IntakeState state){
	if(state == UP && launchCurrentState == READY) // Only allow the intake to be brought up if the catapult is charged
		intakeCurrentState = UP;

	if(state == DOWN)
		intakeCurrentState = DOWN;
}
