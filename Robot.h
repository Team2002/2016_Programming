#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED


#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Drive.h"
#include "Catapult.h"
#include "Lift.h"
#include "LED.h"


class Robot: public SampleRobot{
public:
	Robot(void);
	~Robot(void);

	void RobotInit(void);
	void Autonomous(void);
	void OperatorControl(void);

private:
	void ToggleBool(bool, bool&, bool&);

	Joystick* oJoystick; // Appending "o" to avoid naming conflicts ("o" for object)
	Compressor* oCompressor;
	PowerDistributionPanel* oPDP;
	LED* oLED;
	Drive* oDrive;
	Catapult* oCatapult;
	Lift* oLift;

	// For vision tracking
	USBCamera *oUSBCamera;
	Image *oImage;
	NetworkTable* oNetworkTable;

};


#endif /* ROBOT_H__INCLUDED */
