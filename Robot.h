#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED


#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Config.h"
#include "Drive.h"


class Robot: public SampleRobot{
public:
	Robot(void);
	~Robot(void);

	void RobotInit(void);
	void Test(void);
	void Autonomous(void);
	void OperatorControl(void);

private:
	void CaptureImage(void);

	Joystick* o_Joystick;
	Drive* o_Drive;

	IMAQdxSession session;
	IMAQdxError imaqError;
	Image *frame;

	NetworkTable* table;
};


#endif /* ROBOT_H__INCLUDED */
