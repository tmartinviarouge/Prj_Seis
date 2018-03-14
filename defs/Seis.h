//Date derniere modifs 10 decembre 2014; auteur JV
//

#ifndef SEIS_H
#define SEIS_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <pthread.h>
#include <cstdlib>	// pour la fonction exit()

#include "../defs/sockets.h"
//#include "../defs/rPi2_rPi+.h"
#include "../defs/MPU6050.h"
#include "../defs/ADS1115.h"
#include "../defs/Pied.h"
#include "../defs/GPIOSEIS.h"

#define PORTSEIS	10001

#define PERIODE_MESURES_VIBRATIONS_US		1000000	// en micro seconde pour tests
//#define PERIODE_MESURES_VIBRATIONS_US		10000	// en micro seconde reelle
#define PERIODE_HORS_MESURES_VIBRATIONS_US	10*PERIODE_MESURES_VIBRATIONS_US	
#define PERIODE_SURVEILLANCE_TEMPERATURE_S	6	// en seconde (fonction sleep)

#define DISTANCE_PIED_CENTRE			125 //en mm, distance a confirmer

#define ERREUR_ACCEPTABLE_ACCELERATION		2	// en unité de l'accelerometre
#define NB_PIEDS	3

#define RACINE_CARREE_DE_TROIS 
#define VARIATION_ACCEL                         50  // à confirmer


using namespace std;

class Seis
{
public:

    Seis( );
    ~Seis( );

    pthread_mutex_t semSynchroMesure;
    pthread_cond_t SignalMesure;
    pthread_mutex_t semTramesXYZ;
    pthread_cond_t SignalNouvellesMesure;
    
    void initTimerMesures();
    void attenteCmds();
    void surveillerTemperature();
    void surveillerSortiePieds();
    // méthodes liées aux 4 phases
    void mesurer(bool activer);
    int Approche();
    bool nivellement();
    void determinerCorrectionPositions(int & correctionP1, int & correctionP2, int & correctionP3);
    int repliement();
    bool positionnerPieds(int consP1, int  consP2, int consP3);
    bool testPosition();

    // méthodes pour la mainteanance
    int sortirPiedDe(int pied0,int pied1,int pied2 );
    int rentrerPiedDe(int pied0,int pied1,int pied2 );
   
// attributs publiques
    Mpu6050 accelerometre;
    Pied* Pied1;
    Pied* Pied2;
    Pied* Pied3;

private:
	bool MesuresEnCours;
	int temperature;
	int DistanceMoyenne;
	int _AlimenterDetecteurUltraSon(bool etat);
	int lireDistance(int pied);
        int positionsAtteintes;
	int CanalService;
	double SQR3;
	string CRLF;
        int Ax, Ay, Az;
                
        

};

#endif // SEIS_H
