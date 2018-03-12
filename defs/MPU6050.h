//
// petite présentation du Mpu6050 : accelerometre + giro + capteur température ..
//

#ifndef MPU_6050_H
#define MPU_6050_H

#ifndef WIRINGPI
#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#endif


		// plus propre de faire des énum de la classe concernée (voire ADS1115.h)
#define MPU6050_ACCEL_XOUT_H          0x3B   // R
#define MPU6050_ACCEL_XOUT_L          0x3C   // R
#define MPU6050_ACCEL_YOUT_H          0x3D   // R
#define MPU6050_ACCEL_YOUT_L          0x3E   // R
#define MPU6050_ACCEL_ZOUT_H          0x3F   // R
#define MPU6050_ACCEL_ZOUT_L          0x40   // R

#define MPU6050_GYRO_XOUT_H           0x43   // R
#define MPU6050_GYRO_XOUT_L           0x44   // R
#define MPU6050_GYRO_YOUT_H           0x45   // R
#define MPU6050_GYRO_YOUT_L           0x46   // R
#define MPU6050_GYRO_ZOUT_H           0x47   // R
#define MPU6050_GYRO_ZOUT_L           0x48   // R

#define REG_TEMPERATURE               0x41   // R

#define MPU6050_PWR_MGMT_1            0x6B   // R/W
#define MPU6050_I2C_ADDRESS           0x68   // I2C

//#include "../defs/Seis.h"

//using namespace std;

class Mpu6050
{
public :
	Mpu6050();
	~Mpu6050();

			// methodes

	int init_I2C();
	int MesurerTemp();
	void MesurerGyro (short &AgX, short &AgY, short &AgZ);
	void MesurerAccel (short &AcX, short &AcY, short &AcZ);
	void MesurerGyro ();
	void MesurerAccel();


			// attribut


private : 
	int fd;
	short AX, AY, AZ;
	short GX, GY, GZ;
	int temperature;
	short LectureRegistre;
	short Lectemp;
	short RecuperationTemp;

};


#endif	//MPU_6050






