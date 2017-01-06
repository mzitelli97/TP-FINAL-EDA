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

class MouseED {
public:
    MouseED();
    MouseED(const MouseED& orig);
    unsigned int getX();
    unsigned int getY();
    virtual ~MouseED();
private:

};

#endif /* MOUSEED_H */

