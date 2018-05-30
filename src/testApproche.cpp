/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testApproche.cpp
 * Author: snir2g2
 *
 * Created on 26 mars 2018, 13:15
 */

#include <cstdlib>
#include "../defs/Seis.h"
#include "../defs/Ultrason.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>



using namespace std;

Seis unSeis;

int main(int argc, char** argv) {

    unSeis.Approche();
    
    
    
    
    return 0;
}

