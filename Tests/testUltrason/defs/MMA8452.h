#ifndef MMA8452_H
#define MMA8452_H

#define I2C_ADRESSE	0x1c	// avec SLA à 0 (SLave Aderss à la masse)




#ifndef WIRINGPI
#include "faux_wiringPi.h"
#else
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#endif

#define REGISTRE_WHO_AM_I	0x0D
#define REGISTRE_CTRL_REG1	0x2A
#define REGISTRE_XYZ_DATA_CFG	0x0E
#define REGISTRE_OUT_X_MSB 	0x01
#define REGISTRE_OUT_X_LSB 	0x02
#define REGISTRE_OUT_Y_MSB 	0x03
#define REGISTRE_OUT_y_LSB 	0x04
#define REGISTRE_OUT_Z_MSB 	0x05
#define REGISTRE_OUT_z_LSB 	0x06

#define ACTIVER			0x01
#define DESACTIVER		0xFE


using namespace std;

class MMA8452
{
public:
    enum INCIDENT_MMA8452
    {
        PAS_DINCIDENT			= 0x00 ,
        ECHEC_OUVERTURE_DEVICE		= 0x01 ,
        ECHEC_CONNEXION_AU_DEVICE	= 0x02 ,
	I2C_NON_INITIALISE		= 0x03 ,
    };

	MMA8452();
	~MMA8452();
	bool MesurerAccelerations(int &X,int &Y,int &Z);
	bool init_I2C();
	int  GetCodeErreur(){return codeErreur;};

private:
	int Canal;
	int codeErreur;
 };


#endif	//MMA8452_H

