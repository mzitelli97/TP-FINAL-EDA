/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicGDie.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 02:27
 */

#ifndef GRAPHICGDIE_H
#define GRAPHICGDIE_H

#include "GraphicItem.h"


class GraphicGDie : public GraphicItem{
public:
    GraphicGDie();
    GraphicGDie(ALLEGRO_BITMAP * image);
    GraphicGDie(const GraphicGDie& orig);
    virtual ~GraphicGDie();
    clickItem IAm() override;
    void setPosition(CardLocation location);
    void setNumber(ALLEGRO_BITMAP * die_num);
private:

};

#endif /* GRAPHICGDIE_H */

