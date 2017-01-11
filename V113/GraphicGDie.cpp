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
    zoomed = false;
}

GraphicGDie::GraphicGDie(const GraphicGDie& orig) {
}

GraphicGDie::~GraphicGDie() {
}

ItemInfo GraphicGDie::IAm()
{
    return {NO_ITEM, nullptr};
}

void GraphicGDie::setPosition(CardLocation location)
{
    /*Convert logic location to graphic location*/
    double myWidth = FLOOR_WIDTH, myHeight = FLOOR_HEIGHT;
    double tile_height = TILES_HEIGHT, tile_width = TILES_WIDTH;   
    if(zoomed)
    {
        myWidth = totalWidth;
        myHeight = totalHeight;
        tile_height = myHeight/4.2;
        tile_width = myWidth/4.2;
    }
    if (tile_height < tile_width) tile_width = tile_height;
    else tile_height = tile_width;
    double yDiff = (myHeight-FLOOR_RAWS*tile_height)/(FLOOR_RAWS+1);
    double xDiff = (myWidth-FLOOR_COLUMNS*tile_width)/(FLOOR_COLUMNS+1);
    if ((xDiff > yDiff && !zoomed) || (xDiff < yDiff && zoomed)) yDiff = xDiff;
    else xDiff = yDiff;
    min.y = yDiff * ((float)location.row+1) + tile_height * (float)location.row;
    min.x = xDiff * ((float)location.column+1) + tile_width * (float)location.column;
    if(!zoomed)
    {
        min.y += FLOOR_MIN_Y;
        min.x += FLOOR_MIN_X + FLOOR_WIDTH * location.floor + SPACE_BETWEEN_FLOORS * location.floor;
    }
    max.y = min.y + tile_height;
    max.x = min.x + tile_width;
    
    min.x = min.x + tile_width/3;
    max.x = max.x - tile_width/3;
    min.y = min.y + tile_height/3;
    max.y = max.y - tile_height/3;
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}

void GraphicGDie::setNumber(ALLEGRO_BITMAP* die_num)
{
    this->image = die_num;
}

