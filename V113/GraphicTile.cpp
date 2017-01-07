/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicTile.cpp
 * Author: carlos
 * 
 * Created on 29 de diciembre de 2016, 20:46
 */

#include "GraphicTile.h"
#include "View.h"

GraphicTile::GraphicTile(ALLEGRO_BITMAP * front,ALLEGRO_BITMAP * back,CardLocation location,unsigned int width,unsigned int height)
{
    this->image = front;
    this->back = back;
    this->location=location;
    Visible = false;
    setScreenDimentions(width, height);
    setPosition(location);
}
bool GraphicTile::isVisible()
{
    return Visible;
}
void GraphicTile::setVisible(ALLEGRO_BITMAP * safeNumber)
{
    this->safeNumber=safeNumber;
    Visible=true;
}
void GraphicTile::setPosition(CardLocation location)
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
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}
void GraphicTile::draw()
{
    if(Visible)
    {
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),min.x,min.y,width,height,0);
        al_draw_scaled_bitmap(safeNumber,0,0,al_get_bitmap_width(safeNumber),al_get_bitmap_height(safeNumber),min.x,min.y,width,height,0);
    }
    else
        al_draw_scaled_bitmap(back,0,0,al_get_bitmap_width(back),al_get_bitmap_height(back),min.x,min.y,width,height,0);
}
CardLocation GraphicTile::getLocation()
{
    return location;
}
GraphicTile::~GraphicTile() 
{
}

ItemInfo GraphicTile::IAm()
{
    ItemInfo retVal;
    retVal.type = TILE;
    retVal.info = &location;
    return retVal;
}

