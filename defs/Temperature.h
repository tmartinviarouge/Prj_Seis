#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>


#define CONFIGURATION_REGISTER                      0x01    
#define AMBIENT_TEMPERATURE_REGISTER      0x00    
#define TCN75A_I2C_ADDRESS                               0x49

	using namespace std; 

class Temperature
{
 
public :
	// Constructeur 
	Temperature();
	// Destructeur
	~Temperature(); 


	// Méthodes 
	int MesureTempEnDixieme();
	int init(); 
	char recupMesure();
	

private:

int fd; 
int adresseI2C;

};

#endif
