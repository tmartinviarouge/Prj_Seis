#include "../../defs/MPU6050.h"
#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

	using namespace std;

int main()
{
	Mpu6050 mp;
	mp.init_I2C();
	usleep(50000);
	short AX,AY,AZ;
	//short GX,GY,GZ;
	mp.MesurerAccel(AX, AY, AZ);
	cout << "Accelerometre : " <<endl;
	cout << "X : " << AX << endl;
	cout << "Y : " << AY << endl;
	cout << "Z : " << AZ << endl;
	//mp->MesurerGyro(GX, GY, GZ);
	int temp = mp.MesurerTemp();
	cout <<"Température : "<< temp <<endl;
}
