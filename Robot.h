#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED


#include "WPILib.h"
#include "Config.h"
#include "Drive.h"


class Robot: public SampleRobot{
public:
	Robot(void);
	~Robot(void);

	void RobotInit(void);
	void Autonomous(void);
	void OperatorControl(void);
	
private:
	Joystick* o_Joystick;
	Drive* o_Drive;
};


#endif /* ROBOT_H__INCLUDED */
