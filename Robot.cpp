#include "Robot.h"
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Config.h"
#include "Drive.h"


Robot::Robot(void){
	o_Joystick = new Joystick(JOYSTICK_PORT);
	o_Drive = new Drive();

	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	imaqError = IMAQdxOpenCamera(CAMERA_NAME, IMAQdxCameraControlModeController, &session);

	table = &*NetworkTable::GetTable("datatable");
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

	const int RES_X = 640;
	const int CENTERED_THRESHOLD = 50;
	const float SPEED = 1;

	std::vector<double> coord;

	IMAQdxStartAcquisition(session);

	while(IsOperatorControl() && IsEnabled()){
		IMAQdxGrab(session, frame, true, NULL);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
		}else{
			CameraServer::GetInstance()->SetImage(frame);
		}

		if(o_Joystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)){
			coord = table->GetNumberArray("BLOBS", 0);

			SmartDashboard::PutNumber("BLOB X: ", coord[0]);
			SmartDashboard::PutNumber("BLOB Y: ", coord[1]);

			if(coord[0] < (RES_X / 2) - CENTERED_THRESHOLD){
				SmartDashboard::PutString("TURN DIRECTION:  ", "Left");
				o_Drive->SetMotors(-SPEED, SPEED, false);
			}else if(coord[0] > (RES_X / 2) + CENTERED_THRESHOLD){
				SmartDashboard::PutString("TURN DIRECTION:  ", "Right");
				o_Drive->SetMotors(SPEED, -SPEED, false);
			}else{
				SmartDashboard::PutString("TURN DIRECTION:  ", "Centered");
				o_Drive->SetMotors(0, 0, false);
			}
		}else{
			speed_left = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speed_right = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);
			reverse = o_Joystick->GetRawButton(JOYSTICK_BUTTON_REVERSE);

			o_Drive->SetMotors(speed_left, speed_right, reverse);
		}
		Wait(CYCLE_TIME_DELAY);
	}
	IMAQdxStopAcquisition(session);
}


START_ROBOT_CLASS(Robot);
