#include <wiringPi.h>
#include <iostream>
//#include "Ultrason.h"
#include <unistd.h>		//librairie pour utiliser la fonction usleep()
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include "/home/pi/Desktop/ULTRASON/defs/Ultrason.h"
#include "/home/pi/Desktop/ULTRASON/defs/PiedSeis.h"
#include "/home/pi/Desktop/ULTRASON/defs/rPi2_rPi+.h"
#include "/home/pi/Desktop/ULTRASON/defs/Seis.h"
#include "/home/pi/Desktop/ULTRASON/defs/sockets.h"
#include "/home/pi/Desktop/ULTRASON/defs/GPIOSEIS.h"
#include "/home/pi/Desktop/ULTRASON/defs/MMA8452.h"
#include "/home/pi/Desktop/ULTRASON/defs/faux_wiringPi.h"




using namespace std;

int main()
{	
	
	Ultrason *mUS = new Ultrason();
/*while(1){
	cout << mUS->faireUneMesure() << endl;
	usleep(100000);
}*/		//lance une mesure
for(int i = 0; i<5; i++) {
	cout <<"La distance est de :"<< mUS->determinerDistance() <<endl;	//lance plusieurs mesures d'affilée et fait une moyenne
	usleep(50000);
}
}
