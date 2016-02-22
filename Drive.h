#ifndef DRIVE_H__INCLUDED
#define DRIVE_H__INCLUDED


#include "WPILib.h"


class Drive{
public:
	Drive(void);
	~Drive(void);
	
	void SetMotors(float, float);
	void StopMotors(void);
	
private:
	Talon *oFrontLeft, *oFrontRight, *oBackLeft, *oBackRight;
};


#endif /* DRIVE_H__INCLUDED */
