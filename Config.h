#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


// Ports
const int PORT_JOYSTICK = 0; // Joysticks (found in Driver Station)

const int PORT_DRIVE_TALON_FRONTLEFT = 0; // Talons
const int PORT_DRIVE_TALON_FRONTRIGHT = 0;
const int PORT_DRIVE_TALON_BACKLEFT = 0;
const int PORT_DRIVE_TALON_BACKRIGHT = 0;
const int PORT_INTAKE_TALON = 0;
const int PORT_LAUNCH_TALON = 0;

const int PORT_INTAKE_SOLENOID_1 = 0; // Solenoids
const int PORT_INTAKE_SOLENOID_2 = 0;

const int PORT_LAUNCH_LIMIT_SWITCH = 0; // Limit Switches
const int PORT_INTAKE_LIMIT_SWITCH = 0;


// Motor Reversal
const bool DRIVE_MOTOR_FRONTLEFT_REVERSED = false; // Drive Train
const bool DRIVE_MOTOR_FRONTRIGHT_REVERSED = false;
const bool DRIVE_MOTOR_BACKLEFT_REVERSED = false;
const bool DRIVE_MOTOR_BACKRIGHT_REVERSED = false;

const bool INTAKE_MOTOR_REVERSED = false; // Catapult
const bool LAUNCH_MOTOR_REVERSED = true;


// Joystick Setup
const int JOYSTICK_AXIS_LEFT = 1; // Axes
const int JOYSTICK_AXIS_RIGHT = 3;

const int JOYSTICK_BUTTON_REVERSE = 4; // Buttons
const int JOYSTICK_BUTTON_LOCK_TURNING = 6;
const int JOYSTICK_BUTTON_TRACK_TARGET = 5;
const int JOYSTICK_BUTTON_FIRE_BOULDER = 3;
const int JOYSTICK_BUTTON_INTAKE_DOWN = 2;
const int JOYSTICK_BUTTON_INTAKE_UP = 1;


// Catapult
const float INTAKE_MOTOR_SPEED = 0.5; // Speed to run intake motor when intaking boulders
const float LAUNCH_MOTOR_SPEED = 1; // Speed to run the launcher motor when charging
const float RELEASE_TIME_DELAY = 2; // Time to wait when releasing the launch after the limit switch is triggered to be sure the launch is released


// Camera Settings
const char CAMERA_NAME[] = "cam0\0"; // Found in RoboRio web interface
const int CAMERA_RES_X = 640;
const int CAMERA_RES_Y = 480;
const int CAMERA_FPS = 10;
const unsigned int CAMERA_EXPOSURE = 20; // 0-100


// Target Tracking
const int TARGET_X = 320; // Target x coordinate
const int TARGET_Y = 240; // Target y coordinate
const float CENTERED_THRESHOLD = 0.08; // Threshold for considering the target centered (CENTERED_THRESHOLD * RES_X/RES_Y = pixels target can be off)
const double MIN_SPEED_TURN = 0.25; // Minimum turning speed
const double MIN_SPEED_LINEAR = 0.25; // Minimum linear speed


// Other
const float CYCLE_TIME_DELAY = 0.02; // Time to wait between each update cycle in tele-op (to prevent needless CPU usage)


#endif /* CONFIG_H__INCLUDED */
