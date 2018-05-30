#include "../../defs/MPU6050.h"
#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../../defs/Seis.h"
#include <pthread.h>



	using namespace std;

Seis monSeis;

void  *EnvoiTramVibration(void*) {
	monSeis.EnvoyerTramVibrations();
}

void *demandeMesures(void*) {
	monSeis.MesuresDemandees();
}

int main()
{
	pthread_t trameSend;
	pthread_t demMes;*/
	MPU6050 *mp= new MPU6050();
	mp->init_I2C();
	if (pthread_create(&trameSend, NULL, EnvoiTramVibration, NULL)< 0)
	{
		cerr<<"Impossible d'envoyer la trame de vibration"<<endl;
		exit(1);
	}
	if (pthread_create(&demMes, NULL, demandeMesures, NULL)< 0)
	{
		cerr<<"Erreur lors de la mesure"<<endl;
		exit(1);
	}
	short AX,AY,AZ;
	mp->MesurerAccel(AX, AY, AZ);
	cout <<  "Accelerometre"<< " "  <<endl;
	cout << " AX = "<< AX <<endl;  
	cout << " AY = "<< AY <<endl;  
	cout << " AZ = "<< AZ <<endl; 
  
	short GX,GY,GZ;
	mp->MesurerGyro(GX, GY, GZ);
	cout <<  "Gyroscope"<<" "<<endl;
	cout << " GX = "<< GX <<endl;
	cout << " GY = "<< GY <<endl;	
	cout << " GZ = "<< GZ <<endl;
	
	
	mp->MesurerTemp();
	
}
