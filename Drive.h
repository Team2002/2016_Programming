#ifndef DRIVE_H__INCLUDED
#define DRIVE_H__INCLUDED


#include "WPILib.h"
#include "Config.h"


class Drive{
public:
	Drive(void);
	~Drive(void);
	
	void SetMotors(float, float);
	void SetMotors(float, float, float, float);
	void StopMotors(void);
	
private:
	Talon *frontLeft, *frontRight, *backLeft, *backRight;
};


#endif /* DRIVE_H__INCLUDED */
