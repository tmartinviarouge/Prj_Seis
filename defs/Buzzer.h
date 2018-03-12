#ifndef	BUZZER_H
#define	BUZZER_H

#include <pthread.h>
#include <sys/types.h>
#include <iostream>
#include <signal.h>
#include <wiringPi.h>
#include <unistd.h> 
#include <stdio.h>
#include <string.h>




class Buzzer 
{
public : 
		Buzzer(); 
		virtual ~Buzzer();		
		void beeper(); // met à l'état HAUT le gpio du buzzer 
		void arretBeep(); // met à l'état BAS le gpio du buzzer 

}; 

#endif
