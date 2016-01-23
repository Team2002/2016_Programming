#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


const float CYCLE_TIME_DELAY = 0.020;

const int JOYSTICK_PORT = 0;

const int TALON_PORT_FRONTLEFT = 0;
const int TALON_PORT_FRONTRIGHT = 1;
const int TALON_PORT_BACKLEFT = 2;
const int TALON_PORT_BACKRIGHT = 6;

const bool TALON_REVERSED_FRONTLEFT = true;
const bool TALON_REVERSED_FRONTRIGHT = false;
const bool TALON_REVERSED_BACKLEFT = true;
const bool TALON_REVERSED_BACKRIGHT = false;

const int JOYSTICK_AXIS_LEFT = 1;
const int JOYSTICK_AXIS_RIGHT = 3;
const int JOYSTICK_BUTTON_REVERSE = 7;
const int JOYSTICK_BUTTON_TRACK_TARGET = 8;

const char CAMERA_NAME[] = "cam0\0";


#endif /* CONFIG_H__INCLUDED */
