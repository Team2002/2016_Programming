#include <algorithm> // For std::max
#include "Robot.h"
#include "Config.h"


Robot::Robot(void){
	oJoystick = new Joystick(PORT_JOYSTICK);
	oCompressor = new Compressor();
	oPDP = new PowerDistributionPanel();
	oLED = new LED();
	oDrive = new Drive();
	oCatapult = new Catapult();
	oLift = new Lift();

	oUSBCamera = new USBCamera(CAMERA_NAME, true);
	oImage = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	oNetworkTable = &*NetworkTable::GetTable("datatable"); // GetTable returns a shared pointer, so referencing and dereferencing converts it to a raw pointer
}


Robot::~Robot(void){
	delete oJoystick;
	delete oCompressor;
	delete oPDP;
	delete oLED;
	delete oDrive;
	delete oCatapult;
	delete oLift;

	delete oUSBCamera;
}


void Robot::RobotInit(void){
	// Start the air compressor
	oCompressor->Start();

	// Turn on the LEDs based on what alliance we are on
	switch(DriverStation::GetInstance().GetAlliance()){
		case DriverStation::kRed:
			oLED->ChangeColor(LED::Red);
			break;

		case DriverStation::kBlue:
			oLED->ChangeColor(LED::Blue);
			break;

		case DriverStation::kInvalid:
		default:
			oLED->ChangeColor(LED::White);
			break;
	}

	// Camera settings
	oUSBCamera->SetFPS(CAMERA_FPS);
	oUSBCamera->SetSize(CAMERA_RES_X, CAMERA_RES_Y);
	oUSBCamera->SetExposureManual(CAMERA_EXPOSURE);
	oUSBCamera->UpdateSettings();

	// Initialize smart dashboard keys
	SmartDashboard::PutNumber("VOLTAGE", 0);
	SmartDashboard::PutNumber("TEMPERATURE", 0);
	SmartDashboard::PutNumber("LEFT DRIVE SPEED", 0);
	SmartDashboard::PutNumber("RIGHT DRIVE SPEED", 0);
	SmartDashboard::PutBoolean(" REVERSE", false);
}


void Robot::Autonomous(void){
	// Autonomous code
}


void Robot::OperatorControl(void){
	float speedLeft, speedRight;       // Drive motor speeds for manual control
	float speedTurn, speedLinear;      // Drive motor speeds for auto target tracking
	bool reverse = false;              // Keeps track of robot being in reverse mode
	bool reverseButtonPressed = false; // Needed for toggling reverse mode
	float speedLeftTemp;               // Temporarily used for reversing drive motor speeds
	std::vector<double> coord;         // Target coordinates sent from RoboRealm

	// Start camera
	oUSBCamera->StartCapture();

	// Continue updating robot while in tele-op mode
	while(IsOperatorControl() && IsEnabled()){

		// Get image and send to camera server
		oUSBCamera->GetImage(oImage);
		CameraServer::GetInstance()->SetImage(oImage);

		// Autonomous target tracking
		if(oJoystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)){

			// Get targets coordinates from the network table (return empty vector if network table is unreachable)
			coord = oNetworkTable->GetNumberArray("BLOBS", std::vector<double>());

			// Make sure the network table returned values
			if(!coord.empty()){

				// Calculate motor speeds. The math makes the speed get slower as the robot approaches the target.
				speedTurn = std::max(fabs((TARGET_X - coord[0]) / CAMERA_RES_X), MIN_SPEED_TURN);
				speedLinear = std::max(fabs((TARGET_Y - coord[1]) / CAMERA_RES_Y), MIN_SPEED_LINEAR);

				// First correct robot orientation (x axis on image)...
				if(coord[0] < TARGET_X - (CENTERED_THRESHOLD * CAMERA_RES_X))
					oDrive->SetMotors(-speedTurn, speedTurn);
				else if(coord[0] > TARGET_X + (CENTERED_THRESHOLD * CAMERA_RES_X))
					oDrive->SetMotors(speedTurn, -speedTurn);
				else{

					// ...then correct robot distance to target (y axis on image)
					if(coord[1] < TARGET_Y - (CENTERED_THRESHOLD * CAMERA_RES_Y))
						oDrive->SetMotors(speedLinear, speedLinear);
					else if(coord[1] > TARGET_Y + (CENTERED_THRESHOLD * CAMERA_RES_Y))
						oDrive->SetMotors(-speedLinear, -speedLinear);
					else{

						// Target is centered, stop motors and fire boulder
						oDrive->StopMotors();
						oCatapult->SetLaunchState(Catapult::FIRE);
					}
				}
			}

			// If the network table did not return values, stop drive motors
			else{
				oDrive->StopMotors();
			}
		}

		// Manual driver control
		else{

			// Get joystick values (negated because the stupid driver station reads them that way)
			speedLeft = -oJoystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speedRight = -oJoystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);

			// Reverse mode toggling
			ToggleBool(oJoystick->GetRawButton(JOYSTICK_BUTTON_REVERSE), reverseButtonPressed, reverse);
			if(reverse){
				speedLeftTemp = speedLeft;
				speedLeft = -speedRight;
				speedRight = -speedLeftTemp;
			}

			// Turn locking. Forces all motors to go the same speed.
			if(oJoystick->GetPOV(JOYSTICK_POV_LOCK_TURNING))
				speedLeft = speedRight;

			// Set drive motors
			oDrive->SetMotors(speedLeft, speedRight);

			// Boulder intake
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_INTAKE_DOWN))
				oCatapult->SetIntakeState(Catapult::DOWN);
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_INTAKE_UP))
				oCatapult->SetIntakeState(Catapult::UP);

			// Fire boulder
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FIRE_BOULDER) && oJoystick->GetPOV(JOYSTICK_POV_FIRE_BOULDER_SAFETY))
				oCatapult->SetLaunchState(Catapult::FIRE);
		}

		// Check if the catapult needs to do anything
		oCatapult->CheckCatapult();

		// Set smart dashboard keys
		SmartDashboard::PutNumber("VOLTAGE", oPDP->GetVoltage());
		SmartDashboard::PutNumber("TEMPERATURE", oPDP->GetTemperature());
		SmartDashboard::PutNumber("LEFT DRIVE SPEED", speedLeft);
		SmartDashboard::PutNumber("RIGHT DRIVE SPEED", speedRight);
		SmartDashboard::PutBoolean(" REVERSE", reverse);

		// Wait until next cycle (to prevent needless CPU usage)
		Wait(CYCLE_TIME_DELAY);
	}

	// Reset smart dashboard keys
	SmartDashboard::PutNumber("VOLTAGE", 0);
	SmartDashboard::PutNumber("TEMPERATURE", 0);
	SmartDashboard::PutNumber("LEFT DRIVE SPEED", 0);
	SmartDashboard::PutNumber("RIGHT DRIVE SPEED", 0);
	SmartDashboard::PutBoolean(" REVERSE", false);

	// Stop drive motors
	oDrive->StopMotors();

	// Stop camera
	oUSBCamera->StopCapture();

	// Turn off the LEDs
	oLED->ChangeColor(LED::Off);
}


/*
This function allows a boolean to be toggled with a joystick button, inside of a while loop that is constantly updating.
	button:        Joystick button for toggling.
	buttonPressed: Boolean for tracking whether the button was pressed in the last cycle. This prevents toggleBool from rapidly switching states while the joystick button is held down.
	toggleBool:    Boolean to be toggled.
*/
void Robot::ToggleBool(bool button, bool &buttonPressed, bool &toggleBool){
	if(button && !buttonPressed){
		buttonPressed = true;
		toggleBool ? toggleBool = false : toggleBool = true;
	}else if(!button)
		buttonPressed = false;
}


START_ROBOT_CLASS(Robot);
