
#ifndef PIED_SEIS_H
#define PIED_SEIS_H

#include "rPi2_rPi+.h"

// couplage avec le MCP 3008 pour lecture des feedback
#define GPIO_SC_MCP3008		RPI2plus::SPI_CE0	// cette broche devra etre reliée au CS (pin10) du mcp3008
#define CANAL_SPI_MCP3008	0	//car le MCP3008 sera connecté à SPI_CE0
#define	HORLOGE_MCP3008		1600000	// en hz (pour une alimentation de 3.3v il ne faut pas depasser 1.9Mhz) à placer dans wiringPiSPISetup

#define DISTANCE_PIEDS_REPLIES		100		// il faudra mettre les bonne valeur
#define COURSE_MAX_DUN_PIED		100		// en mm 
#define	PRECISION_ULTRA_SON		3		// en mm

#define VALEUR_ARRET_APPROCHE	DISTANCE_PIEDS_REPLIES+(COURSE_MAX_DUN_PIED/2)+(2*PRECISION_ULTRA_SON)

#define DUREE_IMPULTION_TRIGGER 		10 	// send pulse 10us to trigger
#define	TEMPS_DESCENTE_PIED_DIXIEME_DE_MM_MAX	5000	// vitesse grand maxi du pied 2cm/s soit 5 miliseconde par 0.1 mm
#define VITESSE_SON_ALLER_RETOUR		17000	// nombre de dixieme de mm aller et retour parcouru en 1 us

#define SENS_SORTANT	1
#define ARRET		0
#define SENS_ENTRANT	-1

#ifndef WIRINGPI
#include "faux_wiringPi.h"
#else
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#endif

using namespace std;

class Pied
{
public:

	Pied(RPI2plus::BROCHES_GPIO_ETENDU triger ,
		 RPI2plus::BROCHES_GPIO_ETENDU  echo ,
		 int numpied ,
		 RPI2plus::BROCHES_GPIO_ETENDU  entrerpied ,
		 RPI2plus::BROCHES_GPIO_ETENDU  sortirpied );
	~Pied();

    enum INCIDENTS_PIED
    {
        PAS_INCIDENT			= 0x00 ,
        BLOQUE_EN_DESCENTE		= 0x01 ,
        BLOQUE_EN_MONTE			= 0x02 ,
	CONSIGNE_DEPASSEE_EN_DESCENTE	= 0x03 ,
 	CONSIGNE_DEPASSEE_EN_MONTE	= 0x04
    };
   
	int mesurerDistance();
	int LongueurSortiePied();
	int autoEtalonnage();
	int positionnerPied(int position);
	int corrigerPied(int ofset);

	void arretPied();
	int getsensMouvement(){return sensMouvement;};
	int getPrecedantePosition(){return valPrecedantSortiePied;};
	int getDistanceSol(){return distanceSol;};
	bool etalonageFait(){return piedEtalonne;};
	int getConsigneSortiePied(){return consigneSortiePied;};
	INCIDENTS_PIED incidentPied;

private:
	void mouvementPied(int sens);
	int distanceSol; //dixieme de mm? 
	int consigneSortiePied;
	int GPIOtrigger;
	int GPIOecho;
	int GPIOsortirPied;
	int GPIOentrerPied;
	int feedbackmin;
	int feedbackMax;
	bool piedEtalonne;
	int numPied;
	int sensMouvement;
	int valPrecedantSortiePied; // permet de voir si le moteur force ou pas
};





#endif	// PIED_SEIS_H

