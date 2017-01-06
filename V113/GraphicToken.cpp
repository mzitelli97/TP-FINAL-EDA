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

#define FLOOR_WIDTH (totalWidth/4.5)
#define FLOOR_HEIGHT (totalHeight/2.25)
#define SPACE_BETWEEN_FLOORS (totalWidth/20.0)
#define TOTAL_FLOORS_WIDTH (3.0*FLOOR_WIDTH + 2.0*SPACE_BETWEEN_FLOORS)         //no configurable
#define FLOOR_MIN_X ((totalWidth/2.0) - (TOTAL_FLOORS_WIDTH / 2.0))               //no configurable
#define FLOOR_MIN_Y (totalHeight/10.0)
#define TILES_HEIGHT (FLOOR_HEIGHT/(float)FLOOR_RAWS)
#define TILES_WIDTH  (FLOOR_WIDTH/(float)FLOOR_COLUMNS)

GraphicToken::GraphicToken() {
}

GraphicToken::GraphicToken(ALLEGRO_BITMAP* image)
{
    this->image = image;
}

GraphicToken::GraphicToken(const GraphicToken& orig) {
}

GraphicToken::~GraphicToken() {
}

clickItem GraphicToken::IAm() 
{
    return NO_ITEM;
}
void GraphicToken::draw()
{
    al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),min.x,min.y,width,height,0);
}
void GraphicToken::setPosition(CardLocation location)
{
    /*Convert logic location to graphic location*/
    double yDiff = (totalHeight/8.0);
    double xDiff = (totalWidth/30.0);
    min.y = yDiff + TILES_HEIGHT * (float)location.row;
    min.x = xDiff + TILES_WIDTH * (float)location.column + location.floor * (SPACE_BETWEEN_FLOORS + FLOOR_WIDTH);
    max.y = min.y + TILES_HEIGHT;
    max.x = min.x + TILES_WIDTH;
    
    min.x = min.x + TILES_WIDTH/1.5;
    max.y = max.y - TILES_HEIGHT/1.5;
    
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
    width = max.x-min.x;
    height = max.y- min.y;
}


