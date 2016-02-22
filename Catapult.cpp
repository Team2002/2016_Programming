#include "Catapult.h"
#include "Config.h"


Catapult::Catapult(void){
	oLaunchMotor = new Talon(PORT_LAUNCH_TALON);
	oLaunchEncoder = new Encoder(PORT_LAUNCH_ENCODER_1, PORT_LAUNCH_ENCODER_2, false, Encoder::EncodingType::k4X);
	oLaunchLimitSwitch = new DigitalInput(PORT_LAUNCH_LIMIT_SWITCH);

	oIntakeMotor = new Talon(PORT_INTAKE_TALON);
	oIntakeSolenoid = new DoubleSolenoid(PORT_INTAKE_SOLENOID_1,PORT_INTAKE_SOLENOID_2);
	oIntakeLimitSwitch = new DigitalInput(PORT_INTAKE_LIMIT_SWITCH);

	// Default states
	launchCurrentState = CHARGING; // Set the catapult to start charging ASAP
	intakeCurrentState = DOWN; // Set the intake to start in the down position, so that the catapult can charge
}


Catapult::~Catapult(void){
	delete oLaunchMotor;
	delete oLaunchEncoder;
	delete oLaunchLimitSwitch;

	delete oIntakeMotor;
	delete oIntakeSolenoid;
	delete oIntakeLimitSwitch;
}


void Catapult::CheckCatapult(void){


	SmartDashboard::PutNumber("ENCODER ", oLaunchEncoder->Get());


	switch(launchCurrentState){
		case CHARGING:
			if(oLaunchLimitSwitch->Get()){
				oLaunchMotor->Set(0);
				launchCurrentState = READY;
			}else{
				LAUNCH_MOTOR_REVERSED ? oLaunchMotor->Set(-LAUNCH_MOTOR_SPEED) : oLaunchMotor->Set(LAUNCH_MOTOR_SPEED);
			}
			break;

		case READY: break;

		case FIRE:
			if(oIntakeLimitSwitch->Get()){ // Only fire if the intake is down. Checks the limit switch because it takes some ammount of time for the piston to physically actuate.
				if(oLaunchLimitSwitch->Get())
					LAUNCH_MOTOR_REVERSED ? oLaunchMotor->Set(-LAUNCH_MOTOR_SPEED) : oLaunchMotor->Set(LAUNCH_MOTOR_SPEED);
				else
					launchCurrentState = CHARGING;
			}else{
				intakeCurrentState = DOWN;
			}
			break;
	}

	switch(intakeCurrentState){
		case UP:
			oIntakeSolenoid->Set(DoubleSolenoid::kReverse);
			break;

		case DOWN:
			oIntakeSolenoid->Set(DoubleSolenoid::kForward);
			break;
	}

	if(oIntakeLimitSwitch->Get())
		INTAKE_MOTOR_REVERSED ? oIntakeMotor->Set(-INTAKE_MOTOR_SPEED) : oIntakeMotor->Set(INTAKE_MOTOR_SPEED);
	else
		oIntakeMotor->Set(0);
}


void Catapult::SetLaunchState(LaunchState state){
	if(state == CHARGING || state == READY) // Don't allow the launch state to be changed to these values (reserved for class use)
		return;

	if(state == FIRE && launchCurrentState == READY) // Only allow launch state to be changed to FIRE if it is currently READY
		launchCurrentState = FIRE;
}


void Catapult::SetIntakeState(IntakeState state){
	if(state == UP && launchCurrentState == READY) // Only allow the intake to be brought up if the catapult is charged
		intakeCurrentState = UP;

	if(state == DOWN)
		intakeCurrentState = DOWN;
}
