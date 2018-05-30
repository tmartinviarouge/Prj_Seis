#include "../../defs/Buzzer.h"
#include "../../defs/gestionnaireAlarme.h"

using namespace std;

gestionnaireAlarme gestAlarm;

void *corpsThreadAlarme(void*);

int main( )
{
	pthread_t thread_Alarme;
	if (pthread_create (&thread_Alarme, NULL, corpsThreadAlarme, NULL) < 0)
	{
		cerr<<"ERR échec création 'thread_Alarme' " << endl; 
		return -1; 	
	}; 
	char car=' ';
	do{
			cout <<"taper 'q' pour sortir "<<endl; 
			cout <<"taper 'a' pour couper l'alarme"<<endl; 
			cout <<"taper '1' pour activer alarme accelerometre"<<endl; 
			cout <<"taper '2' pour activer alarme raspberry"<<endl; 
			cout <<"taper '3' pour activer alarme général"<<endl;
			cout <<"taper '4' pour activer alarme test"<<endl;
			cin>>car; 
			switch(car)
			{ 
				case 'a':gestAlarm.arreterAlarme(); break ; 
				case '1' :gestAlarm.activerAlarme(gestionnaireAlarme::ACCELEROMETRE); break; 
				case '2' :gestAlarm.activerAlarme(gestionnaireAlarme::RASPBERRY); break ; 
				case '3' :gestAlarm.activerAlarme(gestionnaireAlarme::GENERALE); break; 
				case '4' :gestAlarm.activerAlarme(gestionnaireAlarme::TEST); break; 
				default : break; 
			};
	}while(car!='q');
	return 0;
}


void *corpsThreadAlarme(void*) 
{
	gestAlarm.emettreAlarme();
	return 0;
}

