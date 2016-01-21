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
	CameraServer::GetInstance()->SetQuality(CAMERA_QUALITY);
	CameraServer::GetInstance()->StartAutomaticCapture("cam0");
}


void Robot::Autonomous(void){
	
}


void Robot::OperatorControl(void){
	float speed_left;
	float speed_right;
	bool reverse;

	while(IsOperatorControl() && IsEnabled()){
		speed_left = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
		speed_right = o_Joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);
		reverse = o_Joystick->GetRawButton(JOYSTICK_BUTTON_REVERSE);

		o_Drive->SetMotors(speed_left, speed_right, speed_left, speed_right, reverse);
	}
}


START_ROBOT_CLASS(Robot);
