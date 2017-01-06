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
    GraphicGuardCards(ALLEGRO_BITMAP * image);
    GraphicGuardCards(const GraphicGuardCards& orig);
    virtual ~GraphicGuardCards();
    clickItem IAm() override;
    void push_top_card(ALLEGRO_BITMAP * card);
private:
    list<ALLEGRO_BITMAP *> cards;
    

};

#endif /* GRAPHICGUARDCARDS_H */

