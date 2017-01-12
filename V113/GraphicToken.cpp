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
//#define SEPARATION (totalWidth/135.0)

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

ItemInfo GraphicToken::IAm() 
{
    return {NO_ITEM_CLICK, nullptr};
}

void GraphicToken::setPosition(CardLocation location, unsigned int number)
{
    /*Convert logic location to graphic location*/
    logic2GraphicCardLocation(location);
    
    min.x = min.x + width/1.4;
    min.y = min.y + height/7.5 * (number%6);
    max.y = max.y - height/1.4 + height/7.5 * (number%6);
    
    width = max.x-min.x;
    height = max.y- min.y;
    if(number>=6)
    {
        min.x = min.x - width;
        max.x = max.x - width;
    }
    center.x= (min.x+max.x)/2;
    center.y= (min.y+max.y)/2;
}
