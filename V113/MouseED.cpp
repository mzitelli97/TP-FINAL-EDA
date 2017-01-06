/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MouseED.cpp
 * Author: javier
 * 
 * Created on January 5, 2017, 9:26 PM
 */

#include "MouseED.h"

MouseED:: MouseED(bool click,unsigned int x,unsigned int y) {
    this->click= click;
    this->x=x;
    this->y=y;
}

MouseED::MouseED(const MouseED& orig) {
}

MouseED::~MouseED() {
}

unsigned int MouseED::getX()
{
    return x;
}

unsigned int MouseED::getY()
{
    return y;
}

bool MouseED::isClicked()
{
    return click;
}


