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
#include <list>

typedef struct
{
    unsigned int floor;
    bool shownDeck;
}auxInfoGuard;

class GraphicGuardCards : public GraphicItem{
public:
    GraphicGuardCards(ALLEGRO_BITMAP * image, unsigned int floor, bool isShownDeck);
    GraphicGuardCards(const GraphicGuardCards& orig);
    virtual ~GraphicGuardCards();
    ItemInfo IAm() override;
    void push_top_card(ALLEGRO_BITMAP * card);
    void clearShownCards();
    virtual void draw() override;
    void setTopOfNonVisibleDeck(bool visible, ALLEGRO_BITMAP *target);
private:
    std::list<ALLEGRO_BITMAP *> cards;
    void setPosition();
    void drawOnZoom();
    auxInfoGuard properties;
    bool topOfNonVisibleDeckShown;
    ALLEGRO_BITMAP * topOfNonVisibleDeckTarget;
};

#endif /* GRAPHICGUARDCARDS_H */

