// #include "../defs/MPU6050.h"
#include <iostream>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../defs/Seis.h"
#include <pthread.h>



using namespace std;

Seis unSeis;

void *mesureVibration(void*) {
    unSeis.GestionMesuresAccelerometre();
}

int main(int argc, char** argv) {
  
    int minX,maxX,minY,maxY,minZ,maxZ;
    int nbInc=0;
    
    pthread_t thmesureVibration;
    if (pthread_create (&thmesureVibration, NULL, mesureVibration, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'mesureVibration'"<<endl;
		exit (1);
	};
        sleep(1);
        
        while(1){
        
        unSeis.demandeMesuresXYZ();
        usleep(10000);
        if (nbInc==0) {
            minX=unSeis.AX;
            maxX=unSeis.AX;
            minY=unSeis.AY;
            maxY=unSeis.AY;
            minZ=unSeis.AZ;
            maxZ=unSeis.AZ;
        };
        if (nbInc==500){ // 5 secondes
            nbInc=0; 
        }else {
            nbInc++;
        }
        if (minX>unSeis.AX)minX=unSeis.AX;
        if (minY>unSeis.AY)minY=unSeis.AY;
        if (minZ>unSeis.AZ)minZ=unSeis.AZ;
        if (maxX<unSeis.AX)maxX=unSeis.AX;
        if (maxY<unSeis.AY)maxY=unSeis.AY;
        if (maxZ<unSeis.AZ)maxZ=unSeis.AZ;
  
        usleep(10000);
            
        cout << "\033[2J";
        cout << "\033[1;1H"<< "AX" <<"="<< unSeis.AX<<"\033[1;10H"<<"-->"<<"    Delta AX="<<maxX-minX<<"   ";
        cout << "\033[2;1H"<< "AY" <<"="<< unSeis.AY<<"\033[2;10H"<<"-->"<<"    Delta AY="<<maxY-minY<<"   ";
        cout << "\033[3;1H"<< "AZ" <<"="<< unSeis.AZ<<"\033[3;10H"<<"-->"<<"    Delta AZ="<<maxZ-minZ<<"   "<<endl;
        
        }
        
    return (EXIT_SUCCESS); 
}

