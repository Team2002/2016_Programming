#include "Robot.h"
#include "WPILib.h"
#include "Config.h"
#include "Drive.h"


Robot::Robot(void){
	o_Joystick = new Joystick(JOYSTICK_PORT);
	o_Drive = new Drive();

	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	imaqError = IMAQdxOpenCamera(CAMERA_NAME, IMAQdxCameraControlModeController, &session);
}


Robot::~Robot(void){
	delete o_Joystick;
	delete o_Drive;
}


void Robot::RobotInit(void){
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
	}
	imaqError = IMAQdxConfigureGrab(session);
	if(imaqError != IMAQdxErrorSuccess){
		DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
	}
}


void Robot::Autonomous(void){
	
}


void Robot::OperatorControl(void){
	float speed_left;
	float speed_right;
	bool reverse;

	IMAQdxStartAcquisition(session);

	while(IsOperatorControl() && IsEnabled()){
		speed_left = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
		speed_right = o_Joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);
		reverse = o_Joystick->GetRawButton(JOYSTICK_BUTTON_REVERSE);

		o_Drive->SetMotors(speed_left, speed_right, speed_left, speed_right, reverse);

		IMAQdxGrab(session, frame, true, NULL);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
		}else{
			CameraServer::GetInstance()->SetImage(frame);
		}

		Wait(CYCLE_TIME_DELAY);
	}

	IMAQdxStopAcquisition(session);
}


START_ROBOT_CLASS(Robot);
