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
	void ToggleBool(bool, bool&, bool&);

	Joystick* o_Joystick;
	Drive* o_Drive;

	// For vision tracking
	USBCamera *o_USBCamera;
	Image *o_Image;
	NetworkTable* table;
};


#endif /* ROBOT_H__INCLUDED */
