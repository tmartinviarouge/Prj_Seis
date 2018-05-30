#include "../defs/gestionnaireAlarme.h"
#include "../defs/Buzzer.h"
#include "../defs/GPIOSEIS.h"
#include "../defs/MPU6050.h"
#include <iostream>

using namespace std;

gestionnaireAlarme uneAlarme;
Buzzer buzz;

void *alarmeTempAccel(void*)
{
	uneAlarme.alarmeTempAccel();
}


int main(){

if (pthread_create (&alarmeTempAccel, NULL, alarmeTempAccel, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'alarme température'"<<endl;
		exit (1);
	};

//int temperature = unAccelerometre.MesurerTemp();


/*while(1) {
cout << temperature << endl;
usleep(500000);
}

*/
}

}


//}










