#ifndef F_WIRINGPI_H
#define F_WIRINGPI_H

#define INPUT		0	
#define OUTPUT		1	
#define HIGH		1	
#define LOW		0	



void pinMode (int pin, int mode);
void digitalWrite (int pin, int etat);
int digitalRead (int pin);

int wiringPiSPISetup(int channel, int speed);
int wiringPiSPIDataRW(int channel, unsigned char *data, int len);

int wiringPiI2CSetup(int devId);
int wiringPiI2CReadReg8 (int fd, int reg);
int wiringPiI2CReadReg16(int fd, int reg);
#endif // F_WIRINGPI_H
