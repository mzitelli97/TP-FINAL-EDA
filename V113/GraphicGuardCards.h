/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicGuardCards.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 17:22
 */

#ifndef GRAPHICGUARDCARDS_H
#define GRAPHICGUARDCARDS_H

#include "GraphicItem.h"


class GraphicGuardCards : public GraphicItem{
public:
    GraphicGuardCards(ALLEGRO_BITMAP * image, unsigned int floor);
    GraphicGuardCards(const GraphicGuardCards& orig);
    virtual ~GraphicGuardCards();
    ItemInfo IAm() override;
    void push_top_card(ALLEGRO_BITMAP * card);
    virtual void draw() override;

private:
    list<ALLEGRO_BITMAP *> cards;
    unsigned int floor;

};

#endif /* GRAPHICGUARDCARDS_H */

