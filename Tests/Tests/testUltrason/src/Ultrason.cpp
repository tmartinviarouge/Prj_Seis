#include <wiringPi.h>
#include <iostream>
#include </home/pi/Desktop/ULTRASON/defs/Ultrason.h>
#include <unistd.h>		//librairie pour utiliser la fonction usleep()
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>


using namespace std;



	Ultrason::Ultrason( ) {  }
	Ultrason::~Ultrason( ) {  }


//CODE DE LA METHODE faireUneMesure()

//Méthode qui consiste à lancer une mesure. Cette méthode consiste à afficher la distance à laquelle on se trouve par rapport au sol//

float Ultrason::faireUneMesure()
{
		wiringPiSetup();
	
	int GPIOtrigger;
	int GPIOecho;
	GPIOtrigger = RPI2plus::WP_GPIO_4;
	GPIOecho = RPI2plus::WP_GPIO_5;
	pinMode(GPIOtrigger,OUTPUT);	//On définit le trigger comme sortie
	pinMode(GPIOecho,INPUT);	//On défint l'echo comme entrée

	//cout<<"Nombre de mesures ="<<endl;
	//cin>>compteur;

	
	
	for (int i =0; i<NB_MESURES_PAR_RAFALES; i++){


		//Allow module to settle
		usleep(500000);

		struct timeval depart;
		struct timeval actuel;
		float ecart_us;		//modifie int en float
	
		digitalWrite (GPIOtrigger, HIGH) ;	//On met le trigger à l'état haut
		usleep(DUREE_IMPULTION_TRIGGER);	//Le trigger envoi son impulsion de 10us
		digitalWrite (GPIOtrigger, LOW) ;	//Le trigger repasse à l'état bas

	
	
		while(digitalRead (GPIOecho) == LOW){	//Tant que l'echo est bas on suspend le programme
		
			gettimeofday(&depart, NULL);
			//cout<<TEMPS_DESCENTE_PIED_DIXIEME_DE_MM_MAX<<endl;
		 	//usleep(TEMPS_DESCENTE_PIED_DIXIEME_DE_MM_MAX);
		
		}
	
		//gettimeofday(&depart, NULL);		//On releve le temps de départ
	
		while(digitalRead (GPIOecho) == HIGH){	//On attend l'echo quitte l'etat haut
			//usleep(TEMPS_DESCENTE_PIED_DIXIEME_DE_MM_MAX);
			gettimeofday(&actuel, NULL);
		}
	

		//gettimeofday(&actuel, NULL);		//On releve le temps d'arrivée
		ecart_us = actuel.tv_usec - depart.tv_usec;
		ecart_us = ecart_us/1000000;		//temps d'aller retour en sec
		//if(ecart_us<0){
			//ecart_us = 100000 + ecart_us;		//modifié 1 000 000 à 100 000
		//};
	

	
	float distanceSol = ecart_us*VITESSE_SON_ALLER_RETOUR; // dixieme de millimetre
	
	
		cout<<"Détection du sol : "<<distanceSol<<" " <<"cm"<<endl;
	
		
		usleep(1000000);
	}
	return 0;
	
}


//====================================================================================================//
	
	// TEST CODAGE DE LA METHODE determinerDistance()//

// Methode qui fait une moyenne des mesures relevées. Cette moyenne supprime les deux valeurs extrèmes et fait une moyenne des mesures restantes//

float Ultrason::determinerDistance(){
	
	float moyenne = 0;
	float min;
	float max=0;
	float mesure;
	float resultat;
	
	for(int i =0; i< NB_MESURES_PAR_RAFALES; i++)
	{
		
		mesure = faireUneMesure();
		cout<<"i ="<<i<<endl;
		if(i=1)
		{
			
			min=mesure;
		}
		else
		{
			
			if(mesure<min)
			{
				min=mesure;
				
			 }	
		}
	//}
		if(mesure>max){
			
			max=mesure;
		}
	//}
		
		moyenne=moyenne+mesure;
	}

		
		cout<<"Moyenne="<<moyenne<<endl;
		resultat = (moyenne-(min+max))/ (NB_MESURES_PAR_RAFALES-2);
		return resultat;

}

