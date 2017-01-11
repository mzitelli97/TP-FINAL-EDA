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



GraphicLoot::GraphicLoot(ActionOrigin owner, ALLEGRO_BITMAP * image) 
{
    this->image = image;
    this->owner = owner;
    isVisible=true;
    zoomed = false;
}
GraphicLoot::GraphicLoot(ALLEGRO_BITMAP * backImage)
{
    isVisible=false;
    image = backImage;
    this->owner = NON_PLAYER;
    zoomed = false;
}
ItemInfo GraphicLoot::IAm()
{
    ItemInfo retVal;
    retVal.type = LOOT_CARDS_CLICK;
    retVal.info = &owner;
    return retVal;
}

void GraphicLoot::setPosition()
{
    if(owner == THIS_PLAYER_ACTION)
            min.x = 4 * SPACE_X + CARD_WIDTH;
    else if (owner == OTHER_PLAYER_ACTION)
            min.x = totalWidth - SPACE_X * 4 - CARD_WIDTH * 2;
    else min.x = 4 * SPACE_X + 3 * CARD_WIDTH;
    min.y = totalHeight - SPACE_Y - CARD_HEIGHT;
    max.x = min.x + CARD_WIDTH;
    max.y = min.y + CARD_HEIGHT;

}
ActionOrigin GraphicLoot::GetOwner()
{
    return owner;
}
void GraphicLoot::setOwner(ActionOrigin owner)
{
    this->owner=owner;
    setPosition();
}
void GraphicLoot::draw()
{
    setPosition();
    al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
        min.x,min.y,CARD_WIDTH,CARD_HEIGHT,0);
}

GraphicLoot::~GraphicLoot() {
}

