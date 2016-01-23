#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


const float CYCLE_TIME_DELAY = 0.020;

const int JOYSTICK_PORT = 0;

const int TALON_PORT_FRONTLEFT = 0;
const int TALON_PORT_FRONTRIGHT = 1;
const int TALON_PORT_BACKLEFT = 6;
const int TALON_PORT_BACKRIGHT = 2;

const int JOYSTICK_AXIS_LEFT = 1;
const int JOYSTICK_AXIS_RIGHT = 3;
const int JOYSTICK_BUTTON_REVERSE = 7;

const float DRIVE_MOTOR_MULTIPLIER = 1;
const float DRIVE_MOTOR_RATIO = 1.5;

const int CAMERA_QUALITY = 50;
const char CAMERA_NAME[] = "cam0\0";


#endif /* CONFIG_H__INCLUDED */
