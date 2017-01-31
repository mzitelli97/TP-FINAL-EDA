/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicLoot.cpp
 * Author: javier
 * 
 * Created on December 30, 2016, 3:52 PM
 */

#include "GraphicLoot.h"

#define CARD_WIDTH (totalWidth/9.0)
#define CARD_HEIGHT (totalHeight/5.4)
#define SPACE_X (totalWidth/40.0)
#define SPACE_Y (totalHeight/20.0)



GraphicLoot::GraphicLoot(PlayerId owner, ALLEGRO_BITMAP * image, bool isAGoldBar) 
{
    this->image = image;
    this->owner = owner;
    isVisible=true;
    isGoldBarOnFloor = isAGoldBar;
}
GraphicLoot::GraphicLoot(ALLEGRO_BITMAP * backImage)
{
    isVisible=false;
    image = backImage;
    this->owner = NON_PLAYER;
}
ItemInfo GraphicLoot::IAm()
{
    ItemInfo retVal;
    retVal.type = LOOT_CARDS_CLICK;
    retVal.info = &owner;
    return retVal;
}

void GraphicLoot::setPosition(unsigned int quantity)
{
    if(zoomed && owner != NON_PLAYER)
    {
        width = CARD_WIDTH * 2;
        height = CARD_HEIGHT * 2;
        min.x = (quantity + 1) * CARD_WIDTH/2.0 + quantity * width;
        min.y = CARD_HEIGHT / 2.0;
    }
    else
    {
        width = CARD_WIDTH;
        height = CARD_HEIGHT;
        if(owner == THIS_PLAYER)
            min.x = 4 * SPACE_X + width + quantity * width/2;
        else if (owner == OTHER_PLAYER)
            min.x = totalWidth - SPACE_X * 4 - width * 2 - quantity * width/2;
        else min.x = 4 * SPACE_X + 3 * width + width/10.0;
        min.y = totalHeight - SPACE_Y - height;
    }
    
    max.x = min.x + width;
    max.y = min.y + height;

}

void GraphicLoot::setPosition(CardLocation location)
{
    logic2GraphicCardLocation(location);
}

PlayerId GraphicLoot::getOwner()
{
    return owner;
}
void GraphicLoot::setOwner(PlayerId owner)
{
    this->owner=owner;
}
GraphicLoot::~GraphicLoot() {
}

