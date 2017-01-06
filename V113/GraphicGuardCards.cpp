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

GraphicGuardCards::GraphicGuardCards(ALLEGRO_BITMAP * image)
{
    this->image = image;
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



