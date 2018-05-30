#include "../defs/Pied.h"
#include <iostream>

#include <wiringPi.h>
#include <wiringPiI2C.h>


using namespace std;

//=========================================================================================================
Pied::Pied() :   ptrCAN(NULL) , initBon(false) , MouvementPied(ARRET) 
{
}


//=========================================================================================================
Pied::Pied(int numpied , ADS1115 *ptCAN) :ptrCAN(ptCAN) ,  initBon(false) , MouvementPied(ARRET) 
{
	init(numpied , ptCAN);
}


//=========================================================================================================
bool Pied::init(int numpied , ADS1115 *ptCAN)
{
	numPied=numpied;
	ptrCAN=ptCAN;
	if (ptrCAN == NULL) return false;
	wiringPiSetup();
cout<<"NumPied = " <<numPied << endl;
	switch (numpied){
	case 1:
		brocheGPIO_N = BROCHE_GPIO_CPONTH_IN2_PIEDS1 ;
		brocheGPIO_P = BROCHE_GPIO_CPONTH_IN1_PIEDS1;
		break;
	case 2:
		brocheGPIO_N = BROCHE_GPIO_CPONTH_IN2_PIEDS2 ;
		brocheGPIO_P = BROCHE_GPIO_CPONTH_IN1_PIEDS2;
		break;
	case 3:
		brocheGPIO_N = BROCHE_GPIO_CPONTH_IN2_PIEDS3 ;
		brocheGPIO_P = BROCHE_GPIO_CPONTH_IN1_PIEDS3;
		break;
	default : return false;
	};
	initBon = true;
	pinMode (brocheGPIO_N , OUTPUT);
	pinMode (brocheGPIO_P, OUTPUT);
cout<<"broche négatif = " << brocheGPIO_N << "       broche positive = "<< brocheGPIO_P <<  endl;
	return true;
}


//=========================================================================================================
Pied::~Pied()
{

}

//=========================================================================================================
int Pied::getNumPied()
{
	return numPied;
}


//=========================================================================================================
int Pied::getMouvementPied()
{
	return MouvementPied;
}


//=========================================================================================================
// méthode à lancer uniquement dans un thread à part 
bool Pied::asservissementPied()
{
	if ( ! initBon){
		cerr<<"pied non initilaisé"<<endl;
		return false;
	};
	while (1){
		if (!determinerPositionPied()) cerr << "Erreur : détermination position impossible" <<endl;
//		cout << "position = " << position <<endl;
		if (etat != ACTIF){
//			cout << "Etat non actif"<< endl;
			MouvementPied = ARRET;
			pthread_mutex_lock(&semPied);
			pthread_cond_wait(&signalNouvelleConsigne, &semPied);
			pthread_mutex_unlock(&semPied); 
//			cout <<"Asservissement activé" << endl;
		}else if ((position >= (POSITION_MAX - DELTA_POS)) && (MouvementPied == SORTANT)){	// si la position est supérieur à la position Max + la tolérance et que le pied sort
			MouvementPied=ARRET;															// on arrete le pied
			modifierEtat(EN_BUTEE_HAUTE);													// on définit l'état sur EN_BUTE_HAUTE
			pthread_cond_signal(&signalFinMouvement);										// envoie un signal 
		}else if ( (position <= DELTA_POS) && (MouvementPied == RENTRANT)){
			MouvementPied=ARRET;
			modifierEtat(EN_BUTEE_BASSE);
			pthread_cond_signal(&signalFinMouvement );
		}else if ( ((consigne + DELTA_POS) >= position) && (position >= (consigne - DELTA_POS)) ) {
			MouvementPied = ARRET;
			modifierEtat(OBJECTIF_ATTEINT);
	 		pthread_cond_signal(&signalFinMouvement);
		}else if ((consigne + DELTA_POS) <= position){
			MouvementPied=RENTRANT;
		}
		

		/*else if (tabPos[0] == tabPos[1]) {
			MouvementPied=ARRET;
			modifierEtat(ARRU);
			pthread_cond_signal(&signalFinMouvement );
		}*/
		
		else{
			MouvementPied=SORTANT;
		}
		commandeMoteur(MouvementPied);
		//tabPos[0] = position;
		usleep (PERIODE_SURVEILLANCE_MOUVEMENT);
		//tabPos[1] = position;
	};
	return true;	
}


//=========================================================================================================
void Pied::modifierEtat(ETATS nouvelEtat)
{
	pthread_mutex_lock(&semPied);
	etat = nouvelEtat;
	pthread_mutex_unlock(&semPied);
}


//=========================================================================================================
void Pied::consignerPied(int nouvelleConsigne)
{
	pthread_mutex_lock(&semPied);
	consigne=nouvelleConsigne;
	etat = ACTIF;
	pthread_mutex_unlock(&semPied);
	pthread_cond_signal(&signalNouvelleConsigne);
}


//=========================================================================================================
void Pied::ArretForce()
{
	pthread_mutex_lock(&semPied);
	if (etat==ACTIF){
		etat=ARRU;
		pthread_cond_signal(&signalFinMouvement);
	}
	pthread_mutex_unlock(&semPied);
}


//=========================================================================================================
bool Pied::attendreFinMouvementAvecSucces()
{
	pthread_mutex_lock(&semPied);
	if(etat==ACTIF){
		pthread_cond_wait(&signalFinMouvement, &semPied);
	}
	pthread_mutex_unlock(&semPied);
	if (etat == OBJECTIF_ATTEINT){
		return true;
	}else{
		return false;
	}
}


//=========================================================================================================
void Pied::commandeMoteur(int sens)
{
	if (sens == SORTANT){
		digitalWrite( brocheGPIO_P, HIGH);
		digitalWrite( brocheGPIO_N, LOW);
	}else if (sens == RENTRANT){
		digitalWrite( brocheGPIO_P, LOW);
		digitalWrite(brocheGPIO_N,HIGH);
	}else if (sens == ARRET){
		digitalWrite( brocheGPIO_P, LOW);
		digitalWrite(brocheGPIO_N, LOW);
	}
		
}	


//=========================================================================================================
bool Pied::determinerPositionPied()
{
	if (ptrCAN == NULL) return false;
	int ref = ptrCAN->lireEntree(CAN_ENTREE_0);
	int val = ptrCAN->lireEntree(numPied);
//cout <<" Valeur potentiomètre : " << val <<" | Valeur de référence : " << ref<< endl;
	position = (val*POSITION_MAX)/ref; 
	return true;
}

int Pied::getPosition()
{
	return position;
}

int Pied::getConsigne()
{
	return consigne;
}
	
	
