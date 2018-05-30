/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Superviseur.h
 * Author: snir2g1
 *
 * Created on 12 mars 2018, 11:36
 */

#ifndef SUPERVISEUR_H
#define SUPERVISEUR_H
#include "c_socket.3.3.h"
#define PORT_SERVEUR 10001
#include "Seis.h"



class Seis; //obligatoire car il y a référence croisée des 2 classes

class Superviseur : public Recepteur {
public:
    Superviseur(Seis *ptseis);
    virtual ~Superviseur();
    //void finServicePour(Seis *ptrseis);
    // ci dessous,la redéfinition de la méthode " traitementSurReception()"
    // de la classe Recepteur est obligatoire car c'est le corps du thread
    void traitementSurReception();
    // doit être accessible par le demon pour son initialisation
    c_socketTCP *ptrSockService;
private:
   // testSeis *seis;
    Seis *ptrSeis;
    pthread_mutex_t sem_cmd_seq;
   // pthread_mutex_t sem_cmd_instant;
   // pthread_mutex_t sem_msg_erreur;
    pthread_cond_t signal_cmd_seq;
    pthread_cond_t signal_cmd_instant;
    pthread_cond_t signal_msg_erreur;
};

#endif /* SUPERVISEUR_H */

