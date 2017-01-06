/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Controller.h
 * Author: user
 *
 * Created on 6 de enero de 2017, 10:59
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventData.h"


class Controller {
public:
    Controller();
    Controller(const Controller& orig);
    virtual Parser(EventData *Newevent)=0;
    virtual ~Controller();
private:

};

#endif /* CONTROLLER_H */

