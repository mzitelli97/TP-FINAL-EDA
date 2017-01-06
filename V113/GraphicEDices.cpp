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


#define FLOOR_WIDTH (totalWidth/4.5)
#define FLOOR_HEIGHT (totalHeight/2.25)
#define SPACE_BETWEEN_FLOORS (totalWidth/20.0)
#define TOTAL_FLOORS_WIDTH (3.0*FLOOR_WIDTH + 2.0*SPACE_BETWEEN_FLOORS)         //no configurable
#define FLOOR_MIN_X ((totalWidth/2.0) - (TOTAL_FLOORS_WIDTH / 2.0))               //no configurable
#define FLOOR_MIN_Y (totalHeight/10.0)
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
void GraphicEDices::draw()
{
    if(image != nullptr)
        al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 
            min.x, min.y, width, height, 0);
}



