#include "../../defs/MPU6050.h"
#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../defs/ADS1115.h"
#include "../../defs/Pied.h"
#include "../../defs/Ultrason.h"



#define PERIODE_AFFICHAGE_POS_PIED	500000  //Durée en µs

using namespace std;

ADS1115 monCAN ;
Pied Pied1;
Mpu6050 mp;
mp.init_I2C();
Ultrason mUS = new Ultrason();


void *asserpieds1(void*)
{
	Pied1.asservissementPied();
}

void *affichagePosition(void*)
{
	while(1){
	if (Pied1.getMouvementPied() == 1 || Pied1.getMouvementPied() == -1) {
		cout <<"Position du pied = " << Pied1.getPosition() << ",      consigne = " << Pied1.getConsigne() << endl;
		usleep(PERIODE_AFFICHAGE_POS_PIED);
	}	
	};
}

	using namespace std;

int main()
{
	

    cout <<"Début du programme "<<endl;
	int cons = 0;
	pthread_t  thAsserPied1;
	pthread_t  thAffPosPied;
	monCAN.init();
	Pied1.init(NUM_PIED , &monCAN);
    if (pthread_create (&thAsserPied1, NULL, asserpieds1, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'asservissement du pied1'"<<endl;
		exit (1);
	};
	if (pthread_create (&thAffPosPied, NULL, affichagePosition, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'affichage du pied 1"<<endl;
		exit (1);
	};

}
    