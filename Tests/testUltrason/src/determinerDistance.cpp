#include <wiringPi.h>
#include <iostream>
#include </home/pi/Desktop/ULTRASON/defs/Ultrason.h>
#include <unistd.h>		//librairie pour utiliser la fonction usleep()
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

Ultrason::Ultrason(){
}

float Ultrason::determinerDistance(){
	
	float moyenne = 0;
	float min;
	float max=0;
	float mesure;
	float resultat;
	
	for(int i =0; i< NB_MESURES_PAR_RAFALES; i++)
	{
		mesure = faireUneMesure();
		if(i=0)
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
		resultat = (moyenne-(min+max))/ (NB_MESURES_PAR_RAFALES-2);
		return resultat;

}
