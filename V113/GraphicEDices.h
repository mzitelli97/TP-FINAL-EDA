/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicEDices.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 17:02
 */

#ifndef GRAPHICEDICES_H
#define GRAPHICEDICES_H

#include "GraphicItem.h"


class GraphicEDices : public GraphicItem{
public:
    GraphicEDices(ALLEGRO_BITMAP * image);
    GraphicEDices(const GraphicEDices& orig);
    virtual ~GraphicEDices();
    ItemInfo IAm() override;
    void setPosition(unsigned int number);
private:

};

#endif /* GRAPHICEDICES_H */

