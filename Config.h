#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED


const float CYCLE_TIME_DELAY = 0.020;         // Time to wait between each update cycle in Tele-op

const int JOYSTICK_PORT = 0;                  // Joystick port (found in driver station)

const int TALON_PORT_FRONTLEFT = 0;           // Motor controller ports
const int TALON_PORT_FRONTRIGHT = 1;
const int TALON_PORT_BACKLEFT = 2;
const int TALON_PORT_BACKRIGHT = 6;

const bool TALON_REVERSED_FRONTLEFT = true;   // If true, that motor will be reversed
const bool TALON_REVERSED_FRONTRIGHT = false;
const bool TALON_REVERSED_BACKLEFT = true;
const bool TALON_REVERSED_BACKRIGHT = false;

const int JOYSTICK_AXIS_LEFT = 1;             // Joystick axis for controlling left motor speed
const int JOYSTICK_AXIS_RIGHT = 3;            // Joystick axis for controlling right motor speed
const int JOYSTICK_BUTTON_TRACK_TARGET = 7;   // Joystick button for tracking target

const char CAMERA_NAME[] = "cam0\0";          // Camera name (found in RoboRio web interface)
const int RES_X = 640;                        // Camera x resolution used in RoboRealm
const int RES_Y = 480;                        // Camera y resolution used in RoboRealm
const int CENTERED_THRESHOLD = 50;            // Threshold for considering the target centered
const float SPEED_ROTATION = 0.65;             // Turning speed when centering target (on x coordinate)
const float SPEED_LINEAR = 0.2;              // Linear speed when centering target (on y coordinate)


#endif /* CONFIG_H__INCLUDED */
