/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicGuard.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 02:25
 */

#include "GraphicGuard.h"
#define SEPARATION (totalWidth/135.0)

GraphicGuard::GraphicGuard() {
}

GraphicGuard::GraphicGuard(ALLEGRO_BITMAP* image)
{
    this->image = image;
    initialized=false;
    zoomed = false;
}

GraphicGuard::GraphicGuard(const GraphicGuard& orig) {
    initialized=false;
}

GraphicGuard::~GraphicGuard() {
    initialized=false;
}

ItemInfo GraphicGuard::IAm()
{
    return {NO_ITEM_CLICK, nullptr};
}

void GraphicGuard::setInitialized(bool setInitialized)
{
    this->initialized=setInitialized;
}

void GraphicGuard::setPosition(CardLocation location)
{
    /*Convert logic location to graphic location*/
    logic2GraphicCardLocation(location);
    
    min.x = min.x + width/2 - SEPARATION * (1 + (int)zoomed * 2.0);
    max.x = max.x - SEPARATION * (1 + (int)zoomed * 2.0);
    min.y = min.y + height/2;
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}
void GraphicGuard::draw()
{
    if(image != nullptr && initialized)
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),min.x,min.y,width,height,0);
}
