#ifndef LED_H__INCLUDED
#define LED_H__INCLUDED


#include "WPILib.h"


class LED{
public:
	LED(void);
	~LED(void);
	
	enum Color {Red, Green, Blue, Purple, Aqua, Yellow, White, Off};
	void ChangeColor(Color);
	
private:
	Relay* oRed;
	Relay* oGreen;
	Relay* oBlue;
};


#endif /* LED_H__INCLUDED */
