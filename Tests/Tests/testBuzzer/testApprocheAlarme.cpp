/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testApprocheAlarme.cpp
 * Author: snir2g1
 *
 * Created on 27 mars 2018, 15:04
 */

#include <cstdlib>
#include "../defs/gestionnaireAlarme.h"
#include "../defs/GPIOSEIS.h"
#include <pthread.h>

using namespace std;

/*
 * 
 */
//void *gestionnaireAlarme::signalerApproche(int distance)
 gestionnaireAlarme gestion;
void *alarmeApproche(void*) {
    
    gestion.signalerApproche(distance);
    
}
int main() {
pthread_t thalarmeApproche;
   
    int distance = 50 ;
    for (int i = 50; i>=14; i--) {
        distance = distance -1;
        cout<<distance<<"cm"<<endl;
        sleep(1);
    }
    if (pthread_create (&thalarmeApproche, NULL, alarmeApproche, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'asservissement du pied1'"<<endl;
		exit (1);
	};
    return 0;
}

