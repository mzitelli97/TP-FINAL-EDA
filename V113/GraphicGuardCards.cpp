/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicGuardCards.cpp
 * Author: carlos
 * 
 * Created on 30 de diciembre de 2016, 17:22
 */

#include "GraphicGuardCards.h"

#define CARD_WIDTH (totalWidth/11.0)
#define CARD_HEIGHT (totalHeight/7.0)
#define SEPARATION (FLOOR_HEIGHT-2*CARD_WIDTH)

GraphicGuardCards::GraphicGuardCards(ALLEGRO_BITMAP * image, unsigned int floor)
{
    this->image = image;
    this->floor = floor;
    topOfNonVisibleDeckShown=false;
}

GraphicGuardCards::GraphicGuardCards(const GraphicGuardCards& orig) {
}

GraphicGuardCards::~GraphicGuardCards() {
}

ItemInfo GraphicGuardCards::IAm()
{
    ItemInfo retVal;
    retVal.type = GUARD_CARDS_CLICK;
    retVal.info = &floor;
    return retVal;
}

void GraphicGuardCards::push_top_card(ALLEGRO_BITMAP* card)
{
    cards.push_front(card);
}

void GraphicGuardCards::clearShownCards()
{
    cards.clear();
}
void GraphicGuardCards::setTopOfNonVisibleDeck(bool visible, ALLEGRO_BITMAP *target)
{
    topOfNonVisibleDeckShown=visible;
    topOfNonVisibleDeckTarget=target;
}

void GraphicGuardCards::draw()
{
    min.x = floor * FLOOR_WIDTH + (floor+1) * SPACE_BETWEEN_FLOORS + CARD_WIDTH + SEPARATION;
    max.x = min.x + CARD_WIDTH;
    min.y = FLOOR_MIN_Y + FLOOR_HEIGHT;
    max.y = min.y + CARD_HEIGHT;
    width = max.x - min.x;
    height = max.y - min.y;
    if(cards.front() != nullptr)
    {
        al_draw_scaled_bitmap(cards.front(),0,0,al_get_bitmap_width(cards.front()),al_get_bitmap_height(cards.front()),
                min.x, min.y, width, height, 0);
    }
    if(image != nullptr)
        al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image),al_get_bitmap_width(image),
                min.x - SEPARATION - CARD_WIDTH, min.y, width, height, 0);
    if(topOfNonVisibleDeckShown && topOfNonVisibleDeckTarget !=NULL)
        al_draw_scaled_bitmap(topOfNonVisibleDeckTarget,0,0,al_get_bitmap_width(topOfNonVisibleDeckTarget),al_get_bitmap_width(topOfNonVisibleDeckTarget),
                min.x - (SEPARATION + CARD_WIDTH) / 2.0, min.y + CARD_HEIGHT / 2.0, width, height, 0);
}
