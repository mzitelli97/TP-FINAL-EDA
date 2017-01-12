/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicGDie.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 02:27
 */

#include "GraphicGDie.h"

GraphicGDie::GraphicGDie() {
}

GraphicGDie::GraphicGDie(ALLEGRO_BITMAP* image)
{
    this->image = image;
    initialized=0;
}

GraphicGDie::GraphicGDie(const GraphicGDie& orig) {
}

GraphicGDie::~GraphicGDie() {
}

ItemInfo GraphicGDie::IAm()
{
    return {NO_ITEM_CLICK, nullptr};
}
void GraphicGDie::setInitialized(bool state)
{
    this->initialized=state;
}
void GraphicGDie::draw()
{
    if(initialized)
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),min.x,min.y,width,height,0);
}
void GraphicGDie::setPosition(CardLocation location)
{
    /*Convert logic location to graphic location*/
    logic2GraphicCardLocation(location);
    
    min.x = min.x + width/3;
    max.x = max.x - width/3;
    min.y = min.y + height/3;
    max.y = max.y - height/3;
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}

void GraphicGDie::setNumber(ALLEGRO_BITMAP* die_num)
{
    this->image = die_num;
}

