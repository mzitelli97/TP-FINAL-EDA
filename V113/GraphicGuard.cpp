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

GraphicGuard::GraphicGuard() {
}

GraphicGuard::GraphicGuard(ALLEGRO_BITMAP* image)
{
    this->image = image;
}

GraphicGuard::GraphicGuard(const GraphicGuard& orig) {
}

GraphicGuard::~GraphicGuard() {
}

clickItem GraphicGuard::IAm()
{
    return NO_ITEM;
}

void GraphicGuard::setPosition(CardLocation location)
{
    /*Convert logic location to graphic location*/
    double tile_height = TILES_HEIGHT, tile_width = TILES_WIDTH;   
    if (tile_height < tile_width) tile_width = tile_height;
    else tile_height = tile_width;
    double yDiff = (FLOOR_HEIGHT-FLOOR_RAWS*tile_height)/(FLOOR_RAWS+1);
    double xDiff = (FLOOR_WIDTH-FLOOR_COLUMNS*tile_width)/(FLOOR_COLUMNS+1);
     if (xDiff > yDiff) yDiff = xDiff;
    else xDiff = yDiff;
    min.y = FLOOR_MIN_Y + yDiff * ((float)location.row+1) + tile_height * (float)location.row;
    min.x = FLOOR_MIN_X + FLOOR_WIDTH * location.floor + SPACE_BETWEEN_FLOORS * location.floor + xDiff * ((float)location.column+1) + tile_width * (float)location.column;
    max.y = min.y + tile_height;
    max.x = min.x + tile_width;
    
    min.x = min.x + TILES_WIDTH/2;
    min.y = min.y + TILES_HEIGHT/2;
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}