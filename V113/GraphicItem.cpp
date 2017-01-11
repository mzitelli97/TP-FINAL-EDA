/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicItem.cpp
 * Author: carlos
 * 
 * Created on 29 de diciembre de 2016, 18:37
 */

#include "GraphicItem.h"

GraphicItem::GraphicItem() {
}

GraphicItem::GraphicItem(Point min, Point max)
{
    this->min = min;
    this->max = max;
    center.x = (min.x+max.x)/2.0;
    center.y = (min.y+max.y)/2.0;
    width = max.x-min.x;
    height = max.y-min.y;
}
GraphicItem::GraphicItem(Point center, double width, double height)
{
    this->width=width;
    this->height=height;
    this->center =center;
    max.x=center.x + (width/2.0);
    min.x=center.x - (width/2.0);
    max.y=center.y + (height/2.0);
    min.y=center.y - (height/2.0);
}
bool GraphicItem::isPointIn(Point point)
{
    bool retVal=false;
    if(point.x<max.x && point.x >min.x && point.y <max.y && point.y > min.y)
        retVal=true;
    return retVal;
}
void GraphicItem::setScreenDimentions(unsigned int totalWidth, unsigned int totalHeight)
{
    this->totalWidth=totalWidth;
    this->totalHeight=totalHeight;
}

void GraphicItem::draw()
{
    if(image != nullptr)
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),min.x,min.y,width,height,0);
}

bool GraphicItem::isZoomed()
{
    return zoomed;
}

void GraphicItem::toggleZoom()
{
    zoomed ^= true;
}

void GraphicItem::logic2GraphicCardLocation(CardLocation location)
{
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
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}


GraphicItem::GraphicItem(const GraphicItem& orig) {
}

GraphicItem::~GraphicItem() {
}



