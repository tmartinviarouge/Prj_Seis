/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testSeis.cpp
 * Author: zeyla
 * 
 * Created on 20 mai 2018, 11:59
 */

//#include "testSeis.h"
#include "defs/testSeis.h"

testSeis::testSeis() {
    this->message="";
}

testSeis::testSeis(const testSeis& orig) {
}

testSeis::~testSeis() {
    
}

testSeis::envoie() {
    return this->message;
}

testSeis::setCMD(string cmd){
    this->message = cmd;
}
