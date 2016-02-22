#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


// Driver Station Ports
const int PORT_JOYSTICK = 0; // Joysticks

// PWM Ports
const int PORT_DRIVE_TALON_FRONTLEFT = 1; // Talons (Motor Controllers)
const int PORT_DRIVE_TALON_FRONTRIGHT = 3;
const int PORT_DRIVE_TALON_BACKLEFT = 0;
const int PORT_DRIVE_TALON_BACKRIGHT = 2;
const int PORT_LAUNCH_TALON = 5;
const int PORT_INTAKE_TALON = 4;
const int PORT_LIFT_TALON_UP = 6;
const int PORT_LIFT_TALON_DOWN = 7;

// DIO Ports
const int PORT_LAUNCH_ENCODER_1 = 2; // Encoders
const int PORT_LAUNCH_ENCODER_2 = 3;

const int PORT_LAUNCH_LIMIT_SWITCH = 0; // Limit Switches
const int PORT_INTAKE_LIMIT_SWITCH = 1;

// PCM Ports
const int PORT_INTAKE_SOLENOID_1 = 5; // Solenoids
const int PORT_INTAKE_SOLENOID_2 = 4;
const int PORT_LIFT_SOLENOID_1 = 0;
const int PORT_LIFT_SOLENOID_2 = 1;

// Relay Ports
const int PORT_RELAY_RED = 0; // Spike H-Bridge Relays (for LEDs)
const int PORT_RELAY_GREEN = 1;
const int PORT_RELAY_BLUE = 2;


// Motor Reversal
const bool DRIVE_MOTOR_FRONTLEFT_REVERSED = true; // Drive Train
const bool DRIVE_MOTOR_FRONTRIGHT_REVERSED = false;
const bool DRIVE_MOTOR_BACKLEFT_REVERSED = true;
const bool DRIVE_MOTOR_BACKRIGHT_REVERSED = false;

const bool INTAKE_MOTOR_REVERSED = true; // Catapult
const bool LAUNCH_MOTOR_REVERSED = true;


// Joystick Setup
const int JOYSTICK_AXIS_LEFT = 1; // Axes
const int JOYSTICK_AXIS_RIGHT = 3;

const int JOYSTICK_BUTTON_REVERSE = 4; // Buttons
const int JOYSTICK_BUTTON_TRACK_TARGET = 5;
const int JOYSTICK_BUTTON_FIRE_BOULDER = 3;
const int JOYSTICK_BUTTON_INTAKE_DOWN = 6;
const int JOYSTICK_BUTTON_INTAKE_UP = 1;

const int JOYSTICK_POV_LOCK_TURNING = 6; // POV
const int JOYSTICK_POV_FIRE_BOULDER_SAFETY = 2;


// Catapult
const float INTAKE_MOTOR_SPEED = 0.75; // Speed to run intake motor when intaking boulders
const float LAUNCH_MOTOR_SPEED = 1; // Speed to run the launcher motor when charging


// Camera Settings
const char CAMERA_NAME[] = "cam0\0"; // Found in RoboRio web interface
const int CAMERA_RES_X = 640;
const int CAMERA_RES_Y = 480;
const int CAMERA_FPS = 10;
const unsigned int CAMERA_EXPOSURE = 0;


// Target Tracking
const int TARGET_X = 320; // Target x coordinate
const int TARGET_Y = 240; // Target y coordinate
const float CENTERED_THRESHOLD = 0.08; // Threshold for considering the target centered (CENTERED_THRESHOLD * RES_X/RES_Y = pixels target can be off)
const double MIN_SPEED_TURN = 0.25; // Minimum turning speed
const double MIN_SPEED_LINEAR = 0.25; // Minimum linear speed


// Other
const float CYCLE_TIME_DELAY = 0.02; // Time to wait between each update cycle in tele-op (to prevent needless CPU usage)


#endif /* CONFIG_H__INCLUDED */
