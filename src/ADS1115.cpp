//#include <stdint.h>

#include <unistd.h>  	// pour usleep()
#include "../defs/ADS1115.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iomanip>
#include <iostream>

using namespace std;

//===================================================================================================
ADS1115::~ADS1115(){};


//===================================================================================================
ADS1115::ADS1115(unsigned char I2Cadresse){
	adresseI2C = (int) I2Cadresse;
	codeErreur = 0;
	fd = -1 ;
}


//===================================================================================================
ADS1115::ADS1115(){
	adresseI2C = ADRESSE_I2C_DEFAUT;
	codeErreur = 0;
	fd = -1 ;
}


//===================================================================================================
int ADS1115::getCodeErreur()
{
	return codeErreur;
}


//===================================================================================================
bool ADS1115::init(unsigned char I2Cadresse)
{
	adresseI2C = (int) I2Cadresse;
	return init();
}


//===================================================================================================
bool ADS1115::init()
{
//	wiringPiSetup(); // utile ici???
	fd = wiringPiI2CSetup(adresseI2C);
	if (fd == -1){
		codeErreur = ERREUR_I2CINIT ;
		return false;
	};
	codeErreur = 0;
	return true;
}


//===================================================================================================
	
int ADS1115::lireEntree(int num)
{

	if (fd == -1 ){
		codeErreur = ERREUR_CANAL_INVALIDE ;
		return -1 ;
	}
	config = CQUE_NONE | CLAT_NONLAT | CPOL_ACTVLOW | CMODE_TRAD | DR_1600SPS | MODE_SINGLE |
		 PGA_6_144V | OS_SINGLE;
	switch (num) {
		case 0 : config |= MUX_SINGLE_0 ; break;
		case 1 : config |= MUX_SINGLE_1 ; break;
		case 2 : config |= MUX_SINGLE_2 ; break;
		case 3 : config |= MUX_SINGLE_3 ; break;
	};
 //cout<<"config ="<<hex<<setfill('0')<<setw(4)<<config<<endl;
	int confwp=((config&0x00ff)<<8)+((config&0xff00)>>8);
	wiringPiI2CWriteReg16 (fd, REG_CONFIG , confwp ); 
	usleep(DELAI_CONVERTION);
	short convert = wiringPiI2CReadReg16 (fd, REG_CONVERSION);
	short convertwp=((convert&0x00ff)<<8)+((convert&0xff00)>>8) +OFFSET_ZERO;
//cout<<"convertwp="<<hex<<setfill('0')<<setw(4)<< convertwp<<endl;
	int valeur =  convertwp >>4 ;
	return  valeur;
}

//======= FIN FICHIER ==================================================================================


