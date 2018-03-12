#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../defs/MPU6050.h"

	using namespace std;

// Déclaration du constructeur et destructeur
//=====================================================================================================
Mpu6050::Mpu6050( ) { }


Mpu6050::~Mpu6050( ) { }
//=====================================================================================================
// Initialisation de l'adresse I2C du composant et reveil du composant 

int Mpu6050::init_I2C()
{	
	 fd = wiringPiI2CSetup(MPU6050_I2C_ADDRESS);
         if (fd == -1){
        	cout << "ERREUR" << endl;
		return  0;
	}

	wiringPiI2CReadReg8 (fd, MPU6050_PWR_MGMT_1);
	wiringPiI2CWriteReg8(fd, MPU6050_PWR_MGMT_1, 0);
	return 1;

}
//=====================================================================================================
// Lecture des valeurs dans les Registres de l'accéléromètre ( High & Low ), pour obtenir la mesure en "mg" on decale de 4 bits vers la droite dans le registre

void Mpu6050::MesurerAccel () {

	short X,Y,Z, x,y,z;
	x = wiringPiI2CReadReg8(fd, MPU6050_ACCEL_XOUT_L);   
	y = wiringPiI2CReadReg8(fd, MPU6050_ACCEL_YOUT_L); 
	z = wiringPiI2CReadReg8(fd, MPU6050_ACCEL_ZOUT_L); 
	
	X = wiringPiI2CReadReg8(fd, MPU6050_ACCEL_XOUT_H); 
	Y = wiringPiI2CReadReg8(fd, MPU6050_ACCEL_YOUT_H);  
	Z = wiringPiI2CReadReg8(fd, MPU6050_ACCEL_ZOUT_H);  

	AX = ((X << 8) | x);  
	AY = ((Y << 8) | y);  
	AZ = ((Z << 8) | z); 
	

	AX = AX>>4; 
	AY = AY>>4;    
	AZ = AZ>>4;  

	
}
// Appel la méthode du dessus pour afficher les valeurs des registres

void Mpu6050::MesurerAccel(short &AcX, short &AcY, short &AcZ)
{
	MesurerAccel();
		AcX = AX;
		AcY = AY;
		AcZ = AZ; 

}	

//=====================================================================================================
// Initialisation a 0 du registre de température, pour trouver la température on declale les bits de poids faiblent a a gauche et de poids fort a droite. Pour avoir la température, il faut  faire une convertion.

int Mpu6050::MesurerTemp(){

	wiringPiI2CWriteReg8(fd, REG_TEMPERATURE,0);
 	unsigned char buf[2] = {0};  
	
	LectureRegistre =wiringPiI2CReadReg16 (fd, REG_TEMPERATURE);   
	Lectemp =(LectureRegistre&0x00ff)<<8;   
	Lectemp +=(LectureRegistre&0xff00)>>8;   
	RecuperationTemp=Lectemp;
	temperature=RecuperationTemp/340+36.53;
	//cout<<"Temperature"<<" "<<endl;  
	//cout << temperature << endl;
	return temperature;
}


//=====================================================================================================
// Lecture des valeurs dans les Registres du gyroscope ( High & Low ), pour obtenir la mesure en "mg" on decale de 4 bits vers la droite dans le registre

void Mpu6050::MesurerGyro () { 

	short X1,Y1,Z1, x1,y1,z1;
	x1 = wiringPiI2CReadReg8(fd, MPU6050_GYRO_XOUT_L);
	y1 = wiringPiI2CReadReg8(fd, MPU6050_GYRO_YOUT_L);  
	z1 = wiringPiI2CReadReg8(fd, MPU6050_GYRO_ZOUT_L);

	X1= wiringPiI2CReadReg8(fd, MPU6050_GYRO_XOUT_H);
	Y1 = wiringPiI2CReadReg8(fd, MPU6050_GYRO_YOUT_H);
	Z1 = wiringPiI2CReadReg8(fd, MPU6050_GYRO_ZOUT_H);

	GX = ((X1 << 8) | x1);
	GY = ((Y1 << 8) | y1);
	GZ = ((Z1 << 8) | z1);

	GX = GX>>4;
	GY = GY>>4;
	GZ = GZ>>4;
	
	
}
// Appel la méthode du dessus pour afficher les valeurs des registres

void Mpu6050::MesurerGyro(short &AgX, short &AgY, short &AgZ)
{
	MesurerGyro();
		AgX = GX;
		AgY = GY;
		AgZ = GZ; 

}

//=====================================================================================================

