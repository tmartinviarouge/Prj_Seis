#include <wiringPi.h>
#include <iostream>
#include </home/pi/Desktop/ULTRASON/defs/Ultrason.h>
#include <unistd.h>		//librairie pour utiliser la fonction usleep()
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>


Ultrason::Ultrason(){
}

float Ultrason::faireUneMesure()
	{
		wiringPiSetup();
		
		int GPIOtrigger;
		int GPIOecho;
		GPIOtrigger = RPI2plus::WP_GPIO_4;
		GPIOecho = RPI2plus::WP_GPIO_5;
		pinMode(GPIOtrigger,OUTPUT);	//On définit le trigger comme sortie
		pinMode(GPIOecho,INPUT);	//On défint l'echo comme entrée

		
			//Allow module to settle
			usleep(500000);

			struct timeval depart;
			struct timeval actuel;
			float ecart_us;		//modifie int en float//
	
			digitalWrite (GPIOtrigger, HIGH) ;	//On met le trigger à l'état haut//
			usleep(DUREE_IMPULTION_TRIGGER);	//Le trigger envoi son impulsion de 10us//
			digitalWrite (GPIOtrigger, LOW) ;	//Le trigger repasse à l'état bas//

	
			while(digitalRead (GPIOecho) == LOW){	//Tant que l'echo est bas on suspend le programme
		
				gettimeofday(&depart, NULL);
				
			}
	
			while(digitalRead (GPIOecho) == HIGH){	//On attend l'echo quitte l'etat haut
				
				gettimeofday(&actuel, NULL);
			}
	

			ecart_us = actuel.tv_usec - depart.tv_usec;
			ecart_us = ecart_us/1000000;		//temps d'aller retour en sec
		
		float distanceSol = ecart_us*VITESSE_SON_ALLER_RETOUR; // dixieme de millimetre
	
		cout<<"Détection du sol : "<<distanceSol<<" " <<"cm"<<endl;
		usleep(1000000);
		
		return 0;
	
	}
