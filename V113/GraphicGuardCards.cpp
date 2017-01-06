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

#define CARD_WIDTH (totalWidth/10.0)
#define CARD_HEIGHT (totalHeight/6.0)
#define SEPARATION (totalWidth/50.0)

GraphicGuardCards::GraphicGuardCards(ALLEGRO_BITMAP * image, unsigned int floor)
{
    this->image = image;
    this->floor = floor;
}

GraphicGuardCards::GraphicGuardCards(const GraphicGuardCards& orig) {
}

GraphicGuardCards::~GraphicGuardCards() {
}

clickItem GraphicGuardCards::IAm()
{
    return GUARD_CARDS;
}

void GraphicGuardCards::push_top_card(ALLEGRO_BITMAP* card)
{
    cards.push_front(card);
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
}
