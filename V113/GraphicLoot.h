/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicLoot.h
 * Author: javier
 *
 * Created on December 30, 2016, 3:52 PM
 */

#ifndef GRAPHICLOOT_H
#define GRAPHICLOOT_H
#include "GraphicItem.h"


class GraphicLoot: public GraphicItem {
public:
    //GraphicLoot();
    GraphicLoot(ActionOrigin owner, ALLEGRO_BITMAP * image);
    
    GraphicLoot(ALLEGRO_BITMAP * backImage);
    GraphicLoot(const GraphicLoot& orig);
    ActionOrigin GetOwner();
    void setOwner(ActionOrigin owner);
    virtual clickItem IAm();
    virtual void draw();
    virtual ~GraphicLoot();
private:
    void setPosition(ActionOrigin owner);
    bool isVisible;
    ActionOrigin owner;
};

#endif /* GRAPHICLOOT_H */

