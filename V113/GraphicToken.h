/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicToken.h
 * Author: carlos
 *
 * Created on 30 de diciembre de 2016, 02:22
 */

#ifndef GRAPHICTOKEN_H
#define GRAPHICTOKEN_H

#include "GraphicItem.h"


class GraphicToken : public GraphicItem{
public:
    GraphicToken(ALLEGRO_BITMAP * image);
    GraphicToken(const GraphicToken& orig);
    virtual ~GraphicToken();
    ItemInfo IAm() override;
    void setPosition(CardLocation location, unsigned int number);

private:
    GraphicToken();
};

#endif /* GRAPHICTOKEN_H */

