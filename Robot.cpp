#include "WPILib.h"
#include "Robot.h"
#include "Drive.h"
#include "Config.h"


Robot::Robot(void){
	o_Joystick = new Joystick(JOYSTICK_PORT);
	o_Drive = new Drive();
}


Robot::~Robot(void){
	delete o_Joystick;
	delete o_Drive;
}


void Robot::RobotInit(void){
	
}


void Robot::Autonomous(void){
	
}


void Robot::OperatorControl(void){
	bool stop;
	float speed;
	float turn;

	while(true){
		stop = o_Joystick->GetRawButton(JOYSTICK_BUTTON_STOP);
		speed = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_Y);
		turn = o_Joystick->GetRawAxis(JOYSTICK_AXIS_Z);

		if(!stop){
			o_Drive->SetMotors(speed + turn, speed - turn, speed + turn, speed - turn);
		}
		else{
			o_Drive->SetMotors(0, 0, 0, 0);
		}
	}
}


START_ROBOT_CLASS(Robot);
