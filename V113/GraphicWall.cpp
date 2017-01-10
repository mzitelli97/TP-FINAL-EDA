/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicWall.cpp
 * Author: ubuntu
 * 
 * Created on January 9, 2017, 9:03 PM
 */

#include "GraphicWall.h"

#define BROWN al_map_rgb(166,94,46)

GraphicWall::GraphicWall()
{
    zoomed = false;
}

GraphicWall::GraphicWall(const GraphicWall& orig) {
}

GraphicWall::~GraphicWall() {
}

ItemInfo GraphicWall::IAm()
{
    return {NO_ITEM, nullptr};
}

void GraphicWall::setLocation(CardLocation front, CardLocation rear)
{
    double tile_height = TILES_HEIGHT, tile_width = TILES_WIDTH;   
    if (tile_height < tile_width) tile_width = tile_height;
    else tile_height = tile_width;
    double yDiff = (FLOOR_HEIGHT-FLOOR_RAWS*tile_height)/(FLOOR_RAWS+1);
    double xDiff = (FLOOR_WIDTH-FLOOR_COLUMNS*tile_width)/(FLOOR_COLUMNS+1);
     if (xDiff > yDiff) yDiff = xDiff;
    else xDiff = yDiff;
    min.y = FLOOR_MIN_Y + yDiff * ((float)front.row+1) + tile_height * (float)front.row;
    min.x = FLOOR_MIN_X + FLOOR_WIDTH * front.floor + SPACE_BETWEEN_FLOORS * front.floor + xDiff * ((float)front.column+1) + tile_width * (float)front.column;
    max.y = min.y + tile_height;
    max.x = min.x + tile_width;
    
    if(front.column == rear.column) //it means the wall is vertical
    {
        width = xDiff;
        height = tile_height;
        min.x = max.x;
    }
    else //it means the wall is horizontal
    {
        width = tile_width;
        height = yDiff;
        min.y = max.y;
    }
    
    max.x = min.x + width;
    max.y = min.y + height;
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
}

void GraphicWall::draw()
{
    al_draw_filled_rounded_rectangle(min.x, min.y, max.x, max.y, 5.0, 5.0, BROWN);
}




