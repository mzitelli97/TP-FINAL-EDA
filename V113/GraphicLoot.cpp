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



GraphicLoot::GraphicLoot(ActionOrigin owner, ALLEGRO_BITMAP * image) 
{
    this->image = image;
    this->owner = owner;
    setPosition(owner);
    isVisible=true;
}
GraphicLoot::GraphicLoot(ALLEGRO_BITMAP * backImage)
{
    isVisible=false;
    image = backImage;
}
clickItem GraphicLoot::IAm()
{
    return LOOT_CARDS;
}

void GraphicLoot::setPosition(ActionOrigin owner)
{
    

}
ActionOrigin GraphicLoot::GetOwner()
{
    return owner;
}
void GraphicLoot::setOwner(ActionOrigin owner)
{
    this->owner=owner;
    setPosition(owner);
}
void GraphicLoot::draw()
{
    if(owner == THIS_PLAYER_ACTION)
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
                CARD_WIDTH*2,totalHeight-CARD_HEIGHT-20,CARD_WIDTH,CARD_HEIGHT,0);
    else if(owner == OTHER_PLAYER_ACTION)
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),
                500,1100,150,150,0);
    else
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_height(image),350,1100,150,150,0);
}

GraphicLoot::~GraphicLoot() {
}

