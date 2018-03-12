#include "Temperature.h"

using namespace std;


//========================================================================

Temperature::Temperature() {
    adresseI2C = TCN75A_I2C_ADDRESS;
}

Temperature::~Temperature() {

}

int Temperature::init() {
    
    /* cout << "adresseI2C :" << adresseI2C << endl;
    cout << "Nouvelle adresse I2C ? (O/o/N/n)" << endl;
    cin >> resultat;

    if (resultat == 'O' || resultat == 'o') {
        int i2cAddr;
        cout << "Entrer nouvelle adresse : ";
        cin >> i2cAddr;
        adresseI2C = i2cAddr;
    } else if ((resultat == 'N') || (resultat == 'n')) {
        Temperature();
    }; */

    fd = wiringPiI2CSetup(adresseI2C); //Demande d'ouverture de l'adresse I2C 
    if (fd == -1) return 0;

    wiringPiI2CWriteReg8(fd, CONFIGURATION_REGISTER, 0x60); // Resolution 12 bit soit 0.0625 Celsius 

    usleep(350000); // Faire une pause, pour que le registre de Configuration est le temps de se faire car il met 240 ms pour faire la résoluti--on à 12 bit

    return 0;

}

int Temperature::MesureTempEnDixieme(int *degre, int *dixieme) {
	   
 int Temperature = wiringPiI2CReadReg16(fd, AMBIENT_TEMPERATURE_REGISTER); // Mesure de la température Ambiante
    *degre = (Temperature & 0xff00) >> 12; //12 bits de décalage pour que les poids faibles et poids forts soit au bon endroit
    *dixieme = Temperature & 0x00ff; // Car WiringPi inverse LSB et MSB
return 0;	
}

