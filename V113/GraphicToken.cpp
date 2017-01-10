/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicToken.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 02:22
 */

#include "GraphicToken.h"

GraphicToken::GraphicToken() {
}

GraphicToken::GraphicToken(ALLEGRO_BITMAP* image)
{
    this->image = image;
    zoomed = false;
}

GraphicToken::GraphicToken(const GraphicToken& orig) {
}

GraphicToken::~GraphicToken() {
}

ItemInfo GraphicToken::IAm() 
{
    return {NO_ITEM, nullptr};
}

void GraphicToken::setPosition(CardLocation location, unsigned int number)
{
    /*Convert logic location to graphic location*/
    double myWidth = FLOOR_WIDTH , myHeight = FLOOR_HEIGHT;
    double tile_height = TILES_HEIGHT, tile_width = TILES_WIDTH;
    if(zoomed)
    {
        myHeight = totalHeight;
        myWidth = totalWidth;
        tile_width = myWidth/5.0;
        tile_height = myHeight/5.0;
    }
    if (tile_height < tile_width) tile_width = tile_height;
    else tile_height = tile_width;
    double yDiff = (myHeight-FLOOR_RAWS*tile_height)/(FLOOR_RAWS+1);
    double xDiff = (myWidth-FLOOR_COLUMNS*tile_width)/(FLOOR_COLUMNS+1);
     if (xDiff > yDiff) yDiff = xDiff;
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
    
    min.x = min.x + tile_width/1.5 - 10.0 * (number%6);
    max.x = max.x - 10.0 * (number%6);
    max.y = max.y - tile_height/1.5;
    
    width = max.x-min.x;
    height = max.y- min.y;
    if(number>=6)
    {
        min.y = min.y + height;
        max.y = max.y + height;
    }
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
}

void GraphicToken::toggleZoom()
{
    zoomed ^= true;
}
