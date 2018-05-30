#ifndef PIED_H
#define PIED_H


#include <stdlib.h>
#include <unistd.h>

#include "../defs/ADS1115.h"			// classe du CAN
#include "../defs/GPIOSEIS.h"			// reservation broches GPIO pour les differents composants du SEIS

#define LONGUEUR_MAX				1000	//Longueur de sortie max d'un pied en dixième de mm
#define ENTREE_REF_CAN				0	//Entrée de référence à 5 volts
#define POSITION_MAX				1000	//Position maximale des pieds en dixième mm
#define DELTA_POS		              	2	//Tolérance de position  en dixième mm
#define PERIODE_SURVEILLANCE_MOUVEMENT		1000
//#define PERIODE_SURVEILLANCE_MOUVEMENT	3000	//Temps de surveillance de sortie ou entrée de pied en µs

#define CAN_ENTREE_0				0


class Pied
{
  public : 
	enum ETATS {ARRU, ACTIF, EN_BUTEE_HAUTE , EN_BUTEE_BASSE, OBJECTIF_ATTEINT};
	enum SENS {
		RENTRANT = -1 , 
		ARRET    =  0 , 
		SORTANT  =  1
	};

	Pied(int numpied , ADS1115 *ptCAN);
	Pied();
	bool init(int numpied , ADS1115 *ptCAN);
	virtual ~Pied();
	bool determinerPositionPied();	
	bool asservissementPied();		//Cette fonction est dans le corps d'un thread (3 threads d'asservissement)
	void modifierEtat(ETATS nouvelEtat);
	bool attendreFinMouvementAvecSucces();
	void ArretForce();
	void commandeMoteur(int sens);
	void consignerPied(int nouvelleConsigne);
	int getNumPied();
	int getMouvementPied();
	int getPosition();
	int getConsigne();

  private :
	ADS1115 *ptrCAN;
	//int tabPos[2];
	int numPied ;
	int position;	// position courante du pied en dixieme de millimètre
	ETATS etat;
	int consigne;	// en dixieme de millimètre; consigne a atteindre; entre 0 et 1000 
	pthread_mutex_t	semPied;
	pthread_cond_t	signalNouvelleConsigne;
	pthread_cond_t	signalFinMouvement;	
	int brocheGPIO_P ;
	int brocheGPIO_N ;
	bool initBon;
	int MouvementPied;
};

#endif	

