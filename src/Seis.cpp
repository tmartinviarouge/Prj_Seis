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
//#include "../defs/rPi2_rPi+.h"
#include "../defs/Superviseur.h"
#include "../defs/c_socket.3.3.h"

//=====================================================================================================

/*Seis::Seis() {
    accelerometre = new MPU6050();
}
*/
Seis::Seis(Superviseur* ptrSuperviseur) : ptrClient(ptrSuperviseur) {

}
//-----------------------------------------------------------------------------------------------------

Seis::~Seis() {
}


//=====================================================================================================
//	CORPS DES  THREADS
//=====================================================================================================

/*void Seis::initTimerMesures() {
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
     
}*/

//-----------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------

/*bool Seis::EnvoyerTramVibrations() {
    short AX, AY, AZ;
    while (1) {
        pthread_mutex_lock(&semTramesXYZ);
        pthread_cond_wait(&SignalNouvellesMesuresXYZ, &semTramesXYZ);
        pthread_mutex_unlock(&semTramesXYZ);
    };
}
//-----------------------------------------------------------------------------------------------------

bool Seis::MesuresDemandees() {
    short AX, AY, AZ;
    while (1) {
        pthread_mutex_lock(&semMesuresXYZ);
        pthread_cond_wait(&SignalActivationMesuresXYZ, &semMesuresXYZ);
        pthread_mutex_unlock(&MesuresXYZ);
        if (MesuresDem) {
            accelerometre->MesurerAccel(AX, AY, AZ);
            pthread_cond_signal(&SignalNouvellesMesuresXYZ);
            usleep(10000);
        }
    };
}*/
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

/*bool Seis::nivellement() {
    int correction1, correction2, correction3;
    bool incident;
    do {
        incident = positionnerPieds(distanceSol[P1], distanceSol[P2], distanceSol[P3]);
        determinerCorrectionPositionPositions(correctionP1, correctionP2, correctionP3);
        distanceSol[P1] = distanceSol[P1] + correctionP1;
        distanceSol[P2] = distanceSol[P2] + correctionP2;
        distanceSol[P3] = distanceSol[P3] + correctionP3;
    } while ((incident == false) && (correctionP1 <> 0) && (correctionP1 <> 0) && (correctionP1 <> 0));
    return incident;
}

void Seis::determinerCorrectionPositions(int& correctionP1, int& correctionP2, int& correctionP3) {
    accelerometre.MesurerAccel(&AcX, &AcY, &AcZ);

    pthread_mutex_lock(&semTramesXYZ);
    pthread_cond_wait(&SignalNouvellesMesuresXYZ, &semTramesXYZ);
    pthread_mutex_unlock(&semTramesXYZ);
    correctionP1 = (Ax * RAYON) / G_TERRE;
    int Aysqrt3 = (RACINE_CARREE_DE_TROIS * Ay);
    correctionP2 = (RAYON * (Aysqrt3 - Ax)) / G_TERRE;
    correctionP3 = -(RAYON * (Aysqrt3 + Ax)) / G_TERRE;


}

bool Seis::positionnerPieds(int consP1, int consP2, int consP3) {

}*/


//========================================================================================================
// on replie les trois pieds
//========================================================================================================



//================================================================================================================================
//traitement demande de connexion 
//================================================================================================================================

/*void Seis::traitementDemandeConnexion() {
    Seis * ptrNewClient;

    if (sockDemon.creerSocket(::PORT_SERVEUR)) {
        while (1) {
            ptrNewClient = new Superviseur(this);
            ptrNewClient->ptrSockService = sockDemon.accepterDemandeConnexion();
            if (ptrNewClient->ptrSockService == NULL) {

                delete ptrNewClient;
                cerr << "echec d'acceptation de connexion" << endl;

            } else {
                // le client est opérationnel et comme on est sur un serveur
                // mono client nous n’allons pas activer le thread de réception
                // mais lancer directement l’attente du stub en réception
                ptrNewClient->traitementSurReception();
            }
            //---------FIN FICHIER--------------------------------------------------------------------

        }*/
//================================================================================================================================        
//traitement recéption de commande         
//================================================================================================================================       
   //     void Seis::
