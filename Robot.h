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

	NetworkTable table;

	IMAQdxSession session;
	IMAQdxError imaqError;
	Image *frame;
};


#endif /* ROBOT_H__INCLUDED */
