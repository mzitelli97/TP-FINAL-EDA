/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MouseController.h
 * Author: user
 *
 * Created on 6 de enero de 2017, 11:08
 */

#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include "Controller.h"


class MouseController: public Controller {
public:
    MouseController();
    MouseController(const MouseController& orig);
    virtual Parser(EventData *Newevent);
    virtual ~MouseController();
private:

};

#endif /* MOUSECONTROLLER_H */

