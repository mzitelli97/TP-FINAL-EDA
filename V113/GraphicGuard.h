/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicGuard.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 02:25
 */

#ifndef GRAPHICGUARD_H
#define GRAPHICGUARD_H

#include "GraphicItem.h"


class GraphicGuard : public GraphicItem{
public:
    GraphicGuard();
    GraphicGuard(ALLEGRO_BITMAP * image);
    GraphicGuard(const GraphicGuard& orig);
    virtual ~GraphicGuard();
    ItemInfo IAm() override;
    virtual void draw();
    void setInitialized(bool setInitialized);
    void setPosition(CardLocation location);
private:
    bool initialized;
};

#endif /* GRAPHICGUARD_H */

