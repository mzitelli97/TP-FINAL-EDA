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
#define RADIX (totalWidth/270.0)
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
    
    logic2GraphicCardLocation(front);
    double myWidth = FLOOR_WIDTH, myHeight = FLOOR_HEIGHT; 
    if(zoomed)
    {
        myWidth = totalWidth;
        myHeight = totalHeight;
    }
    double yDiff = (myHeight-FLOOR_RAWS*height)/(FLOOR_RAWS+1);
    double xDiff = (myWidth-FLOOR_COLUMNS*width)/(FLOOR_COLUMNS+1);
    if ((xDiff > yDiff && !zoomed) || (xDiff < yDiff && zoomed)) yDiff = xDiff;
    else xDiff = yDiff;
    if(front.row == rear.row) //it means the wall is vertical
    {
        width = xDiff;
        min.x = max.x;
    }
    else //it means the wall is horizontal
    {
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
    al_draw_filled_rounded_rectangle(min.x, min.y, max.x, max.y, RADIX, RADIX, BROWN);
}




