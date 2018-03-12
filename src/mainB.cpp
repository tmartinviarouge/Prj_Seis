#include "../defs/gestionnaireAlarme.h"
#include "../defs/Buzzer.h"
#include "../defs/GPIOSEIS.h"
#include "../defs/MPU6050.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std;

gestionnaireAlarme uneAlarme;
Buzzer buzz;
Mpu6050 mpu;

void *alarmeTempAccel(void*)
{
	uneAlarme.alarmeTempAccel();
}


int main(){

int temp;

pthread_t thalarmeTempAccel;
if (pthread_create (&thalarmeTempAccel, NULL, alarmeTempAccel, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'alarme température'"<<endl;
		exit (1);
	};

//int temperature = unAccelerometre.MesurerTemp();


while(1) {
temp = mpu.MesurerTemp();
cout << temp << endl;
usleep(500000);
}


}













