/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MouseED.h
 * Author: javier
 *
 * Created on January 5, 2017, 9:26 PM
 */

#ifndef MOUSEED_H
#define MOUSEED_H

#include "EventData.h"

class MouseED : public EventData{
public:
    
    MouseED(bool click,unsigned int x,unsigned int y);
    MouseED(const MouseED& orig);
    unsigned int getX();
    unsigned int getY();
    bool isClicked();
    virtual ~MouseED();
    
private:
    unsigned int x;
    unsigned int y;
    bool click;
};

#endif /* MOUSEED_H */

