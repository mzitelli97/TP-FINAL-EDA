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
    
    max.x = max.x - TILES_WIDTH/2;
    min.y = min.y + TILES_HEIGHT/4.5;
    
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}

void GraphicPlayer::zoom(CardLocation location)
{
    zoomed = true;
    double tile_height = totalHeight/6.0, tile_width = totalWidth/6.0;   
    if (tile_height < tile_width) tile_width = tile_height;
    else tile_height = tile_width;
    double yDiff = (totalHeight-FLOOR_RAWS*tile_height)/(FLOOR_RAWS+1);
    double xDiff = (totalWidth-FLOOR_COLUMNS*tile_width)/(FLOOR_COLUMNS+1);
     if (xDiff < yDiff) yDiff = xDiff;
    else xDiff = yDiff;
    min.y =  yDiff * ((float)location.row+1) + tile_height * (float)location.row;
    min.x =  xDiff * ((float)location.column+1) + tile_width * (float)location.column;
    max.y = min.y + tile_height;
    max.x = min.x + tile_width;
    
    max.x = max.x - tile_height/2;
    min.y = min.y + tile_width/4.5;
    
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

