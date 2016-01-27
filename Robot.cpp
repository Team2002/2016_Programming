#include "Robot.h"
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Config.h"
#include "Drive.h"


Robot::Robot(void){
	o_Joystick = new Joystick(JOYSTICK_PORT);
	o_Drive = new Drive();

	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	IMAQdxOpenCamera(CAMERA_NAME, IMAQdxCameraControlModeController, &session);

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


void Robot::Autonomous(void){}


void Robot::OperatorControl(void){
	float speed_left, speed_right; // Drive motor speeds
	std::vector<double> coord;     // Target coordinates sent from RoboRealm

	// Start camera
	IMAQdxStartAcquisition(session);

	// Continue updating robot while in tele-op mode
	while(IsOperatorControl() && IsEnabled()){

		// Capture and process an image
		CaptureImage();

		// Autonomous target tracking
		if(o_Joystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)){

			// Get targets coordinates from the network table (return empty vector if network table fails)
			coord = table->GetNumberArray("BLOBS", std::vector<double>());

			// Make sure the network table returned values
			if(!coord.empty()){

				// First correct robot orientation (x axis on image)...
				if(coord[0] < (RES_X / 2) - CENTERED_THRESHOLD)
					o_Drive->SetMotors(-SPEED_ROTATION, SPEED_ROTATION);
				else if(coord[0] > (RES_X / 2) + CENTERED_THRESHOLD)
					o_Drive->SetMotors(SPEED_ROTATION, -SPEED_ROTATION);
				else{

					// ...then correct robot distance to target (y axis on image)
					if(coord[1] < (RES_Y / 2) - CENTERED_THRESHOLD)
						o_Drive->SetMotors(SPEED_LINEAR, SPEED_LINEAR);
					else if(coord[1] > (RES_Y / 2) + CENTERED_THRESHOLD)
						o_Drive->SetMotors(-SPEED_LINEAR, -SPEED_LINEAR);
					else
						o_Drive->StopMotors();
						// Launch boulder
				}
			}
			else
				o_Drive->StopMotors();
		}

		// Manual driver control
		else{
			speed_left = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speed_right = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);

			o_Drive->SetMotors(speed_left, speed_right);
		}

		// Wait until next cycle (to prevent needless CPU usage)
		Wait(CYCLE_TIME_DELAY);
	}

	// Stop camera
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
