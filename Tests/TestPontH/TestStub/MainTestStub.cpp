/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainTestStub.cpp
 * Author: zeyla
 *
 * Created on 20 mai 2018, 13:25
 */

#include <cstdlib>
#include "defs/testSeis.h"
#include "defs/testStub.h"
#include "../../defs/Superviseur.h"
#include<strind>
#include <iostream>

using namspace std;

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Superviseur *stub = new Superviseur();
    TestSeis * testseis = new testSeis();
    strind msg;
    cout<<"Rentrer la commande : "<<endl;
    cin>>msg;
    testseis->setCMD(msg);
    //testseis->envoie();
    
    return 0;
}

