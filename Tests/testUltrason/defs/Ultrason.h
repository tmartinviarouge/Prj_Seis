#ifndef Ultrason_H
#define Ultrason_H
#ifndef WIRINGPI
#include <wiringPi.h>
#include <iostream>
#include <stdint.h>
#include "PiedSeis.h"
#include "Seis.h"
#include "rPi2_rPi+.h"
#endif
#define NB_MESURES_PAR_RAFALES	10	// émission de 5 rafales


using namespace std;


class Ultrason
{

public :

	//Constructeur
	Ultrason();
	//Destructeur
	~Ultrason();


	//Méthode publique
	float determinerDistance();
	float faireUneMesure();

private : 

	//Attributs privés
	
	int BrocheTriger;
	int BrocheEcho;
	
	
	//Méthode privée
	
	//float faireUneMesure();

protected : 

};
#endif
