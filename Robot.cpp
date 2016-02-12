#include <algorithm> // For std::max
#include "Robot.h"
#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Config.h"
#include "Drive.h"


Robot::Robot(void){
	o_Joystick = new Joystick(JOYSTICK_PORT);
	o_Drive = new Drive();

	o_USBCamera = new USBCamera(CAMERA_NAME, true);
	o_Image = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	table = &*NetworkTable::GetTable("datatable"); // GetTable returns a shared pointer, so referencing and dereferencing converts it to a raw pointer
}


Robot::~Robot(void){
	delete o_Joystick;
	delete o_Drive;
	delete o_USBCamera;
}


void Robot::RobotInit(void){
	// Camera settings
	o_USBCamera->SetFPS(CAMERA_FPS);
	o_USBCamera->SetSize(CAMERA_RES_X, CAMERA_RES_Y);
	o_USBCamera->SetExposureManual(CAMERA_EXPOSURE);
	o_USBCamera->UpdateSettings();
}


// Use test mode for testing individual motors and pistons
void Robot::Test(void){
	while(IsTest() && IsEnabled()){ // Loop while still in test mode
		if(o_Joystick->GetRawButton(TEST_JOYSTICK_BUTTON_FRONTLEFT))       // Front left drive motor
			o_Drive->SetMotors(TEST_SPEED, 0, 0, 0);
		else if(o_Joystick->GetRawButton(TEST_JOYSTICK_BUTTON_FRONTRIGHT)) // Front right drive motor
			o_Drive->SetMotors(0, TEST_SPEED, 0, 0);
		else if(o_Joystick->GetRawButton(TEST_JOYSTICK_BUTTON_BACKLEFT))   // Back left drive motor
			o_Drive->SetMotors(0, 0, TEST_SPEED, 0);
		else if(o_Joystick->GetRawButton(TEST_JOYSTICK_BUTTON_BACKRIGHT))  // Back right drive motor
			o_Drive->SetMotors(0, 0, 0, TEST_SPEED);
		else
			o_Drive->StopMotors();
	}

	o_Drive->StopMotors();
}


void Robot::Autonomous(void){
	// Autonomous code
}


void Robot::OperatorControl(void){
	float speed_left, speed_right;       // Drive motor speeds for manual control
	float speed_turn, speed_linear;      // Drive motor speeds for auto target tracking
	bool reverse = false;                // Keeps track of robot being in reverse mode
	bool reverse_button_pressed = false; // Needed for toggling reverse mode
	std::vector<double> coord;           // Target coordinates sent from RoboRealm

	// Start camera
	o_USBCamera->OpenCamera();
	o_USBCamera->StartCapture();

	// Continue updating robot while in tele-op mode
	while(IsOperatorControl() && IsEnabled()){

		// Get image and send to camera server
		o_USBCamera->GetImage(o_Image);
		CameraServer::GetInstance()->SetImage(o_Image);

		// Autonomous target tracking
		if(o_Joystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)){

			// Get targets coordinates from the network table (return empty vector if network table is unreachable)
			coord = table->GetNumberArray("BLOBS", std::vector<double>());

			// Calculate motor speeds
			speed_turn = std::max(fabs((TARGET_X - coord[0]) / CAMERA_RES_X), MIN_SPEED_TURN);
			speed_linear = std::max(fabs((TARGET_Y - coord[1]) / CAMERA_RES_Y), MIN_SPEED_LINEAR);

			// Make sure the network table returned values
			if(!coord.empty()){

				// First correct robot orientation (x axis on image)...
				if(coord[0] < TARGET_X - (CENTERED_THRESHOLD * CAMERA_RES_X))
					o_Drive->SetMotors(-speed_turn, speed_turn);
				else if(coord[0] > TARGET_X + (CENTERED_THRESHOLD * CAMERA_RES_X))
					o_Drive->SetMotors(speed_turn, -speed_turn);
				else{

					// ...then correct robot distance to target (y axis on image)
					if(coord[1] < TARGET_Y - (CENTERED_THRESHOLD * CAMERA_RES_Y))
						o_Drive->SetMotors(speed_linear, speed_linear);
					else if(coord[1] > TARGET_Y + (CENTERED_THRESHOLD * CAMERA_RES_Y))
						o_Drive->SetMotors(-speed_linear, -speed_linear);
					else
						o_Drive->StopMotors();
						// LAUNCH BOULDER
				}
			}

			// If the network table did not return values, stop drive motors
			else{
				o_Drive->StopMotors();
			}
		}

		// Manual driver control
		else{
			// Get joystick values (negated because the stupid driver station reads them that way)
			speed_left = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speed_right = -o_Joystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);

			// Reverse mode toggling
			ToggleBool(o_Joystick->GetRawButton(JOYSTICK_BUTTON_REVERSE), reverse_button_pressed, reverse);

			// Set drive motors
			if((speed_left < 0 && speed_right < 0) || (speed_left > 0 && speed_right > 0)) // Turn off front motors if robot is doing a point turn
				reverse ? o_Drive->SetMotors(-speed_right, -speed_left) : o_Drive->SetMotors(speed_left, speed_right);
			else
				reverse ? o_Drive->SetMotors(0, 0, -speed_right, -speed_left) : o_Drive->SetMotors(0, 0, speed_left, speed_right);
		}

		// Wait until next cycle (to prevent needless CPU usage)
		Wait(CYCLE_TIME_DELAY);
	}

	o_Drive->StopMotors();

	// Stop camera
	o_USBCamera->StopCapture();
	o_USBCamera->CloseCamera();
}


/*
This function allows a boolean to be toggled with a joystick button, inside of a while loop that is constantly updating.
	button:         Joystick button for toggling.
	button_pressed: Boolean for tracking whether the button was pressed in the last cycle. This prevents toggle_bool from rapidly switching states while the joystick button is held down.
	toggle_bool:    Boolean to be toggled.
*/
void Robot::ToggleBool(bool button, bool &button_pressed, bool &toggle_bool){
	if(button && !button_pressed){
		button_pressed = true;
		toggle_bool ? toggle_bool = false : toggle_bool = true;
	}else if(!button)
		button_pressed = false;
}


START_ROBOT_CLASS(Robot);
