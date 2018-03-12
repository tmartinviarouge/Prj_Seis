
#include "../defs/gestionnaireAlarme.h"
#include "../defs/Buzzer.h"
#include "../defs/GPIOSEIS.h"
#include "../defs/MPU6050.h"
#include <iostream>

using namespace std;

int main(){

int temperature;
Mpu6050 unAccelerometre;
unAccelerometre.init_I2C();

//int temperature = unAccelerometre.MesurerTemp();
gestionnaireAlarme uneAlarme;
Buzzer buzz;

while(1) {
temperature = unAccelerometre.MesurerTemp();
cout << temperature << endl;
usleep(500000);

if(temperature>=30){
 	buzz.beeper();
	usleep(500000);
	buzz.arretBeep();   
//uneAlarme.activerAlarme(gestionnaireAlarme::ACCELEROMETRE);
}
//cout << temperature << endl;
}


}










