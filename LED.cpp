#include "LED.h"
#include "Config.h"


LED::LED(void){
	oRed = new Relay(PORT_RELAY_RED);
	oGreen = new Relay(PORT_RELAY_GREEN);
	oBlue = new Relay(PORT_RELAY_BLUE);
}


LED::~LED(void){
	delete oRed;
	delete oGreen;
	delete oBlue;
}


void LED::ChangeColor(Color color){
	switch(color){
		case Red:
			oRed->Set(Relay::kOn);
			oGreen->Set(Relay::kOff);
			oBlue->Set(Relay::kOff);
			break;

		case Green:
			oRed->Set(Relay::kOff);
			oGreen->Set(Relay::kOn);
			oBlue->Set(Relay::kOff);
			break;

		case Blue:
			oRed->Set(Relay::kOff);
			oGreen->Set(Relay::kOff);
			oBlue->Set(Relay::kOn);
			break;

		case Purple:
			oRed->Set(Relay::kOn);
			oGreen->Set(Relay::kOff);
			oBlue->Set(Relay::kOn);
			break;

		case Aqua:
			oRed->Set(Relay::kOff);
			oGreen->Set(Relay::kOn);
			oBlue->Set(Relay::kOn);
			break;

		case Yellow:
			oRed->Set(Relay::kOn);
			oGreen->Set(Relay::kOn);
			oBlue->Set(Relay::kOff);
			break;

		case White:
			oRed->Set(Relay::kOn);
			oGreen->Set(Relay::kOn);
			oBlue->Set(Relay::kOn);
			break;

		case Off:
		default:
			oRed->Set(Relay::kOff);
			oGreen->Set(Relay::kOff);
			oBlue->Set(Relay::kOff);
			break;
	}
}
