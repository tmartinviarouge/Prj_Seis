/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   recepteurCmdShell.h
 * Author: snir2g1
 *
 * Created on 3 mai 2018, 16:30
 */

#ifndef RECEPTEURCMDSHELL_H
#define RECEPTEURCMDSHELL_H
#include "c_socket.3.3.h"

class recepteurCmdShell : public Recept {
public: 
    recepteurCmdShell();
    recepteurCmdShell(const recepteurCmdShell& orig);
    virtual ~recepteurCmdShell();
private:

};

#endif /* RECEPTEURCMDSHELL_H */

