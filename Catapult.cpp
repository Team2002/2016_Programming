#include "Catapult.h"
#include "Config.h"


Catapult::Catapult(void){
	oLaunchMotor = new Talon(PORT_TALON_LAUNCH);
	oLaunchLimitSwitch = new DigitalInput(PORT_LIMIT_SWITCH_LAUNCH);

	oIntakeMotor = new Talon(PORT_TALON_INTAKE);
	oIntakeSolenoid = new DoubleSolenoid(PORT_SOLENOID_INTAKE_1,PORT_SOLENOID_INTAKE_2);
	oIntakeLimitSwitch = new DigitalInput(PORT_LIMIT_SWITCH_INTAKE);

	// Default states. These states will prevent the launch from moving on its own, but call SetCharging() or SetReady() before using the catapult to be sure that the states are set to what they should be.
	launchCurrentState = READY;
	intakeCurrentState = DOWN;
	intakeWheelsState = OFF;
	intakeStateChanged = false;
}


Catapult::~Catapult(void){
	delete oLaunchMotor;
	delete oLaunchLimitSwitch;
	delete oIntakeMotor;
	delete oIntakeSolenoid;
	delete oIntakeLimitSwitch;
}


void Catapult::SetCharging(void){
	launchCurrentState = CHARGING;
	intakeCurrentState = DOWN;

	intakeStateChanged = true;
}


void Catapult::SetReady(void){
	launchCurrentState = READY;
	intakeCurrentState = UP;

	intakeStateChanged = true;
}


void Catapult::CheckCatapult(void){
	// Launch state
	switch(launchCurrentState){
		case CHARGING:
			if(oLaunchLimitSwitch->Get()){
				Wait(0.75); // Make this a timer, rather than a wait
				oLaunchMotor->Set(0);
				launchCurrentState = READY;
			}else{
				if(oIntakeLimitSwitch->Get()) // Only CHARGE if the intake is DOWN
					LAUNCH_MOTOR_REVERSED ? oLaunchMotor->Set(-LAUNCH_MOTOR_SPEED) : oLaunchMotor->Set(LAUNCH_MOTOR_SPEED);
				else
					oLaunchMotor->Set(0);
			}
			break;

		case FIRE:
			if(oLaunchLimitSwitch->Get()){
				if(oIntakeLimitSwitch->Get()) // Only FIRE if the intake is DOWN
					LAUNCH_MOTOR_REVERSED ? oLaunchMotor->Set(-LAUNCH_MOTOR_SPEED) : oLaunchMotor->Set(LAUNCH_MOTOR_SPEED);
				else
					oLaunchMotor->Set(0);
			}else{
				oLaunchMotor->Set(0);
				launchCurrentState = CHARGING;
			}
			break;

		case READY:
		default:
			break;
	}

	// Intake state
	if(intakeStateChanged){ // Only check the solenoid state if it needs to change
		switch(intakeCurrentState){
			case UP:
				oIntakeSolenoid->Set(DoubleSolenoid::kReverse);
				break;

			case DOWN:
				oIntakeSolenoid->Set(DoubleSolenoid::kForward);
				break;

			default:
				oIntakeSolenoid->Set(DoubleSolenoid::kOff);
				break;
		}

		intakeStateChanged = false;
	}

	// Intake wheels
	if(intakeWheelsState == FORWARD)
		INTAKE_MOTOR_REVERSED ? oIntakeMotor->Set(-INTAKE_MOTOR_SPEED) : oIntakeMotor->Set(INTAKE_MOTOR_SPEED);
	else if(intakeWheelsState == BACK)
		INTAKE_MOTOR_REVERSED ? oIntakeMotor->Set(INTAKE_MOTOR_SPEED) : oIntakeMotor->Set(-INTAKE_MOTOR_SPEED);
	else if(oIntakeLimitSwitch->Get())
		INTAKE_MOTOR_REVERSED ? oIntakeMotor->Set(-INTAKE_MOTOR_SPEED) : oIntakeMotor->Set(INTAKE_MOTOR_SPEED);
	else
		oIntakeMotor->Set(0);
}


void Catapult::ForceIntakeWheels(IntakeWheels state){
	intakeWheelsState = state;
}


void Catapult::SetLaunchState(LaunchState state){
	if(state == CHARGING || state == READY) // Don't allow the launch state to be changed to these values
		return;

	if(state == FIRE && launchCurrentState == READY && oIntakeLimitSwitch->Get()) // Only allow the launch state to be changed to FIRE if it is currently READY and the intake is DOWN
		launchCurrentState = FIRE;
}


void Catapult::SetIntakeState(IntakeState state){
	intakeStateChanged = true;

	if(state == UP && launchCurrentState == READY) // Only allow the intake to be brought UP if the launch state is READY
		intakeCurrentState = UP;

	if(state == DOWN)
		intakeCurrentState = DOWN;
}
