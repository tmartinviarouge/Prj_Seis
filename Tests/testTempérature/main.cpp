/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: snir2g2
 *
 * Created on 31 janvier 2018, 19:13
 */

#include <cstdlib>
#include <iostream>
#include "Temperature.h"

using namespace std;

int main() {
    int a,b;
    Temperature uneTemperature;
    
    uneTemperature.init();
    uneTemperature.MesureTempEnDixieme(&a,&b);
    cout << b <<"," << a << endl;
    
    
}
