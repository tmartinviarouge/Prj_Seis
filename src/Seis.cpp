//Date derniere modifs 10 decembre 2014; auteur JV
//
//=====================================================================================================

#include <math.h>
#include <fcntl.h> // definitions de constantes pour configurer la socket en non bloquante
#include <cstring>
#include <string.h>
#include <unistd.h> // pour usleep(useconds_t usec);
#include <errno.h> // pour EBUSY
#include <sys/time.h> //gettimeofday
#include <math.h>
#include <pthread.h>

#include "../defs/Seis.h"
#include "../defs/rPi2_rPi+.h"

//=====================================================================================================
Seis::Seis ( ) 
{
	accelerometre = new MPU6050();
 }

//-----------------------------------------------------------------------------------------------------
Seis::~Seis( )
{ 
}


//=====================================================================================================
//	CORPS DES  THREADS
//=====================================================================================================

void	Seis::initTimerMesures()
{
/*	int attente=PERIODE_HORS_MESURES_VIBRATIONS_US; 
    	for(;;){
		usleep(attente);
		if(MesuresEnCours){
			attente=PERIODE_MESURES_VIBRATIONS_US;
                	pthread_cond_signal (&SignalMesure);
		}else{
			attente=PERIODE_HORS_MESURES_VIBRATIONS_US;
		}
	}
*/
}

//-----------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool	Seis::EnvoyerTramVibrations()
{
	short AX, AY, AZ;
	while(1){
		pthread_mutex_lock(&semTramesXYZ);
		pthread_cond_wait(&SignalNouvellesMesuresXYZ, &semTramesXYZ);
		pthread_mutex_unlock(&semTramesXYZ);
	};
}
//-----------------------------------------------------------------------------------------------------
bool	Seis::MesuresDemandees()
{
	short AX, AY, AZ;
	while(1){
		pthread_mutex_lock(&semMesuresXYZ);
		pthread_cond_wait(&SignalActivationMesuresXYZ, &semMesuresXYZ);
		pthread_mutex_unlock(&MesuresXYZ);
		if(MesuresDem){
			accelerometre->MesurerAccel(AX, AY, AZ);
			pthread_cond_signal(&SignalNouvellesMesuresXYZ);
			usleep(10000);
		}
	};
}
//-----------------------------------------------------------------------------------------------------			


//-----------------------------------------------------------------------------------------------------
// 	corps de thread qui restent à traiter
//-----------------------------------------------------------------------------------------------------



//========================================================================================================
// 	Cette action d'approche n'est faite que par le detecteur ultra son, sa precision est maximum 3mm
//	Retourne 0 si pas de probleme
//========================================================================================================



//========================================================================================================
// le nivellement se fait conformement à l'algo du dossier
//========================================================================================================
bool Seis::nivellement()
{
    int correction1, correction2, correction3;
    bool incident;
    do {
        incident = positionnerPieds ( distanceSol[P1], distanceSol[P2], distanceSol[P3]);
        determinerCorrectionPositionPositions(correctionP1, correctionP2, correctionP3);
        distanceSol[P1] = distanceSol[P1] + correctionP1;
        distanceSol[P2] = distanceSol[P2] + correctionP2;
        distanceSol[P3] = distanceSol[P3] + correctionP3;        
    } while ((incident == false) && ((correctionP1 <> 0) || (correctionP2 <> 0) || (correctionP3 <> 0)));
    return incident;
       
}

bool Seis::testPosition()
{
    
    accelerometre.MesurerAccel(Ax, Ay, Az);
    Pied1->consignerPied(100);
    if (Az <= VARIATION_ACCEL) {
        return false;
    }
    else {
        return true;
    }
    
    
}

void Seis::determinerCorrectionPositions(int& correctionP1, int& correctionP2, int& correctionP3) {
    accelerometre.MesurerAccel(&AcX, &AcY, &AcZ);
    
    pthread_mutex_lock(&semTramesXYZ);
    pthread_cond_wait(&SignalNouvellesMesure, &semSynchroMesure);
    pthread_mutex_unlock(&semTramesXYZ);
    correctionP1 = (Ax * RAYON)/ G_TERRE;
    int Aysqrt3 = (RACINE_CARREE_DE_TROIS * Ay);
    correctionP2 = (RAYON * (Aysqrt3 - Ax)) / G_TERRE;
    correctionP3 = -(RAYON * (Aysqrt3 + Ax)) /G_TERRE;
        
       
}

bool Seis::positionnerPieds(int consP1, int  consP2, int consP3) 
{
    positionsAtteintes = true;
    if ((0 <= consP1) && (consP1 <= POSITION_MAX)) {
        Pied1.consignerPied(consP1);
    }
    if ((0<=consP2) && (consP1 <= POSITION_MAX)) {
        Pied1.consignerPied(consP1);
    }
    if ((0<=consP3) && (consP3 <= POSITION_MAX)) {
        Pied1.consignerPied(consP3);
    }
    if (Pied1.attendreFinMouvementAvecSucces() == false)
    {
        positionsAtteintes = false;
    }
    if (Pied2.attendreFinMouvementAvecSucces() == false)
    {
        positionsAtteintes = false;
    }
    if (Pied3.attendreFinMouvementAvecSucces() == false)
    {
        positionsAtteintes = false;
    }
    return positionsAtteintes;
    
}


//========================================================================================================
// on replie les trois pieds
//========================================================================================================



//================================================================================================================================



//---------FIN FICHIER--------------------------------------------------------------------

