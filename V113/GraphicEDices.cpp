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
#define DICE_WIDTH (totalWidth/30.0)
#define DICE_HEIGHT (totalHeight/15.0)

GraphicEDices::GraphicEDices(ALLEGRO_BITMAP * image)
{
    this->image = image;
    zoomed = false;
}

GraphicEDices::GraphicEDices(const GraphicEDices& orig) {
}

GraphicEDices::~GraphicEDices() {
}

ItemInfo GraphicEDices::IAm()
{
    ItemInfo retVal = {EXTRA_DICE_CLICK, nullptr};
    return retVal;
}

void GraphicEDices::setPosition(unsigned int number)
{
    width = DICE_WIDTH;
    height = DICE_HEIGHT;
    if(zoomed)
    {
        width += DICE_WIDTH/2;
        height += DICE_HEIGHT/2;
        min.x -= DICE_WIDTH;
        max.x -= DICE_WIDTH;
    }
    if(width < height) width = height;
    else height = width;
    
    min.x = FLOOR_MIN_X + TOTAL_FLOORS_WIDTH;
    min.y = FLOOR_MIN_Y + number*height + (number+1)*SPACE_BETWEEN_DICES;
    max.x = min.x + width;
    max.y = min.y + height;
}



