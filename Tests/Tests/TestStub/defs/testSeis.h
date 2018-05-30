/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testSeis.h
 * Author: zeyla
 *
 * Created on 20 mai 2018, 11:59
 */

#ifndef TESTSEIS_H
#define TESTSEIS_H
#include <string>
class testSeis {
public:
    testSeis();
    testSeis(const testSeis& orig);
    virtual ~testSeis();
    string envoie();
    string setCMD(string cmd);
private:
    string message;
};

#endif /* TESTSEIS_H */

