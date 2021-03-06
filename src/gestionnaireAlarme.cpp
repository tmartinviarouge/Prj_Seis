#include "../defs/gestionnaireAlarme.h"
#include "../defs/MPU6050.h"

gestionnaireAlarme::gestionnaireAlarme() {

}

gestionnaireAlarme::~gestionnaireAlarme() {
}

void gestionnaireAlarme::arreterAlarme() {
    alarme = AUCUNE;
}

void gestionnaireAlarme::activerAlarme(ALARME _alarme) {
    alarme = _alarme;
    alarmeActive = true;
    pthread_cond_signal(&SignalAlarme);
}

void gestionnaireAlarme::alarmeTempAccel() {
    int temperature;
    Mpu6050 mpu;
    while (1) {
        temperature = mpu.MesurerTemp();
        if (temperature > 30) {
            alarmeActive = true;
            pthread_cond_signal(&SignalAlarme);
        }
    }
}

void gestionnaireAlarme::signalerApproche(int distance) {
    if (distance <= DIST_MIN) {
        dureeBeepApprochBas = 0;//en dessous de 15 cm beep en continu
    } else if (distance >= DIST_APPROCHE_HAUTE) {
        dureeBeepApprochBas = MAX_APPROCHE_BAS;// au dessus de 45 cm beep avec 1s d'intervalle
    } else {
        dureeBeepApprochBas = ((distance - DIST_MIN) / (DIST_APPROCHE_HAUTE - DIST_MIN)) * MAX_APPROCHE_BAS; // entre 15 cm et 45 c m beep de plus en plus rapidement 
    }
    alarmeActive = true;
    pthread_cond_signal(&SignalAlarme);
}

void gestionnaireAlarme::emettreAlarme() {
    alarme = AUCUNE;
    alarmeActive = false;

    while (1) {
        if (alarmeActive == false) {
            leBuzzer.arretBeep();
            pthread_mutex_lock(&semAlarme); //prise du sémaphore 
            pthread_cond_wait(&SignalAlarme, &semAlarme); //attendre SignalAlarme 
            pthread_mutex_unlock(&semAlarme); //libération du sémaphore 
            alarmeActive = true;
        }

        switch (alarme) {
            case AUCUNE: alarmeActive = false;
                leBuzzer.arretBeep();

                break;

            case ACCELEROMETRE: leBuzzer.beeper();

                usleep(DUREE_BEEP_ACC); // en micro seconde 
                leBuzzer.arretBeep();
                usleep(TEMP_INTER_BEEP_ACC); // en micro seconde 
                break;

            case RASPBERRY: leBuzzer.beeper();
                usleep(DUREE_BEEP_RASPB); // en micro seconde 
                leBuzzer.arretBeep();
                usleep(TEMPS_INTER_BEEP_RASPB); // en micro seconde 

                break;

            case GENERALE: leBuzzer.beeper();

                break;

            case TEST: leBuzzer.beeper();
                usleep(DUREE_BEEP_TEST); // en seconde 
                leBuzzer.arretBeep();
                alarmeActive = false;
                break;

            case APPROCHE: leBuzzer.beeper();
                usleep(APPROCHE_HAUT); // en seconde 
                leBuzzer.arretBeep();
                usleep(dureeBeepApprochBas); // en seconde 

                break;
        }
    }
}

