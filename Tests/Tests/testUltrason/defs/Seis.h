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

#include "sockets.h"
#include "rPi2_rPi+.h"
#include "MMA8452.h"
#include "PiedSeis.h"

#define PORTSEIS	10001

#define PERIODE_MESURES_VIBRATIONS_US		1000000	// en micro seconde pour tests
//#define PERIODE_MESURES_VIBRATIONS_US		10000	// en micro seconde reelle
#define PERIODE_HORS_MESURES_VIBRATIONS_US	10*PERIODE_MESURES_VIBRATIONS_US	
#define PERIODE_SURVEILLANCE_TEMPERATURE_S	6	// en seconde (fonction sleep)

#define DISTANCE_PIED_CENTRE			125 //en mm, distance a confirmer

#define ERREUR_ACCEPTABLE_ACCELERATION		2	// en unité de l'accelerometre
#define NB_PIEDS	3

#define PIED0	0	// sortie pate 1 du MCP 3004 ou 3008
#define PIED1	1	// sortie pate 2 du MCP 3004 ou 3008
#define PIED2	2	// sortie pate 3 du MCP 3004 ou 3008

#define	GPIO_TRIG_PIED0		RPI2plus::GPIO_17
#define	GPIO_TRIG_PIED1		RPI2plus::GPIO_18
#define	GPIO_TRIG_PIED2		RPI2plus::GPIO_27
#define	GPIO_ECHO_PIED0		RPI2plus::GPIO_06
#define	GPIO_ECHO_PIED1		RPI2plus::GPIO_12
#define	GPIO_ECHO_PIED2		RPI2plus::GPIO_13

// broches GPIO connectées aux deux ponts H SN754410, notons 
//	SN754410(01) le pont H pilottant la puissance dans les pieds 0 et 1
//	SN754410(2)  le pont H pilottant la puissance dans le pied 2
#define	GPIO_SORTIR_PIED0	RPI2plus::GPIO_23  // vers pin 2 du SN754410(01),sa pin 3 sera reliée au fil 3(red) du pied 0
#define	GPIO_SORTIR_PIED1	RPI2plus::GPIO_16  // vers pin 7 du SN754410(01),sa pin 6 sera reliée au fil 4(black) du pied 0
#define	GPIO_SORTIR_PIED2	RPI2plus::GPIO_22  // vers pin 10 du SN754410(01),sa pin 10 sera reliée au fil 3(red) du pied 1
#define	GPIO_RENTRER_PIED0	RPI2plus::GPIO_22  // vers pin 15 du SN754410(01),sa pin 14 sera reliée au fil 4(black) du pied 1
#define	GPIO_RENTRER_PIED1	RPI2plus::GPIO_26  // vers pin 2 du SN754410(2),sa pin 3 sera reliée au fil 3(red) du pied 2
#define	GPIO_RENTRER_PIED2	RPI2plus::GPIO_19  // vers pin 7 du SN754410(01),sa pin 6 sera reliée au fil 4(black) du pied 2
#define	GPIO_ENABLE_PIEDS	RPI2plus::GPIO_04  // broches 1 et 9 du SN754410(2) et broches 1 du SN754410(2) 

#define ENTETE_TRAME_MESURE	"$!mv,"		// correspond à l'entete d'une trame de mesure type $!mv,+0012,-1023,+1245;


using namespace std;

class Seis
{
public:

    Seis( );
    ~Seis( );

    pthread_mutex_t semSynchroMesure;
    pthread_cond_t SignalMesure;

// les callback
    void initTimerMesures();
    void mesurer();
    void attenteCmds();
    void surveillerTemperature();
    void surveillerSortiePieds();

// autres methodes publiques
    int Approche();
    int nivellement();
    int repliement();
    int sortirPiedDe(int pied0,int pied1,int pied2 );
    int rentrerPiedDe(int pied0,int pied1,int pied2 );
   
// attributs publiques
    MMA8452 accelerometre;
private:
	bool MesuresEnCours;
	int temperature;
	int DistanceMoyenne;
	int _AlimenterDetecteurUltraSon(bool etat);
	int lireDistance(int pied);
	Pied* ptrPied[NB_PIEDS];
	int CanalService;
	double SQR3;
	string CRLF;

};

#endif // SEIS_H
