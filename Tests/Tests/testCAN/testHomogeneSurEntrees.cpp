#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iomanip>
#include "../../defs/ADS1115.h"

using namespace std;

int main()
{
	ADS1115 monCan;
	int entree;
	int ref;
	int val1;
	int val2;
	int val3;
	cout<<"Veuillez entrer le numéro de sortie désiré (0, 1, 2 ou 3) : " << endl;
	cin >> entree;
	monCan.init();
	while(1){
		ref = monCan.lireEntree(0);
		val1 = monCan.lireEntree(1);
		val2 = monCan.lireEntree(2);
		val3 = monCan.lireEntree(3);
		cout<<"valeur lue sur l'entree  0:"<<"( 0x"<<hex<<setfill('0')<<setw(4)<<ref<<" )"<<dec<<ref;
		cout<<"  |    sur l'entree  1:"<<"( 0x"<<hex<<setfill('0')<<setw(4)<<val1<<" )"<<dec<<val1;
		cout<<" |    sur l'entree  2:"<<"( 0x"<<hex<<setfill('0')<<setw(4)<<val2<<" )"<<dec<<val2;
		cout<<" |     sur l'entree  3:"<<"( 0x"<<hex<<setfill('0')<<setw(4)<<val3<<" )"<<dec<<val3<< endl;
	};
	return 0; 
}
