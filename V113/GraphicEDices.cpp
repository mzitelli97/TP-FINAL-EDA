/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicEDices.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 17:02
 */

#include "GraphicEDices.h"
#include "BurgleBrosView.h"

#define SPACE_BETWEEN_DICES (FLOOR_HEIGHT/35.0)

GraphicEDices::GraphicEDices(ALLEGRO_BITMAP * image)
{
    this->image = image;
    width = 50;
    height = 50;
}

GraphicEDices::GraphicEDices(const GraphicEDices& orig) {
}

GraphicEDices::~GraphicEDices() {
}

clickItem GraphicEDices::IAm()
{
    return EXTRA_DICE;
}

void GraphicEDices::setPosition(unsigned int number)
{
    min.x = FLOOR_MIN_X + TOTAL_FLOORS_WIDTH;
    min.y = FLOOR_MIN_Y + number*height + (number+1)*SPACE_BETWEEN_DICES;
    max.x = min.x + width;
    max.y = min.y + height;
}



