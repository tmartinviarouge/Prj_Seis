/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Superviseur.cpp
 * Author: snir2g1
 * 
 * Created on 12 mars 2018, 11:36
 */

#include "../defs/Superviseur.h"
#define PORT_SERVEUR 10001
#include <iostream>
//#include <c_s>
#include "../defs/c_socket.3.3.h"
#include "../Tests/TestStub/defs/testSeis.h"
using namespace std;

Superviseur::Superviseur(Seis *ptseis) : ptrSeis(ptseis) {
    
}

Superviseur::~Superviseur() {
    if (ptrSockService != NULL) {
        if (ptrSockService->socket_active())
            ptrSockService->fermer_socket();
        delete ptrSockService;

    }
    //ptrSeis->finServicePour(this);
}

void Superviseur::traitementSurReception() {
    	testSeis *seis = new testSeis;
	string msgSeis = seis->envoie();
	string cmd_seq ;
	string cmd_instant;
    // si le client ferme la socket alors la fonction lire retourne une valeur nulle

    while (ptrSockService->lire(msgSeis) > 0) {

        if ((msgSeis == "$eth;") ||
	(msgSeis == "$tacc;") || 
	(msgSeis == "$Capp;") || 
	(msgSeis == "Crepli;") || 
	(msgSeis == "Cnivel;") || 
	(msgSeis == "$!mv,sXXXX;") || 
	(msgSeis == "$!mv,tYYYY;") || 	
	(msgSeis == "$!mv,uZZZZ;") || 
	(msgSeis == "$tcon;") || 
	(msgSeis == "$tcapt;") || 
	(msgSeis == "$tmot;") || 
	(msgSeis == "$?vibOn;") || 
	(msgSeis == "$?vibOff;"))  
  {
        /*    case "$eth;" :
            case "$tacc;" :

            case "$Capp;" :

            case "$Crepli;" :

            case "$Cnivel;" :

            case "$!mv,sXXXX;" :

            case "$!mv,tYYYY;" :

            case "$!mv,uZZZZ;" :

            case "$tcon;" :

            case "$tcapt;" :

            case "$tmot;" :

            case "$?vibOn;" :

            case "$?vibOff;" :*/
                cmd_seq = msgSeis;
                pthread_mutex_lock(&sem_cmd_seq);
                pthread_cond_signal(&signal_cmd_seq);
                cout<<"cmd seq : " << cmd_seq << endl;
               // break;
  }
	    else if ((msgSeis == "$?accOn;") || 
	    (msgSeis == "$?accOff;") ||
       	    (msgSeis == "$?posPied1") ||
            (msgSeis == "$?posPied2") ||
            (msgSeis == "$?posPied3") ||
            (msgSeis == "$?lUltra1") ||
            (msgSeis == "$?lUltra2") ||
            (msgSeis == "$?lUltra3")) {
	    	cmd_instant = msgSeis;
                pthread_cond_signal(&signal_cmd_instant);
                cout<<"cmd_instant : "<<cmd_instant<<endl;
            }
	    else {
	    	pthread_cond_signal(&signal_msg_erreur);
                pthread_mutex_unlock(&sem_cmd_seq);
	    }

/*
            case "$?accOn;":

            case "$?accOff;":

            case "$?posPied1;":

            case "$?posPied2;":

            case "$?posPied3;":

            case "$?lUltra1;":

            case "$?lUltra2;":

            case "$?lUltra3;":
                cmd_instant = msgSeis;
                pthread_cond_signal(&signal_cmd_instant);
                cout<<"cmd_instant : "<<cmd_instant<<endl;
                break;

            default: pthread_cond_signal(&signal_msg_erreur);

                pthread_mutex_unlock(&sem_cmd_seq);
*/
        }
        /*if (msgSeis == cmd_seq) {

            cmd_seq = msgSeis;
            pthread_cond_signal(&signal_cmd_seq);

        } else if (msgSeis == cmd_instant) {
            cmd_instant = msgSeis;
            pthread_cond_signal(&signal_cmd_instant);
        } else () {
            pthread_cond_signal(&ignal_msg_erreur);
        }
        ;
        ptrSockService->fermer_socket();
    }*/
    };

