#include <wiringPi.h>
#include <iostream>
#include <string>

#define NPIED	23
#define PPIED	24

using namespace std;

int main (void){
	
	wiringPiSetup();
	string reponse;
	pinMode (NPIED, OUTPUT);
	pinMode (PPIED, OUTPUT);
	cout << "Veuiller entrer un choix (E = entrer pied, S = sortir pied, A = Arret, Q = Quitter)" <<endl;
	cin >> reponse;
cout<<"reponse = "<<reponse<<endl;
	while (reponse != "Q")
	{
		if (reponse == "A")
		{
cout<<"arret demandé "<<endl;
			digitalWrite(NPIED,LOW);
			digitalWrite(PPIED,LOW);
		}	
		else if (reponse == "E")
		{
cout<<"rentrer  demandé "<<endl;
			digitalWrite(NPIED, HIGH);
			digitalWrite(PPIED, LOW);
		}
		else if (reponse == "S")
		{
cout<<"sortie demandé "<<endl;
			digitalWrite(PPIED, HIGH);
			digitalWrite(NPIED, LOW);
		}
		else
		{
			while((reponse != "A") && (reponse!="S") && (reponse!="E") && (reponse!="Q"))
			{
				cout<<"Veuillez entrer un choix valide (A,S,E ou Q...)"<<endl;
				cin >> reponse;
			}
		}
        	cout<<"Veuillez entrer un choix valide (A,S,E ou Q...)"<<endl;
		cin >>reponse;
		cout<<"reponse = "<<reponse;
	}
}		
