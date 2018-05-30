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
#include "../../defs/gestionnaireAlarme.h"
#include "../../defs/GPIOSEIS.h"
//#include <pthread.h>

using namespace std;

/*
 * 
 */
//void *gestionnaireAlarme::signalerApproche(int distance)
gestionnaireAlarme gestion;

void *alarmeApproche(void*) {   
 gestion.emettreAlarme();
    
}

int main() {

pthread_t thalarmeApproche;
//gestionnaireAlarme gestion;
  
 float distance = 500;
//while(1){   
// gestion.activerAlarme();
if (pthread_create (&thalarmeApproche, NULL, alarmeApproche, NULL) < 0){
                cerr<<"ERR Impossible de créer le thread 'asservissement du pied1'"<<endl;
                exit (1);
        };

 for (int i = 500; i>=140; i--) {
        distance = distance -10;
        cout<<distance<<"mm"<<endl;
        sleep(1);
	//gestion.signalerApproche(distance);
	if (distance >= 140){
        cout << "if" <<endl;
        //gestion.arreterAlarme();
         gestion.signalerApproche(distance);
}
else {
gestion.arreterAlarme();
}
}
/*	//gestion.signalerApproche(distance);
        if (distance <= 14){
        sleep(5);
        gestion.arreterAlarme();
        }
 */  
// }
	//gestion.signalerApproche(distance);
	/*if (distance <= 14){
	sleep(5);
	gestion.arreterAlarme();
	}*/
//}
   /* if (pthread_create (&thalarmeApproche, NULL, alarmeApproche, NULL) < 0){
		cerr<<"ERR Impossible de créer le thread 'asservissement du pied1'"<<endl;
		exit (1);
	};
   */
	return 0;
}

