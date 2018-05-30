/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testMesures.c
 * Author: snir2g2
 *
 * Created on 8 mars 2018, 19:04
 */

#include <iostream>
#include <cstdlib>
#include <wiringPiI2C.h>
#include "../defs/Seis.h"
#include <pthread.h>

using namespace std;

int main(int argc, char** argv) {
    
    Seis unSeis;
    unSeis.MesuresDemandees();
    cout <<  "Accelerometre"<< " "  <<endl;
	cout << " AX = "<< AX <<endl;  
	cout << " AY = "<< AY <<endl;  
	cout << " AZ = "<< AZ <<endl; 
    

    return (EXIT_SUCCESS);
    
}

