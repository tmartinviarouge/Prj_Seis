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
	int val;
	cout<<"Veuillez entrer le numéro de sortie désiré (0, 1, 2 ou 3) : " << endl;
	cin >> entree;
	monCan.init();
	while(1){
		val = monCan.lireEntree(entree);
		cout<<"valeur lue sur l'entree "<<entree<<" = "<<"( 0x"<<hex<<setfill('0')<<setw(4)<<val<<" )"<<dec<<val<< endl;
	};
	return 0; 
}
