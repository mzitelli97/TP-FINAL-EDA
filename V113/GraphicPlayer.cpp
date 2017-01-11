/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicPlayer.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 00:40
 */
#include <allegro5/bitmap.h>
#include "GraphicPlayer.h"

GraphicPlayer::GraphicPlayer() 
{
}

GraphicPlayer::GraphicPlayer(ALLEGRO_BITMAP * image, CardLocation location,unsigned int width, unsigned int height)
{
    this->image = image;
    setScreenDimentions(width,height);
    setLocation(location);
    zoomed = false;
}

GraphicPlayer::GraphicPlayer(const GraphicPlayer& orig) {
}
void GraphicPlayer::setLocation(CardLocation location)
{
    logic2GraphicCardLocation(location);
    
    max.x = max.x - width/2;
    min.y = min.y + height/4.5;
    
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}

GraphicPlayer::~GraphicPlayer() {
}

ItemInfo GraphicPlayer::IAm()
{
    return {NO_ITEM, nullptr};
}

