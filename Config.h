#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


// Drive.h / Drive.cpp constants
const int TALON_PORT_FRONTLEFT = 9;            // Motor controller ports
const int TALON_PORT_FRONTRIGHT = 8;
const int TALON_PORT_BACKLEFT = 4;
const int TALON_PORT_BACKRIGHT = 3;

const bool TALON_REVERSED_FRONTLEFT = false;   // If true, that motor will be reversed
const bool TALON_REVERSED_FRONTRIGHT = true;
const bool TALON_REVERSED_BACKLEFT = false;
const bool TALON_REVERSED_BACKRIGHT = true;


// Robot.h / Robot.cpp constants
const float CYCLE_TIME_DELAY = 0.02;           // Time to wait between each update cycle in tele-op (to prevent needless CPU usage)

const int JOYSTICK_PORT = 0;                   // Joystick port (found in driver station)
const int JOYSTICK_AXIS_LEFT = 1;              // Joystick axis for controlling left motor speed
const int JOYSTICK_AXIS_RIGHT = 3;             // Joystick axis for controlling right motor speed
const int JOYSTICK_BUTTON_REVERSE = 4;         // Joystick button for tracking target
const int JOYSTICK_BUTTON_LOCK_TURNING = 7;    // Joystick button locking left and right drive motor speeds
const int JOYSTICK_BUTTON_TRACK_TARGET = 8;    // Joystick button for tracking target

const char CAMERA_NAME[] = "cam0\0";           // Camera name (found in RoboRio web interface)
const int CAMERA_RES_X = 640;                  // Camera x resolution
const int CAMERA_RES_Y = 480;                  // Camera y resolution
const int CAMERA_FPS = 10;                     // Camera FPS
const unsigned int CAMERA_EXPOSURE = 20;       // Camera exposure (0-100)

const int TARGET_X = 320;                      // Target x coordinate
const int TARGET_Y = 240;                      // Target y coordinate
const float CENTERED_THRESHOLD = 0.08;         // Threshold for considering the target centered (CENTERED_THRESHOLD * RES_X/RES_Y = pixels target can be off)
const double MIN_SPEED_TURN = 0.25;            // Minimum turning speed
const double MIN_SPEED_LINEAR = 0.25;          // Minimum linear speed

const float TEST_SPEED = 0.25;                 // Drive motor speed when testing
const int TEST_JOYSTICK_BUTTON_FRONTLEFT = 1;  // Joystick buttons for testing drive motors
const int TEST_JOYSTICK_BUTTON_FRONTRIGHT = 4;
const int TEST_JOYSTICK_BUTTON_BACKLEFT = 2;
const int TEST_JOYSTICK_BUTTON_BACKRIGHT = 3;


#endif /* CONFIG_H__INCLUDED */
