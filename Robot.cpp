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
	std::vector<double> coord;

	IMAQdxStartAcquisition(session);

	while(IsOperatorControl() && IsEnabled()){
		CaptureImage();

		if(o_Joystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)){
				coord = table->GetNumberArray("BLOBS", std::vector<double>());

				if(!coord.empty()){
					while(true){
						CaptureImage();

						if(coord[0] < (RES_X / 2) - CENTERED_THRESHOLD){
							o_Drive->SetMotors(-SPEED_TURN, SPEED_TURN);
						}else if(coord[0] > (RES_X / 2) + CENTERED_THRESHOLD){
							o_Drive->SetMotors(SPEED_TURN, -SPEED_TURN);
						}else{
							o_Drive->StopMotors();
							break;
						}

						if(o_Joystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET_ESTOP))
							break;

						Wait(CYCLE_TIME_DELAY);
					}

					while(true){
						CaptureImage();

						if(coord[1] < (RES_Y / 2) - CENTERED_THRESHOLD){
							o_Drive->SetMotors(SPEED_STRAIGHT, SPEED_STRAIGHT);
						}else if(coord[1] > (RES_Y / 2) + CENTERED_THRESHOLD){
							o_Drive->SetMotors(-SPEED_STRAIGHT, -SPEED_STRAIGHT);
						}else{
							o_Drive->StopMotors();
							break;
						}

						if(o_Joystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET_ESTOP))
							break;

						Wait(CYCLE_TIME_DELAY);
					}
				}else{
					o_Drive->StopMotors();
				}
		}else{
			speed_left = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speed_right = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);

			o_Drive->SetMotors(speed_left, speed_right);
		}

		Wait(CYCLE_TIME_DELAY);
	}

	IMAQdxStopAcquisition(session);
}


void Robot::CaptureImage(void){
	IMAQdxGrab(session, frame, true, NULL);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
	}else{
		CameraServer::GetInstance()->SetImage(frame);
	}
}


START_ROBOT_CLASS(Robot);
