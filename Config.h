#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


const float CYCLE_TIME_DELAY = 0.020;       // Time to wait between each update cycle in Tele-op

const int JOYSTICK_PORT = 0;                // Joystick port

const int TALON_PORT_FRONTLEFT = 0;         // Motor ports
const int TALON_PORT_FRONTRIGHT = 1;
const int TALON_PORT_BACKLEFT = 2;
const int TALON_PORT_BACKRIGHT = 6;

const bool TALON_REVERSED_FRONTLEFT = true; // True = motor is mounted backwards
const bool TALON_REVERSED_FRONTRIGHT = false;
const bool TALON_REVERSED_BACKLEFT = true;
const bool TALON_REVERSED_BACKRIGHT = false;

const int JOYSTICK_AXIS_LEFT = 1;           // Joystick buttons & axes
const int JOYSTICK_AXIS_RIGHT = 3;
const int JOYSTICK_BUTTON_TRACK_TARGET = 7;
const int JOYSTICK_BUTTON_TRACK_TARGET_ESTOP = 2;

const char CAMERA_NAME[] = "cam0\0";        // Camera name (found in RoboRio web interface)

const int RES_X = 640;                      // Constants for autonomous target centering
const int RES_Y = 480;
const int CENTERED_THRESHOLD = 50;
const float SPEED_TURN = 0.5;
const float SPEED_STRAIGHT = 0.2;


#endif /* CONFIG_H__INCLUDED */
