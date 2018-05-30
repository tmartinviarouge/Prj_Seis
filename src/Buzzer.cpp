#include "../defs/Buzzer.h"
#include "../defs/GPIOSEIS.h"


Buzzer::Buzzer(){
	wiringPiSetup();	
}

Buzzer::~Buzzer(){
}

void Buzzer::beeper(){
	pinMode(BROCHE_GPIO_BUZZER, OUTPUT);
	digitalWrite(BROCHE_GPIO_BUZZER, HIGH);
}

void Buzzer::arretBeep()
{
	pinMode(BROCHE_GPIO_BUZZER, OUTPUT);
	digitalWrite(BROCHE_GPIO_BUZZER, LOW);
}

