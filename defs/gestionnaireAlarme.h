#ifndef GESTIONNAIREALARME_H
#define GESTIONNAIREALARME_H


#include <iostream>
#include "../defs/Buzzer.h"

#define	DUREE_BEEP_ACC			500000	
#define	TEMP_INTER_BEEP_ACC		200000
#define	DUREE_BEEP_RASPB			100000
#define	TEMPS_INTER_BEEP_RASPB	200000
#define	DUREE_BEEP_TEST			5000000




class  gestionnaireAlarme
{
	public :

		enum ALARME {
							AUCUNE,
							ACCELEROMETRE,
							RASPBERRY,
							GENERALE,
							TEST,
		};
	
		gestionnaireAlarme();
		virtual~gestionnaireAlarme();
		void arreterAlarme();
		void activerAlarme(ALARME _alarme);
		void emettreAlarme();
		void alarmeTempAccel();
		void testerBuzzer();
		bool alarmeActive; 
		pthread_mutex_t semAlarme; 
		pthread_cond_t SignalAlarme; 

	private :  
			
		Buzzer leBuzzer; 
		ALARME alarme; 
			
};		

#endif
